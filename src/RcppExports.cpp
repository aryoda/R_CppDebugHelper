// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rcpp_example_simple
List rcpp_example_simple();
RcppExport SEXP _CppDebugHelper_rcpp_example_simple() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(rcpp_example_simple());
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_CppDebugHelper_rcpp_example_simple", (DL_FUNC) &_CppDebugHelper_rcpp_example_simple, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_CppDebugHelper(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
