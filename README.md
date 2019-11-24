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

TODO

- Show problems and solutions (offered by this package) as table
- Explain the reasons for the problems



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


# Functions and supported data types

You can call the debug functions `dbg_*` in `gdb` via the `call` command, eg.

```
(gdb) call dbg_ls()
(gdb) call dbg_str("myVar_in_global_env")
(gdb) call dbg_attributes(x)
(gdb) call dbg_print(x)
(gdb) call dbg_print(dbg_table(y))
...
```

The supported combination of functions and the data type of the first argument are marked with an `x` in the cell.

For non-obvious cases the meaning of the first argument for the function is described in the cell.

The last column (`...`) contains names of functions specialized for the data type.

**TODO: Add row to show signatures to make this table more cheat-sheet alike**

| Input Data Type  | dbg_ls()     | dbg_str()              | dbg_print()         | dbg_attributes() | dbg_table()              | dbg_get()     | dbg_subset()           | ... |
|------------------|:------------:|:----------------------:|:-------------------:|:----------------:|:------------------------:|:-------------:|:----------------------:|:---:|
| *Function description* | *List objects* | *Print object structure* | *Print object value*  | *Print attributes* | *Create contingency table* | *Find object in env* | *Filter objects* |     |
| *Corresponding R function* | `ls()`       | `str()`                | `print()`           | `attributes()`   | `table()`                | `get()`       | `myVar[begin:end]`     |     |
| *Return type*    |              |                        |                     |                  | *class "table"*          | *found object* | *same type as input*   |     |
| *Side effects*   | print        | print                  |  print              |  print           |                          |               |                        |     |
| char *           | x            | x                      | object name (in global env) | object name (in global env) |                        | object name (in global env) |    |     |
| std::string      |              |                        |                     |                  |                          |               |                        |     |
| Rcpp::String     |              |                        | prints the string content (!)b |            |                          |               |                        |     |
| SEXP             |              | x                      |  x                  |  x                | x                       |               |                        |     |
| Environment      | x            |                        | prints names of all objects in the env | prints attributes of an object in the env | env to search a named object     | | | |
| ComplexVector    |              | x                      |  x                  |  x               |                          |               |                        |     |
| DataFrame        |              | x                      |  x                  |  x               |                          |               |                        |     |
| IntegerVector    |              | x                      |  x                  |  x               |                          |               |                        |     |
| LogicalVector    |              | x                      |  x                  |  x               |                          |               |                        |     |
| NumericVector    |              | x                      |  x                  |  x               | x                        |               |                        |     |
| DoubleVector     |              | x                      |  x                  |  x               |                          |               |                        |     |
| RawVector        |              | x                      |  x                  |  x               |                          |               |                        |     |
| CharacterVector  |              | x                      |  x                  |  x               |                          |               |                        |     |
| StringVector     |              | x                      |  x                  |  x               |                          |               |                        |     |
| GenericVector    |              | x                      |  x                  |  x               |                          |               |                        |     |
| ExpressionVector |              | x                      |  x                  |  x               |                          |               |                        |     |
| Rcpp::List       |              | x                      |  x                  |  x               |                          |               |                        |     |
| DateVector       |              | x                      |  x                  |  x               |                          |               |                        |     |
| DatetimeVector   |              | x                      |  x                  |  x               |                          |               |                        |     |
| ... Matrices...  |              |                        |                     |                  |                          |               |                        |     |

*Note: This table was created using http://www.tablesgenerator.com/markdown_tables*



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
     and add (or edit) the line `CXXFLAGS = -g3 -O0 -Wall` (for Linux only).
     For Windows you have to add `CXXFLAGS = -g3 -std=c++14`. Save the file.
     
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
3. Provide a tutorial using `gdb` (incl. test functions as a separate R package to learn debugging)



## Planned debugging API functions

Offer public C/C++-level functions to

