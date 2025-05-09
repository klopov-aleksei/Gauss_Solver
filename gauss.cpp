#include <Eigen/Dense>
#include <stdexcept>

Eigen::VectorXd gauss(Eigen::MatrixXd A)
{
    const int n{ static_cast<int>(A.rows()) };
    if (A.cols() != n+1)
        throw std::invalid_argument("Augmented matrix must have n+1 columns");

    for (int i{ 0 }; i < n; ++i)
    {
        Eigen::Index relPivot = 0;
        A.col(i).segment(i, n-i).cwiseAbs().maxCoeff(&relPivot);
        int pivot = static_cast<int>(relPivot) + i;
        if (pivot != i)
            A.row(i).swap(A.row(pivot));
        double diag = A(i,i);
        if (std::abs(diag) < 1e-12)
            throw std::runtime_error("Matrix is singular or nearly singular");
        A.row(i).tail(n+1-i) /= diag;
        for (int r{ 0 }; r < n; ++r)
        {
            if (r == i) continue;
            double factor = A(r,i);
            A.row(r).tail(n+1-i).noalias() -= factor * A.row(i).tail(n+1-i);
        }
    }
    // Решение -- последний столбец
    return A.col(n);
}