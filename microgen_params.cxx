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
#include "microgen_params.hxx" 

namespace microgen {

void Params::echo(std::ostream &out) { 
  femdk::OutputParams::echo(out); 

  out << "# Microstructure parameters:"   << "\n";
  out << "   micro-size        " << micro_size << "\n";

  femdk::LoggerParams::echo(out);
  femdk::MiscParams::echo(out);
}

} /* namespace microgen */
