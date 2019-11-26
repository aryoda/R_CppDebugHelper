#include <Rcpp.h>
using namespace Rcpp;


// Required declarations
void dbg_ls(Environment e);



// provides print functions for all R and Rcpp types
// (typedef'ed Vector and Matrix types as defined in include/Rcpp/vector/instantiation.h)

// For ease-of-use in gdb the functions use overloading
// since gdb C/C++ expressions support overloading:
// https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html



// Prints the content of an SEXP.
void dbg_print(SEXP x) {
  if (x == NULL || x == R_NilValue)
    return;
  Rcpp::print(x);
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



void dbg_print(ComplexVector x) {
  Rcpp::print(x);
}



void dbg_print(IntegerVector x) {
  Rcpp::print(x);
}



void dbg_print(LogicalVector x) {
  Rcpp::print(x);
}



void dbg_print(NumericVector x) {
  Rcpp::print(x);
}



// same type as NumericVector
// void dbg_print(DoubleVector x) {
//     Rcpp::print(x);
// }



void dbg_print(RawVector x) {
  Rcpp::print(x);
}



void dbg_print(CharacterVector x) {
  Rcpp::print(x);
}



// same type as CharacterVector
// void dbg_print(StringVector x) {
//   Rcpp::print(x);
// }



void dbg_print(GenericVector x) {
  Rcpp::print(x);
}



// Same type as GenericVector
// void dbg_print(List x) {
//   Rcpp::print(x);
// }



void dbg_print(ExpressionVector x) {
  Rcpp::print(x);
}



void dbg_print(DataFrame df) {
  Rcpp::print(df);
}



// Print the variable of an environment. Also searches the parent environments for the variable
void dbg_print(Environment e, const char *name) {
  if (name == NULL)
    return;
  std::string varname(name);
  if (varname.size() < 1)   // size in bytes (not chars)!
    return;
  // TODO catch binding_not_found exception by calling dbg_get
  print(e.find(varname)); // find instead of get to search parent environments too
}




// Print all public variables of an environment (= dbg_ls)
void dbg_print(Environment e) {
  dbg_ls(e);   // print(e.ls(false));
}



// Rcpp primitives --------------------------------------------



// print the value of the string (x is NOT interpreted as containing a variable name!)
void dbg_print(Rcpp::String x) {
  if (x == NULL || x.get_sexp() == NULL )   // TODO avoid NULL pointer crashes ;-)
    return;
  Rcpp::print(x.get_sexp());  // "print" does not directly work on String (no casting possible)
}


