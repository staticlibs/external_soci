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

set ( ${PROJECT_NAME}_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../soci )

set ( ${PROJECT_NAME}_SRC 
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/blob.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/connection-parameters.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/connection-pool.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/error.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/into-type.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/once-temp-type.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/prepare-temp-type.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/procedure.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/ref-counted-prepare-info.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/ref-counted-statement.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/row.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/rowid.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/session.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/soci-simple.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/statement.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/transaction.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/use-type.cpp
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core/values.cpp )
file ( GLOB ${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_SOURCE_DIR}/src/core/*.h )
file ( GLOB ${PROJECT_NAME}_SQLITE3_SRC ${${PROJECT_NAME}_SOURCE_DIR}/src/backends/sqlite3/*.cpp )
add_library ( ${PROJECT_NAME} STATIC 
        ${${PROJECT_NAME}_SRC}         
        ${${PROJECT_NAME}_HEADERS}
        ${${PROJECT_NAME}_SQLITE3_SRC}
        ${${PROJECT_NAME}_SOURCE_DIR}/src/backends/sqlite3/soci-sqlite3.h )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE 
        ${${PROJECT_NAME}_SOURCE_DIR}/src/core 
        ${${PROJECT_NAME}_SOURCE_DIR}/src/bckends/sqlite3 )
