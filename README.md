# CppDebugHelper

**An [R](https://www.r-project.org/) package with functions for debuggers like ['gdb'](https://www.gnu.org/software/gdb/documentation/) to inspect R and [Rcpp](https://github.com/RcppCore/Rcpp) specific types in C and C++ based code called from R**

This packages provides functions that can be called from a debugger (eg. [gdb](https://www.gnu.org/software/gdb/documentation/))
to easily inspect (print) the content of R and [Rcpp](https://github.com/RcppCore/Rcpp) specific data types like variables or environments
on the console when debugging C or C++ called called from R.
This can be done without modifying the source code of the debugged code.

**This package is experimental and meant as a prove of concept**



# Status

Initiated in Oct, 2019 after some questions and discussions at Stackoverflow regarding debugging of `Rcpp` code with `gdb`

**Currently work in (slow or no ;-) progress... Nothings works. A lot of ideas are collected in the [RESEARCH_NOTES.txt](RESEARCH_NOTES.txt)...**



# Background

Debugging C and C++ code called from R using a debugger like `gdb` is often a pain because it is difficult to
inspect the R and `Rcpp` specific data types (like variables or environments) with a debugger that
does not know the internals of these data types.

This package is an attempt to improve this situation.


# Expected deliverables

1. An R package that offers low-level C/C++ functions to painlessly inspect R/Rcpp specific data types from a debugger
2. Document the options you have to debug
3. Provide a tutorial using `gdb` (incl. test functions to learn debugging)




# License

GPL-3 (see file [LICENSE](LICENSE))
