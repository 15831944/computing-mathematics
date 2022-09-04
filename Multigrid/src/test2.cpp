/**
 * @file test2.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Multigrid.h"
#include "genJson.h"
#include "test_helper.h"
#include <cmath>

using std::exp, std::sin, std::cos, std::string;

double u(double x, double y)
{
    // return x*x;
    return exp(y+sin(x));
}

double f(double x, double y)
{
    // return -2;
    return (sin(x)-cos(x)*cos(x)-1)*exp(y+sin(x));
}

double ux(double x, double y)
{
    return cos(x)*exp(y+sin(x));
}

double uy(double x, double y)
{
    return exp(y+sin(x));
}

int main()
{
    class helper* test_dirichlet = new helper2d(0, string("2d_dirichlet"), u, f);
    class helper* test_mixed = new helper2d(1, string("2d_mixed"), u, f, 0, ux, uy, Vec(1,1));
    class helper* test_ir = new helper2d(0, string("2d_ir"), u, f, 1/16.0);
    test_dirichlet -> start_test();
    test_mixed->start_test();
    test_ir->start_test();
}