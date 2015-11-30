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

void test_generic(const std::string& conn) {
    soci::session sql{conn};
    soci::transaction tr(sql);
    std::vector<int> vals_out;
    vals_out.resize(1);
    soci::statement st = (sql.prepare << "select count(*) + 42", 
            soci::into(vals_out));
    st.execute();
    while (st.fetch()) {
        for (auto el : vals_out) {
            std::cout << el << std::endl;
        }
    }
    tr.commit();
}

void test_sqlite() {
    test_generic("sqlite://mydb.sqlite");
}

void test_odbc() {
    test_generic("odbc://DRIVER={FreeTDS};Server=127.0.0.1,1433;Database=master;UID=sa;PWD=root;");
}

void test_postgres() {
    test_generic("postgresql://host=127.0.0.1 port=5432 dbname=postgres user=postgres password=postgres");
}

int main() {
    try {
        test_sqlite();
//        test_odbc();
//        test_postgres();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
