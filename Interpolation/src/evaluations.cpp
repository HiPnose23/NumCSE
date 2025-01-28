#include "evaluations.hpp"
#include <cmath>

#include <limits>

using namespace Eigen;
VectorXd calc_lambda(int n, VectorXd t) {
  VectorXd lambda(n);
  for (unsigned k = 0; k < n; ++k) {
    // little workaround: in \eigen cannot subtract a vector
    // from a scalar; multiply scalar by vector of ones
    lambda(k) =
        1. / ((t(k) * VectorXd::Ones(k) - t.head(k)).prod() *
              (t(k) * VectorXd::Ones(n - k - 1) - t.tail(n - k - 1)).prod());
  }
  return lambda;
}

VectorXd eval(const VectorXd &y, const VectorXd &x, const VectorXd &lambda,
              const VectorXd &t) {
  assert(t.size() == lambda.size() && "Sizes of 't' and 'lambda' must match.");
  assert(y.size() == lambda.size() && "Sizes of 'y' and 'lambda' must match.");

  int N = x.size();
  VectorXd p(N);
  for (int i = 0; i < N; ++i) {
    const VectorXd z =
        (x[i] * VectorXd::Ones(t.size()) - t); // ERROR HERE (Size Mismatch) ???

    // Check if we want to evaluate close to a node
    const double tref{z.cwiseAbs().maxCoeff()}; // reference size
    int k;
    if (z.cwiseAbs().minCoeff(&k) <
        tref * std::abs(std::numeric_limits<double>::epsilon())) {
      // evaluation at node $\cob{t_k}$
      p[i] = y[k];

    } else {
      const VectorXd mu = lambda.cwiseQuotient(z);

      p[i] = (mu.cwiseProduct(y)).sum() / mu.sum();
    }
  } // end for

  return p;
}
