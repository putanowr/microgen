/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** 
 *  This file provides implementation of exceptions and exception handling
 *  for FEMDK framework.
 */

#include "femdk_except.hxx"
#include <iostream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp> 

namespace femdk {

void Warning(const std::string &function, 
             const std::string &file, 
             int line,
             const std::string &message) {
   std::cerr << "FEMDK Warning (" 
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
   std::cerr << "FEMDK Error (" 
             << function << ":"  
             << boost::filesystem::path(file).filename().native() <<":" << line 
             <<")" << std::endl; 
   std::string fmtmessage = boost::replace_all_copy(message, "\n", "\n\t");
   std::cerr << "\t" << fmtmessage << std::endl;
   abort();
}

} /* namespace femk */
