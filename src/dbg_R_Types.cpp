#include <Rcpp.h>

using namespace Rcpp;



// Helper routine ps to print a string class variable.
// void ps(string& s){ cout << s << endl; }

// For ease-of-use in gdb the functions use overloading
// since gdb C/C++ expressions support overloading:
// https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html



// Test function with default values
// Note: gdb does not know default values (only the compiler knows) so using default values does not work
// void dbg_test(int a = 1) {
//   std::cout << a << std::endl;
// }


// Prints the content of an SEXP.
void dbg_print(SEXP x) {
  Rcpp::print(x);
}


// Prints all variable names in the global environment without the hidden variables (starting with a dot).
// R command: ls(all.names = FALSE)
void dbg_ls() {
  Environment e = Rcpp::Environment::global_env();
  print(e.ls(false));
}

// Prints all variable names in the global environment incl. the hidden variables (starting with a dot).
// R command: ls(all.names = TRUE)
void dbg_ls(bool all_names) {
  Environment e = Rcpp::Environment::global_env();
  print(e.ls(all_names));
}



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
  std::string varname(name);
  Symbol sym(name);
  // Rcpp::Rcout << name << std::endl;
  // std::cout << "name: " << varname << std::endl;
  Environment e = Rcpp::Environment::global_env();
  print(e.get(name));
}



