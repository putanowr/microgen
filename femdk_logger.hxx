/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** \addtogroup core */
/*\@{*/
/** 
 *  This file provides logging facilities for FEMDK framework.
 */

#ifndef FEMDK_LOGGER_HXX 
#define FEMDK_LOGGER_HXX

#include <string>

#include "femdk_config.h"

#ifdef FEMDK_HAVE_LOG4CPP

#include <log4cpp/Category.hh>
#include <log4cpp/NDC.hh>

#define FEMDK_LOGFUN_PUSH ::femdk::logging::push_context(__FUNCTION__);
#define FEMDK_LOGFUN_POP ::femdk::logging::pop_context();
#define FEMDKLOGGER() ::femdk::logging::getFEMDKLogger()

namespace femdk {
class LoggerParams;

namespace logging {
  typedef log4cpp::Category Logger;

  /** @brief Setup logger for FEMDK framework.
   */
  void setup(const LoggerParams &params);
  
  /** @brief Configure given logger.
   */
  void configureLogger(Logger &logger, const LoggerParams &params);

  void shutdown(int status);
  inline void push_context(const std::string &message) {
    log4cpp::NDC::push(message);
  }
  const char * getLogFileName(); 
  inline std::string pop_context() { 
    return log4cpp::NDC::pop(); 
  }
  /** @brief Return root logger */
  log4cpp::Category& getLogger();

  /** @brief Return main logger for FEMDK framework */
  log4cpp::Category& getFEMDKLogger();

  /** @brief Return user logger of given name */
  log4cpp::Category& getLogger(const std::string &name);

  /** @brief Create a new logger */
  inline log4cpp::Category& createLogger(const std::string &name) {
    return log4cpp::Category::getInstance(name);
  }
  
}
} /* namespace femdk */
#else 

#include <iostream>
namespace femdk {
class LoggerParams;

namespace logging {
struct DummyLogger {
  void debug(const char *, ...) {;}
  void debug(std::string &) {;}
  void error(std::string &) {;}
  void error(const char *, ...) {;}
  
  void notice(std::string &) {;}
  void notice(const char *, ...) {;}
  void info(std::string &) {;}
  void info(const char *, ...) {;}
  void warn(std::string &) {;}
  void warn(const char *, ...) {;}
  void crit(std::string &) {;}
  void crit(const char *, ...) {;}

  void alert(std::string &) {;}
  void alert(const char *, ...) {;}
  void emer(std::string &) {;}
  void emer(const char *, ...) {;}
  void fatal(std::string &) {;}
  void fatal(const char *, ...) {;}
};

  typedef DummyLogger Logger;
  void setup(const LoggerParams &params);
  void configureLogger(Logger &logger, const LoggerParams &params);
  void shutdown(int status);
  DummyLogger& getLogger();
  DummyLogger& getLogger(const std::string &name) {return getLogger();}
  DummyLogger& createLogger(const std::string &name);
  void inline push_context(const std::string &message) {;}
  inline std::string  pop_context() { return std::string("");}
}
} /* namespace femdk */
#endif 

/*\@}*/

#endif /* FEMDK_LOGGER_HXX */
