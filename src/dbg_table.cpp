#include <Rcpp.h>
using namespace Rcpp;


// DOES NOT COMPILE for RObject
// like the R function "table"
// void dbg_table(RObject o) {
//   return Rcpp::table(o);
// }



// Returns a contingency table (R function "table" with useNA="ifany")
SEXP dbg_table(SEXP x) {
  SEXP res = as<SEXP>(IntegerVector(0));  // empty result vector (better than R_NilValue)
  if (x == NULL or x == R_NilValue)
    return res;
  try {
    // TODO Should we call Rcpp::table instead (but still return an SEXP)?
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



// Returns a contingency table (like the R function "table")
// In C++11 auto can be used for declaring local variables and for the return type of a function with a trailing return type:
//   auto dbg_table(NumericVector x) -> IntegerVector
// In C++14 auto can be used for the return type of a function without specifying a trailing type:
//    auto dbg_table(NumericVector x)
// (gdb) call dbg_print(dbg_table(x))
IntegerVector dbg_table(NumericVector x) {
  return Rcpp::table(x);  // useNA="ifany"? This seems to be the default behaviour!
}

IntegerVector dbg_table(LogicalVector x) {
  return Rcpp::table(x);
}

IntegerVector dbg_table(RawVector x) {
  return Rcpp::table(x);
}

IntegerVector dbg_table(CharacterVector x) {
  return Rcpp::table(x);
}

// Unsupported Rcpp types (not allowed by Rcpp::table())

// IntegerVector dbg_table(ComplexVector x) {
//   return Rcpp::table(x);
// }

// table(aList) does work in R but the result seems to be useless
// IntegerVector dbg_table(List x) {
//   return Rcpp::table(x);
// }

// a <- parse(text = "1+2")
// typeof(a)
// [1] "expression"
// IntegerVector dbg_table(ExpressionVector x) {
//   return Rcpp::table(x);
// }

IntegerVector dbg_table(DateVector x) {
  // TODO dimnames are printed as integer instead of Date
  IntegerVector res = Rcpp::table(x);
  return res;
}

IntegerVector dbg_table(DatetimeVector x) {
  // TODO dimnames are printed as double instead of Datetime
  return Rcpp::table(x);
}



// TODO Add functions for missing types (mainly matrices)
