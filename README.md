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
  - templates: only instances available that are really used in the "library under debugging"
- ease of use (compared to plain R and Rcpp API)
  - missing easy subsetting options (may flood the debugger console during printing)




# Goals

Functional requirements:

1. Inspect variable values and structures of `R` and `Rcpp` variables during debugging

1. Debugging support for C++ code

1. Optional: Debugging support for plain C code

1. Optional: Support for modifying variable values (to try to find bug fixes during debugging)



Non-functional requirements:

1. No need to [recompile R on Windows for debugging](https://cran.r-project.org/bin/windows/base/rw-FAQ.html#How-do-I-debug-code-that-I-have-compiled-and-dyn_002eload_002ded_003f) (unless you want to debug R itself and are resistent against *build headaches* ;-)

1. Minimize preparation efforts for debugging

    - no need to add extra C/C++ code (eg. `main.cpp` with `Rinside`)
    - no need to modify existing C/C++ code

1. Easy-to-use debugging helper functions

    - query R and Rcpp variables in the same debugging session
    - short function names
    - overloaded debugging helper functions to let `gdb` decide which function to call instead
      of forcing the user to find the right function name by knowing the data type

1. Support for at least `gdb` and optionally the `LLDB` debugger




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

**TODO: Add row to show signatures to make this table more cheat-sheet alike. SEXP should always return an SEXP. Show example calls...**

| Input Data Type  | dbg_ls()     | dbg_str()              | dbg_print()         | dbg_attributes() | dbg_table()              | dbg_get()     | dbg_subset()           | Others... |
|------------------|:------------:|:----------------------:|:-------------------:|:----------------:|:------------------------:|:-------------:|:----------------------:|:---:|
| *Function description* | *List objects* | *Print object structure* | *Print object value*  | *Print attributes* | *Create contingency table* | *Find object in env* | *Filter objects* |     |
| *Corresponding R function* | `ls()`       | `str()`                | `print()`           | `attributes()`   | `table()`                | `get()`       | `myVar[begin:end]`     |     |
| *Return type*    |              |                        |                     |                  | *IntegerVector of class "table"*          | *SEXP* | *same type as input object*   |     |
| *Side effects*   | print        | print                  |  print              |  print           |                          |               |                        |     |
| char *           |              | object name (in global env) | object name (in global env) | object name (in global env) |                        | object name (in global env) |    | dbg_as_std_string(x) |
| std::string      |              |                        | TODO (semantics?)   |                  |                          |               |                        |     |
| Rcpp::String     |              |                        | prints the string content |            |                          |               |                        |     |
| SEXP             |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| Environment      | print names of all objects in the env | str() of an object in the env | prints names of all objects in the env | prints attributes of an object in the env | env to search a named object | get object from the env | | |
| ComplexVector    |              | x                      |  x                  |  x               | (not supported in R)     |               | x                      |     |
| DataFrame        |              | x                      |  x                  |  x               | (not supported)          |               | x (filters **rows** like R: `df[begin:end, ]`)      |     |
| IntegerVector    |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| LogicalVector    |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| NumericVector    |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| DoubleVector     |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| RawVector        |              | x                      |  x                  |  x               | (not supported in R)     |               | x                      |     |
| CharacterVector  |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| StringVector     |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| ExpressionVector |              | x                      |  x                  |  x               | (not supported in R)     |               | x                      |     |
| GenericVector    |              | x                      |  x                  |  x               | (not supported in Rcpp)  |               | x                      |     |
| Rcpp::List       |              | x                      |  x                  |  x               | (not supported by Rcpp)  |               | x                      |     |
| DateVector       |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| DatetimeVector   |              | x                      |  x                  |  x               | x                        |               | x                      |     |
| ... Matrices...  |              |                        |                     |                  |                          |               |                        |     |

*Note: This table was initially created using http://www.tablesgenerator.com/markdown_tables*



# Getting started 

To debug your own package or R code that uses C/C++ (eg. via `Rcpp`) you have
to follow these steps:

1. Install and compile this package if not already done (currently only from github, not CRAN):

```R
# install.packages("devtools")
devtools::install_github("aryoda/CppDebugHelper")
```

1. Build your package or C/C++ library called from R with debugging information

   - For R packages modify the `Makevars` file via `usethis::edit_r_makevars()`
     and add (or edit) the line `CXXFLAGS = -g3 -O0 -Wall` (for Linux only).
     For Windows you have to add `CXXFLAGS = -g3 -std=c++11`. Save the file.
     
     **Don't forget to remove or comment the line later or you may slow down your R or newly installed packages!**

   - Clean and build your package (or C/C++ libary)

1. Open a command shell ("terminal") and cd into the location where your C/C++ source code was compiled

   If you have multiple locations you can add more locations in `gdb` later via
   the `directory` command (see `help directory` in `gdb`).

1. Start the debugger:

    ```
    # open a command shell ("terminal")
    # on Linux use:
    R -d gdb
    # on Windows use
    gdb /path/to/R-3.x.x/bin/x64/Rgui.exe
    ```
    
    **Note:**
    All examples here are based on `gdb`.
    `lldb` does not work so far  (for the current status see [issue #5](https://github.com/aryoda/R_CppDebugHelper/issues/5)),
    but perhaps you are the lucky one ;-)
    You can use this [GDB to LLDB command map](https://lldb.llvm.org/use/map.html)
    to "translate" the example `gdb` commands to `lldb`.
    

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
- DONE (`dbg_get`): `get` function that returns a variable from an environment to be used for filtering
- DONE (`dbg_subset`): simple vector filtering for important R and Rcpp data types (element range with range checks) (idea: as piped functions)
- DONE (`dbg_subset`): subset `data.frame` rows
- subset `data.frame` columns
- DONE (`dbg_str`): inspect the `str()` of an R variable
- DONE (`dbg_str`): inspect the `str()` of Rcpp data types
- DONE (`dbg_table`): get tabulation (`table` in R) with limited output (may be quite chatty)
- DONE (`dbg_syscalls`) print sys.calls (also `call Rf_PrintValue(R_GetTraceback(0))` ?)
- summarize vector (like `summary` in R; Rcpp knows "only" `table`) (idea: as piped functions)
- `head` and `tail` (as piped functions or just for direct printing? Printing should be the main goal IMHO...)
- NA value diagnostics
- print encoding of strings and string vectors
- common STL containers (but gdb offers pretty printers for that AFAIK)
- optional: set `options("max.print")` to reduce print results to a sensible maximum (default is 99999!)
- optional: change R variable values (eg. via an overloaded function names `dbg_assign()`)
- optional: change Rcpp variable values
- optional: support for data types of packages derived from `Rcpp` (eg. ` RcppArmadillo`)
- optional: show how to use logging in Rcpp code that is synchronised with logging in R (hopefully even the same logging package)
- optional: provide gdb macros as shortcuts for the dbg_* functions.
            See: http://www.yolinux.com/TUTORIALS/src/dbinit_stl_views-1.03.txt
- optional: RStudio addin to configure everything, give hints for missing tools and
            start debugging via gdb in the RStudio terminal. The variable values of the current frame
            could be shown in the "Environment" windows of RStudio. Execution commands
            like `next` could be presented as buttons and with keyboard shortcuts.
            Breakpoints could be set in the code as usual and "translated" into `gdb`
            breakpoints automatically...

**Note:** Each print function should respect `getOption("max.print")` and cut the output
with `[ reached getOption("max.print") -- omitted 9000 entries ]`



## gdb pretty printers

For

- STL classes
- common Rcpp data types

A function for automatic installation or at least instructions would be helpful.


## Open issues

TODO

- Does this package also support debugging of plain C code if `Rcpp` is not used at all?
  `R` is implemented in C and this packages uses function overloading which is not
  a supported feature in the C language (AFAIK).

- Verify that `lldb` can also be used (see FAQ entry for that)

- Explain why this package delivers CPP functions instead of a `gdb` pretty printers
  (short answer: this pkg shall be debugger independent but pretty printers are debugger specific
   + a pretty printer needs to call a specific debug helper function anyhow
   + the debug functions do already print very pretty ;-)

- Explain when compilers generate the code from template definitions.

  Since the compiler generates the code from the template definition,
  it means that the full definitions need to be visible to the calling code,
  not only the declaration, as was the case for functions and classes.
  
  => Rcpp always contains the template definitions in the header files (I guess -> check it)


  

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
- `gdb`'s `display` command does not work with the `call` command (`display call f()` is not allowed)
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



## I have compiler errors or warning when building this package on Windows

If you get errors or warnings like

- *Warning: function uses 'auto' type specifier without trailing return type*
- *Warning: 'auto' changes meaning in C++11; please remove it*

the used CPP compiler uses an older C++ standard as default.

To build successfully you have to enable a newer C++ standard (at least C++11) in the `Makevars` file:

```
CXXFLAGS = -g3 -O0 -Wall -std=c++11
# CXXFLAGS = -g3 -O0 -Wall -std=c++14   # or this for C++14
```

For details see:

- https://stackoverflow.com/questions/44798728/warning-function-uses-auto-type-specifier-without-trailing-return-type
- https://stackoverflow.com/questions/25170251/auto-changes-meaning-in-c11-please-remove-it-what-does-this-mean



## How can I debug on Windows (`R` has no `-d` switch)?

Precondition: The code under inspection has been compiled for debugging (TODO: add link to howto instructions)

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



## During debugging with `gdb` on Windows I see a lot of warnings containing `attribute.cpp(92)\dwmapi.dll`

You can see a lot of warning similar to this one:

> windows\dwm\dwmapi\attribute.cpp(92)\dwmapi.dll!00007FFFAD51594E: (caller: 00007FFFABCA071A) ReturnHr(30) tid(10a0) 80070006 The handle is invalid.

This is a Windows 10 bug. It seems Microsoft has forgotten to disable tracing code before releasing this DLL.

You can ignore these warnings (even though it is annoying to be flooded with them).

For details see:
https://social.msdn.microsoft.com/Forums/en-US/3a5a145a-c13d-4898-bb61-a5baadc9332f/why-am-i-getting-hundreds-of-weird-messages-in-debug-output-window



## Debugging with `gdb` on Windows fails with error "cannot execute this command while the selected thread is running"

Sometimes during debugging it is no longer possible to step (via the `next` command) or continue the execution.

The error message is:

```
(gdb) c
Continuing.
Cannot execute this command while the selected thread is running.
```

This problem was observed with `gdb --version` *GNU gdb (GDB) 7.9.1* as installed with Rtools v3.5 and is not easily reproducible.

This seems to be bug but the exact reason is unclear:

- https://stackoverflow.com/questions/16900615/gdb-step-not-working-as-expected
- https://sourceware.org/bugzilla/show_bug.cgi?id=17134



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


## Calling a debug function (`dbg_*`) in `gdb` fails with: *Attempt to take address of value not located in memory.*

When you call a debug function `gdb` you will get an error message like

> Attempt to take address of value not located in memory.

if an function argument is a variable that is not stored in memory but in a CPU register:

```
(gdb) call dbg_print(x)
Attempt to take address of value not located in memory.
```

This most probably occurs because you have enabled code optimization during compilation.
Check if in the `Makevars` file the `-O` flag is set to `-O0` ("optimization = zero").
Then clean-up the binaries of your code and recompile (*Build > Clean & Rebuild* in RStudio).



## Can I use the `lldb` debugger instead of `gdb`?

`lldb` is the default debugger in Xcode on macOS/OS X for C++ and typically used with the `Clang` compiler.

All examples here are based on `gdb` but it should (= not yet tested!) be possible to use `lldb` instead of `gdb`
because this packages does not depend on any special debugger.

You can use this [GDB to LLDB command map](https://lldb.llvm.org/use/map.html) to "translate" the example `gdb` commands to `lldb` commands.

**In practice it did not work so far (for the current status see [issue #5](https://github.com/aryoda/R_CppDebugHelper/issues/5)).**

See also:
[Is it possible to debug a gcc-compiled program using lldb, or debug a clang-compiled program using gdb?](https://stackoverflow.com/questions/21132194/is-it-possible-to-debug-a-gcc-compiled-program-using-lldb-or-debug-a-clang-comp)



# License

GPL-3 (see file [LICENSE](LICENSE))



# Links

## `gdb`

- [gdb documentation](https://sourceware.org/gdb/onlinedocs/gdb)
- TODO Links to gdb tutorials + cheat sheets
  - [YoLinux.com GDB command cheat sheet](http://www.yolinux.com/TUTORIALS/GDB-Commands.html)
  - [gdb command reference by VisualGDB](https://visualgdb.com/gdbreference/commands/)
  - [GDB to LLDB command map](https://lldb.llvm.org/use/map.html#examining-variables)
- `gdb` does not know default arguments:
  - https://stackoverflow.com/questions/58827121/how-to-use-c-default-arguments-in-the-call-command-of-gdb?noredirect=1#comment103957145_58827121
  - https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html
- [SO question: Better variable exploring when debugging C++ code (answer explains `gdb`s pretty printers)](https://stackoverflow.com/questions/3651862/better-variable-exploring-when-debugging-c-code-with-eclipse-cdt?rq=1)

## `lldb`

- [Debugging compiled code in R with lldb](https://www.jimhester.com/post/2019-04-05-lldb-debugging/) (Video by Jim Hester):
  - A must-have-seen video showing a live debugging session with how-to instructions
  - Shows that `lldb` works on a OS X/Mac
  - Direct link to the video: https://www.youtube.com/watch?v=R3-IMGyNJY4
- [Debugging with LLDB](https://kevinushey.github.io/blog/2015/04/13/debugging-with-lldb/): A brief introduction to lldb on OS X

## `Rcpp`

- [Rcpp source code](https://github.com/RcppCore/Rcpp)
- [Good introduction into `Rcpp`](https://teuder.github.io/rcpp4everyone_en)
- [Rcpp Gallery: Working with Rcpp StringVector](https://gallery.rcpp.org/articles/working-with-Rcpp-StringVector/)
- [Advanced R: High performance functions with Rcpp (Hadley Wickham)](http://adv-r.had.co.nz/Rcpp.html) 
- [Table: Correspondance of data types between R, Rcpp an dC++](https://teuder.github.io/rcpp4everyone_en/070_data_types.html)
- [Debugging: Using gdb](http://dirk.eddelbuettel.com/papers/rcpp_uzuerich_2015_part5_packaging.pdf)
- [Debugging an R Package with C++](https://blog.davisvaughan.com/2019/04/05/debug-r-package-with-cpp/) (Data Insights): Excellent introduction

## `R` API

- [Advanced R: R's C interface (Hadley Wickham)](http://adv-r.had.co.nz/C-interface.html)
- [Writing R Extensions: Debugging compiled code](https://cran.r-project.org/doc/manuals/R-exts.html#Debugging-compiled-code)
- [Writing R Extensions: The R API](https://cran.rstudio.com/doc/manuals/r-devel/R-exts.html#The-R-API)
- [R for Windows FAQ](https://cran.r-project.org/bin/windows/base/rw-FAQ.html)
  - see esp. the section *How do I debug code that I have compiled and dyn.load-ed?* 
- [R Internals](https://cran.r-project.org/doc/manuals/r-release/R-ints.html)
- [Debugging C/C++ code that interfaces with R](https://github.com/wch/r-debug/blob/master/debugging-r.md)