- WIP (`dbg_print`): inspect Rcpp's *Vector, *Matrix and List data types
- DONE (`dbg_print`): inspect SEXP types (native R)
- DONE (`dbg_print(Environment, varname)`): inspect a variable by name (along the search path)
- WIP (`dbg_print`): inspect `data.frame`s (eg. via something like `head` to print the first and last n rows)
- WIP (`dbg_attributes`): support simple attribute queries like
  - DONE: inspect all attributes
  - inspect a single attribute
    - convenience function for the class attribute
    - names of an R object (`names` attribute?)
- DONE (`dbg_ls`): list all variables in an environment (default: global)
- DONE (`dbg_ls`): inspect R variable in an environment (default: global)
- WIP (`dbg_subset`): simple vector filtering for important R and Rcpp data types (element range with range checks) (idea: as piped functions)
- subset `data.frame`s (rows and columns)
- DONE (`dbg_str`): inspect the `str()` of an R variable
- WIP (`dbg_str`): inspect the `str()` of Rcpp data types
- WIP (`dbg_table`): tabulation (`table` in R) with limited output (may be quite chatty)
- summarize vector (like `summary` in R; Rcpp knows "only" `table`) (idea: as piped functions)
- `head` and `tail` (idea: as piped functions)
- NA value diagnostics
- print encoding of strings and string vectors
- common STL containers (but gdb offers pretty printers for that AFAIK) 
- optional: change R variable values (eg. via an overloaded function names `dbg_assign()`)
- optional: change Rcpp variable values
- optional: `get` function that returns a variable from an environment to be used for filtering
- optional: support for data types of packages derived from `Rcpp` (eg. ` RcppArmadillo`)
- optional: show how to use logging in Rcpp code that is synchronised with logging in R (hopefully even the same logging package)

**Note:** Each print function should respect `getOption("max.print")` and cut the output
with `[ reached getOption("max.print") -- omitted 9000 entries ]`



## gdb pretty printers

For

- STL classes
- common Rcpp data types

A function for automatic installation or at least instructions would be helpful.


## Open issues

TODO



## Known limitations

### General prerequisites

- GDB can only debug C++ code if you use the proper compiler and the [proper debug format](https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html) (DWARF is preferred).

### A debugger is no compiler

So `gdb` cannot

- bring back optimized code in a more logical structure to debug it
- undo function inlining
- handle expressions that perform overload resolution in expressions involving
  - user-defined type conversions
  - calls to constructors or
  - instantiations of templates that do not exist in the program.
- instantiate a "simple"" thing like a string (without complex steps to allocate memory and write the string into it)
  - See
    - https://stackoverflow.com/questions/7429462/creating-c-string-in-gdb
    - https://stackoverflow.com/questions/42462860/calling-stdbasic-string-in-gdb?noredirect=1&lq=1
    - https://www.toptip.ca/2013/04/change-value-of-stdstring-in-gdb.html
    - https://stackoverflow.com/questions/2502314/setting-an-stdstring-variable-value-from-gdb
    - https://stackoverflow.com/questions/54240951/how-to-change-the-c-string-value-in-eclipse-debugger?noredirect=1&lq=1
  - Note: Because a `std::string` is not a primitive data type, it cannot be changed using `(gdb) set var myvar="asdf"`
    but by calling its `assign` member function.
- handle ellipsis argument lists in expressions
  - https://stackoverflow.com/a/58867535/4468078
- handle default arguments
  - https://stackoverflow.com/a/58867535

See the [gdb documentation of C++ Expressions](https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html)
for what is possible and which limitations apply:



### Limitations of `gdb` regarding the `R` and `Rcpp` API

- You can call most of the `dbg_*` functions only from within your C/C++ code (when a breakpoint is hit)
  but not by interrupting the R main loop (pressing Strg+C at the R command prompt) since this leads
  to strange `gdb` error messages when doing `(gdb) call dbg_ls()` or `(gdb) call dbg_str("myVar")` for example.
