#include <Rcpp.h>

using namespace Rcpp;

// provides print functions for all typedef'ed Vector and Matrix types
// (as defined in include/Rcpp/vector/instantiation.h)

// For ease-of-use in gdb the functions use overloading
// since gdb C/C++ expressions support overloading:
// https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html



// Taken from Rcpp's instantiation.h
//
// typedef Vector<CPLXSXP> ComplexVector ;
// typedef Vector<INTSXP> IntegerVector ;
// typedef Vector<LGLSXP> LogicalVector ;
// typedef Vector<REALSXP> NumericVector ;
// typedef Vector<REALSXP> DoubleVector ;
// typedef Vector<RAWSXP> RawVector ;
//
// typedef Vector<STRSXP> CharacterVector ;
// typedef Vector<STRSXP> StringVector ;
// typedef Vector<VECSXP> GenericVector ;
// typedef Vector<VECSXP> List ;
// typedef Vector<EXPRSXP> ExpressionVector ;

// TODO Functions for DateVector and DatetimeVector are still missing?



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

// Print all public variables of an environment (= dbg_ls)
void dbg_print(Environment e) {
  dbg_ls(e);   // print(e.ls(false));
}



// Rcpp attributes --------------------------------------------

void dbg_attributes(RObject o) {
  // wrap() from std::vector<std::string>
  // CharacterVector attr_names = wrap(o.attributeNames());
  auto attr_names = o.attributeNames();
  // Rcpp::print(attr_names);

  // Print names + values in the same format as R
  auto i = attr_names.size();  // workaround to get the right size type without thinking
  for(i=0; i < attr_names.size(); i++) {
    Rcpp::Rcout << "$" << attr_names[i] << std::endl;
    Rcpp::print(o.attr(attr_names[i]));
    Rcpp::Rcout << std::endl;
  }
}

// dbg_attributes(SEXP) is missing
void dbg_attributes(SEXP x) {
  dbg_attributes(as<RObject>(x));
}

// Print the attributes of a variable in an environment (also searches parent environments for the variable)
void dbg_attributes(Environment e, const char *name) {
  if (name == NULL)
    return;
  std::string varname(name);
  if (varname.size() < 1)   // size in bytes (not chars)!
    return;
  // Symbol sym(name);
  // TODO catch binding_not_found exception by calling dbg_get
  RObject o = as<RObject>(e.find(varname));  // find instead of get to search parent environments too
  dbg_attributes(o);
}

// Print the attributes of a variable in the global environment.
// name = name of the variable
void dbg_attributes(const char *name) {
  Environment e = Rcpp::Environment::global_env();
  dbg_attributes(e, name);
}


void dbg_attributes(ComplexVector df) {
  RObject o = df;
  dbg_attributes(o);
}

void dbg_attributes(IntegerVector df) {
  RObject o = df;
  dbg_attributes(o);
}

void dbg_attributes(LogicalVector df) {
  RObject o = df;
  dbg_attributes(o);
}

void dbg_attributes(NumericVector df) {
  RObject o = df;
  dbg_attributes(o);
}

// charToRaw("hello world")
void dbg_attributes(RawVector df) {
  RObject o = df;
  dbg_attributes(o);
}

/**
 * @title test
 *
 */
void dbg_attributes(CharacterVector df) {
  RObject o = df;
  dbg_attributes(o);
}

void dbg_attributes(GenericVector df) {
  RObject o = df;
  dbg_attributes(o);
}

void dbg_attributes(ExpressionVector df) {
  RObject o = df;
  dbg_attributes(o);
}

void dbg_attributes(DataFrame df) {
  RObject o = df;
  dbg_attributes(o);
}



// dbg_str -----------------------------------------------------


// Print structure of an variable in the global env (like R's "str")
void dbg_str(Environment e, const char *name) {
  if (name == NULL)   // TODO reliable way to detect empty strings
    return;
  try {
    std::string varname(name);
    if (varname.size() < 1)   // size in bytes (not chars)!
      return;
    RObject o = e.find(varname); // find instead of get to search parent environments too
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
  Function f = Environment::global_env().find("str");  // should be in "namespace:utils"
  // Rcpp::print(f);
  f(df);  // does print via R
}


// TODO dbg_str for other Rcpp types (not that important as data.frame at the moment ;-)
//      x->data is always a workaround (= using the underlying SEXP)



// Rcpp primitives --------------------------------------------

// print the value of the string
void dbg_print(Rcpp::String x) {
  if (x == NULL || x.get_sexp() == NULL )   // TODO avoid NULL pointer crashes ;-)
    return;
  Rcpp::print(x.get_sexp());  // "print" does not directly work on String (no casting possible)
}



// TODO

// typedef Matrix<CPLXSXP> ComplexMatrix ;
// typedef Matrix<INTSXP> IntegerMatrix ;
// typedef Matrix<LGLSXP> LogicalMatrix ;
// typedef Matrix<REALSXP> NumericMatrix ;
// typedef Matrix<RAWSXP> RawMatrix ;
//
// typedef Matrix<STRSXP> CharacterMatrix ;
// typedef Matrix<STRSXP> StringMatrix ;
// typedef Matrix<VECSXP> GenericMatrix ;
// typedef Matrix<VECSXP> ListMatrix ;
// typedef Matrix<EXPRSXP> ExpressionMatrix ;
