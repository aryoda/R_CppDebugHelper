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



## Planned debugging API functions

Off public C/C++-level functions to

- inspect Rcpp's *Vector, *Matrix and List data types
- inspect SEXP types (native R)
- inspect `data.frame`s (eg. via something like `head` to print the first and last n rows)
- support simple attribute queries like
  - inspect all attributes
  - inspect a single attribute
- list all variables in an environment (default: global)
- inspect R variable in an environment (default: global)
- list the `search()` path as basis to get the i-th environment
- inspect a variable by name (along the search path)
- simple vector filtering for important R and Rcpp data types (element range with range checks)
- common STL containers (but gdb offers pretty printers for that AFAIK) 
- inspect the `str()` of an R variable
- inspect the `str()` of Rcpp data types
- change R variable values
- change Rcpp variable values



## gdb pretty printers

For

- STL classes
- common Rcpp data types

A function for automatic installation or at least instructions would be helpful.


## Open issues

TODO



## Known limitations

A debugger is no compiler so you can't

- bring back optimized code in a more logical structure to debug it
- undo function inlining
- call code for templated functions that the compiler has not instantiated (since not needed)
- instantiate a simple thing like strings (without complex steps to allocate memory and write the string into it)
  to be used to call a function which requires a string.
  - Because an std::string is not a primitive data type, it cannot be changed using `(gdb) set var myvar="asdf"`
  - See
    - https://stackoverflow.com/questions/7429462/creating-c-string-in-gdb
    - https://stackoverflow.com/questions/42462860/calling-stdbasic-string-in-gdb?noredirect=1&lq=1
    - https://www.toptip.ca/2013/04/change-value-of-stdstring-in-gdb.html
    - https://stackoverflow.com/questions/2502314/setting-an-stdstring-variable-value-from-gdb
    - https://stackoverflow.com/questions/54240951/how-to-change-the-c-string-value-in-eclipse-debugger?noredirect=1&lq=1

Limitations of `gdb` paired with `Rcpp` or `R` API:

- `gdb` does not apply pagination for `Rcpp::print()` output
- `gdb`'s `display` command does not work with call (`display call f()` is not allowed)
  so printing each time the program stops into `gdb` does not work


# FAQs

## Suppress noisy startup print of `gdb` when debugging with R

```
R -d gdb --debugger-args=--quiet
```



# License

GPL-3 (see file [LICENSE](LICENSE))



# Links

- Rcpp source code: https://github.com/RcppCore/Rcpp
- Good introduction into `Rcpp`: https://teuder.github.io/rcpp4everyone_en
