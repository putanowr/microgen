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

#ifndef MICROGEN_PARAMS_HXX 
#define MICROGEN_PARAMS_HXX

#include "microgen_options.h" 
#include "femdk_common.hxx"
#include "femdk_params.hxx"

namespace microgen {

class Params : public femdk::OutputParams,
               public femdk::LoggerParams,
               public femdk::MiscParams {
  public:
    Params() : myHaveMicroSize(false), myHaveSelftest(false) {}
    void setUp(void);
    void echo(std::ostream &out);
    std::string micro_size;
    bool myHaveMicroSize;
    bool myHaveSelftest;
};

inline void Params::setUp(void) {
  femdk::OutputParams::setUp();
#ifdef VALUE_OPT_MICRO_SIZE
  if (HAVE_OPT(MICRO_SIZE)) {
    myHaveMicroSize=true;
    micro_size = std::string(OPT_ARG(MICRO_SIZE));
  }  
#endif

#ifdef VALUE_OPT_SELFTEST
  if (HAVE_OPT(SELFTEST)) {
    myHaveSelftest = true;
  }  
#endif 
  femdk::LoggerParams::setUp();
  femdk::MiscParams::setUp();
}

} /* namespace microgen */

#endif /* ifndef MICROGEN_PARAMS_HXX */
