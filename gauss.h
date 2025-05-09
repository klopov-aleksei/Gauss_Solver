#ifndef GAUSS_H
#define GAUSS_H

#include <Eigen/Dense>
// Решает расширенную матрицу размером n×(n+1) методом Гаусса с частичным выбором главного элемента.
// A -- копируемый augmented matrix (n rows, n+1 cols).
// Возвращает вектор решения размерности n.
Eigen::VectorXd gauss(Eigen::MatrixXd A);

#endif