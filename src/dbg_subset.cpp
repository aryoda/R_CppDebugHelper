#include <Rcpp.h>
using namespace Rcpp;


// Vector is the base class for all Rcpp vectors. See the source code in the file
// Rcpp/inst/include/Rcpp/vector/vector.h



// Returns a range complying to the vector bounds. -1 indicates an empty range for whatever reason.
// indexes are 0-based (Rcpp/CPP compliant)
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



// Question:        Should we substract 1 (R indexes start with 1) or assume the user is aware of that?
// Design decision: Use the index base of the underlying data type (R = 1, Rcpp = 0)
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index_from, R_xlen_t index_to) {

  Rcpp::Range r = make_Range(index_from, index_to, x.size());

  if (r.get_end() < 0)
    return(NumericVector(0));  // empty vector

  return x[r];  // zero-based index
}



// TODO returns an element instead of an vector. Is this OK (Vector or scalar?)?
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index) {
  // return x[index];  // return type is element type
  return dbg_subset(x, index, index);  // return type is a vector
}





// TODO dispatch SEXP type to Rcpp type via a self-made macro like RCPP_RETURN_VECTOR
// Design decision: Use the index base of the underlying data type (R = 1, Rcpp = 0)
// SEXP dbg_subset(SEXP x, R_xlen_t index_from, R_xlen_t index_to) {
// }



// TODO Keep attributes in the subset result
// std::vector<std::string> nm = X.attributeNames();
// https://teuder.github.io/rcpp4everyone_en/202_attributes.html



// TODO Keep factors like shown here:
// https://stackoverflow.com/questions/58965423/return-subset-of-a-given-sexp-without-knowing-the-actual-internal-data-type?noredirect=1#comment104185955_58965423
// if (x.hasAttribute("levels")){
//   subset.attr("class") = x.attr("class");
//   subset.attr("levels") = x.attr("levels");
// }




/* ********* Implementation alternative (not used) ***********************************************************
 *
 * Theoretically template functions + RCPP_RETURN_VECTOR would create all required dbg functions
 * with minimal repetitive code but in practice it is too confusing to call the correct function in gdb then..
 *
 * Eg. which dbg_subset function do you have to call to print a Rcpp::CharacterVector?
 * These are the signatures shown in gdb via tab autocompletion after typing "call dbg_subset":
 *
 * dbg_subset(SEXPREC*, long, long)
 * dbg_subset<14>(Rcpp::Vector<14, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<20>(Rcpp::Vector<20, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<15>(Rcpp::Vector<15, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<24>(Rcpp::Vector<24, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<10>(Rcpp::Vector<10, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<16>(Rcpp::Vector<16, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<13>(Rcpp::Vector<13, Rcpp::PreserveStorage>, long, long)
 * dbg_subset<19>(Rcpp::Vector<19, Rcpp::PreserveStorage>, long, long)
 *
 * So overloaded functions (with repetetive code) is the way to go here for the sake of usability!
 *
 * Compare the signature of an overloaded function:
 * dbg_subset(Rcpp::Vector<14, Rcpp::PreserveStorage>, long, long)
 *
 * See:
 * https://stackoverflow.com/questions/58965423/return-subset-of-a-given-sexp-without-knowing-the-actual-internal-data-type

template <int RTYPE>
Rcpp::Vector<RTYPE> dbg_subset(Rcpp::Vector<RTYPE> x, R_xlen_t index_from, R_xlen_t index_to) {

  Rcpp::Range r = make_Range(index_from, index_to, x.size());

  if (r.get_end() < 0)
    return(Rcpp::Vector<RTYPE>(0));  // empty vector

  return x[r];  // zero-based index
}

template <int RTYPE>
Rcpp::Vector<RTYPE> dbg_subset(Rcpp::Vector<RTYPE> x, R_xlen_t index) {
  // return x[index];  // return type is element type
  return dbg_subset(x, index, index);  // return type is a vector
}

SEXP dbg_subset(SEXP x, R_xlen_t index_from, R_xlen_t index_to){
  // 1-based -> 0-based
  RCPP_RETURN_VECTOR(dbg_subset, x, index_from - 1, index_to);
 // The RCPP_RETURN_VECTOR macro causes all required template instances to be created!
}

*/



