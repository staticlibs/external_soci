# Copyright 2015, alex at staticlibs.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

# project
project ( external_soci CXX C )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 3.2.3.1 )
set ( ${PROJECT_NAME}_DESCRIPTION "SOCI library build for Staticlibs" )
set ( ${PROJECT_NAME}_URL https://github.com/staticlibs/external_soci )
include ( ${CMAKE_CURRENT_LIST_DIR}/resources/macros.cmake )

# options
option ( SOCI_REMOVE_AUTOPTR "Apply patch to version 3.2.3 to remove auto_ptr" ON )
option ( SOCI_ENABLE_SQLITE3 "Enable SQlite3 backend" ON )
option ( SOCI_ENABLE_ODBC "Enable SQlite3 backend" OFF )
set ( SOCI_ODBC_INCLUDE_DIR "" CACHE STRING "Path to the ODBC headers" )
option ( SOCI_ENABLE_POSTGRES "Enable PostgreSQL backend" OFF )
set ( SOCI_POSTGRES_INCLUDE_DIR "" CACHE STRING "Path to the PostgreSQL headers" )

# apply patch
if ( SOCI_REMOVE_AUTOPTR AND ( NOT DEFINED SOCI_REMOVE_AUTOPTR_APPLIED ) )
    message ( STATUS "Applying patch to soci-3.2.3 sources to remove auto_ptr" )
    execute_process ( COMMAND git reset --hard HEAD
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/soci )
    execute_process ( COMMAND git apply ${CMAKE_CURRENT_LIST_DIR}/resources/remove_autoptr_323.patch
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/soci )
    set ( SOCI_REMOVE_AUTOPTR_APPLIED "" CACHE INTERNAL "" )
endif ( )

# standalone build
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
endif ( )
if ( NOT DEFINED STATICLIB_TOOLCHAIN )
    if ( NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" ) # system dependencies implied on other platforms
        external_soci_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/../external_sqlite )
    endif ( )
endif ( )

# dependencies
set ( ${PROJECT_NAME}_DEPS sqlite3 )
external_soci_pkg_check_modules ( ${PROJECT_NAME}_DEPS_PC REQUIRED ${PROJECT_NAME}_DEPS )

# soci library
add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/resources/soci_323_cmake ${CMAKE_CURRENT_BINARY_DIR}/soci )
add_custom_target ( ${PROJECT_NAME} DEPENDS soci )
if ( TARGET external_sqlite )
    add_dependencies ( soci external_sqlite )
endif ( )
if ( ( NOT STATICLIB_USE_DEPLIBS_CACHE ) OR
        ( NOT EXISTS ${STATICLIB_DEPLIBS_CACHE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}soci${CMAKE_STATIC_LIBRARY_SUFFIX} ) )
    target_include_directories ( soci BEFORE PRIVATE ${${PROJECT_NAME}_DEPS_PC_INCLUDE_DIRS} )
endif ( )

# pkg-config
set ( ${PROJECT_NAME}_MODULE soci )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${CMAKE_CURRENT_LIST_DIR}/soci/src/core" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -lsoci" )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/soci.pc )