- Local R/Rcpp variables exist and can be used to call `dbg_*` functions **before** they are initialized.
  This may cause segfaults (of course):
  
  ```
  (gdb) n
  19	    Environment e = Rcpp::Environment::global_env();
  (gdb) p e
  $7 = {
    <Rcpp::PreserveStorage<Rcpp::Environment_Impl<Rcpp::PreserveStorage> >> = {
      data = 0x7fffffffb940 }, 
    <Rcpp::SlotProxyPolicy<Rcpp::Environment_Impl<Rcpp::PreserveStorage> >> = {<No data fields>}, 
    <Rcpp::AttributeProxyPolicy<Rcpp::Environment_Impl<Rcpp::PreserveStorage> >> = {<No data fields>}, 
    <Rcpp::RObjectMethods<Rcpp::Environment_Impl<Rcpp::PreserveStorage> >> = {<No data fields>}, 
    <Rcpp::BindingPolicy<Rcpp::Environment_Impl<Rcpp::PreserveStorage> >> = {<No data fields>}, <No data fields>}
  (gdb) call dbg_print(e)
  8
  Program received signal SIGSEGV, Segmentation fault.
  0x00007ffff7836a80 in getAttrib0 (vec=0x7fffffffb940, name=0x55555576c9a8) at attrib.c:142
  ...
  ```
  
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

## Where are the divers R config files like `Makevars` stored?

```
# Where is my home folder?
path.expand("~")
```

```
# Where is R's default Makefile configuration?
file.path(R.home("etc"), "Makeconf")
[1] "/usr/lib/R/etc/Makeconf"
# In this file you will find the build flags (variables) like: PKG_CXXFLAGS, PKG_LIBS...
```

```
# Where is user Makevars file (which overrides the default make file generated by R)?
usethis::edit_r_makevars()
```



## I have compiler errors or warning when building the package on Windows

If you get errors or warnings like

- *Warning: function uses 'auto' type specifier without trailing return type*
- *Warning: 'auto' changes meaning in C++11; please remove it*

the used CPP compiler uses an older C++ standard as default.

To build successfully you have to enable a newer C++ standard (at least C++14) in the `Makevars` file:

```
CXXFLAGS = -g3 -O0 -Wall -std=c++14
```

For details see:

- https://stackoverflow.com/questions/44798728/warning-function-uses-auto-type-specifier-without-trailing-return-type
- https://stackoverflow.com/questions/25170251/auto-changes-meaning-in-c11-please-remove-it-what-does-this-mean



## How to debug on Windows (`gdb` has no `-d` switch)?

On Linux you can debug an R script or R package with `gdb` via `R -d gdb`.
This start R and attaches `gdb` as debugger.

The `gdb` version delivered on Windows via the `Rtools` does not support the `-d` switch
(perhaps because you cannot send a signal to running processes to stop the execution for debugging
like Linux does eg. with the shortcut Ctrl+C).

But: To set a breakpoint in Windows DLL it must be loaded first and this requires R to be started.

Once you have started R you cannot pause R (with out-of-the-box Windows ways) to call the debugger.

The solution is to "debug" the `RGui.exe` which has a built-in menu item *Misc > Break to debugger*.
This allows you the pause R and work in `gdb`:

```
gdb /path/to/R/bin/x64/Rgui.exe
```

To make the source code visible in `gdb` you also

- have to be in the folder where your source code is located or
- use the `directory` command in `gdb` to add the path to your source code

