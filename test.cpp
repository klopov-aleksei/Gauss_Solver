#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "gauss.h"
#include <random>

TEST(GaussSolver, SimpleSystem)
{
    Eigen::MatrixXd A(2,3);
    A << 1, 2, 3,
         4, 5, 6;
    auto x = gauss(A);
    ASSERT_EQ(x.size(), 2);
    EXPECT_NEAR(x(0), -1.0, 1e-9);
    EXPECT_NEAR(x(1),  2.0, 1e-9);
}

TEST(GaussSolver, RandomSystem)
{
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(1.0, 10.0);
    for (int n : {10,50,100})
    {
        Eigen::MatrixXd A(n,n);
        Eigen::VectorXd b(n);
        Eigen::MatrixXd aug(n,n+1);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                double v = dist(gen);
                A(i,j) = v;
                aug(i,j) = v;
            }
            b(i) = aug(i,n) = dist(gen);
        }
        Eigen::VectorXd x1 = gauss(aug);
        Eigen::VectorXd x2 = A.partialPivLu().solve(b);
        for (int i = 0; i < n; ++i)
            EXPECT_NEAR(x1(i), x2(i), 1e-6);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}