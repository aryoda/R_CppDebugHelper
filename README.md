# CppDebugHelper

**An [R](https://www.r-project.org/) package with functions for debuggers like ['gdb'](https://www.gnu.org/software/gdb/documentation/) to inspect R and [Rcpp](https://github.com/RcppCore/Rcpp) specific types in C and C++ based code called from R**

This packages provides functions that can be called from a debugger (eg. [gdb](https://www.gnu.org/software/gdb/documentation/))
to easily inspect (print) the content of R and [Rcpp](https://github.com/RcppCore/Rcpp) specific data types like variables or environments
on the console when debugging C or C++ called called from R.
This can be done without modifying the source code of the debugged code.



# Status

Initiated in Oct, 2019 after some questions and discussions at Stackoverflow regarding debugging of `Rcpp` code with `gdb`

**Currently work in (slow or no ;-) progress...**



# Background

Debugging C and C++ code called from R is pain because it is difficult to
inspect the 



# License

GPL-3 (see file [LICENSE](LICENSE))
