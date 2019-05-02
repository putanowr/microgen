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
#ifndef MICROGEN_PARSING_HXX
#define MICROGEN_PARSING_HXX 

#include <vigra/multi_shape.hxx>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

namespace microgen {

bool parseCubeSize(const std::string& s, vigra::Shape3& shape);

} /* namespace microgen */

#endif /* MICROGEN_PARSING_HXX */
