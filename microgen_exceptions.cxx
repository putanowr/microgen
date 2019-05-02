/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** 
 *  This file provides implementation of exceptions and exception handling
 *  for @microgen application.
 */

#include "microgen_exceptions.hxx"
#include <iostream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp> 

namespace microgen {

void Warning(const std::string &function, 
             const std::string &file, 
             int line,
             const std::string &message) {
   std::cerr << "MICROGEN Warning (" 
             << function << ":"  
             << boost::filesystem::path(file).filename().native() <<":" << line 
             <<")" << std::endl; 
   std::string fmtmessage = boost::replace_all_copy(message, "\n", "\n\t");
   std::cerr << "\t" << fmtmessage << std::endl;
}

void Error(const std::string &function, 
             const std::string &file, 
             int line,
             const std::string &message) {
   std::cerr << "MICROGEN Error (" 
             << function << ":"  
             << boost::filesystem::path(file).filename().native() <<":" << line 
             <<")" << std::endl; 
   std::string fmtmessage = boost::replace_all_copy(message, "\n", "\n\t");
   std::cerr << "\t" << fmtmessage << std::endl;
   abort();
}

void checkStatus(bool status, const char *msg, 
                 const char *function, const char *filename, int line) {
  if (true != status) {
    std::ostringstream oss;
    oss << "Operation failed: " << msg << "\n"
        << "    function: " << function 
        << "        file: " << filename
        << "     at line: " << line;
    throw Exception(oss.str());
  }
}

} /* namespace microgen */
