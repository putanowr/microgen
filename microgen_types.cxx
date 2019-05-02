/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
#include <string>
#include "microgen_types.hxx"
#include "microgen_exceptions.hxx"

namespace microgen {

const ConfigData& getConfigNode(const ConfigData &config, 
                             const std::string &name) {
  ConfigData::const_assoc_iterator node = config.find(name);
  if (node != config.not_found()) {
    return node->second;
  } else {
    std::string msg = "Cannot find config param : \"" + name + "\"";
    throw Exception(msg); 
  }
} 

} /* namespace microgen */
