#include "/usr/local/include/eigen3/Eigen/Dense"
#include <iostream>

void givens2d(Eigen::MatrixXd &A, int k){
  Eigen::Matrix2d G;
  double gamma;
  double sigma;
  double rho;
    

  if(k == A.rows()-2){
    Eigen::MatrixXd B = A.block(k,k,2,2);
    gamma = B(0,0)/(std::sqrt(B(0,0)*B(0,0)+B(1,0)*B(1,0)));
    sigma = B(1,0)/(std::sqrt(B(0,0)*B(0,0)+B(1,0)*B(1,0)));
    G << gamma, sigma, -sigma, gamma;
    std::cout << "Matrix G: " << std::endl;
    std::cout << G << std::endl << std::endl;
    A.block(k,k,2,2) = G*B;
  }
  else {
    Eigen::MatrixXd B = A.block(k,k,2,3);
    gamma = B(0,0)/(std::sqrt(B(0,0)*B(0,0)+B(1,0)*B(1,0)));
    sigma = B(1,0)/(std::sqrt(B(0,0)*B(0,0)+B(1,0)*B(1,0)));
    G << gamma, sigma, -sigma, gamma;
    std::cout << "Matrix G: " << std::endl;
    std::cout << G << std::endl << std::endl;
    A.block(k,k,2,3) = G*B;
  }
}

int main(){
  int n = 10;
  Eigen::VectorXd d = Eigen::VectorXd::LinSpaced(n,1,n);
  Eigen::VectorXd l = Eigen::VectorXd::LinSpaced(n-1,n+1,n+9);
  Eigen::VectorXd u = Eigen::VectorXd::LinSpaced(n-1,n+10,n+18);
  Eigen::MatrixXd A = d.asDiagonal();
  A.diagonal(1) = u; A.diagonal(-1) = l;

  std::cout << "Tridiagonal Matrix A before a 2D givens rotation: " << std::endl;
  std::cout << A << std::endl << std::endl;
  for(int i = 0; i<n-1; i++){
    givens2d(A,i);
    std::cout << "Matrix A after " << i+1 << " iterations of 2D givens: " << std::endl;
    std::cout << A << std::endl<< std::endl;

  }

  return 0;
}
