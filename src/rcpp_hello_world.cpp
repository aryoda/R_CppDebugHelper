#include <Rcpp.h>
// #include <R.h>
// #include <Rinternals.h>

using namespace Rcpp;

// [[Rcpp::export]]
List rcpp_hello_world() {

    CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;

    Environment e = Rcpp::Environment::global_env();
    print(e.ls(false));

    // Possible options to print values in Rcpp:
    // https://stackoverflow.com/questions/28152406/print-integer-vector-from-rcpp-function
    // https://stackoverflow.com/questions/35982284/how-to-print-an-r-object-to-stderr-in-rcpp
    // https://stackoverflow.com/questions/51169994/how-to-print-raw-values-in-rcpp
    // 1. Rf_PrintValue(a);
    // 2. Rcpp::print(a); // wraps the Rf_PrintValue
    // 3. Rcpp::Rcout << a << std::endl; // or Rcpp::Rcerr for output on the stderr device
    // SEXP a = Rcpp::wrap(x);
    // print(a);
    //
    // // Functions to print R objects
    // Rcpp::Rcout << "Debug output:" << std::endl;
    // Rf_PrintValue(x);
    // print(SEXPREC *)
    // print(y);
    // // R_PV(x);  // R API function (not from Rcpp). Calls Rf_PrintValue internally?
    // // R_PV was not declared in this scope
    // Rcpp::Rcout << "End of debug output" << std::endl;

    return z ;
}
