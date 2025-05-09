#include <stdexcept>

Eigen::VectorXd gauss(Eigen::MatrixXd A)
{
    const int n{ A.rows() };
    if (A.cols() != n+1)
        throw std::invalid_argument("Augmented matrix must have n+1 columns");

    for (int i{ 0 }; i < n; ++i)
    {
        // Partial pivoting: find max abs in column i on rows i..n-1
        int pivot{ i };
        A.col(i).segment(i, n-i).cwiseAbs().maxCoeff(&pivot);
        if (pivot != i)
            A.row(i).swap(A.row(pivot));
        double diag = A(i,i);
        if (std::abs(diag) < 1e-12)
            throw std::runtime_error("Matrix is singular or nearly singular");
        // Normalize pivot row (vectorized)
        A.row(i).tail(n+1-i) /= diag;
        // Eliminate other rows using vectorized outer-product
        for (int r{ 0 }; r < n; ++r)
        {
            if (r == i) continue;
            double factor = A(r,i);
            // A.row(r).segment(i, n+1-i) -= factor * A.row(i).segment(i, n+1-i);
            A.row(r).tail(n+1-i).noalias() -= factor * A.row(i).tail(n+1-i);
        }
    }
    // Решение -- последний столбец
    return A.col(n);
}

using std::vector<std::vector<double>> = matrix;
std::vector<double> gauss(matrix A)
{
    int n{ static_cast<int>(A[0].size()) };
    for (int i{ 0 }; i < n; i++)
    {
        // finding pivot
        int best{ i };
        for (int j{ i + 1 }; j < n; j++)
            if (std::abs(a[j][i]) > abs(a[best][i]))
                best = j;
        // swapping rows
        std::swap(a[best], a[i]);
        // normalize i-th row (in the left are nulls, nothing to do with them)
        for (int j{ n }; j >= i; j--)
            a[i][j] /= a[i][i];
        // zero out all left сells in i-th column
        for (int j{ 0 }; j < n; j++)
            if (j != i)
                // in the left are only nulls, so you can pass only the right side
                for (int k{ n }; k >= i; k--)
                    a[j][k] -= a[i][k] * a[j][i];
    }
    std::vector<double> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = a[i][n];
    return ans;
}