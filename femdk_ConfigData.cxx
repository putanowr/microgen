/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
#include "femdk_ConfigData.hxx"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <istream>
#include <iostream>

namespace femdk {

const ConfigData& getSubConfig(const ConfigData &data, 
                               const std::string& name,
                               bool &found) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()){
     found = true;
     return data.get_child(name);
  } else {
    found = false;
    return data;
  }
}


double getDouble(const ConfigData &data, const std::string &name, 
           const double defaultValue) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()){
     const ConfigData &nodeData = data.get_child(name);
     return nodeData.get_value<double>();
  } else {
     return defaultValue;
  }
}

int getInt(const ConfigData &data, const std::string &name, 
           const int defaultValue) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()){
     const ConfigData &nodeData = data.get_child(name);
     return nodeData.get_value<int>();
  } else {
     return defaultValue;
  }
}

bool getBool(const ConfigData &data, const std::string &name, 
            const bool defaultValue) {
  return 0 != getInt(data, name, defaultValue); 
}

std::string getString(const ConfigData &data, const std::string &name, 
                      const std::string &defaultValue) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()){
     const ConfigData &nodeData = data.get_child(name);
     return nodeData.get_value<std::string>();
  } else {
     return defaultValue;
  }
}

int getStringList(const ConfigData &data, const std::string &name, 
                  std::list<std::string> &lst) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()) {
    const ConfigData &lstData = data.get_child(name);
    for (ConfigDataIter j = lstData.begin(); j != lstData.end(); ++j){
      lst.push_back(j->second.get<std::string>(""));
    }
  } 
  return lst.size();
}

} /* namespace femdk */
