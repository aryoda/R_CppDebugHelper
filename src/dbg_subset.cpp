#include <Rcpp.h>
using namespace Rcpp;


/* Design decisions:

   1. Use internally templated functions to avoid code duplication
      but instantiate all required types via overloaded functions that use concrete data types.

   2. Use the index base of the underlying data type (R = 1, Rcpp = 0).
      Do not substract 1 from Rcpp indexes (R indexes start with 1).
      Developers and (human) debugger do know those details - don't confuse them with a 3rd variation!

      TODO I am questioning this decision. It is sometimes difficult to recognize the index base, eg. here:

         (gdb) call dbg_print(dbg_get(e, "a"))
         [1]  1  2  3  4  5  6  7  8  9 10
         (gdb) call dbg_print(dbg_subset(dbg_get(e, "a"), 3, 5))
         [1] 3 4 5

         (gdb) call dbg_print(dv)
         [1] "2010-12-31" "2011-01-01" "2011-05-29" NA
         (gdb) call dbg_print(dbg_subset(dv, 1, 2))
         [1] "2011-01-01" "2011-05-29"
         (gdb) call dbg_print(dbg_subset(dv->data, 1, 2))
         [1] "2010-12-31" "2011-01-01"

 */



// Vector is the templated base class for all Rcpp vectors. See the source code in the file
// Rcpp/inst/include/Rcpp/vector/vector.h



// Returns a range guaranteed to respect the vector boundaries.
// -1 indicates an empty range for whatever reason.
// indexes are 0-based (Rcpp/CPP compliant)
Rcpp::Range make_Range(R_xlen_t index_from, R_xlen_t index_to, R_xlen_t vec_size) {
  // ensure  bounds
  if (index_from < 0) {
    Rcpp::Rcout << "index_from is out of range: " << index_from << " (assuming 0)" << std::endl;
    index_from = 0;
  }

  if (index_to >= vec_size) {
    Rcpp::Rcout << "index_to is out of range: " << index_to << " (assuming " << vec_size - 1 << ")" << std::endl;
    index_to = vec_size - 1;
  }

  if (vec_size < 1 || index_from > index_to || index_from >= vec_size) {
    index_from = index_to = -1;  // empty subset
  }

  return Rcpp::Range(index_from, index_to);  // Rcpp::seq seems to be the same (inlined function returning a Range)
}



// Subset an index range
// TODO Use const T&
// TODO How to hide this function (= no export from the shared library)?
template<typename T>
T internal_subset(T x, R_xlen_t index_from, R_xlen_t index_to) {
    Rcpp::Range r = make_Range(index_from, index_to, x.size());

    if (r.get_end() < 0)
      return(T(0));  // empty vector

    T res = x[r];

    // copy class attribute
    if (x.hasAttribute("class"))
      res.attr("class") = x.attr("class");

    // copy levels
    if (x.hasAttribute("levels"))
      res.attr("levels") = x.attr("levels");

    return res;  // zero-based index

}



Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index_from, R_xlen_t index_to) {

  return internal_subset(x, index_from, index_to);
//   Rcpp::Range r = make_Range(index_from, index_to, x.size());
//   if (r.get_end() < 0)
//     return(NumericVector(0));  // empty vector
//
//   Rcpp::NumericVector res = x[r];
//   return res;  // zero-based index
}

