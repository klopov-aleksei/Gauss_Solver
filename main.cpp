#include <Eigen/Dense>
#include <lazycsv.hpp>
#include "gauss.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <augmented_matrix.csv>";
        return 1;
    }

    std::vector<std::vector<double>> rows;
    lazycsv::parser parser(argv[1]);
    for (const auto& row : parser)
    {
        std::vector<double> r{};
        for (const auto& cell : row)
        {
            r.push_back(std::stod(std::string(cell.raw())));
        }
        rows.push_back(std::move(r));
    }

    const int n{ static_cast<int>(rows.size()) };
    if (n == 0)
    {
        std::cerr << "Empty or invalid CSV";
        return 1;
    }

    Eigen::MatrixXd A(n, n + 1);
    for (int i{ 0 }; i < n; ++i)
    {
        if (static_cast<int>(rows[i].size()) != n + 1)
        {
            std::cerr << "Row length mismatch at row " << i << std::endl;
            return 1;
        }
        for (int j = 0; j < n + 1; ++j)
            A(i, j) = rows[i][j];
    }

    auto it = parser.begin();
    std::vector<std::string> header;
    for (const auto& cell : *it)
        header.push_back(std::string(cell.raw()));
    ++it;

    if (static_cast<int>(header.size()) != static_cast<int>(rows[0].size()))
    {
        std::cerr << "Header length and row length mismatch";
        return 1;
    }

    try
    {
        Eigen::VectorXd x = gauss(A);
        std::ofstream ofs("result.csv");
        if (!ofs) throw std::runtime_error("Cannot open result.csv for writing");
        for (int j = 0; j < n; ++j)
        {
            ofs << header[j] << (j + 1 < n ? "," : " ");
        }
        for (int i = 0; i < x.size(); ++i)
        {
            ofs << x(i) << (i + 1 < x.size() ? ", " : " ");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}