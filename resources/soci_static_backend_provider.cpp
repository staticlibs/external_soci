/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   soci_static_backend_provider.cpp
 * Author: alex
 * 
 * Created on November 30, 2015, 1:18 PM
 */

#include <exception>

#include "backend-loader.h"

#include "soci.h"
#ifdef SOCI_ENABLE_SQLITE3
#include "soci-sqlite3.h"
#endif // SOCI_ENABLE_SQLITE3
#ifdef SOCI_ENABLE_ODBC
#include "soci-odbc.h"
#endif // SOCI_ENABLE_ODBC
#ifdef SOCI_ENABLE_POSTGRES
#include "soci-postgresql.h"
#endif // SOCI_ENABLE_POSTGRES

namespace soci {
namespace dynamic_backends {

namespace { // anonymous

std::vector<std::string>& get_empty_vector() {
    static std::vector<std::string> empty;
    return empty;
}

} // namespace

soci::backend_factory const& get(std::string const& name) {
#ifdef SOCI_ENABLE_SQLITE3
    if ("sqlite3" == name || "sqlite" == name) return soci::sqlite3;
#endif // SOCI_ENABLE_SQLITE3
#ifdef SOCI_ENABLE_ODBC
    if ("odbc" == name) return soci::odbc;
#endif // SOCI_ENABLE_ODBC
#ifdef SOCI_ENABLE_POSTGRES
    if ("postgresql" == name || "postgres" == name) return soci::postgresql;
#endif // SOCI_ENABLE_POSTGRES
    throw std::runtime_error("Unsupported SOCI backend: [" + name + "]");
}

// no-op symbols
std::vector<std::string> list_all() { return get_empty_vector(); }
std::vector<std::string>& search_paths() { return get_empty_vector(); }
void register_backend(const std::string&, const std::string&) { }
void register_backend(const std::string&, const soci::backend_factory&) { }
void unload(const std::string&) { }
void unload_all() { }

}
}
