// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// break_to_debugger
void break_to_debugger();
RcppExport SEXP _CppDebugHelper_break_to_debugger() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    break_to_debugger();
    return R_NilValue;
END_RCPP
}
// debug_example_rcpp
List debug_example_rcpp();
RcppExport SEXP _CppDebugHelper_debug_example_rcpp() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(debug_example_rcpp());
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_CppDebugHelper_break_to_debugger", (DL_FUNC) &_CppDebugHelper_break_to_debugger, 0},
    {"_CppDebugHelper_debug_example_rcpp", (DL_FUNC) &_CppDebugHelper_debug_example_rcpp, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_CppDebugHelper(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
