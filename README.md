SOCI library build for Staticlibs
=================================

This project is a part of [Staticlibs](http://staticlibs.net/).

This project contains a custom CMake script for the [SOCI](http://soci.sourceforge.net/) library.

[SOCI repository imported from Fedora EPEL lookaside](https://github.com/ojdkbuild/lookaside_soci) is used as a git submodule of this project.

Link to the [documentation](http://soci.sourceforge.net/doc/3.2/).

Supported Databases
-------------------

Support for [SQlite](http://soci.sourceforge.net/doc/3.2/backends/sqlite3.html), 
[PostgreSQL](http://soci.sourceforge.net/doc/3.2/backends/postgresql.html) and
[ODBC](http://soci.sourceforge.net/doc/3.2/backends/odbc.html) capable databases 
(including MS SQL Server, works through [FreeTDS](http://www.freetds.org/) on Linux) is included
into this build using the following CMake options:

 - `SOCI_ENABLE_SQLITE3=ON`
 - `SOCI_ENABLE_ODBC=ON`
 - `SOCI_ODBC_INCLUDE_DIR=path/to/odbc/headers`
 - `SOCI_ENABLE_POSTGRES=ON`
 - `SOCI_POSTGRES_INCLUDE_DIR=path/to/libpq/headers`

Application should be linked with the appropriate client libraries, 
[external_sqlite](https://github.com/staticlibs/external_sqlite.git) build can be used
for SQlite library.

[Oracle](http://soci.sourceforge.net/doc/3.2/backends/oracle.html), 
[DB2](http://soci.sourceforge.net/doc/3.2/backends/db2.html), 
[MySQL](http://soci.sourceforge.net/doc/3.2/backends/mysql.html) and
[Firebird](http://soci.sourceforge.net/doc/3.2/backends/firebird.html) are
also supported by SOCI and can be enabled with minor build/code changes.

How to build
------------

[CMake](http://cmake.org/) is required for building.

[pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config/) utility is used for dependency management.
For Windows users ready-to-use binary version of `pkg-config` can be obtained from [tools_windows_pkgconfig](https://github.com/staticlibs/tools_windows_pkgconfig) repository.
See [PkgConfig](https://github.com/staticlibs/wiki/wiki/PkgConfig) for Staticlibs-specific details about `pkg-config` usage.

[GNU Awk](https://www.gnu.org/software/gawk/) and [Tcl/Tk](http://www.tcl.tk/) are also required for building SQLite,
Windows users can obtain ready-to-use distributions from [tools_windows_awk](https://github.com/staticlibs/tools_windows_awk)
and [tools_windows_tcl](https://github.com/staticlibs/tools_windows_tcl) repositories.

To build the library on Windows using Visual Studio 2013 Express run the following commands using
Visual Studio development command prompt 
(`C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts\VS2013 x86 Native Tools Command Prompt`):

    git clone --recursive https://github.com/staticlibs/external_sqlite.git
    git clone --recursive https://github.com/staticlibs/external_soci.git
    cd external_soci
    mkdir build
    cd build
    cmake ..
    msbuild external_soci.sln

Cloning of [external_sqlite](https://github.com/staticlibs/external_sqlite) is not required on Linux - 
system SQLite library will be used instead.

See [StaticlibsToolchains](https://github.com/staticlibs/wiki/wiki/StaticlibsToolchains) for 
more information about the toolchain setup and cross-compilation.

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2016-10-29**

 * version 3.2.3-2
 * use pre-patched SOCI from Fedora EPEL lookaside

**2016-01-17**

 * version 3.2.3.1
 * minor CMake changes

**2015-11-30**

 * version 3.2.3.0
 * initial public version
