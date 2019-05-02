/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** \addtogroup core */
/*\@{*/
/** \file femdk_params.hxx
 *  This file provides calasses to make easier building support
 *  for user settable parameters.
 */

#ifndef FEMDK_FEMDK_PARAMS_HXX
#define FEMDK_FEMDK_PARAMS_HXX

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "femdk_types.hxx"

namespace femdk {
 void param2double(const char *param_name, const char *str, double &param);
 void param2long(const char *param_name, const char *str, long &param);
 /** Parse string into a vector of doubles. The separator can be a regular
  * expression.
  */ 
 void param2vector(const std::string &param_name, const std::string &input,
                   std::vector<double> &vec,
                   const std::string &separator="[\\s,]+");
 /** Parse string into a vector of integers. The separator can be a regular
  * expression.
  */ 
 void param2vector(const std::string &param_name, const std::string &input,
                   std::vector<int> &vec,
                   const std::string &separator="[\\s,]+");
 int parse_geometry_string(const std::string &str, unsigned int *width,
                            unsigned int *height, int *xoffset, int *yoffset);

/** \@brief ExportParams -- parameters for data export
 * Handle the following parameters:
 *   ex_mesh_format -- format name for writing mesh data,
 *   ex_model_format -- format name for writing model data
 *   ex_geom_format -- format name for writing geometric data
 */
class ExportParams {
  public:
    ExportParams() : ex_mesh_format("femdk"),
                     ex_model_format("femdk"),
                     ex_geom_format("none"),
                     print_header(true),
                     myHaveMeshFormat(false),
                     myHaveModelFormat(false),
                     myHaveGeomFormat(false) {}
    void setUp(void);
    void echo(std::ostream &out);
    std::string ex_mesh_format;
    std::string ex_model_format;
    std::string ex_geom_format;
  protected:
    bool print_header;
    bool myHaveMeshFormat;
    bool myHaveModelFormat;
    bool myHaveGeomFormat;
};

inline void
ExportParams::setUp(void) {
#ifdef VALUE_OPT_EX_MESH_FORMAT
  te_Ex_Mesh_Format opt_mesh = (te_Ex_Mesh_Format)OPT_VALUE_EX_MESH_FORMAT;
  ex_mesh_format = std::string(OPT_EX_MESH_FORMAT_VAL2STR(opt_mesh));
  myHaveMeshFormat=true;
#endif
#ifdef VALUE_OPT_EX_MODEL_FORMAT
  te_Ex_Model_Format opt_model = (te_Ex_Model_Format)OPT_VALUE_EX_MODEL_FORMAT;
  ex_model_format = std::string(OPT_EX_MODEL_FORMAT_VAL2STR(opt_model));
  myHaveModelFormat=true;
#endif
#ifdef VALUE_OPT_EX_GEOM_FORMAT
  te_Ex_Geom_Format opt_geom = (te_Ex_Geom_Format)OPT_VALUE_EX_GEOM_FORMAT;
  ex_geom_format = std::string(OPT_EX_GEOM_FORMAT_VAL2STR(opt_geom));
  myHaveGeomFormat=true;
#endif
}


/** \@brief BGDParams -- parameters related to BGD shapes
 *   bgd-shape -- type of BGD shape,
 */
class BGDParams {
  public:
    BGDParams();
    void setUp(void);
    void echo(std::ostream &out);
    std::string bgd_shape;
  protected:
    bool print_header;
    bool myHaveBGDShape;
};

inline void
BGDParams::setUp(void) {
#ifdef VALUE_OPT_BGD_SHAPE
  if ( HAVE_OPT(BGD_SHAPE)) {
    te_Bgd_Shape opt_bgdshape = (te_Bgd_Shape)OPT_VALUE_BGD_SHAPE;
    bgd_shape = std::string(OPT_BGD_SHAPE_VAL2STR(opt_bgdshape));
    myHaveBGDShape = true;
  }
#endif
}

/** \@brief ViewerParams -- parameters for mesh viewers
 * Handle the following parameters:
 *   viewer-type -- type of mesh viewer,
 */
class ViewerParams {
  public:
    ViewerParams();
    void setUp(void);
    void echo(std::ostream &out);
    std::string viewer_bgcolor;
    bool viewer_dump;
    std::string viewer_dump_basename;
    std::string viewer_dump_dir;
    std::string viewer_geometry;
    double viewer_pause;
    std::string viewer_title;
    std::string viewer_type;
    unsigned int viewer_width;
    unsigned int viewer_height;
    int viewer_xoffset;
    int viewer_yoffset;
    int viewer_geometry_flags;
  protected:
    bool print_header;
    bool myHaveViewerBGColor;
    bool myHaveViewerDump;
    bool myHaveViewerDumpBasename;
    bool myHaveViewerDumpDir;
    bool myHaveViewerGeometry;
    bool myHaveViewerPause;
    bool myHaveViewerTitle;
    bool myHaveViewerType;
};

inline void
ViewerParams::setUp(void) {
#ifdef VALUE_OPT_VIEWER_TYPE
  if ( HAVE_OPT(VIEWER_BGCOLOR)) {
    viewer_bgcolor = std::string(OPT_ARG(VIEWER_BGCOLOR));
    myHaveViewerBGColor=true;
  }
  if ( HAVE_OPT(VIEWER_DUMP)) {
    viewer_dump = OPT_ARG(VIEWER_DUMP);
    myHaveViewerDump=true;
  }
  if ( HAVE_OPT(VIEWER_DUMP_BASENAME)) {
    viewer_dump_basename = std::string(OPT_ARG(VIEWER_DUMP_BASENAME));
    myHaveViewerDumpBasename=true;
  }
  if ( HAVE_OPT(VIEWER_DUMP_DIR)) {
    viewer_dump_dir = std::string(OPT_ARG(VIEWER_DUMP_DIR));
    myHaveViewerDumpDir=true;
  }
  if ( HAVE_OPT(VIEWER_GEOMETRY)) {
    viewer_geometry = std::string(OPT_ARG(VIEWER_GEOMETRY));
    viewer_geometry_flags = parse_geometry_string(viewer_geometry,
                 &viewer_width, &viewer_height, &viewer_xoffset,
                 &viewer_yoffset);
    myHaveViewerGeometry=true;
  }
  if ( HAVE_OPT(VIEWER_PAUSE)) {
    param2double("viewer-pause", OPT_ARG(VIEWER_PAUSE), viewer_pause);
    myHaveViewerPause=true;
  }
  if ( HAVE_OPT(VIEWER_TITLE)) {
    viewer_title = std::string(OPT_ARG(VIEWER_TITLE));
    myHaveViewerTitle=true;
  }
  if ( HAVE_OPT(VIEWER_TYPE)) {
    te_Viewer_Type opt_meshviewer = (te_Viewer_Type)OPT_VALUE_VIEWER_TYPE;
    viewer_type = std::string(OPT_VIEWER_TYPE_VAL2STR(opt_meshviewer));
    myHaveViewerType = true;
  }
#endif
}

/** \@brief CPointsParams -- parameters for characteristic points
 * Handle the following parameters:
 *   cp_format -- file format for writing characteristic points,
 *   cp_fname -- file path for writing characteristic points
 *   cp_write -- boolean flag
 */
class CPointsParams {
  public:
    CPointsParams() : cp_format("json"),
                     cp_fname("info"),
                     cp_write(false) {}
    void setUp(void);
    void echo(std::ostream &out);
    std::string cp_format;
    std::string cp_fname;
    bool cp_write;
};

inline void
CPointsParams::setUp(void) {
#ifdef VALUE_OPT_CP_FORMAT
  cp_format = std::string(OPT_ARG(CP_FORMAT));
  cp_fname = std::string(OPT_ARG(CP_FNAME));
  if (ISSEL_OPT(CP_FNAME)) {
    if (cp_fname != "") {
      cp_write = true;
    }
  }
#endif
}


/** \@brief LoggerParams -- parameters for managing logger
 * Handle the following parameters:
 *   log_level -- name of the log level,
 */
class LoggerParams {
  public:
    LoggerParams() : log_level("info"),
                     femdk_log_level("info"),
                     femdk_parent_logger(""),
                     log_keep(false),
                     hasLogFormat(false) {}
    void setUp(void);
    void echo(std::ostream &out);
    std::string log_level;
    std::string femdk_log_level;
    std::string femdk_parent_logger;
    bool log_keep;
    bool log_savelog;
    std::string log_filename;
    std::string log_format;
    bool hasLogFormat;
};

inline void
LoggerParams::setUp(void) {
#ifdef VALUE_OPT_LOG_LEVEL
  te_Log_Level opt = (te_Log_Level)OPT_VALUE_LOG_LEVEL;
  log_level = std::string(OPT_LOG_LEVEL_VAL2STR(opt));
#endif
#ifdef VALUE_OPT_FEMDK_LOG_LEVEL
  te_Femdk_Log_Level optf = (te_Femdk_Log_Level)OPT_VALUE_FEMDK_LOG_LEVEL;
  if (optf > FEMDK_LOG_LEVEL_NOTSET) {
     optf = FEMDK_LOG_LEVEL_NOTSET;
  }
  femdk_log_level = std::string(OPT_FEMDK_LOG_LEVEL_VAL2STR(optf));
#endif
#ifdef VALUE_OPT_FEMDK_PARENT_LOGGER
  femdk_parent_logger = std::string(OPT_ARG(FEMDK_PARENT_LOGGER));
#endif
#ifdef VALUE_OPT_LOG_KEEP
  log_keep = OPT_ARG(LOG_KEEP);
#endif
#ifdef VALUE_OPT_LOG_FORMAT
  log_format = std::string(OPT_ARG(LOG_FORMAT));
  hasLogFormat = true;
#endif
#ifdef VALUE_OPT_LOG_FORMAT
  log_filename = std::string(OPT_ARG(LOG_FILENAME));
#endif
#ifdef VALUE_OPT_LOG_SAVELOG
  log_savelog = OPT_ARG(LOG_SAVELOG);
#endif
}

/** \@brief CppUnitParams -- parameters for managing CppUnit based testing
 * Handle the following parameters:
 *   test_repeat -- number of test repeats,
 *   test_progress -- name of progress reporter,
 *   test_format  -- name of the output format,
 *   test_name -- name of the test to run
 */
class CppUnitParams {
  public:
    CppUnitParams()  = default;
    void setUp(void);
    void echo(std::ostream &out);

