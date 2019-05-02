/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** \file femdk_common.hxx
 *  This file provides FEMDK configuration, initialization and shuddown
 *  services.
 */



#ifndef FEMDK_COMMON_HXX 
#define FEMDK_COMMON_HXX

#include <string>
#include <fstream>
#include "femdk_config.h"
#include "femdk_logger.hxx"

namespace femdk {

class LoggerParams;

/** Initialize FEMDK framework with logger settings. 
 *
 *  Use this form of initialization if your application 
 *  crates custom logger object and you want your logger
 *  to be the parrent for FEMDK logger.
 *  
 *  FEMDK logger will be created as a child of a logger
 *  specified in 'params.femdk_parent_logger'.
 *  If the logger with name given in 'params.femdk_parent_logger'
 *  do not exists raise an exception.
 *
 */
void Initialize(const LoggerParams &params);

/** Initialize FEMDK framework. 
 *
 *  The logger for FEMDK is created as an independent logger
 *  with parent being roog logger
 */
void Initialize();

void Finalize(int status);

/* Error and warning reporting */

void Warning(const std::string &function, const std::string &file, 
             int line, const std::string &message);
void Error(const std::string &function, const std::string &file, 
             int line, const std::string &message);
} /* namespace femdk */
#define FEMDK_WARNING(message) ::femdk::Warning(__FUNCTION__, __FILE__, __LINE__, message)

#define FEMDK_ERROR(message) ::femdk::Error(__FUNCTION__, __FILE__, __LINE__, message)

#define ROOT_LOGGER_SETUP()

/**Standard FEMDK main procedure. It uses AutoOpts generated code to 
 * parse command line arguments into an instance of ParamsType.
 * The name of AutoOpts structure for parsed optins is set to
 * {optionsName}Options.
 * Besides parsing command line options this routine initializes and 
 * finalizes FEMK framework by calling femdk::Initialize and femdk::Finalize,
 * respectively. User code should be placed in the function 
 *      int main_body(int argc, char **argv, ParamsType &params);
 */
#define FEMDK_STANDARD_MAIN(ParamsType, optionsName, customLogger) \
int main(int argc, char **argv) { \
  int result =  EXIT_SUCCESS; \
  { \
     int optct = optionProcess(&optionsName##Options, argc, argv); \
     argc -= optct; \
     argv += optct; \
  } \
  ParamsType params;\
  params.setUp();\
  ROOT_LOGGER_SETUP(); \
  if (true == customLogger) { \
    femdk::logging::Logger &logger =  \
         femdk::logging::createLogger(#optionsName); \
    femdk::Initialize(params);\
  } else { \
    femdk::Initialize(params); \
  } \
  if (true == params.dry_run) {\
    if (true == params.echo_params) { \
      params.echo(std::cout);\
    } \
    femdk::Finalize(result); \
    return result; \
  }\
  if (true == params.echo_params) { \
    params.echo(std::cout); \
  } \
  if ( ISSEL_OPT(SAVE_PARAMS) ) { \
    if (params.save_params != "") { \
      std::ofstream paramsout(params.save_params.c_str());\
      params.echo(paramsout); \
      paramsout.close(); \
    } \
  } \
  result = main_body(argc, argv, params);\
  femdk::Finalize(result);\
  femdk::logging::shutdown(result); \
  return result;\
}

/*@}*/
#endif /* FEMDK_COMMON_HXX */
