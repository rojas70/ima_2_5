mysql++ 1.7.1 readme (Win32/Visual C++) version
-----------------------------------------

NOTES:
-------
1)The main workspace and project for the mysql++ API are located in the root directory
2)This project, when built, will yield the static library mysql++.lib in the /lib directory
3)This library needs the header files in the /include and /mysql/include directory, and libmysql.lib in the mysql/lib directory
4)In the /example directory a workspace and project have been made for building the examples

PROBLEMS:
----------
1)Visual C++ doesn't provide full functionality for longlongs, such as strtoll and ostream operator <<, so all longlongs have been replaced with ints in the examples
2)The example custom4.cpp could not be compiled
3)There are still some problems with the functions for static result sets. They seem to work alright with vectors, but might not work for the other STL containers

HOW TO RUN
-----------
1) You should have mysql server installed on your localhost with user root and no password.
2) Run resetdb.exe example in order to create test database.
3) Run other examples

Good Luck !

The Lazy Fox
mailto:lazyfox@foxden.dhs.org
