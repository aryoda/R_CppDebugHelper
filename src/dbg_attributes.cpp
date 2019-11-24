#include <Rcpp.h>

using namespace Rcpp;

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

// TODO:

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


// TODO why "df"? copy&paste blindness? ;-)
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
