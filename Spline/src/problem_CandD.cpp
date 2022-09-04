/**
 * @file problem_CandD.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief for solving problem C and problem D
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Spline.h"
#include "InterpConditions.h"
#include "output.h"

double func(double x)
{
    return 1 / (1 + x*x);
}

int main(int argc, char** argv)
{
    STRING path = "../octave/problem_C.m";
    STRING save_path = "./images/C.png";
    clean_file(path);
    out_new_fig(path);

    /**
     * Spline I
     */
    InterpConditions cond1;
    Spline<1, 3, cardinalB> spline1;
    for(int i = 1 ; i <= 11 ; i ++)
    {
        (cond1.x).push_back(-6+i);
        (cond1.fx).push_back(vector_double{func(-6+i)});
    }
    (cond1.fx[0]).push_back(10/(26*26));
    (cond1.fx[(cond1.fx).size()-1]).push_back(-10/(26*26));
    spline1 = interpolate<3, cardinalB>(cond1);
    std::map<double, Vec<double,1>> t1 = spline1.scanning(-5, 5);
    STRING legend = "cubic";
    out4map<1>(path, t1, 1, legend, STRING("--"));
    /**
     * Spline II
     */
    InterpConditions cond2;
    Spline<1, 2, cardinalB> spline2;
    (cond2.x).push_back(-5);
    (cond2.fx).push_back(vector_double{func(-5)});
    for(int i = 1 ; i <= 10 ; i ++)
    {
        (cond2.x).push_back(i - 5.5);
        (cond2.fx).push_back(vector_double{func(i - 5.5)});
    }
    (cond2.x).push_back(5);
    (cond2.fx).push_back(vector_double{func(5)});
    spline2 = interpolate<2, cardinalB>(cond2, complete);
    std::map<double, Vec<double,1>> t2 = spline2.scanning(-5, 5);
    legend = "quadratic";
    out4map<1>(path, t2, 1, legend, STRING("--"));

    M_DOUBLE_DOUBLE t;
    for(double i = -5; i <= 5 ; i += SCANNING_STEP)
        t.insert(P_DOUBLE_DOUBLE(i, func(i)));
    out4map(path, t, 0, STRING("f(x)"), STRING("-k"));
    out_save(path, save_path);

    /**
     * @brief Problem D
     * 
     */
    vector_double list_x = {-3.5, -3, -0.5, 0, 0.5, 3, 3.5};
    std::cout << "For the cubic cardinalB spline: " << std::endl;
    for(auto it = list_x.begin() ; it < list_x.end() ; it ++)
    {
        std::cout << "x = " << *it << "; err = " 
            << std::abs(func(*it) - spline1(*it)[0]) << std::endl;
    }
    std::cout << "For the quadratic cardinalB spline: " << std::endl;
    for(auto it = list_x.begin() ; it < list_x.end() ; it ++)
    {
        std::cout << "x = " << *it << "; err = " 
            << std::abs(func(*it) - spline2(*it)[0]) << std::endl;
    }
    return 0;
}