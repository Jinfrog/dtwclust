#include "distmat.h"

#include <memory> // make_shared
#include <string>

#include <RcppArmadillo.h>

namespace dtwclust {

// =================================================================================================
/* Factory methods */
// =================================================================================================

std::shared_ptr<Distmat> DistmatFactory::create(const SEXP& MAT_TYPE, const SEXP& D) {
    std::string type = Rcpp::as<std::string>(MAT_TYPE);
    if (type == "R_MATRIX") {
        return std::make_shared<RDistmat>(D);
    }
    else {
        Rcpp::stop("Unknown matrix type"); // nocov
    }
}

// =================================================================================================
/* R matrix distmat */
// =================================================================================================

// constructor
RDistmat::RDistmat(const SEXP& D)
    : distmat_(RcppParallel::RMatrix<double>(Rcpp::NumericMatrix(D)))
{ }

// operator() for assignment
double& RDistmat::operator() (const int i, const int j) {
    return distmat_(i,j);
}

// dimensions
int RDistmat::nrow() const { return distmat_.nrow(); }
int RDistmat::ncol() const { return distmat_.ncol(); }

} // namespace dtwclust