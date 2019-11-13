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



# Motivation

Debugging C and C++ code called from R using a debugger like `gdb` is often a pain because it is difficult to
inspect the R and `Rcpp` specific data types (like variables or environments) with a debugger that
does not know the internals of these data types.

This package is an attempt to improve this situation.



# Goals

Functional requirements:

1. Inspect variable values of `R` and `Rcpp` variables

1. Optional support for modifying variable values (to try to find bug fixes during debugging)


Non-functional requirements:

1. Minimize preparation efforts for debugging

    - no need to add extra C/C++ code to be compiled (eg. no `main.cpp` with `Rinside` required)
    - no need to modify C/C++ code

1. Easy-to-use debugging helper functions

    - query R and Rcpp variables in the same debugging session
    - short function names
    - overloaded debugging helper functions to let `gdb` decide which function to call instead
      of forcing the user to find the right function name by knowing the data type



# Getting started 

To debug your own package or R code that uses C/C++ (eg. via `Rcpp`) you have
to follow these steps:

1. Install and compile this package if not already done (currently only from github, not CRAN):

```R
# install.packages("devtools")
devtools::install_github("aryoda/CppDebugHelper")
```

1. Build your package or C/C++ library called from R with debugging information

   - For R packages modify the `Makevars` file via `usethis::usethis::edit_r_makevars()`
     and add (or edit) the line `CXXFLAGS = -g3 -O0 -Wall`. Save the file.
     
     **Don't forget to remove or comment line later or you may slow down your R or newly installed packages!**

   - Clean and build your package (or C/C++ libary)

1. Open a command shell ("terminal") and cd into the location where your C/C++ source code was compiled

   If you have multiple locations you can add more locations in `gdb` later via
   the `directory` command (see `help directory` in `gdb`).

1. Start the gdb debugger debugging your own code or package:

    ```
    # open a command shell ("terminal")
    # on Linux use:
    R -d gdb
    # on Windows use
    gdb /path/to/R-3.x.x/bin/x64/Rgui.exe
    ```

1. Start R in `gdb`

   `(gdb) run   # or short: just an "r"`
   
   The R command prompt appears.
   
1. Load the `CppDebugHelper` package to "inject" the debug functions

   ```R
   library(CppDebugHelper)
   ```
   
1. Load all your packages and libraries to be able to set breakpoints in `gdb`

   - The R package to be debugged must be loaded via `library`.
   
   - C/C++ libraries you are calling directly via `.C` or `.Call` must be loaded
     via `dyn.load`.
     
1. Interrupt R to put you back to the `gdb` debugger to set breakpoints

   - On Linux: Press CTRL+C
   - On Windows: In `RGui` select the *Misc > Break to debugger* menu item
   
   In `gdb` set breakpoints, eg. in the `CppDebugHelper` test function:
   
   ```
   TODO
   ```
   
1. TODO



# Expected deliverables when this package gets released one day

1. An R package that offers low-level C/C++ functions to painlessly inspect R/Rcpp specific data types from a debugger
2. Document the options you have to debug
3. Provide a tutorial using `gdb` (incl. test functions to learn debugging)



## Planned debugging API functions

Offer public C/C++-level functions to

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
- summarize vector
- tabulation (`table` in R) with limited output (may be quite chatty)
- names of an R object
- `head` and `tail`
- NA value diagnostics
- optional: change R variable values
- optional: change Rcpp variable values
- each print function should respect `getOption("max.print")` and cut the output
  with `[ reached getOption("max.print") -- omitted 9000 entries ]`



## gdb pretty printers

For

- STL classes
- common Rcpp data types

A function for automatic installation or at least instructions would be helpful.


## Open issues

TODO



## Known limitations

General prerequisites

- GDB can only debug C++ code if you use the proper compiler and the [proper debug format](https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html) (DWARF is preferred).

A debugger is no compiler so `you`gdb` cannot

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
- perform overload resolution in expressions involving user-defined type conversions, calls to constructors, or instantiations of templates that do not exist in the program.
- handle ellipsis argument lists in expressions
- handle default arguments


See the [gdb documentation of C++ Expressions](https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html)
for what is possible and which limitations apply:


Limitations of `gdb` paired with `R` or `Rcpp` API:

- `gdb` does not apply pagination for `Rcpp::print()` output
- `gdb`'s `display` command does not work with call (`display call f()` is not allowed)
  so printing each time the program stops into `gdb` does not work
- `gdb` does not know the C++ bool constants `true` and `false` that could be used as an argument in function calls.
   Luckily `Rcpp` includes the `R` API header file `Boolean.h` which defines an enum for that
   (`typedef enum { FALSE = 0, TRUE /*, MAYBE */ } Rboolean;`) so you can use the constants `TRUE` and `FALSE` instead:

   ```
   // CPP declaration
   // void dbg_test(bool b);
   (gdb) call dbg_test(true)
   No symbol "true" in current context.
   (gdb) call dbg_test(TRUE)
   1
   ```

- `gdb` does not support function default values, eg.:

   ```
   // CPP declaration
   // void dbg_test(int a = 1, bool b = true, const char *name = "myname");
   (gdb) call dbg_test()
   Too few arguments in function call.
   (gdb) call dbg_test(10)
   Too few arguments in function call.
   (gdb) call dbg_test(10, 1, "hello")
   10-1-hello
   ```




# FAQs

## Suppress noisy startup print of `gdb` when debugging with R

```
R -d gdb --debugger-args=--quiet
```



# License

GPL-3 (see file [LICENSE](LICENSE))



# Links

- [gdb documentation](https://sourceware.org/gdb/onlinedocs/gdb)
- [Rcpp source code](https://github.com/RcppCore/Rcpp)
- [Good introduction into `Rcpp`](https://teuder.github.io/rcpp4everyone_en)
- `gdb` does not know default arguments:
  - https://stackoverflow.com/questions/58827121/how-to-use-c-default-arguments-in-the-call-command-of-gdb?noredirect=1#comment103957145_58827121
  - https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html
- [Writing R Extensions](https://cran.r-project.org/doc/manuals/R-exts.html)
  - See esp. the section [Debugging compiled code](https://cran.r-project.org/doc/manuals/R-exts.html#Debugging-compiled-code)
- [R for Windows FAQ](https://cran.r-project.org/bin/windows/base/rw-FAQ.html)
  - see esp. the section *How do I debug code that I have compiled and dyn.load-ed?* 
- [R Internals](https://cran.r-project.org/doc/manuals/r-release/R-ints.html)
