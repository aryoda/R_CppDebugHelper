#include <Rcpp.h>
using namespace Rcpp;



// Prints all variable names in the global environment without the hidden variables (starting with a dot).
// R command: ls(all.names = FALSE)
void dbg_ls() {
  Environment e = Rcpp::Environment::global_env();
  print(e.ls(false));
}



// Prints all variable names in the global environment
// incl. the hidden variables (starting with a dot) if all_names = 1.
// R command: ls(all.names = TRUE)
void dbg_ls(bool all_names) {
  Environment e = Rcpp::Environment::global_env();
  print(e.ls(all_names));
}



// Prints all variable names of an environment without the hidden variables (starting with a dot).
// R command: ls(all.names = TRUE)
void dbg_ls(Environment e) {
  bool all_names = false;
  // TODO segfault if e is not yet initialized (eg. if it is a local variable and used before init)
  // Rcpp::Rcout << "SEXP type: " << e.sexp_type() << std::endl;
  Rcpp::print(e.ls(all_names));
}



// Prints all variable names of an environment
// incl. the hidden variables (starting with a dot) if all_names = 1.
// R command: ls(all.names = TRUE)
void dbg_ls(Environment e, bool all_names) {
  Rcpp::print(e.ls(all_names));
}

