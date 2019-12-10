// #include <Rinternals.h>
// #include <Rinterface.h>
#include <Rcpp.h>

using namespace Rcpp;


// void my_WriteConsole(const char *buf, int len) {
//   // NOP
// }
//
// // "register" call-back function
// ptr_R_WriteConsole = &my_WriteConsole;



// #include <Rcpp.h>
// using namespace Rcpp;
//
// // head_tail function
//
// class Ends {
// private:
//   int n;
//
// public:
//   Ends(int n)
//     : n(n)
//   {}
//
//   template <int RTYPE>
//   Vector<RTYPE> operator()(const Vector<RTYPE>& x)
//   {
//     n = std::min((R_xlen_t)n, x.size() / 2);
//     Vector<RTYPE> res(2 * n);
//
//     std::copy(x.begin(), x.begin() + n, res.begin());
//     std::copy(x.end() - n, x.end(), res.begin() + n);
//
//     return res;
//   }
// };
//
//
// RObject dbg_ends(RObject x, int n = 6)
// {
//   RCPP_RETURN_VECTOR(Ends(n), x);
// }
//
//
//
// // head function
//
// template <int RTYPE>
// Vector<RTYPE> first_two_impl( Vector<RTYPE> xin){
//   Vector<RTYPE> xout(2) ;
//   for( int i=0; i<2; i++ ){
//     xout[i] = xin[i] ;
//   }
//   return xout ;
// }
//
// // [[Rcpp::export]]
// SEXP first_two( SEXP xin ){
//   RCPP_RETURN_VECTOR(first_two_impl, xin) ;
// }




// subset function

// [[Rcpp::plugins(cpp11)]]

// template <int RTYPE>
// Rcpp::Vector<RTYPE> subset_impl(Rcpp::Vector<RTYPE> x,
//                                 R_xlen_t index_from,
//                                 R_xlen_t index_to){
//   // range [index_from, index_to)
//   Rcpp::Vector<RTYPE> subset(index_to - index_from);
//   std::copy(x.cbegin() + index_from, x.cbegin() + index_to, subset.begin());
//   // special case for factors == INTSXP with "class" and "levels" attribute
//   if (x.hasAttribute("levels")){
//     subset.attr("class") = x.attr("class");
//     subset.attr("levels") = x.attr("levels");
//   }
//   return subset;
// }
//


// SEXP dbg_subset(SEXP x, R_xlen_t index_from, R_xlen_t index_to){
//   // 1-based -> 0-based
//   RCPP_RETURN_VECTOR(subset_impl, x, index_from - 1, index_to);
// }


