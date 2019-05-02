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

#include "femdk_common.hxx"
#include "femdk_logger.hxx"
#include "femdk_params.hxx"

namespace femdk {

void Initialize() {
  LoggerParams params;
  Initialize(params);
}

void Initialize(const LoggerParams &logparams) {
  static bool called = false;
  if (false == called) {
    called = true;
    logging::setup(logparams);
    logging::getFEMDKLogger().info("FEMDK framework initialized");
  }
}

void Finalize(int status) {
  static bool called = false;
  if (false == called) {
    called = true;
    logging::getFEMDKLogger().info("FEMDK framework finalized");
  }
}

} /* namespace femdk */