For details see the [R for Windows FAQ](https://cran.r-project.org/bin/windows/base/rw-FAQ.html#How-do-I-debug-code-that-I-have-compiled-and-dyn_002eload_002ded_003f)



## Suppress noisy startup print of `gdb` when debugging with R

```
R -d gdb --debugger-args=--quiet
```


## How can I pass additional arguments to `gdb`?

You can use the R argument `--debugger-args=ARGS` where `ARGS` are arguments to the debugger.

```
R -d gdb --debugger-args=--quiet
```


## How can I use the debugging helper functions in `gdb` directly without R?

The easiest way to load the debugging helper functions is via R's `library(CppDebugHelper)` command
but if you want to debug an application that does use R directly you
can load the underlying shared library using the `LD_PRELOAD` environment variable:

```
gdb myApp
(gdb) set environment LD_PRELOAD ./CppDebugHelper.so
(gdb) run
(gdb) # Press Ctrl+C to break R into gdb
(gdb) # verify that the library has been loaded by gdb
(gdb) info sharedlibrary 
From                To                  Syms Read   Shared Object Library
0x00007ffff7bbc040  0x00007ffff7bca2e0  Yes         ./CppDebugHelper.so
...
(gdb) # The debug functions are now available, eg.
(gdb) ptype dbg_as_std_string("hello world")
```

See:

- [Load an additional shared library in gdb to inject debugging helper functions](https://stackoverflow.com/q/58888795)
- [How to use gdb with LD_PRELOAD](https://stackoverflow.com/q/10448254)
- [What is the LD_PRELOAD trick?](https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick)
- [What is preloading?](https://blog.cryptomilk.org/2014/07/21/what-is-preloading/)


## During debugging with `gdb` on Windows I see a lot of warning containing `attribute.cpp(92)\dwmapi.dll`. Why?

You can see a lot of warning similar to this one:

> windows\dwm\dwmapi\attribute.cpp(92)\dwmapi.dll!00007FFFAD51594E: (caller: 00007FFFABCA071A) ReturnHr(30) tid(10a0) 80070006 The handle is invalid.

This is a Windows 10 bug. It seems Microsoft has forgotten to disable tracing code before releasing this DLL.

You can ignore these warnings (even though it is annoying to be flooded with them).

For details see:
https://social.msdn.microsoft.com/Forums/en-US/3a5a145a-c13d-4898-bb61-a5baadc9332f/why-am-i-getting-hundreds-of-weird-messages-in-debug-output-window



# License

GPL-3 (see file [LICENSE](LICENSE))



# Links

## `gdb`

- [gdb documentation](https://sourceware.org/gdb/onlinedocs/gdb)
- TODO Links to gdb tutorials + cheat sheets
  - [YoLinux.com GDB command cheat sheet](http://www.yolinux.com/TUTORIALS/GDB-Commands.html)
  - [GDB to LLDB command map](https://lldb.llvm.org/use/map.html#examining-variables)
- `gdb` does not know default arguments:
  - https://stackoverflow.com/questions/58827121/how-to-use-c-default-arguments-in-the-call-command-of-gdb?noredirect=1#comment103957145_58827121
  - https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html
- [SO question: Better variable exploring when debugging C++ code (answer explains `gdb`s pretty printers)](https://stackoverflow.com/questions/3651862/better-variable-exploring-when-debugging-c-code-with-eclipse-cdt?rq=1)

## `Rcpp`

- [Rcpp source code](https://github.com/RcppCore/Rcpp)
- [Good introduction into `Rcpp`](https://teuder.github.io/rcpp4everyone_en)
- [Rcpp Gallery: Working with Rcpp StringVector](https://gallery.rcpp.org/articles/working-with-Rcpp-StringVector/)
- [Advanced R: High performance functions with Rcpp (Hadley Wickham)](http://adv-r.had.co.nz/Rcpp.html) 
- [Table: Correspondance of data types between R, Rcpp an dC++](https://teuder.github.io/rcpp4everyone_en/070_data_types.html)

## `R` API

- [Advanced R: R's C interface (Hadley Wickham)](http://adv-r.had.co.nz/C-interface.html)
- [Writing R Extensions: Debugging compiled code](https://cran.r-project.org/doc/manuals/R-exts.html#Debugging-compiled-code)
- [Writing R Extensions: The R API](https://cran.rstudio.com/doc/manuals/r-devel/R-exts.html#The-R-API)
- [R for Windows FAQ](https://cran.r-project.org/bin/windows/base/rw-FAQ.html)
  - see esp. the section *How do I debug code that I have compiled and dyn.load-ed?* 
- [R Internals](https://cran.r-project.org/doc/manuals/r-release/R-ints.html)

