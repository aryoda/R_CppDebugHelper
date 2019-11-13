#include <Rcpp.h>

using namespace Rcpp;

// provides print functions for all typedef'ed Vector and Matrix types
// (as defined in include/Rcpp/vector/instantiation.h)

// For ease-of-use in gdb the functions use overloading
// since gdb C/C++ expressions support overloading:
// https://sourceware.org/gdb/onlinedocs/gdb/C-Plus-Plus-Expressions.html



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


// Prints all variable names in the global environment without the hidden variables (starting with a dot).
// R command: ls(all.names = TRUE)
void dbg_ls(Environment e) {
  bool all_names = false;
  print(e.ls(all_names));
}


// Prints all variable names in the global environment incl. the hidden variables (starting with a dot).
// R command: ls(all.names = TRUE)
void dbg_ls(Environment e, bool all_names) {
  print(e.ls(all_names));
}


// Print all public variables
void dbg_print(Environment e) {
  dbg_ls(e);   // print(e.ls(false));
}



// Rcpp attributes --------------------------------------------

void dbg_attributes(RObject o) {
  // wrap() from std::vector<std::string>
  CharacterVector attr_names = wrap(o.attributeNames());
  Rcpp::print(attr_names);
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

void dbg_attributes(RawVector df) {
  RObject o = df;
  dbg_attributes(o);
}

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



// Rcpp primitives --------------------------------------------

void dbg_print(String x) {
  // TODO avoid NULL pointer crashes ;-)
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
