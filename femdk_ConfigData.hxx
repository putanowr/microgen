/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
#ifndef FEMDK_CONFIGDATA_HXX
#define FEMDK_CONFIGDATA_HXX

/** @file femdk_ConfigData.hxx 
 * Utility function to help parse configuration represented by ConfiData type;
 */
#include <list>
#include <vector>
#include <string>
#include "femdk_types.hxx"

namespace femdk{

int getInt(const ConfigData &data, const std::string &name, 
           const int defaultValue);
double getDouble(const ConfigData &data, const std::string &name, 
           const double defaultValue);
bool getBool(const ConfigData &data, const std::string &name,
             const bool defaultValue);
std::string getString(const ConfigData &data, const std::string &name, 
                      const std::string &defaultValue);


/** Return subconfig branch of a given name */
const ConfigData& getSubConfig(const ConfigData &data, const std::string &name,
                               bool &found);

int getStringList(const ConfigData &data, const std::string &name, 
                  std::list<std::string> &lst);

template <class Container>
int getStrings(const ConfigData &data, const std::string &name, 
               Container &lst) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()) {
    const ConfigData &lstData = data.get_child(name);
    for (ConfigDataIter j = lstData.begin(); j != lstData.end(); ++j){
      lst.push_back(j->second.get<std::string>(""));
    }
  } 
  return lst.size();
}

/** Read vector from data.
 *  Return the number of elements in updated vector. 
 *  been found.
 */
template <typename T>
int getVector(std::vector<T> &v, const ConfigData &data, 
                                      const std::string &name,
                                      int size, T defaultValue) {
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()) {
    const ConfigData &vecData = data.get_child(name);
    for (ConfigDataIter j = vecData.begin(); j != vecData.end(); ++j){
      v.push_back(j->second.get<T>(""));
    }
  } else if (size > 0) {
    v.resize(size, defaultValue);
  }
  return v.size();
}

template <typename T>
int getVector(T *v, const ConfigData &data, 
                                      const std::string &name,
                                      int size, T defaultValue) {
  int ti=0;
  ConfigData::const_assoc_iterator node = data.find(name);
  if (node != data.not_found()) {
    const ConfigData &vecData = data.get_child(name);
    for (ConfigDataIter j = vecData.begin(); j != vecData.end(); ++j){
      if (ti < size) {
         v[ti] = j->second.get<T>("");
         ti++;
      }
    }
  } else if (size > 0) {
    for (ti=0; ti<size; ti++) {
       v[ti] = defaultValue;
    }
  }
  return ti;
}

} /* namespace femdk */

#endif /* ifndef FEMDK_CONFIGDATA_HXX */
