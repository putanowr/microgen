/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */

#include "microgen_parsing.hxx"
#include <vector>

namespace microgen {

bool parseCubeSize(const std::string &s, vigra::Shape3 &shape) {
  std::vector<std::string> tok; 
  std::vector<int> numbers;
  bool isOK = true;
  boost::split(tok, s, boost::is_any_of(",x "));
  try {
    std::transform(tok.begin(), tok.end(), std::back_inserter(numbers),
        &boost::lexical_cast<int,std::string>);
  } catch (boost::bad_lexical_cast e) {
    isOK = false; 
  }
  int ns = numbers.size();
  if (isOK) {
    if (3 == ns) {
      shape[0] = numbers[0];
      shape[1] = numbers[1];
      shape[2] = numbers[2];
    } else if (1 == ns) {
      shape[0] = shape[1] = shape[2] = numbers[0];
    } else {
      isOK = false;
    }  
  } 
  return isOK;
}

} /* namespace microgen */
