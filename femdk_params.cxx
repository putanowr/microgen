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

#include "femdk_params.hxx"
#include "femdk_common.hxx"
#include <errno.h>
#include <stdlib.h>
#include <regex>


namespace femdk {

static
bool string2double(const char *str, double *val) {
  bool result = false;
  char *endptr;
  double v;
  v = strtod(str, &endptr);
  if (endptr == str) {
   result = false;
  } else {
    if (NULL != val) {
      *val = v;
      result = true;
    } else {
      FEMDK_ERROR("Unexpected NULL argument");
    }
  }
  return result;
}

static
bool string2long(const char *str,  long *val) {
  bool result = false;
  char *endptr;
  long v;
  v = strtol(str, &endptr, 10);
  if (endptr == str) {
   result = false;
  } else {
    if (NULL != val) {
      *val = v;
      result = true;
    } else {
      FEMDK_ERROR("Unexpected NULL argument");
    }
  }
  return result;
}

void param2double(const char *param_name, const char *str, double &param) {
   double v;
   if (false == string2double(str, &v)) {
     std::cerr << "Invalid value for parameter '"
               << param_name
               << "' (expected double) : "
               << ">" << str << "<"
               << "\n";
     exit(1);
   } else {
     param = v;
   }
}

void param2long(const char *param_name, const char *str, long &param) {
   long v;
   if (false == string2long(str, &v)) {
     std::cerr << "Invalid value for parameter '"
               << param_name
               << "' (expected integer) : "
               << ">" << str << "<"
               << "\n";
     exit(1);
   } else {
     param = v;
   }
}


void param2vector(const std::string &param_name, const std::string &input,
                  std::vector<double> &vec, const std::string &separator) {
  // passing -1 as the submatch index parameter performs splitting
  std::regex re(separator);
  std::sregex_token_iterator
      first{input.begin(), input.end(), re, -1},
      last;
  auto components = std::vector<std::string>{first, last};
  for (auto &&str : components) {
    double val;
    param2double(param_name.c_str(), str.c_str(), val);
    vec.push_back(val);
  }
}

void param2vector(const std::string &param_name, const std::string &input,
                  std::vector<int> &vec, const std::string &separator) {
  // passing -1 as the submatch index parameter performs splitting
  std::regex re(separator);
  std::sregex_token_iterator
      first{input.begin(), input.end(), re, -1},
      last;
  auto components = std::vector<std::string>{first, last};
  for (auto &&str : components) {
    long val;
    param2long(param_name.c_str(), str.c_str(), val);
    vec.push_back(static_cast<int>(val));
  }
}

#include <X11/Xlib.h>
#include <string.h>
/* FIXME -- calling X11 for this parsing is an overkill -- provide
 * own implementation
 */
int parse_geometry_string(const std::string &str, unsigned int *width,
            unsigned int *height,
                           int *xoffset, int *yoffset) {
  char *tmpstr;
  size_t s = str.size();
  tmpstr = new char [s+1];
  memcpy(tmpstr, str.c_str(), s);
  tmpstr[s] = '\0';
  int result = XParseGeometry(tmpstr, xoffset, yoffset, width, height);
  delete [] tmpstr;
  return result;
}

//--------------ExportParams-----------------------------------------------
void
ExportParams::echo(std::ostream &out) {
   if (true == print_header) {
     out << "# Export parameters:"   << "\n";
   }
  if (myHaveMeshFormat) {
    out << "   ex-mesh-format           " << ex_mesh_format << "\n";
  }
  if (myHaveModelFormat) {
    out << "   ex-model-format          " << ex_model_format << "\n";
  }
  if (myHaveGeomFormat) {
    out << "   ex-geom-format          " << ex_geom_format << "\n";
  }
}

//--------------BGDParams--------------------------------------------------
BGDParams::BGDParams() :
                     bgd_shape("rectangle"),
                     myHaveBGDShape(false) {
}

void
BGDParams::echo(std::ostream &out) {
   if (true == print_header) {
     out << "# BGD parameters:"   << "\n";
   }
   out << "   bgd-shape        " << bgd_shape << "\n";
}

//--------------ViewerParams-----------------------------------------------

ViewerParams::ViewerParams() :
                     viewer_bgcolor("black"),
                     viewer_dump("false"),
                     viewer_dump_basename("viewdump"),
                     viewer_dump_dir("/tmp/viewdump"),
                     viewer_geometry("200x200+0+0"),
                     viewer_pause(-1.0),
                     viewer_type("gnuplot"),
                     viewer_width(200),
                     viewer_height(200),
                     viewer_xoffset(0),
                     viewer_yoffset(0),
                     print_header(true),
                     myHaveViewerBGColor(false),
                     myHaveViewerDump(false),
                     myHaveViewerDumpBasename(false),
                     myHaveViewerDumpDir(false),
                     myHaveViewerGeometry(false),
                     myHaveViewerPause(false),
                     myHaveViewerTitle(false),
                     myHaveViewerType(false) {
}

void
ViewerParams::echo(std::ostream &out) {
   if (true == print_header) {
     out << "# Viewer parameters:"   << "\n";
   }
   out << "   viewer-bgcolor        " << viewer_bgcolor << "\n";
   out << "   viewer-dump-basename  " << viewer_dump_basename << "\n";
   out << "   viewer-dump-dir       " << viewer_dump_dir << "\n";
   out << "   viewer-dump           " << viewer_dump << "\n";
   out << "   viewer-geometry       " << viewer_geometry << "\n";
   out << "   viewer-pause          " << viewer_pause << "\n";
   out << "   viewer-title          " << viewer_title << "\n";
   out << "   viewer-type           " << viewer_type << "\n";
}

//--------------CPointsParams-----------------------------------------------
void
CPointsParams::echo(std::ostream &out) {
  out << "# Characteristic points parameters:" << "\n";
  out << "   cp_fname           " << cp_fname << "\n";
  out << "   cp_format            " << cp_format << "\n";
}

//--------------LoggerParams-------------------------------------------------
void
LoggerParams::echo(std::ostream &out) {
  out << "# Logger parameters:" << "\n";
  out << "   log-level           " << log_level << "\n";
  out << "   log-savelog         " << log_savelog << "\n";
  out << "   log-filename        " << log_filename << "\n";
  out << "   log-keep            " << log_keep << "\n";
  out << "   log-format          " << log_format << "\n";
  out << "   femdk-log-level     " << femdk_log_level << "\n";
  out << "   femdk-parent-logger " << femdk_parent_logger << "\n";
}


//--------------CppUnitParams-------------------------------------------------
void
CppUnitParams::echo(std::ostream &out) {
  out << "# Self testing parameters:" << "\n";
  out << "   test-format         " << test_format << "\n";
  out << "   test-progress       " << test_progress << "\n";
  out << "   test-repeat         " << test_repeat << "\n";
  out << "   test-name           " << test_name << "\n";
}

//--------------MeshFormatParams----------------------------------------------
void
MeshFormatParams::echo(std::ostream &out) {
  out << "# Mesh format parameters:" << "\n";
  out << "   pts-header     " << pts_header << "\n";
  out << "   pts-footer     " << pts_footer << "\n";
  out << "   pts-prefix     " << pts_prefix << "\n";
  out << "   pts-suffix     " << pts_suffix << "\n";
  out << "   pts-separator  " << pts_separator << "\n";
  out << "   pts-indices    " << pts_indices << "\n";
}

//--------------SegmentParams-------------------------------------------------
void
SegmentParams::echo(std::ostream &out) {
  out << "# Segment parameters:" << "\n";
  out << "   segment-begin   " << segment_end << "\n";
  out << "   segment-end     " << segment_begin << "\n";
  out << "   segment-at      " << segment_at << "\n";
  out << "   segment-lambda  " << segment_lambda << "\n";
}

//--------------FEMParams-----------------------------------------------------
void
FEMParams::echo(std::ostream &out) {
   out << "# FEM parameters:"          << "\n";
   out << "   elem-type    " << elemtype << "\n";
   out << "   geom-degree  " << geomdegree << "\n";
   out << "   elem-degree  " << elemdegree << "\n";
   out << "   int-degree   " << intdegree << "\n";
}

//--------------MeshgenParams-------------------------------------------------
void
MeshgenParams::echo(std::ostream &out) {
   out << "# Mesh generation parameters:"     << "\n";
   out << "   mesh-family     " << mesh_family << "\n";
   out << "   global-lc       " << global_lc << "\n";
   out << "   meshgen-verbose " << meshgen_verbose << "\n";
}

//--------------MaterialModelParams--------------------------------------------
void
MaterialModelParams::echo(std::ostream &out) {
   out << "# Material model parameters:"     << "\n";
   out << "   material-model   " << material_model2str(material_model) << "\n";
}

//--------------RectangleParams------------------------------------------------
void
RectangleParams::echo(std::ostream &out) {
   out << "# Geometry parameters:"          << "\n";
   out << "   Lx   " << Lx << "\n";
   out << "   Ly   " << Ly << "\n";

   out << "# Mesh parameters:"          << "\n";
   out << "   Nx   " << Nx << "\n";
   out << "   Ny   " << Ny << "\n";
   out << "   mesh_shaken : " << mesh_shaken << "\n";
}

//--------------CubeParams------------------------------------------------
void
CubeParams::echo(std::ostream &out) {
   out << "# Geometry parameters:"          << "\n";
   out << "   Lx   " << Lx << "\n";
   out << "   Ly   " << Ly << "\n";
   out << "   Lz   " << Lz << "\n";
}

//--------------CubeMeshParams------------------------------------------------
void
CubeMeshParams::echo(std::ostream &out) {
   out << "# Mesh parameters:"          << "\n";
   out << "   Nx   " << Nx << "\n";
   out << "   Ny   " << Ny << "\n";
   out << "   Nz   " << Nz << "\n";
}

//--------------CircHoleQuarterParams------------------------------------------
void
CircHoleQuarterParams::echo(std::ostream &out) {
   out << "# Geometry parameters:"          << "\n";
   out << "   Lx  " << Lx << "\n";
   out << "   Ly  " << Ly << "\n";
   out << "   Rh  " << Rh << "\n";

   out << "# Mesh parameters:"          << "\n";
   out << "   Nx  " << Nx << "\n";
   out << "   Ny  " << Ny << "\n";
   out << "   Nh  " << Nh << "\n";
}


//--------------TimeDispatchParams---------------------------------------------
void
TimeDispatcherParams::echo(std::ostream &out) {
   out << "# Time dispatcher parameters:"   << "\n";
   out << "   td-theta      " <<   td_theta << "\n";
}

//--------------MiscParams----------------------------------------------------
void
MiscParams::echo(std::ostream &out) {
   out << "# Miscellaneous parameters:"          << "\n";
   out << "   dry-run      " << dry_run << "\n";
   out << "   echo-params  " << echo_params << "\n";
   out << "   save-params  " << save_params << "\n";
}

//--------------ElasticMatParams-----------------------------------------------
void
ElasticMatParams::echo(std::ostream &out) {
   if (true == print_header) {
     out << "# Material parameters:"   << "\n";
   }
   out << "   E      " <<       E << "\n";
   out << "   nu     " <<      nu << "\n";
}

//--------------ElastoPlasticMatParams----------------------------------------
void
ElastoPlasticMatParams::echo(std::ostream &out) {
   ElasticMatParams::echo(out);
   out << "   sigma0  " <<       sigma0 << "\n";
}


//--------------GnuplotParams--------------------------------------------------
void
GnuplotParams::echo(std::ostream &out) {
  out << "# Gnuplot parameters:"   << "\n";
  out << "   gpt-keep-datafiles  " << gpt_keep_datafiles << "\n";
  out << "   gpt-mesh-file       " << gpt_mesh_file << "\n";
  out << "   gpt-png-size        " << gpt_png_size << "\n";
  print_commands(out, gptCommands.begin(), gptCommands.end(), "");
}

void
GnuplotParams::print_commands(std::ostream &out,
                        CmdConstIter begin, CmdConstIter end,
                        const char *prefix) const {
  std::string prf(prefix);
  for (CmdConstIter i=begin; i != end; ++i) {
    out << prf << *i << "\n";
  }
}


//--------------GetFEMSolverParams---------------------------------------------
void GetFEMSolverParams::echo(std::ostream &out) {
   out << "# Solver parameters:"         << "\n";
   out << "   res       " << residuum << "\n";
   out << "   maxiter   " << maxiter << "\n";
   out << "   noised    " << noised << "\n";
}

//--------------OutputParams---------------------------------------------
void OutputParams::echo(std::ostream &out) {
   out << "# Output parameters:"            << "\n";
   out << "   out-file    " << out_file   << "\n";
   out << "   out-dir     " << out_dir    << "\n";
   out << "   out-policy  " << out_policy << "\n";
}

const char* OutputParams::validOutPolicies[] = {"abort", "override", "addtag"};


//--------------GetFEMMiscParams---------------------------------------------
void GetFEMMiscParams::echo(std::ostream &out) {
   out << "# GetFEM miscellaneous parameters:"         << "\n";
   out << "    getfem-traces  "   << getfem_traces << "\n";
   out << "    getfem-warnlevel " << getfem_warnlevel << "\n";
}


//--------------SkewThrowParams-----------------------------------------------
void
SkewThrowParams::echo(std::ostream &out) {
   if (true == print_header) {
     out << "# Skew-throw parameters:"   << "\n";
   }
   out << "   st-alpha  " << st_alpha << "\n";
   out << "   st-v0     " << st_v0    << "\n";
   out << "   st-x0     " << st_x0    << "\n";
   out << "   st-y0     " << st_y0    << "\n";
   out << "   st-dt     " << st_dt    << "\n";
}

} /* namespace femdk */
