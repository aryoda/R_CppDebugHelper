

#' Trigger a breakpoint hit to transfer the control to the debugger
#'
#' Important: This does only work on x86 instruction set CPUs!
#'
#' Warning: If R was not started within a debugger the result is undetermined (may be segfault
#' or R is exiting immediately).
#'
#' Currently this seems to work on Linux, but on Windows only Rgui and Rterm do work
#' but R started via R.exe does not break but exit.
#'
#' For more background see:
#'
#' https://cran.r-project.org/bin/windows/base/rw-FAQ.html#How-do-I-debug-code-that-I-have-compiled-and-dyn_002eload_002ded_003f
#'
#' https://stat.ethz.ch/pipermail/r-devel/2019-December/078794.html
#'
#' @return Nothing
#' @export
#'
break_to_debugger <- function() {

  if (!(Sys.info()["machine"] %in% c("x86_64", "i386")))
    print("Warning: break_to_debugger may not work on your machine!")

  internal_break_to_debugger()  # calls C++ code

}
