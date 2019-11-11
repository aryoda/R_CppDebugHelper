#include <Rcpp.h>

using namespace Rcpp;

// provides print functions for all typedef'ed Vector and Matrix types
// (as defined in include/Rcpp/vector/instantiation.h)

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



void dbg_Rcpp(ComplexVector x) {
  Rcpp::print(x);
}

void dbg_Rcpp(IntegerVector x) {
  Rcpp::print(x);
}

void dbg_Rcpp(LogicalVector x) {
  Rcpp::print(x);
}

void dbg_Rcpp(NumericVector x) {
  Rcpp::print(x);
}

// same type as NumericVector
// void dbg_Rcpp(DoubleVector x) {
//     Rcpp::print(x);
// }

void dbg_Rcpp(RawVector x) {
  Rcpp::print(x);
}

void dbg_Rcpp(CharacterVector x) {
  Rcpp::print(x);
}

// same type as CharacterVector
// void dbg_Rcpp(StringVector x) {
//   Rcpp::print(x);
// }

void dbg_Rcpp(GenericVector x) {
  Rcpp::print(x);
}

// Same type as GenericVector
// void dbg_Rcpp(List x) {
//   Rcpp::print(x);
// }

void dbg_Rcpp(ExpressionVector x) {
  Rcpp::print(x);
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
