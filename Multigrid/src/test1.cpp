/**
 * @file test1.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief 1-dimension. \n
 * u(x) = exp(1+sin(x)), Dirichlet
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Multigrid.h"
#include "genJson.h"
#include "test_helper.h"
#include <cmath>

using std::exp, std::sin, std::cos, std::string;

double u(double x)
{
    // return x*x;
    return exp(1+sin(x));
}

double f(double x)
{
    // return -2;
    return (sin(x)-cos(x)*cos(x))*exp(1+sin(x));
}

int main()
{
    double neumann = cos(1)*exp(1+sin(1));
    class helper* test_dirichlet = new helper1d(0, string("1d_dirichlet"), u, f);
    test_dirichlet->start_test();
    class helper* test_mixed = new helper1d(1, "1d_mixed", u, f, neumann);
    test_mixed -> start_test();
}