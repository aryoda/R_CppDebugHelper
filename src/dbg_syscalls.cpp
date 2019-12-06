#include <Rcpp.h>
using namespace Rcpp;



// Prints the R function call stack that lead to calling the current code
void dbg_syscalls() {

  try {
    Function f = Environment::global_env().find("sys.calls");  // should be in "namespace:base"
    SEXP res = f();
    Rcpp::print(res);
  } catch(std::exception& ex) {
    Rcpp::Rcout << ex.what() << std::endl;
  } catch(...) {
    Rcpp::Rcout << "Unknown error" << std::endl;
  }

}
