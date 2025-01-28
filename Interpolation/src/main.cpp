#include "evaluations.hpp"
#include "nodes.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace Eigen;

template <class Function> VectorXd get_values(Function &&f, const VectorXd &t) {
  int n = t.size();
  VectorXd y(n);
  for (int i = 0; i < n; i++) {
    y(i) = f(t(i));
  }
  return y;
}

// Function to save into .csv file (Chat-GPT)
void saveToCSV(const VectorXd &x, const VectorXd &y,
               const std::string &filename) {
  std::ofstream file(filename);
  if (file.is_open()) {
    file << "x,y\n"; // Optional header
    for (int i = 0; i < x.size(); ++i) {
      file << x[i] << "," << y[i] << "\n";
    }
    file.close();
  } else {
    std::cerr << "Unable to open file " << filename << std::endl;
  }
}

int main() {

  auto testfunc = [](double x) { return x * x; }; // Function to approximate
  // define interval
  double a = -1;
  double b = 1;
  int n = 13; // number of nodes
  VectorXd t(n);
  VectorXd y(n);
  t = get_chebychev_nodes(a, b, n);
  y = get_values(testfunc, t);
  VectorXd lambda = calc_lambda(n, t);
  int num_plotpoints = 200;

  // Output the approximation

  VectorXd x = VectorXd::LinSpaced(num_plotpoints, -10, 10);
  VectorXd values_of_poly = eval(y, x, lambda, t);

  std::cout << std::setw(15) << "x values" << std::setw(15) << "y values"
            << std::endl
            << std::endl;

  for (int i = 0; i < x.size(); i++) {
    std::cout << std::setw(15) << x[i] << std::setw(15) << values_of_poly[i]
              << std::endl;
  }

  // Save vectors to .csv file so python script can access them
  saveToCSV(x, values_of_poly, "output.csv");

  return 0;
}
