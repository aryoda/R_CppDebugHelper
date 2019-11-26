#include <Rcpp.h>
// #include <R.h>
// #include <Rinternals.h>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
List debug_example_rcpp() {

    CharacterVector x    = CharacterVector::create("foo", "bar", NA_STRING, "hello")  ;
    NumericVector y      = NumericVector::create(0.0, 1.0, NA_REAL, 10) ;
    DataFrame df         = DataFrame::create(Named("name1") = x, _["value1"] = y);  // Named and _[] are the same
    CharacterVector col1 = df["name1"];          // get the first column
    String s             = col1[0];              // element #1
    // HACK Internally it is a NumericVector so I pass date integers (number of days since 1970-01-01)
    DateVector d         = DateVector::create( 14974, 14975, 15123, NA_REAL); // TODO how to use real dates instead?
    DateVector d2        = DateVector::create(Date("2010-12-31"), Date("01.01.2011", "%d.%m.%Y"), Date(2011, 05, 29), NA_REAL);
    // DateVector d3 = DateVector::create("2010-12-31", "2011-01-01", "2011-05-29");  // compiler error
    // Datetime(const std::string &s, const std::string &fmt="%Y-%m-%d %H:%M:%OS");
    DatetimeVector dt    = DatetimeVector::create(1293753600, Datetime("2011-01-01"), Datetime("2011-05-29 10:15:30"), NA_REAL);

    ComplexVector  cv(10);
    Rcomplex rc;
    for(int i = 0; i < 4; i++) {
        rc.r = rc.i = i + 0.0;
        cv[i] = rc;
    }

    List z               = List::create(x, y, df, s);

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
