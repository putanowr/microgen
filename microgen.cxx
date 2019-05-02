/*
 * 
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
#include <stdlib.h> // for EXIT_SUCCESS
#include "microgen_options.h" 
#include "microgen_params.hxx"
#include "microgen_testing.hxx"
#include "microgen_parsing.hxx"
#include <iostream>

#include "femdk_common.hxx"
#include "femdk_params.hxx"

#include "MicroGenerator.hxx"
#include <vigra/multi_shape.hxx>

#define INVALID_SIZE 22

int main_body(int argc, char **argv, microgen::Params &options);

FEMDK_STANDARD_MAIN(microgen::Params, microgen, true);

/** The function where the main work is done after configuration
 * and command line parsing.
 */
int main_body(int argc, char **argv, microgen::Params &options) {
  MYLOGGER().info("Starting program microgen");
  int result = EXIT_SUCCESS;

  if (options.myHaveSelftest) {
    return microgen::selftesting_main();
  }

  std::string inputFile;

  if (argc > 0) {
    inputFile = argv[0];
  }

  microgen::MicroGenerator mg;

  result = mg.Setup(options, inputFile); 

  if (result != EXIT_SUCCESS) {
    return result;
  }

  std::string outfile = options.out_file;
  if (outfile.empty()) {
    outfile = "microgen_output.vtk";
  }

  mg.Generate();
  mg.Write(outfile);
  mg.WriteSlice(outfile);

  result = EXIT_SUCCESS;
  return result;
}
