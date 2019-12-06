#include <Rcpp.h>
// #include <R.h>
// #include <Rinternals.h>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
List debug_example_rcpp() {

    // you can use these Rcpp objects to test the debugging helper functions...

    CharacterVector cv   = CharacterVector::create("foo", "bar", NA_STRING, "hello")  ;
    NumericVector nv     = NumericVector::create(0.0, 1.0, NA_REAL, 10) ;
    // HACK Internally it is a NumericVector so I pass date integers (number of days since 1970-01-01)
    DateVector dv        = DateVector::create( 14974, 14975, 15123, NA_REAL); // TODO how to use real dates instead?
    DateVector dv2       = DateVector::create(Date("2010-12-31"), Date("01.01.2011", "%d.%m.%Y"), Date(2011, 05, 29), NA_REAL);
    DatetimeVector dtv   = DatetimeVector::create(1293753600, Datetime("2011-01-01"), Datetime("2011-05-29 10:15:30"), NA_REAL);
    DataFrame df         = DataFrame::create(Named("name1") = cv, _["value1"] = nv, _["dv2"] = dv2);  // Named and _[] are the same
    CharacterVector col1 = df["name1"];          // get the first column
    String s             = col1[0];              // element #1
    // DateVector d3 = DateVector::create("2010-12-31", "2011-01-01", "2011-05-29");  // compiler error
    // Datetime(const std::string &s, const std::string &fmt="%Y-%m-%d %H:%M:%OS");
    ComplexVector  cxv(10);
    Rcomplex rc;
    for(int i = 0; i < 10; i++) {
        rc.r = rc.i = i + 0.0;
        cxv[i] = rc;
    }

    Rcpp::List l               = List::create(cv, nv, df, s);

    Environment e = Rcpp::Environment::global_env();
    e.assign("a", Range(1, 10));
    print(e.ls(false));

    return l;
}
