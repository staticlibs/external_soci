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

# this file is based on https://github.com/SOCI/soci/blob/3.2.3/src/CMakeLists.txt
cmake_minimum_required ( VERSION 2.8.12 )
project ( soci CXX )

if ( NOT DEFINED ${PROJECT_NAME}_LOOKASIDE_DIR )
    set ( ${PROJECT_NAME}_LOOKASIDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../lookaside_soci CACHE INTERNAL "" )
endif ( )

# check deplibs cache
if ( STATICLIB_USE_DEPLIBS_CACHE )
    set ( ${PROJECT_NAME}_CACHED_LIB_PATH ${STATICLIB_DEPLIBS_CACHE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX} )
    if ( EXISTS ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        add_library( ${PROJECT_NAME} STATIC IMPORTED GLOBAL )
        set_target_properties( ${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        message ( STATUS "Using cached library: [${${PROJECT_NAME}_CACHED_LIB_PATH}]" )
        return ( )
    endif ( )
endif ( )

# core
set ( ${PROJECT_NAME}_SRC
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/blob.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/connection-parameters.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/connection-pool.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/error.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/into-type.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/once-temp-type.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/prepare-temp-type.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/procedure.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/ref-counted-prepare-info.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/ref-counted-statement.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/row.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/rowid.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/session.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/soci-simple.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/statement.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/transaction.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/use-type.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/core/values.cpp )
set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_LOOKASIDE_DIR}/core )
set ( ${PROJECT_NAME}_DEFINITIONS "" )
set ( ${PROJECT_NAME}_OPTIONS "" )

# sqlite3
if ( SOCI_ENABLE_SQLITE3 )
    file ( GLOB ${PROJECT_NAME}_SQLITE3_SRC ${${PROJECT_NAME}_LOOKASIDE_DIR}/backends/sqlite3/*.cpp )
    set ( ${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_SQLITE3_SRC} )
    set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} 
            ${${PROJECT_NAME}_LOOKASIDE_DIR}/backends/sqlite3 )
    set ( ${PROJECT_NAME}_DEFINITIONS ${${PROJECT_NAME}_DEFINITIONS} -DSOCI_ENABLE_SQLITE3 )
endif ( )

# odbc
if ( SOCI_ENABLE_ODBC )
    file ( GLOB ${PROJECT_NAME}_ODBC_SRC ${${PROJECT_NAME}_LOOKASIDE_DIR}/backends/odbc/*.cpp )
    set ( ${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_ODBC_SRC} )
    set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} 
            ${${PROJECT_NAME}_LOOKASIDE_DIR}/backends/odbc
            ${SOCI_ODBC_INCLUDE_DIR} )
    set ( ${PROJECT_NAME}_DEFINITIONS ${${PROJECT_NAME}_DEFINITIONS} -DSOCI_ENABLE_ODBC )
endif ( )

# postgres
if ( SOCI_ENABLE_POSTGRES )
    file ( GLOB ${PROJECT_NAME}_POSTGRES_SRC ${${PROJECT_NAME}_LOOKASIDE_DIR}/backends/postgresql/*.cpp )
    set ( ${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_POSTGRES_SRC} )
    set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} 
            ${${PROJECT_NAME}_LOOKASIDE_DIR}/backends/postgresql 
            ${SOCI_POSTGRES_INCLUDE_DIR} )
    set ( ${PROJECT_NAME}_DEFINITIONS ${${PROJECT_NAME}_DEFINITIONS} -DSOCI_ENABLE_POSTGRES )
endif ( )

# static provider for backends
set ( ${PROJECT_NAME}_STATICLIBS_SRC ${CMAKE_CURRENT_LIST_DIR}/../soci_static_backend_provider.cpp )

if ( ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )
    set ( ${PROJECT_NAME}_DEFINITIONS ${${PROJECT_NAME}_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS )
    set ( ${PROJECT_NAME}_OPTIONS ${${PROJECT_NAME}_OPTIONS} /wd4244 /wd4512 )
elseif ( ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU|Clang" )
    set ( ${PROJECT_NAME}_OPTIONS ${${PROJECT_NAME}_OPTIONS} -Wno-unused-variable )
endif ( )

add_library ( ${PROJECT_NAME} STATIC 
        ${${PROJECT_NAME}_SRC}         
        ${${PROJECT_NAME}_STATICLIBS_SRC} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE ${${PROJECT_NAME}_INCLUDES} )
target_compile_definitions ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DEFINITIONS} )
target_compile_options ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_OPTIONS} )
