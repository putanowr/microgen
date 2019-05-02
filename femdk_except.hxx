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
 *  This file defines FEMDK exceptions and exception handling related
 *  utilities.
 */

#ifndef FEMDK_FEMDK_EXCEPT_HXX 
#define FEMDK_FEMDK_EXCEPT_HXX

#include <exception>
#include <string>

namespace femdk {

  class FEMDKException : public std::exception {
    public:
      FEMDKException(void)  : message("Unspecified exception for"
                                  " FEMDK framework") {}
      explicit FEMDKException(const char *msg) : message(msg) {}
      explicit FEMDKException(const std::string & msg) : message(msg) {}
      virtual ~FEMDKException() throw () {}
      virtual const char* what() const throw() {
         return message.c_str(); 
      }
    protected:
      std::string message;
  };

  class FEMDKIOError : public FEMDKException {
    public:
    FEMDKIOError() : FEMDKException("Input/output error") {}
  };

  class FEMDKNotImplemented : public FEMDKException {
    public:
    FEMDKNotImplemented() : FEMDKException("Feature not implemented") {}
    explicit FEMDKNotImplemented(const std::string & msg) : 
                           FEMDKException(msg) {}
  };

  class FEMDKInvalidArgs : public FEMDKException {
    public:
      FEMDKInvalidArgs() : FEMDKException("Invalid arguments") {}
      FEMDKInvalidArgs(std::string descr) {
         message = std::string("Invalid arguments: ") + descr;
      }
  };
} /* namespace femdk */
/*\@}*/

#endif /* FEMDK_FEMDK_EXCEPT_HXX */
