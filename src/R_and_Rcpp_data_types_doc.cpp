/*

 Summary of R and Rcpp data types that should be supported by this package finally:

 SEXP types of R:

 no	SEXPTYPE	Description
 0	NILSXP	  NULL
 1	SYMSXP	  symbols
 2	LISTSXP	  pairlists
 3	CLOSXP	  closures
 4	ENVSXP	  environments
 5	PROMSXP	  promises
 6	LANGSXP	  language objects
 7	SPECIALSXP	special functions
 8	BUILTINSXP	builtin functions
 9	CHARSXP	  internal character strings
 10	LGLSXP	  logical vectors
 13	INTSXP	  integer vectors
 14	REALSXP	  numeric vectors
 15	CPLXSXP	  complex vectors
 16	STRSXP	  character vectors
 17	DOTSXP	  dot-dot-dot object
 18	ANYSXP	  make “any” args work
 19	VECSXP	  list (generic vector)
 20	EXPRSXP	  expression vector
 21	BCODESXP	byte code
 22	EXTPTRSXP	external pointer
 23	WEAKREFSXP	weak reference
 24	RAWSXP	  raw vector
 25	S4SXP	    S4 classes not of simple type

 Source:
 https://cran.r-project.org/doc/manuals/r-release/R-ints.html#SEXPTYPEs



 Rcpp types:

 typedef Vector<CPLXSXP> ComplexVector ;    // supported by RCPP_RETURN_VECTOR
 typedef Vector<INTSXP>  IntegerVector ;    // supported by RCPP_RETURN_VECTOR
 typedef Vector<LGLSXP>  LogicalVector ;    // supported by RCPP_RETURN_VECTOR
 typedef Vector<REALSXP> NumericVector ;    // supported by RCPP_RETURN_VECTOR
 typedef Vector<REALSXP> DoubleVector ;     // alias
 typedef Vector<RAWSXP>  RawVector ;        // supported by RCPP_RETURN_VECTOR

 typedef Vector<STRSXP>  CharacterVector ;  // supported by RCPP_RETURN_VECTOR
 typedef Vector<STRSXP>  StringVector ;     // alias
 typedef Vector<VECSXP>  GenericVector ;    // alias
 typedef Vector<VECSXP>  List ;             // supported by RCPP_RETURN_VECTOR - DataFrame is also a list?!
 typedef Vector<EXPRSXP> ExpressionVector ; // supported by RCPP_RETURN_VECTOR

 typedef Matrix<CPLXSXP> ComplexMatrix ;
 typedef Matrix<INTSXP>  IntegerMatrix ;
 typedef Matrix<LGLSXP>  LogicalMatrix ;
 typedef Matrix<REALSXP> NumericMatrix ;
 typedef Matrix<RAWSXP>  RawMatrix ;

 typedef Matrix<STRSXP>  CharacterMatrix ;
 typedef Matrix<STRSXP>  StringMatrix ;     // alias
 typedef Matrix<VECSXP>  GenericMatrix ;    // alias
 typedef Matrix<VECSXP>  ListMatrix ;
 typedef Matrix<EXPRSXP> ExpressionMatrix ;

 Source: Taken from Rcpp's include/Rcpp/vector/instantiation.h



 The implementation for DateVector and DatetimeVector changed in Rcpp 0.12.14

 typedef newDateVector DateVector;          // is a NumericVector internally
 typedef newDatetimeVector DatetimeVector;  // is a NumericVector internally

 Source: Taken from Rcpp's include/Rcpp/date_datetime/date_datetime.h



 typedef DataFrame_Impl<PreserveStorage> DataFrame ;

 Source: include/Rcpp/DataFrame.h

 */

