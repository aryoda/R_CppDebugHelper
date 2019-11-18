#include <Rcpp.h>
using namespace Rcpp;


// Vector is the base class for all Rcpp vectors. See the source code in the file
// Rcpp/inst/include/Rcpp/vector/vector.h




// TODO Should we substract 1 (R indexes start with 1) or assume the user is aware of that?
// TODO How to reuse this "complicated" range checking logic?
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index_from, R_xlen_t index_to) {
  if (x.size() < 1)
    return(x);

  if (index_from > index_to || index_from >= x.size())
    return(NumericVector(0));  // empty vector

  if (index_from < 0)
    index_from = 0;

  if (index_to >= x.size())
    index_to = x.size() - 1;

  return x[Rcpp::Range(index_from, index_to)];  // zero-based index
}



// TODO returns an element instead of an vector. Is this OK?
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index) {
  // return x[index];  // return type is element type
  return dbg_subset(x, index, index);  // return type is a vector
}



