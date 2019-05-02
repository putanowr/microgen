/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** 
 *  Support for type conversion.
 */

#include <string.h>
#include "femdk_types.hxx"
#include "femdk_except.hxx"

namespace femdk {

static const char *mesh_type_names[MESH_TYPE_MAX] = { "getfem",
                                                        "gmsh",
                                                        "moab"
                                                      };
static const char *geom_model_names[GEOM_MODEL_MAX] = { "bgd",
                                                        "gmsh",
                                                        "igeom"
                                                      };
std::string
mesh_type2str(mesh_type_t val) {
  if (val < sizeof(mesh_type_names)/sizeof(char *)) {
    return std::string(mesh_type_names[val]);  
  } else {
    throw FEMDKException("Internal error: invalid value for mesh_type_t");
  }
}

mesh_type_t 
str2mesh_type(const std::string &name) {
  for (int i=0; i<MESH_TYPE_MAX; i++) {
     if (name == mesh_type_names[i]) {
        return mesh_type_t(i); 
     }
  }
  std::string msg="Invalid mesh model type: ";
  msg +=name;
  throw FEMDKInvalidArgs(msg);
  return MESH_TYPE_MAX;
}

std::string
geom_type2str(geom_type_t val) {
  if (val < sizeof(geom_model_names)/sizeof(char *)) {
    return std::string(geom_model_names[val]);  
  } else {
    throw FEMDKException("Internal error: invalid value for geom_type_t");
  }
}

geom_type_t 
str2geom_type(const std::string &name) {
  for (int i=0; i<GEOM_MODEL_MAX; i++) {
     if (name == geom_model_names[i]) {
        return geom_type_t(i); 
     }
  }
  std::string msg= std::string("Invalid geom model type: ");
  msg += name;
  throw FEMDKInvalidArgs(msg);
  return GEOM_MODEL_MAX;
}

std::string
mesh_family2str(mesh_family_t val) {
   switch(val) {
     case SIMPLICAL_MESH:
        return std::string("simplical");
     case CUBICAL_MESH:
        return std::string("cubical");
     case MIXED_MESH:
        return std::string("mixed");
     default: {
       throw FEMDKException("Internal error: invalid value for mesh_family_t");
     }
   }
}

mesh_family_t str2mesh_family(const char *name) {
  if (strcmp(name, "simplical") == 0) {
     return SIMPLICAL_MESH;
  } else if (strcmp(name, "cubical") == 0) {
     return CUBICAL_MESH;
  } else if (strcmp(name, "mixed") == 0) {
     return MIXED_MESH;
  } else {
    std::string msg="Invalid mesh family type: ";
    msg +=name;
    throw FEMDKInvalidArgs(msg);
  }
}

std::string
material_model2str(material_model_t val) {
   switch(val) {
     case ELASTIC_MAT:
        return std::string("elastic");
     case PLASTIC_MAT:
        return std::string("plastic");
     case ELASTO_PLASTIC_MAT:
        return std::string("elasto-plastic");
     default: {
       throw FEMDKException("Internal error: invalid value for material_model_t");
     }
   }
}

material_model_t str2material_model(const char *name) {
  if (strcmp(name, "elastic") == 0) {
     return ELASTIC_MAT;
  } else if (strcmp(name, "plastic") == 0) {
     return PLASTIC_MAT;
  } else if (strcmp(name, "elasto-plastic") == 0) {
     return ELASTO_PLASTIC_MAT;
  } else {
    std::string msg="Invalid material model type: ";
    msg +=name;
    throw FEMDKInvalidArgs(msg);
  }
}


} /* namespace femdk */
