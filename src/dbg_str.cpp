#include <Rcpp.h>
using namespace Rcpp;



// TODO dbg_str for other Rcpp types (not that important as data.frame at the moment ;-)
//      x->data is always a workaround (= using the underlying SEXP)



// Print structure of an variable in the global env (like R's "str")
void dbg_str(const char *name) {
  if (name == NULL)   // TODO reliable way to detect empty strings
    return;
  try {
    std::string varname(name);
    if (varname.size() < 1)   // size in bytes (not chars)!
      return;
    Environment e = Rcpp::Environment::global_env();
    RObject o = e.find(varname);
    // TODO What is the difference to
    //   Function f("str"); // "declare" R function
    Function f = e.find("str");  // should be in "namespace:utils"
    // Rcpp::print(f);
    f(o);  // does print via R
  } catch(std::exception& ex) {
    Rcpp::Rcout << ex.what() << std::endl;
  } catch(...) {
    Rcpp::Rcout << "Unknown error" << std::endl;
  }
}



// Print structure of an object (like R's "str")
void dbg_str(SEXP x) {
  if (x == NULL || x == R_NilValue)
    return;
  try {
    Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
    // Rcpp::print(f);
    f(x);  // does print via R
  } catch(std::exception& ex) {
    Rcpp::Rcout << ex.what() << std::endl;
  } catch(...) {
    Rcpp::Rcout << "Unknown error" << std::endl;
  }
}



// Print structure of an variable in the global env (like R's "str")
void dbg_str(Environment e, const char *name) {
  if (name == NULL)   // TODO reliable way to detect empty strings
    return;
  try {
    std::string varname(name);
    if (varname.size() < 1)   // size in bytes (not chars)!
      return;
    RObject o = e.find(varname); // find instead of get to search parent environments too
    // TODO dirty search in wrong environment, use the standard way: Function f("R_func_name"); + encapsulte exception handling
    Function f = e.find("str");  // should be in "namespace:utils"
    // Rcpp::print(f);
    f(o);  // does print via R
  } catch(std::exception& ex) {
    Rcpp::Rcout << ex.what() << std::endl;
  } catch(...) {
    Rcpp::Rcout << "Unknown error" << std::endl;
  }
}


// Print structure of an object (like R's "str")
void dbg_str(DataFrame df) {
  // TODO dirty search, use the standard way: Function f("R_func_name"); + encapsulte exception handling
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  // Rcpp::print(f);
  f(df);  // does print via R
}



void dbg_str(ComplexVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}

void dbg_str(IntegerVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}
void dbg_str(LogicalVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}
void dbg_str(NumericVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}
void dbg_str(RawVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}


void dbg_str(CharacterVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}

// same as GenericVector
void dbg_str(List x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}

void dbg_str(ExpressionVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}

void dbg_str(DateVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}

void dbg_str(DatetimeVector x) {
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  f(x);  // does print via R
}
