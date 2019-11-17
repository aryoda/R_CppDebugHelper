#include <Rcpp.h>

using namespace Rcpp;



// Helper routine ps to print a string class variable.
// void ps(string& s){ cout << s << endl; }

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




// Test function with default values
// Note: gdb does not know default values (only the compiler knows) so using default values does not work
// void dbg_test(int a = 1) {
//   std::cout << a << std::endl;
// }


// Prints the content of an SEXP.
void dbg_print(SEXP x) {
  if (x == NULL || x == R_NilValue)
    return;
  Rcpp::print(x);
}


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



// Other "dbg_ls" functions are defined in the Rcpp related source file(s), eg. for passing Rcpp::Environment




// Prints the value of an R variable in the global environment via its name.
// gdb seems to store string command arguments as "char" internally using UTF-8:
//   (gdb) ptype "hello"
//   type = char [6]
//   (gdb) ptype "voilà"
//   type = char [7]
//   (gdb) print "voilà"
//   $2 = "voilà"
//   (gdb) ptype "äöü"
//   type = char [7]
//   (gdb)
// This debug helper function uses this gdb behaviour to pass gdb string argument to
// an Rcpp function to query R variables by their name...
// https://stackoverflow.com/questions/42462860/calling-stdbasic-string-in-gdb?noredirect=1&lq=1
void dbg_print(const char *name) {
  if (name == NULL)
    return;
  std::string varname(name);
  if (varname.size() < 1)   // size in bytes (not chars)!
    return;
  // Symbol sym(name);
  // Rcpp::Rcout << name << std::endl;
  // std::cout << "name: " << varname << std::endl;
  Environment e = Rcpp::Environment::global_env();
  // print(e.get(name));
  // TODO catch binding_not_found exception by calling dbg_get
  print(e.find(varname)); // find instead of get to search parent environments too
}





// dbg_str -----------------------------------------------------

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
