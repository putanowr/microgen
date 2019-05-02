/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
/** \addtogroup core */
/*\@{*/
/** \file femdk_types.hxx
 *  Types and definition used all over the whole FEMDK library.
 */

#ifndef FEMDK_TYPES_HXX 
#define FEMDK_TYPES_HXX

#include "femdk_config.h"
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>


#include <iostream>
#include <bitset>
namespace femdk {

typedef enum {
  SIMPLICAL_MESH,
  CUBICAL_MESH,
  MIXED_MESH
} mesh_family_t;

typedef enum {
  ELASTIC_MAT,
  PLASTIC_MAT,
  ELASTO_PLASTIC_MAT
} material_model_t;

typedef enum {
  GEOM_BGD,
  GEOM_GMSH,
  GEOM_IGEOM,
  GEOM_MODEL_MAX /* sentinel keep it last */
} geom_type_t;

typedef enum {
  MESH_GETFEM,
  MESH_GMSH,
  MESH_MOAB,
  MESH_TYPE_MAX /* sentinel keep it last */
} mesh_type_t;

geom_type_t str2geom_type(const std::string &name);
std::string geom_type2str(geom_type_t type);

mesh_type_t str2mesh_type(const std::string &name);
std::string mesh_type2str(mesh_type_t type);

mesh_family_t str2mesh_family(const char *name);
std::string mesh_family2str(mesh_family_t value);

material_model_t str2material_model(const char *name);
std::string material_model2str(material_model_t value);

typedef boost::property_tree::ptree ConfigData;
typedef boost::property_tree::ptree::const_iterator ConfigDataIter;

/** Namespace for summary flags */
namespace sf {
typedef std::bitset<2> flag;
const flag normal =    flag(std::string("00"));
const flag detailed =  flag(std::string("01"));
const flag recursive = flag(std::string("10"));
inline bool check(const flag &flg, const flag &mask) {
  flag tmp = (flg & mask);
  return tmp == mask;
}
inline void unset(flag &flg, const flag &mask) {
  flg ^= mask;
}

} /*namespace sf */


} /* namespace femdk */

/*\@}*/
#endif /* FEMDK_TYPES_HXX */
