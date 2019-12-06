#include <Rcpp.h>

using namespace Rcpp;



// For ease-of-use in gdb the functions use overloading
// since gdb C/C++ expressions support overloading:
// https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html



// TODO: Encapsulate Environment::find call for reusing the exception handling if the variable does not exist
// Return a variable from the global environment
// Note: May return R builtins if no variable is found (eg. the "combine" function "c" for "call dbg_get("c")")
SEXP dbg_get(Environment e, const char *name) {
  SEXP res = R_NilValue;
  if (name == NULL)
    return res;
  try {
    std::string varname(name);
    if (varname.size() < 1)   // size in bytes (not chars)!
      return res;
    res = e.find(varname); // find instead of get to search parent environments too
  } catch(std::exception& ex) {
    res = R_NilValue;      // Rcpp::Rcout << ex.what() << std::endl;
  } catch(...) {
    Rcpp::Rcout << "Unknown error" << std::endl;
    res = R_NilValue;
  }
  return res;
}



// Return a variable from an environment (parent environments are searched too)
SEXP dbg_get(const char *name) {
  Environment e = Rcpp::Environment::global_env();
  return dbg_get(e, name);
}




// Test function with default values to find out if gdb uses the default values.
// Result: gdb does not know default values (only the compiler knows) so using default values does not work
// void dbg_test(int a = 1) {
//   std::cout << a << std::endl;
// }

