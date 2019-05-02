/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** 
 *  This file defines microgen exceptions and exception handling related
 *  utilities.
 */

#ifndef MICROGEN_EXCEPTIONS_HXX 
#define MICROGEN_EXCEPTIONS_HXX

#include <exception>
#include <sstream>
#include <string>

#define MICROGEN_WARN(msg) \
        microgen::Warning(__FUNCTION__, __FILE__, __LINE__, msg)
#define MICROGEN_ERROR(msg) \
        microgen::Error(__FUNCTION__, __FILE__, __LINE__, msg)

namespace microgen {

void Warning(const std::string &function, 
             const std::string &file, 
             int line,
             const std::string &message); 

void Error(const std::string &function, 
             const std::string &file, 
             int line,
             const std::string &message);

void checkStatus(bool status, const char *msg, 
                 const char *function, const char *filename, int line);

  class Exception : public std::exception {
    public:
      Exception(void)  : message("Unspecified exception for"
                                  " microgen framework") {}
      explicit Exception(const char *msg) : message(msg) {}
      explicit Exception(const std::string & msg) : message(msg) {}
      virtual ~Exception() throw () {}
      virtual const char* what() const throw() {
         return message.c_str(); 
      }
    protected:
      std::string message;
  };

  class NotImplemented : public Exception {
    public:
    NotImplemented() : Exception("Feature not implemented") {}
  };

#ifdef NDEBUG
  #define MICROGENCHK(status) 
  #define MICROGENCHK(status, msg)
#else
  #define MICROGENCHK(status) checkStatus(status, "", __FUNCTION__, __FILE__, __LINE__);
  #define MICROGENCHKMSG(status, msg) checkStatus(status, msg, __FUNCTION__, __FILE__, __LINE__);
#endif

} /* namespace microgen */
#endif /* MICROGEN_EXCEPTIONS_HXX */