    int         test_repeat = 1;
    std::string test_progress = "dots";
    std::string test_format = "test";
    std::string test_name = "All Tests";
};


inline void
CppUnitParams::setUp(void) {

#ifdef VALUE_OPT_TEST_PROGRESS
  test_progress = std::string(OPT_ARG(TEST_PROGRESS));
#endif

#ifdef VALUE_OPT_TEST_FORMAT
  test_format = std::string(OPT_ARG(TEST_FORMAT));
#endif

#ifdef VALUE_OPT_TEST_NAME
  test_name = std::string(OPT_ARG(TEST_NAME));
#endif

#ifdef VALUE_TEST_REPEAT
  test_repeat = OPT_ARG(TEST_REPEAT);
#endif

}

/** \@brief MeshFormatParams -- parameters describing formating mesh when
 *  saving to file
 *  FIXME
 */
class MeshFormatParams {
  public:
    MeshFormatParams() : pts_header(""), pts_footer(""),
                         pts_separator(" "),
                         pts_prefix(""),
                         pts_suffix("\n"),
                         pts_indices(true) {
    }
    std::string pts_header;
    std::string pts_footer;
    std::string pts_separator;
    std::string pts_prefix;
    std::string pts_suffix;
    bool pts_indices;
    void setUp(void);
    void echo(std::ostream &out);
};


inline void
MeshFormatParams::setUp(void) {
#ifdef VALUE_OPT_PTS_FOOTER
  pts_indices = OPT_ARG(PTS_INDICES);
  if ( HAVE_OPT(PTS_FOOTER)) {
    pts_footer = std::string(OPT_ARG(PTS_FOOTER));
  }
  if ( HAVE_OPT(PTS_HEADER)) {
    pts_header = std::string(OPT_ARG(PTS_HEADER));
  }
  if ( HAVE_OPT(PTS_SUFFIX)) {
    pts_suffix = std::string(OPT_ARG(PTS_SUFFIX));
  }
  if ( HAVE_OPT(PTS_PREFIX)) {
    pts_prefix = std::string(OPT_ARG(PTS_PREFIX));
  }
  if ( HAVE_OPT(PTS_SEPARATOR)) {
    pts_separator = std::string(OPT_ARG(PTS_SEPARATOR));
  }
#endif
}

/** \@brief Class for handling material model parameters.
 *
 * Handle the following parameters:
 *   material_type -- string describing type of material model:
 *                    "elastic", "plastic", elasto-plastic",
 */
struct MaterialModelParams {
  MaterialModelParams() : material_model(ELASTIC_MAT) {
  }
  void echo(std::ostream &out);
  void setUp(void);
  material_model_t material_model;
};

inline
void MaterialModelParams::setUp() {
#ifdef VALUE_OPT_MATERIAL_MODEL
  te_Material_Model opt = (te_Material_Model)OPT_VALUE_MATERIAL_MODEL;
  switch (opt) {
    case MATERIAL_MODEL_ELASTIC : material_model = ELASTIC_MAT;
         break;
    case MATERIAL_MODEL_PLASTIC : material_model = PLASTIC_MAT;
         break;
    case MATERIAL_MODEL_ELASTO_PLASTIC : material_model = ELASTO_PLASTIC_MAT;
         break;
    default:
      throw FEMDKException("Internal error invalid option enum te_Material_Model");
  }
#endif
}

/** \@brief SegmentParams -- parameters describing geometric segments
 *
 * Handle the following parameters:
 *   segment_begin  -- string with begin point coordinates,
 *   segment_end    -- string with end point coordinates
 *   segment_at     -- explicit point at segment
 *   segment_lambda -- segment paramter
 *
 * The coorindate strings are not interpreted nor validated by this class.
 */
class SegmentParams {
  public:
    SegmentParams() : segment_begin("0,0,0"), segment_end("1,1,1"),
                      segment_at("0.5,0.5,0.5"), segment_lambda(0.5) {}
    std::string segment_begin;
    std::string segment_end;
    std::string segment_at;
    double segment_lambda;
    void setUp(void);
    void echo(std::ostream &out);
};
inline void
SegmentParams::setUp(void) {
#ifdef VALUE_OPT_SEGMENT_BEGIN
  if ( HAVE_OPT(SEGMENT_BEGIN)) {
    segment_begin = std::string(OPT_ARG(SEGMENT_BEGIN));
  }
  if ( HAVE_OPT(SEGMENT_END)) {
    segment_end = std::string(OPT_ARG(SEGMENT_END));
  }
  if ( HAVE_OPT(SEGMENT_AT)) {
    segment_at = std::string(OPT_ARG(SEGMENT_AT));
  }
  if ( HAVE_OPT(SEGMENT_LAMBDA)) {
    param2double("segment-lambda", OPT_ARG(SEGMENT_LAMBDA), segment_lambda);
  }
#endif
}

/** \@brief FEMParams -- parameters describing FEM interpolation.
 *
 * Handle the following parameters:
 *   elemtype -- string describing geometric shape of element, e.g. triang,
 *                quad, etc.
 *   elemdegree -- degree of element shape functions
 *   geomdegree -- degree of geometric mapping shape functions
 *   intdegree -- max. degree of polinomial integrated exactly by the
 *                  quadrature rules
 */
struct FEMParams {
  FEMParams() : elemtype("quad"), elemdegree(1), geomdegree(1),
                    intdegree(3) {}
  void setUp(void);
  void echo(std::ostream &out);
  std::string elemtype;
  int elemdegree;
  int geomdegree;
  int intdegree;
};

inline void
FEMParams::setUp(void) {
#ifdef VALUE_OPT_GEOM_DEGREE
  te_Elem_Type opt = (te_Elem_Type)OPT_VALUE_ELEM_TYPE;
  elemtype = std::string(OPT_ELEM_TYPE_VAL2STR(opt));
  geomdegree = OPT_VALUE_GEOM_DEGREE;
  elemdegree = OPT_VALUE_ELEM_DEGREE;
  intdegree = OPT_VALUE_INT_DEGREE;
#endif
}

/** \@brief MeshgenParams -- mesh generation parameter.
 *
 * Handle the following parameters:
 *   mesh_family -- string describing family of element types: simplical,
 *   cubical, mixed
 *   global_lc -- global edge length
 *   meshgen_verbose -- enable/disable messages from mesh generator
 */
struct MeshgenParams {
  MeshgenParams() : mesh_family(SIMPLICAL_MESH), meshgen_verbose(false) {}
  void setUp(void);
  void echo(std::ostream &out);
  void setMeshFamily(const std::string & name);
  std::string getMeshFamilyName() const;
  mesh_family_t mesh_family;
  double global_lc;
  bool meshgen_verbose;
};

inline void
MeshgenParams::setMeshFamily(const std::string &name) {
  mesh_family = str2mesh_family(name.c_str());
}

inline std::string
MeshgenParams::getMeshFamilyName() const {
  return mesh_family2str(mesh_family);
}

inline void
MeshgenParams::setUp(void) {
#ifdef VALUE_OPT_MESH_FAMILY
  te_Mesh_Family opt = (te_Mesh_Family)OPT_VALUE_MESH_FAMILY;
  switch (opt) {
    case MESH_FAMILY_SIMPLICAL : mesh_family = SIMPLICAL_MESH; break;
    case MESH_FAMILY_CUBICAL : mesh_family = CUBICAL_MESH; break;
    case MESH_FAMILY_MIXED : mesh_family = MIXED_MESH; break;
    default:
      throw FEMDKException("Internal error invalid option enum te_Mesh_Family");
  }
  /*setMeshFamily(std::string(OPT_MESH_FAMILY_VAL2STR(opt)));*/
  param2double("global-lc", OPT_ARG(GLOBAL_LC), global_lc);
  meshgen_verbose = OPT_ARG(MESHGEN_VERBOSE);
#endif
}

/** \@brief RectangleParams -- parameters describing rectangular geometric
 *                             domain.
 *
 * Handle the following parameters:
 *   Lx -- rectangle dimension in X direction
 *   Ly -- rectangle dimension in Y direction
 *   Nx -- mesh density (number of segments) in X direction
 *   Ny -- mesh density (number of segments) in Y direction
 */
struct RectangleParams {
  RectangleParams() : Nx(1), Ny(1), Lx(1.0), Ly(1.0), mesh_shaken(false){}
  void setUp(void);
  void echo(std::ostream &out);
  int Nx;
  int Ny;
  double Lx;
  double Ly;
  bool mesh_shaken;
};

inline void
RectangleParams::setUp(void) {
#ifdef VALUE_OPT_MESH_SHAKEN
  param2double("Lx",OPT_ARG(LX), Lx);
  param2double("Ly",OPT_ARG(LY), Ly);

  Nx = OPT_VALUE_NX;
  Ny = OPT_VALUE_NY;
  mesh_shaken = OPT_ARG(MESH_SHAKEN);
#endif
}

/** \@brief CubeParams -- parameters describing cube geometric domain.
 *
 * Handle the following parameters:
 *   Lx -- cube dimension in X direction
 *   Ly -- cube dimension in Y direction
 *   Lz -- cube dimension in Z direction
 */
struct CubeParams {
  CubeParams() : Lx(1.0), Ly(1.0), Lz(1.0) {}
  void setUp(void);
  void echo(std::ostream &out);
  double Lx;
  double Ly;
  double Lz;
};

inline void
CubeParams::setUp(void) {
#ifdef VALUE_OPT_LZ
  param2double("Lx",OPT_ARG(LX), Lx);
  param2double("Ly",OPT_ARG(LY), Ly);
  param2double("Lz",OPT_ARG(LZ), Lz);
#endif
}

/** \@brief CubeMeshParams -- mesh parameters for cube mesh
 *
 * Handle the following parameters:
 *   Nx -- mesh density (number of segments) in X direction
 *   Ny -- mesh density (number of segments) in Y direction
 *   Nz -- mesh density (number of segments) in Z direction
 *
 * If setup from parsed command line, the above parameters can be specified
 * by --Nx, --Ny and --Nz flags or by --mesh-resolution flag which takes
 * a vector. The --mesh-resolution values can be overwritten by specifying
 * resolution in any specific direction.
 */
struct CubeMeshParams {
  void setUp(void);
  void echo(std::ostream &out);
  int Nx = 1;
  int Ny = 1;
  int Nz = 1;
};

inline void
CubeMeshParams::setUp(void) {
#ifdef VALUE_OPT_MESH_RESOLUTION
  if (HAVE_OPT(MESH_RESOLUTION)) {
    std::string param = OPT_ARG(MESH_RESOLUTION);
    std::vector<int> resolution;
    param2vector("mesh-resolution", param, resolution);
    auto dim = resolution.size();
    if (dim > 0) Nx = resolution[0];   
    if (dim > 1) Ny = resolution[1];   
    if (dim > 2) Nz = resolution[2];   
  }
#endif
#ifdef VALUE_OPT_NZ
  if (ISSEL_OPT(NX)) Nx = OPT_VALUE_NX;
  if (ISSEL_OPT(NY)) Ny = OPT_VALUE_NY;
  if (ISSEL_OPT(NZ)) Nz = OPT_VALUE_NZ;
#endif
}


/** \@brief CircHoleQuarterParams -- parameters describing 1/4 of a rectangular
 * domain with circular hole.
 *
 * Handle the following parameters:
 *   Lx -- rectangle dimension in X direction
 *   Ly -- rectangle dimension in Y direction
 *   Rh -- hole radius
 *   Nx -- number of boundary segments in X direction
 *   Ny -- number of boundary segments in Y direction
 *   Nh -- number of boundary segments at the hole
 */
struct CircHoleQuarterParams {
  CircHoleQuarterParams() : Nx(1), Ny(1), Nh(3), Lx(1.0), Ly(1.0), Rh(0.25) {}
  void setUp(void);
  void echo(std::ostream &out);
  int Nx;
  int Ny;
  int Nh;
  double Lx;
  double Ly;
  double Rh;
};

inline void
CircHoleQuarterParams::setUp(void) {
#ifdef VALUE_OPT_RH
  param2double("Lx", OPT_ARG(LX), Lx);
  param2double("Ly", OPT_ARG(LY), Ly);
  param2double("Rh", OPT_ARG(RH), Rh);

  Nx = OPT_VALUE_NX;
  Ny = OPT_VALUE_NY;
  Nh = OPT_VALUE_NH;
#endif
}


/** \@brief MiscParams -- miscellaneous parameters -- mainly related
 *                        to programs running.
 *
 * Handle the following parameters:
 *   dry_run -- simulate program running
 */
struct MiscParams {
 MiscParams() : dry_run(false), echo_params(false), save_params("") {}
 void setUp(void);
 void echo(std::ostream &out);
 bool dry_run;
 bool echo_params;
 std::string save_params;
};

inline void
MiscParams::setUp(void) {
#ifdef VALUE_OPT_DRY_RUN
  dry_run = HAVE_OPT(DRY_RUN);
  echo_params = HAVE_OPT(ECHO_PARAMS);
  save_params = std::string(OPT_ARG(SAVE_PARAMS));
#endif
}


/** \@brief GetFEMMiscParams -- GetFEM miscellaneous parameters.
 *
 * Handle the following parameters:
 *   getfem_traces -- the level of GetFEM traces printed
 *   getfem_warnlevel -- the leovel of GetFEM warnings printed
 */
struct GetFEMMiscParams {
  GetFEMMiscParams() : getfem_traces(0) {}
  void setUp(void);
  void echo(std::ostream &out);
  int getfem_traces;
  int getfem_warnlevel;
};

inline void
GetFEMMiscParams::setUp(void) {
#ifdef VALUE_OPT_GETFEM_TRACES
  getfem_traces = OPT_VALUE_GETFEM_TRACES;
  getfem_warnlevel = OPT_VALUE_GETFEM_WARNLEVEL;
#endif
}

/** \@brief TimeDispatcherParams -- parameters for time dispatchers
 *
 * Handle the following parameters:
 *   td_theta -- theta parametes
 */
struct TimeDispatcherParams {
  TimeDispatcherParams() : td_theta(0.0) {}
  virtual ~TimeDispatcherParams() {}
  double td_theta;
  void setUp(void);
  void echo(std::ostream &out);
  protected:
  bool print_header;
};

inline void
TimeDispatcherParams::setUp(void) {
#ifdef VALUE_OPT_TD_THETA
  param2double("td-theta", OPT_ARG(TD_THETA), td_theta);
#endif
}

/** \@brief ElasticMatParams -- parameters describing elastic material
 *
 * Handle the following parameters:
 *   E -- Young modulus
 *   nu -- Poisson ratio
 */
struct ElasticMatParams {
  ElasticMatParams() : E(1.0), nu(0.3), print_header(false) {}
  virtual ~ElasticMatParams() {}
  double E;
  double nu;
  void setUp(void);
  void echo(std::ostream &out);
  protected:
  bool print_header;
};

inline void
ElasticMatParams::setUp(void) {
#ifdef VALUE_OPT_NU
  param2double("E", OPT_ARG(E), E);
  param2double("nu", OPT_ARG(NU), nu);
#endif
}

struct ElastoPlasticMatParams : public ElasticMatParams {
  ElastoPlasticMatParams() {}
  virtual ~ElastoPlasticMatParams() {}
  double sigma0;
  void setUp(void);
  void echo(std::ostream &out);
};

inline void
ElastoPlasticMatParams::setUp(void) {
  ElasticMatParams::setUp();
#ifdef VALUE_OPT_SIGMA0
  param2double("sigma0", OPT_ARG(SIGMA0), sigma0);
#endif
}

/** \@brief GnuplotParams -- parameters for making graphs with gnuplot.
 *
 * Handle the following parameters:
 *   gptCommands -- vector of commands
 *   gpt_keep_datafiels -- boolean, if true do not delete auxiliary data files
 *   gpt_mesh_file -- name of file for saving mesh data
 */
struct GnuplotParams {
  typedef std::vector<std::string> CmdVector;
  typedef CmdVector::const_iterator CmdConstIter;
  GnuplotParams() : gpt_keep_datafiles(false),
                    gpt_mesh_file("/tmp/gpt_mesh.dat"),
                    gpt_png_size("640,480") {}
  ~GnuplotParams() {}
  CmdVector gptCommands;
  bool gpt_keep_datafiles;
  std::string gpt_mesh_file;
  std::string gpt_png_size;
  void print_commands(std::ostream &out,
                      CmdConstIter begin, CmdConstIter end,
                      const char *prefix=NULL) const;
  void setUp(void);
  void echo(std::ostream &out);
};

inline void
GnuplotParams::setUp(void) {
#ifdef VALUE_OPT_GPT_CMD
  if ( HAVE_OPT(GPT_CMD)) {
    int    dirct = STACKCT_OPT(GPT_CMD);
    const char** dirs  = STACKLST_OPT(GPT_CMD);
    while (dirct-- > 0) {
      gptCommands.push_back(std::string(*dirs++));
    }
  }
#endif
#ifdef VALUE_OPT_GPT_KEEP_DATAFILES
  gpt_keep_datafiles = OPT_ARG(GPT_KEEP_DATAFILES);
#endif
#ifdef VALUE_OPT_GPT_MESH_FILE
  if ( HAVE_OPT(GPT_MESH_FILE)) {
    gpt_mesh_file = std::string(OPT_ARG(GPT_MESH_FILE));
  }
#endif
#ifdef VALUE_OPT_GPT_PNG_SIZE
  if ( HAVE_OPT(GPT_PNG_SIZE)) {
    gpt_png_size = std::string(OPT_ARG(GPT_PNG_SIZE));
  }
#endif
}

/** \@brief GetFEMSolverParams -- parametrs for steering GetFEM solver.
 *
 * Handle the following parameters:
 *   noised -- if true prints more verbose output while solving
 *   maxiter -- maximum number of iterations
 *   residuum -- residuum value
 */
struct GetFEMSolverParams {
  GetFEMSolverParams() : residuum(1e-8), maxiter(400), noised(false) {}
  double residuum;
  int maxiter;
  int noised;
  void setUp(void);
  void echo(std::ostream &out);
};

inline void GetFEMSolverParams::setUp(void) {
#if defined(VALUE_OPT_MAXITER)
  param2double("residuum", OPT_ARG(RES), residuum);
  maxiter = OPT_VALUE_MAXITER;
  noised = atoi(OPT_ARG(NOISED));
#endif
}

/** \@brief OutputParams -- parametrs for managing output data.
 *
 * Handle the following parameters:
 */
struct OutputParams {
  OutputParams() : out_dir("./"),
                   out_policy("abort"),
                   out_file("/dev/stdout"),
                   have_out_file(false) {}
  std::string out_dir;
  std::string out_policy;
  std::string out_file;
  bool have_out_file;
  void setUp(void);
  void echo(std::ostream &out);
  public:
    static const char *validOutPolicies[];
};

inline void OutputParams::setUp(void) {
#ifdef VALUE_OPT_OUT_DIR
  out_dir = std::string(OPT_ARG(OUT_DIR));
  if (HAVE_OPT(OUT_FILE)) {
    out_file = std::string(OPT_ARG(OUT_FILE));
  }
  if (ISSEL_OPT(OUT_FILE)) {
    have_out_file = true;
  }
  te_Out_Policy opt = (te_Out_Policy)OPT_VALUE_OUT_POLICY;
  out_policy = std::string(OPT_OUT_POLICY_VAL2STR(opt));
#endif
}


/** \@brief SkewThrowParams -- parameters for skew-throw problem
 *
 * Handle the following parameters:
 *   st_alpha -- throw angle (degrees)
 *   st_v0 -- initial velocity
 *   st_x0 -- initial position X-coordinate
 *   st_y0 -- initial position Y-coordinate
 *   st_dt -- time step
 */
struct SkewThrowParams {
  SkewThrowParams() : st_alpha(45.0),
                      st_v0(1.0),
                      st_x0(0.0),
                      st_y0(0.0),
                      st_dt(0.01),
                      print_header(true) {}
  virtual ~SkewThrowParams() {}
  double st_alpha;
  double st_v0;
  double st_x0, st_y0;
  double st_dt;
  void setUp(void);
  void echo(std::ostream &out);
  protected:
  bool print_header;
};

inline void
SkewThrowParams::setUp(void) {
#ifdef VALUE_OPT_ST_ALPHA
  param2double("st-alpha", OPT_ARG(ST_ALPHA), st_alpha);
  param2double("st-v0", OPT_ARG(ST_V0), st_v0);
  param2double("st-x0", OPT_ARG(ST_X0), st_x0);
  param2double("st-y0", OPT_ARG(ST_Y0), st_y0);
  param2double("st-dt", OPT_ARG(ST_DT), st_dt);
#endif
}

} /* namespace femdk */

/*\@}*/
#endif /* FEMDK_FEMDK_PARAMS_HXX */
