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
 * File:   soci_test.cpp
 * Author: alex
 *
 * Created on November 29, 2015, 9:13 PM
 */

#include <iostream>

#include "soci.h"
#include "soci-sqlite3.h"

namespace soci{
namespace dynamic_backends {

void register_backend(std::string const&, soci::backend_factory const&) {
}

soci::backend_factory const& get(std::string const&) {
    return *soci::factory_sqlite3();
}

}
}

void test_sqlite() {
    soci::session sql(soci::sqlite3, "mydb.sqlite");
    int count;
    sql << "select count(*) + 42 FROM sqlite_master", soci::into(count);
    std::cout << count << std::endl;
}

int main() {
    try {
        test_sqlite();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
