#include "nodes.hpp"
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;

VectorXd get_chebychev_nodes(double a, double b, int n) {
  VectorXd t(n);
  for (int k = 0; k < n; k++) {
    t(k) = a + 0.5 * (b - a) *
                   (std::cos((2. * k + 1.) / (2. * (n + 1.)) * M_PI) + 1.);
  }
  return t;
}
