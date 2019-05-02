/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** 
 *  FIXME : describe the purpose of this file here
 */

#ifndef FEMDK_MICROGENERATOR_HXX 
#define FEMDK_MICROGENERATOR_HXX

#include <string>
#include <vigra/multi_shape.hxx>
#include <vigra/multi_array.hxx>
#include "microgen_params.hxx"
#include "microgen_types.hxx"
#include "microgen_algebra3.hxx"


namespace microgen {

class MicroGenerator {
  public:
    explicit MicroGenerator(vigra::Shape3 shape);
    MicroGenerator();

    /** Setup geneator from command line parameters and config file */
    int Setup(Params &params, const std::string& configFile);

    /** Write microstructure to file. 
     *
     *  The file format is deduced from file extension.
     */
    void Generate(void);
    void Write(const std::string& filename);
    void WriteVtk(const std::string& filename);
    void WriteSlice(const std::string& filenam);

  private:
    vigra::MultiArray<3, double> kernelImage;
    vigra::MultiArray<3, double> randTopoImage;
    vigra::MultiArray<3, double> outImage;
    double randomInterval[2];
    double myDeltas[3];
    double myOrigin[3];
    double myDimensions[3];
    vigra::Shape3 myShape;
    ConfigData myInputConfig;

    void GenerateRandomTopoImage(void);
    void GenerateKernelImage(void);
    void CalculateGaussianKernel(const Matrix3& Lambda);
    void CalculateIsotropicGaussianKernel(const double lambda);
    void CalculateUniformKernel(const double lambda[3]);
    void CalculateIsotropicUniformKernel(const double lambda);
    void Initialize(void);
    void ReadConfig(const std::string& inputFileName);
    void SetupFromConfig(const ConfigData &configData);
    void SetDeltas(void);
    /** Calculate physical position from cell index (i,j,k); */
    void CellIndex2Position(int i, int j, int k, Vector3 &x);
    void NodeIndex2Position(int i, int j, int k, Vector3 &x);
};

inline void
MicroGenerator::SetDeltas(void) {
  for (int i=0; i<3; i++) {
     myDeltas[i] = myDimensions[i]/myShape[i];
  }
}

inline void 
MicroGenerator::NodeIndex2Position(int i, int j, int k, Vector3 &x) {
  x[0] = myOrigin[0] + i * myDeltas[0];
  x[1] = myOrigin[1] + j * myDeltas[1];
  x[2] = myOrigin[2] + k * myDeltas[2];
}

inline void 
MicroGenerator::CellIndex2Position(int i, int j, int k, Vector3 &x) {
  x[0] = myOrigin[0] + i * myDeltas[0] + myDeltas[0]/2;
  x[1] = myOrigin[1] + j * myDeltas[1] + myDeltas[1]/2;
  x[2] = myOrigin[2] + k * myDeltas[2] + myDeltas[2]/2;
//  x[0] = (i - myShape[0]/2.0)*myDeltas[0] + myOrigin[0];
//  x[1] = (j - myShape[1]/2.0)*myDeltas[1] + myOrigin[1];
//  x[2] = (k - myShape[2]/2.0)*myDeltas[2] + myOrigin[2];
}

} /* namespace microgen */

#endif /* FEMDK_MICROGENERATOR_HXX */
