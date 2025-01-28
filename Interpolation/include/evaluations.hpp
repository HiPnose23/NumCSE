#pragma once
#include <Eigen/Dense>

using namespace Eigen;

VectorXd calc_lambda(int n, VectorXd t);

VectorXd eval(const VectorXd &y, const VectorXd &x, const VectorXd &lambda,
              const VectorXd &t);
