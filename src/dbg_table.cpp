#include <Rcpp.h>
using namespace Rcpp;


// DOES NOT COMPILE for RObject
// like the R function "table"
// void dbg_table(RObject o) {
//   return Rcpp::table(o);
// }

// Returns a contingency table ()like the R function "table")
auto dbg_table(NumericVector x) {
  return Rcpp::table(x);  // TODO how to set useNA="ifany"?
  // TODO Avoid nasty result for NULL ptr
  //   (gdb) call dbg_print(dbg_table(0)
  //   A syntax error in expression, near `'.
}

// TODO could be buggy but works for now
SEXP dbg_table(SEXP x) {
  SEXP res = as<SEXP>(IntegerVector(0));  // empty result vector (better than R_NilValue)
  if (x == NULL or x == R_NilValue)
    return res;
  try {
    Function f = Environment::global_env().find("table");  // should be in "namespace:utils"
    // Rcpp::print(f);
    res = f(x, Named("useNA") = "ifany");
  } catch(std::exception& ex) {
    Rcpp::Rcout << ex.what() << std::endl;
  } catch(...) {
    Rcpp::Rcout << "Unknown error" << std::endl;
  }
  return res;
}

// TODO Add functions for types

