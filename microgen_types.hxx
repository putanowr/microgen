/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
#ifndef MICROGEN_TYPES_HXX
#define MICROGEN_TYPES_HXX

#include <boost/property_tree/ptree.hpp>

/** This file gathers declaration of various types used accross iga */

namespace microgen {

typedef boost::property_tree::ptree ConfigData;
typedef boost::property_tree::ptree::const_iterator ConfigDataIter;

const ConfigData & getConfigNode(const ConfigData &config, const std::string &name);


} /* namespace microgen */

#endif /* ifndef MICROGEN_TYPES_HXX */