// subset one element
Rcpp::NumericVector dbg_subset(Rcpp::NumericVector x, R_xlen_t index) {
  // Design decision: Returns a vector with one element (not the element itself)
  // return x[index];  // return type is element type
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::ComplexVector dbg_subset(Rcpp::ComplexVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::ComplexVector dbg_subset(Rcpp::ComplexVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::IntegerVector dbg_subset(Rcpp::IntegerVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::IntegerVector dbg_subset(Rcpp::IntegerVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::LogicalVector dbg_subset(Rcpp::LogicalVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::LogicalVector dbg_subset(Rcpp::LogicalVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::RawVector dbg_subset(Rcpp::RawVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::RawVector dbg_subset(Rcpp::RawVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::CharacterVector dbg_subset(Rcpp::CharacterVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::CharacterVector dbg_subset(Rcpp::CharacterVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::List dbg_subset(Rcpp::List x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::List dbg_subset(Rcpp::List x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::ExpressionVector dbg_subset(Rcpp::ExpressionVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::ExpressionVector dbg_subset(Rcpp::ExpressionVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::DateVector dbg_subset(Rcpp::DateVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::DateVector dbg_subset(Rcpp::DateVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



Rcpp::DatetimeVector dbg_subset(Rcpp::DatetimeVector x, R_xlen_t index_from, R_xlen_t index_to) {
  return internal_subset(x, index_from, index_to);
}

Rcpp::DatetimeVector dbg_subset(Rcpp::DatetimeVector x, R_xlen_t index) {
  return dbg_subset(x, index, index);  // return type is a vector
}



// subsetting a data.frame means to subset the rows (not the columns!)
// so we need to have different implementation here...
Rcpp::DataFrame dbg_subset(Rcpp::DataFrame x, R_xlen_t row_index_from, R_xlen_t row_index_to) {

  // // TODO Assumption: col names do always exist
  // Rcpp::CharacterVector col_names = x.names();
  //
  // Rcpp::DataFrame res = Rcpp::DataFrame::create();
  //
  // // copy each subsetted column vector into the result data.frame
  // for (R_xlen_t i = 0; i < x.ncol(); ++i) {
  //   // res.push_back(NumericVector(0));  // dbg_subset(x[i], index_from, index_to)
  //   // res.push_back(dbg_subset(x[i], row_index_from, row_index_to)); // Error: call to dbg_subset is ambiguous
  // }

  // Based on the ideas shown here:
  // https://stackoverflow.com/questions/22828361/rcpp-function-to-select-and-to-return-a-sub-dataframe

  // use R function to subset the data.frame
  Function subset("[.data.frame");  // "declare" R function

  Rcpp::Range r = make_Range(row_index_from, row_index_to, x.nrows());

  if (r.get_end() < 0)
    return(Rcpp::DataFrame::create());  // empty data.frame

  // convert Rcpp index values from 0-based to R's 1-based index values (see include/Rcpp/sugar/Range.h)
  r++;

  Rcpp::Rcout << "data.frame row subset: " << r.get_start() << "-" << r.get_end() << std::endl;

  // Rcpp::IntegerVector(r.begin(), r.end())
  return subset(x, r, R_MissingArg);  // row numbers in "r" seem to be shifted from 0-based to 1-base when calling R
}

Rcpp::DataFrame dbg_subset(Rcpp::DataFrame x, R_xlen_t row_index) {
  return dbg_subset(x, row_index, row_index);  // return type is a vector
}




// SEXP indexes start with 1 (not 0 as in Rcpp data types)!!!
SEXP dbg_subset(SEXP x, R_xlen_t index_from, R_xlen_t index_to){
  // TODO data.frame's are currently handled as lists. Add an alternative implementation here...
  //      May require including the SEXP internal data structure to query the internal type...
  if (Rf_inherits(x, "data.frame")) {
    Rcpp::Rcout << "data.frame recognized..." << std::endl;
    // convert R index values from 1-based to Rcpp's 0-based
    return dbg_subset(Rcpp::as<DataFrame>(x), index_from - 1, index_to - 1);
  }

  // convert R index values from 1-based to Rcpp's 0-based
  RCPP_RETURN_VECTOR(internal_subset, x, index_from - 1, index_to - 1);

  // Idea based on:
  // https://stackoverflow.com/questions/58965423/return-subset-of-a-given-sexp-without-knowing-the-actual-internal-data-type

  // See the code of RCPP_RETURN_VECTOR in:
  // include/Rcpp/macros/dispatch.h

}




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
 // See the code in:
 // include/Rcpp/macros/dispatch.h
}

*/



