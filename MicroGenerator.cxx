/*
 * Copyright (c) 2014 Roman Putanowicz 
 * 
 * This file is distributed on "Simplified BSD License" as approved by 
 * the OSI Board. For licensing terms see LICENSE.BSD file distributed 
 * with this file.
 */

/** 
 *  FIXME : describe the purpose of this file here
 */

#include "microgen_config.h"
#include "boost/format.hpp"
#include "boost/filesystem.hpp"
#include "vtkRectilinearGrid.h"
#include "vtkRectilinearGridWriter.h"
#include "vtkFloatArray.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"

#include "MicroGenerator.hxx"
#include "microgen_parsing.hxx"
#include "microgen_exceptions.hxx"
#include "femdk_common.hxx"
#include "femdk_ConfigData.hxx"
#include "vigra/multi_array.hxx"
#include "vigra/random.hxx"
#include <vigra/linear_algebra.hxx>
#include <vigra/multi_pointoperators.hxx>
#include <vigra/multi_fft.hxx>
#include "vigra/impex.hxx"
#include <iostream>

namespace microgen {

using boost::format;

namespace bf=boost::filesystem;

MicroGenerator::MicroGenerator() {
  Initialize();
}

MicroGenerator::MicroGenerator(vigra::Shape3 shape) : myShape(shape),
                                                 kernelImage(shape),
                                                 randTopoImage(shape)  {
  Initialize();
  std::string s= str(format("Generating microstructure  %d x %d x %d ") 
                    % shape[0] % shape[1] % shape[2] );
  MYLOGGER().debug(s);    
} 

#define INVALID_SIZE 22

void 
MicroGenerator::SetupFromConfig(const ConfigData &configData) {
  std::vector<int> v;  
  femdk::getVector<int>(v, configData, "micro-size", 3, 10); 
  std::copy(v.begin(), v.end(), myShape.begin());
  SetDeltas();
  std::string s= str(format("Read microstructure size %d x %d x %d ") 
                    % v[0] % v[1] % v[2] );
  MYLOGGER().debug(s);    
}

int
MicroGenerator::Setup(Params &params, const std::string& filename) {
  if (! filename.empty()) {
    ReadConfig(filename);
  }

  SetupFromConfig(myInputConfig);

  /* Overwrite microstructure size by command line parameters */
  if (params.myHaveMicroSize) {
    bool ok = parseCubeSize(params.micro_size, myShape);
    if (false == ok) {
      std::cerr << "Invalid value for options 'micro-size': " 
              << params.micro_size << "\n";
      return INVALID_SIZE;
    }
  }
  SetDeltas();

  kernelImage.reshape(myShape);
  randTopoImage.reshape(myShape);
  outImage.reshape(myShape);

  int i=kernelImage.shape(0);
  int j=kernelImage.shape(1);
  int k=kernelImage.shape(2);
  std::string s= str(format("Generating microstructure  %d x %d x %d ") 
                    % i % j % k );
  MYLOGGER().debug(s);    
  return EXIT_SUCCESS;
}


void
MicroGenerator::ReadConfig(const std::string& filename) {
  std::ifstream inputfile(filename.c_str());
  boost::property_tree::json_parser::read_json(inputfile, myInputConfig);
  inputfile.close();
}

void
MicroGenerator::Initialize() {
  MYLOGGER().debug("Initialize default micro generator");
  randomInterval[0] = 0.0;
  randomInterval[1] = 1.0;
  myDimensions[0] = myDimensions[1] = myDimensions[2] = 1.0;
      myOrigin[0] =     myOrigin[1] =     myOrigin[2] = 0.0;
       myShape[0] =      myShape[1] =      myShape[2] = 10;
  SetDeltas();
}

void 
MicroGenerator::GenerateRandomTopoImage(void) {
  vigra::RandomTT800 random1;
  vigra::UniformRandomFunctor<vigra::RandomTT800> f1(randomInterval[0],
             randomInterval[1], random1);
  typedef vigra::MultiArray<3,double>::iterator Iter;
  for (Iter i = randTopoImage.begin(); i != randTopoImage.end(); ++i) {
     *i = f1();
  }
}

void 
MicroGenerator::GenerateKernelImage(void) {
  bool found;
  const ConfigData &kernelConfig = femdk::getSubConfig(myInputConfig, 
                                   "kernel", found);
  if (false == found) {
    std::string msg("No \"kernel\" section in input file");
    throw Exception(msg);
  }
  std::string kernelType = femdk::getString(kernelConfig, "type", "isotropic-gaussian");
  if (kernelType == "isotropic-gaussian") {
    double lambda = femdk::getDouble(kernelConfig, "lambda", 1.e-4);
    CalculateIsotropicGaussianKernel(lambda);
  } else if (kernelType == "isotropic-uniform") {
    double lambda = femdk::getDouble(kernelConfig, "lambda", 1.e-4);
    CalculateIsotropicUniformKernel(lambda);
  } else {
    std::string msg= str(format("Unsupported kernel type: %s") % kernelType); 
    throw Exception(msg);
  }
}


void
MicroGenerator::CalculateUniformKernel(const double lambda[3]) {
   Vector3 x;
   long int center[3] = {myShape[0]/2, myShape[1]/2, myShape[2]/2};
   for (int i = 0; i < myShape[0]; i++) {
     x[0] = i - myShape[0]/2.0;
     for (int j = 0; j < myShape[1]; j++) {
        x[1] = j - myShape[1]/2.0;
       for (int k = 0; k < myShape[2]; k++) {
          x[2] = k - myShape[2]/2.0;
          int hi=1;
          for (int d=0; d<3; d++) {
            if (fabs(x[d]-center[d]) < lambda[d]*myShape[d]/2.0) {
              hi = hi * 1;
            } else {
              hi = 0;
            }
          }
          kernelImage(i,j,k) = 1.0;
       }
     }
   } 
}

void
MicroGenerator::CalculateGaussianKernel(const Matrix3 &Lambda) {
   const int n = 3;
   const double f1 = std::pow(2*M_PI, n/2.0);
   const double det = vigra::linalg::determinant(Lambda);
   const double factor = 1.0/(f1 * sqrt(det));
   std::string msg= str(format("factor: %f") % factor); 
   MYLOGGER().debug(msg);
   const Matrix3 LambdaInv = vigra::linalg::inverse(Lambda);
   Vector3 x;
   for (int i = 0; i < myShape[0]; i++) {
     x[0] = i - myShape[0]/2.0;
     for (int j = 0; j < myShape[1]; j++) {
        x[1] = j - myShape[1]/2.0;
       for (int k = 0; k < myShape[2]; k++) {
          x[2] = k - myShape[2]/2.0;
          //CellIndex2Position(i,j,k, x); 
          double xe = -VecMatVec3(x, LambdaInv, x)/2.0;
          kernelImage(i,j,k) =  factor*exp(xe);
       }
     }
   } 
}


void
MicroGenerator::CalculateIsotropicUniformKernel(const double lambda) {
  double Lambda[3] = {lambda, lambda, lambda};
  CalculateUniformKernel(Lambda);
}

void
MicroGenerator::CalculateIsotropicGaussianKernel(const double lambda) {
  vigra::Matrix<double> v(1, 3);
  v[0] = v[1] = v[2] = lambda; 
  v[0] = v[0] * myShape[0]/myDimensions[0];
  v[1] = v[1] * myShape[1]/myDimensions[1];
  v[2] = v[2] * myShape[2]/myDimensions[2];
  Matrix3 Lambda = diagonalMatrix(v);
  CalculateGaussianKernel(Lambda);
  std::string msg= str(format("Calculated Gausssiang kernel with lambda : %f") % lambda); 
  MYLOGGER().debug(msg);
}

void 
MicroGenerator::Generate(void) {
  MYLOGGER().debug("Generating microstructure");
  GenerateRandomTopoImage();
  GenerateKernelImage();

  double gamma = femdk::getDouble(myInputConfig, "gamma", 0.5);

  vigra::convolveFFT(randTopoImage, kernelImage, outImage);
  vigra::transformMultiArray(outImage, outImage, 
         vigra::Threshold<double, double>(0.0, gamma, 1.0, 0.0));

  std::string msg= str(format("Thresholding with value: %f") % gamma); 
  MYLOGGER().debug(msg);
}


void
MicroGenerator::WriteSlice(const std::string& filename) {
  vigra::ImageExportInfo myExportInfo("slice.png");
  vigra::exportImage(outImage.bind<0>(0), myExportInfo);
}


void
MicroGenerator::Write(const std::string& filename) {
  bf::path p(filename);
  std::string e = p.extension().string();
  if ("vtk" == e) {
    WriteVtk(filename);
  } else {
    WriteVtk(filename);
  } 
}
  
void
MicroGenerator::WriteVtk(const std::string& filename) {
  std::string s= str(format("Writing to file: %s") % filename); 
  MYLOGGER().debug(s);

  vigra::MultiArray<3, double> &myImage = outImage;

  int Nx, Ny, Nz;

  /* Caution -- here +1 is because image is cell oriented and we write
   * nodal based grid
   */
  Nx = myImage.shape(0)+1; // number of nodes in X direction
  Ny = myImage.shape(1)+1;
  Nz = myImage.shape(2)+1;

  vtkFloatArray *xCoords = vtkFloatArray::New();
  for (int i=0; i<Nx; i++) xCoords->InsertNextValue(i);
  vtkFloatArray *yCoords = vtkFloatArray::New();
  for (int i=0; i<Ny; i++) yCoords->InsertNextValue(i);
  vtkFloatArray *zCoords = vtkFloatArray::New();
  for (int i=0; i<Nz; i++) zCoords->InsertNextValue(i);

  vtkRectilinearGrid *rgrid = vtkRectilinearGrid::New();
  rgrid->SetDimensions(Nx,Ny,Nz);
  rgrid->SetXCoordinates(xCoords);
  rgrid->SetYCoordinates(yCoords);
  rgrid->SetZCoordinates(zCoords);

  vtkCellData *cellData = rgrid->GetCellData();

  std::string acname("phase");
  vtkDoubleArray *cd = vtkDoubleArray::New();
  cd->SetName(acname.c_str());
  cd->SetNumberOfValues(myImage.size());

  for (int i=0; i<myImage.size(); i++) {
     cd->SetValue(i, myImage[i]);
  }

  cellData->AddArray(cd);
  cellData->SetActiveScalars(acname.c_str());

  vtkRectilinearGridWriter *writer = vtkRectilinearGridWriter::New();
  writer->SetFileName(filename.c_str());
  writer->SetInputData(rgrid);
  writer->Write();

  writer->Delete();
  rgrid->Delete();
}

} /* namespace microgen */
