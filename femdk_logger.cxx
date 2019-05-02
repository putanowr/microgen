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

#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include "femdk_logger.hxx"
#include "femdk_params.hxx"
#include "femdk_common.hxx"
#include "femdk_except.hxx"
#include <assert.h>
#include <stdlib.h>


namespace femdk {

namespace logging {

static bool log_keep = false;
static int  logfile_id = -1;
static const size_t  logfilenamelen = 512;
static char logfilename[512+7]= {"/tmp/femdk.log.XXXXXX"};

static int log_level_to_priority(const std::string &loglevel);
static int create_logfile(const std::string &filename);

static int log_level_to_priority(const std::string &loglevel) {
//  static const char *levels[] = { "emerg", "crit", "alert", "err", "warning", "notice", "info", "debug", "notset" }
 static const char *levels[] = {
    "emerg",
    "fatal",
    "alert",
    "crit",
    "error",
    "warn",
    "notice",
    "info",
    "debug",
    "notset"};
 // static int priorities[] = {800, 700, 600, 500, 400, 300, 200, 100, 0, 0};
  static int priorities[] = {0, 0, 100, 200, 300, 400, 500, 600, 700, 800};
  for (size_t i = 0; i<sizeof(levels)/sizeof(char*); ++i) {
    if (loglevel == levels[i]) {
      return priorities[i];
    }
  }
  return priorities[0];
}

const char* getLogFileName() { return logfilename; }

#ifdef FEMDK_HAVE_LOG4CPP

static log4cpp::Category *femdkLogger = NULL;

log4cpp::Category& getFEMDKLogger() {
  return *femdkLogger;
} 

log4cpp::Category& getLogger() {
  return log4cpp::Category::getInstance("");
} 

log4cpp::Category& getLogger(const std::string &name) {
  log4cpp::Category *logger = log4cpp::Category::exists(name);
  if (logger != NULL) {
    return log4cpp::Category::getInstance(name);
  } else {
    std::string msg("Requesting unknown logger: ");
    msg+=name;
    throw FEMDKException(msg);
  }
}

void shutdown(int status) {
  log4cpp::Category::shutdown();
  if (logfile_id != -1) {
    close(logfile_id);
    if ( EXIT_SUCCESS == status && true != log_keep) {
      remove(logfilename);
    }
  }
}

void setup(const LoggerParams &params) {
  static bool called = false;
  if (false == called) {
    called = true;
    std::string femdkLoggerName = std::string(FEMDK_LOGGER_NAME);
    if (params.femdk_parent_logger != "") {
      if (NULL == log4cpp::Category::exists(params.femdk_parent_logger)) {
        std::stringstream ss;
        ss << "The parent logger '" << params.femdk_parent_logger 
           << "' does not exist";
        FEMDK_ERROR(ss.str());
      }
      /* Set parent logger for FEMDK logger */
      femdkLoggerName = params.femdk_parent_logger + "." + femdkLoggerName;
    }
	  log_keep = params.log_keep;

    /* Create logger for FEMDK framework */
    (void) log4cpp::Category::getInstance(femdkLoggerName);
    femdkLogger = log4cpp::Category::exists(femdkLoggerName);
    assert(femdkLogger != NULL);

    /* Configure the main logger */
    configureLogger(getLogger(params.femdk_parent_logger), params);

    getLogger(params.femdk_parent_logger).setPriority(
                              log_level_to_priority(params.log_level));
    
    /* Setup priority for FEMDK logger */
    femdkLogger->setPriority(log_level_to_priority(params.femdk_log_level));
  }
}

void configureLogger(Logger &logger, const LoggerParams &params) {
  std::ostream *fp = &std::cout;

  logger.setAdditivity(true);

  if (true == params.log_savelog) {
    int fd = create_logfile(params.log_filename); 

    if (-1 != fd ) {
	    log4cpp::Appender* app = new log4cpp::FileAppender(
                                     std::string(logfilename), fd);

      log4cpp::PatternLayout *pl = new log4cpp::PatternLayout();
      if (params.hasLogFormat) {
        pl->setConversionPattern(params.log_format);
      }
	    app->setLayout(pl);

	    logger.addAppender(app);
    } else {
      FEMDK_WARNING("Cannot create log file");
    }
  }
  

  log4cpp::Appender *sapp = new log4cpp::OstreamAppender("ConsoleAppender",
              fp);
  log4cpp::PatternLayout *pl = new log4cpp::PatternLayout();
  if (params.hasLogFormat) {
    pl->setConversionPattern(params.log_format);
  }
  sapp->setLayout(pl);

  // logger steals ownership to appender */
  logger.addAppender(sapp);

	logger.setPriority(log_level_to_priority(params.log_level));
}

static int create_logfile(const std::string &filename) {
  static bool called = false;
  if (false == called) {
    size_t flen = filename.size(); 
    if (flen > logfilenamelen) {
      std::ostringstream oss;
      oss << "Log filename to long (> " << logfilenamelen << ")" 
          << "using default: " << logfilename;
      FEMDK_WARNING(oss.str()); 
    } else {
      strncpy(logfilename, filename.c_str(), logfilenamelen);
      strcat(logfilename+flen, "XXXXXX");
      logfilename[flen+6] = '\0';
    }
    logfile_id = mkstemp(logfilename);
    called = true;
  }
  return logfile_id;
}

#else 
  static DummyLogger dml;
  DummyLogger &getFEMDKLogger() { return dml;}
  DummyLogger &getLogger() {return dml;}
  DummyLogger &createLogger(const std::string& name) {return dml;}
  void setup(const LoggerParams &params) {;}
  void configureLogger(Logger &logger, const LoggerParams &params) {;}
  void shutdown(int status) {;}
#endif

} /* namespace Logger */

} /* namespace femdk */
