#pragma once

// Computes KroneckerProduct of A and B
template <class Mat_Type>
Mat_Type KroneckerProduct(const Mat_Type &A, const Mat_Type &B) {
    int arows = A.rows();
    int acols = A.cols();
    int brows = B.rows();
    int bcols = B.cols();

    Mat_Type result(arows*brows,acols*bcols);

    for(int i = 0; i<arows; i++){
        for(int j = 0; j<acols; j++){
            result.block(i*brows, j*bcols, brows, bcols) = A(i,j)*B;
        }
    }

    return result;
}
