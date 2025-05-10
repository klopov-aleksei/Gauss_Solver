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
        std::cerr << "Usage: " << argv[0] << " <augmented_matrix.csv>" << std::endl;
        return 1;
    }

    std::vector<std::vector<double>> rows;
    lazycsv::parser parser(argv[1]);
    auto it{ parser.begin() };
    if (it == parser.end())
    {
        std::cerr << "Empty or invalid CSV" << std::endl;
        return 1;
    }
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
        std::cerr << "No data rows in CSV" << std::endl;
        return 1;
    }
    std::vector<std::string> header;
    for (const auto& cell : *it)
        header.push_back(std::string(cell.raw()));
    ++it;
    const int m{ static_cast<int>(header.size()) };
    if (m != static_cast<int>(rows[0].size()))
    {
        std::cerr << "Header and row size mismatch" << std::endl;
        return 1;
    }

    Eigen::MatrixXd A(n, m);
    for (int i{ 0 }; i < n; ++i)
    {
        if (static_cast<int>(rows[i].size()) != m)
        {
            std::cerr << "Row length mismatch at row " << i << std::endl;
            return 1;
        }
        for (int j = 0; j < m; ++j)
            A(i, j) = rows[i][j];
    }

    try
    {
        Eigen::VectorXd x = gauss(A);
        std::ofstream ofs("result.csv");
        if (!ofs)
            throw std::runtime_error("Cannot open result.csv for writing");
        for (int j{ 0 }; j < m-1; ++j)
        {
            ofs << header[j];
            if (j+1 < m-1) ofs << ",";
        }
        ofs << "\n";
        for (int i{ 0 }; i < x.size(); ++i)
        {
            ofs << x(i);
            if (i+1 < x.size()) ofs << ",";
        }
        ofs << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}