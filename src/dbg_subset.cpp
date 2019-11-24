#include <Rcpp.h>
using namespace Rcpp;


// Vector is the base class for all Rcpp vectors. See the source code in the file
// Rcpp/inst/include/Rcpp/vector/vector.h



// Returns a range complying to the vector bounds. -1 indicates an empty range for whatever reason
Rcpp::Range make_Range(R_xlen_t index_from, R_xlen_t index_to, R_xlen_t vec_size) {
  // ensure  bounds
  if (index_from < 0) {
    Rcpp::Rcout << "index_from is out of range: " << index_from << " (assuming 0)" << std::endl;
    index_from = 0;
  }

  if (index_to >= vec_size) {
    Rcpp::Rcout << "index_to is out of range: " << index_to << " (assuming " << vec_size -1 << ")" << std::endl;
    index_to = vec_size - 1;
  }

  if (vec_size < 1 || index_from > index_to || index_from >= vec_size) {
    index_from = index_to = -1;  // empty subset
  }

  return Rcpp::Range(index_from, index_to);
}



// TODO Should we substract 1 (R indexes start with 1) or assume the user is aware of that?
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index_from, R_xlen_t index_to) {

  Rcpp::Range r = make_Range(index_from, index_to, x.size());

  if (r.get_end() < 0)
    return(NumericVector(0));  // empty vector

  return x[r];  // zero-based index
}



// TODO returns an element instead of an vector. Is this OK?
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index) {
  // return x[index];  // return type is element type
  return dbg_subset(x, index, index);  // return type is a vector
}



// TODO Should we substract 1 (R indexes start with 1) or assume the user is aware of that?
// https://stackoverflow.com/questions/58965423/return-subset-of-a-given-sexp-without-knowing-the-actual-internal-data-type
// SEXP dbg_subset(SEXP x, R_xlen_t index_from, R_xlen_t index_to) {
// }

// TODO Keep attributes in the subset result
// std::vector<std::string> nm = X.attributeNames();
// TODO Keep factors
