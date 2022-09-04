/**
 * @file problem_B.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief for solving problem B
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
    return 1 / (1 + 25*x*x);
}

int main(int argc, char** argv)
{
    STRING path = "../octave/problem_B.m";
    STRING save_path1 = "./images/B_complete.png";
    STRING save_path2 = "./images/B_notAknot.png";
    vector_int list_N = {6,11,21,41,81};
    clean_file(path);
    
    /**
     * @brief Complete cubic spline.
     * 
     */
    out_new_fig(path, 1, true, STRING("complete cubic spline"));
    std::cout << "For complete cubic spline: " << std::endl;
    for(auto it = list_N.begin() ; it < list_N.end(); it ++)
    {
        double N = *it;
        double step = 2 / (N-1);
        InterpConditions cond;
        Spline<1, 3, ppForm> mySpline;
        for(double i = -1 ; i <= 1+EPSILON ; i += step)
        {
            (cond.x).push_back(i);
            (cond.fx).push_back(vector_double{func(i)});
        }
        mySpline = interpolate<3, ppForm>(cond, complete);
        std::map<double, Vec<double,1>> t = mySpline.scanning(-1, 1);
        STRING legend = "N = ";
        out4map<1>(path, t, *it, legend.append(std::to_string(*it)), STRING("--"));
        /**
         * Compute the max-norm.
         */ 
        double max = -1;
        for(auto it1 = (cond.x).begin(); it1 < (cond.x).end() - 1 ; it1 ++)
        {
            double mid = (*it1 + *(it1+1))/2;
            double t = std::abs(func(mid) - mySpline(mid)[0]);
            if(t > max)
                max = t;
        }
        std::cout << "While N = " << *it << ", the max-norm is " << max << std::endl;
    }

    M_DOUBLE_DOUBLE t;
    for(double i = -1; i <= 1 ; i += SCANNING_STEP)
        t.insert(P_DOUBLE_DOUBLE(i, func(i)));
    out4map(path, t, 0, STRING("f(x)"), STRING("-k"));
    out_save(path, save_path1);

    /**
     * @brief NotAknot cubic spline.
     * 
     */
    out_new_fig(path, 2, true, STRING("notAknot cubic spline"));
    std::cout << "For notAknot cubic spline: " << std::endl;
    for(auto it = list_N.begin() ; it < list_N.end(); it ++)
    {
        double N = *it;
        double step = 2 / (N-1);
        InterpConditions cond;
        Spline<1, 3, ppForm> mySpline;
        for(double i = -1 ; i <= 1+EPSILON ; i += step)
        {
            (cond.x).push_back(i);
            (cond.fx).push_back(vector_double{func(i)});
        }
        mySpline = interpolate<3, ppForm>(cond, notAknot);
        std::map<double, Vec<double,1>> t = mySpline.scanning(-1, 1);
        STRING legend = "N = ";
        out4map<1>(path, t, *it, legend.append(std::to_string(*it)), STRING("--"));
        /**
         * Compute the max-norm.
         */ 
        double max = -1;
        for(auto it1 = (cond.x).begin(); it1 < (cond.x).end() - 1 ; it1 ++)
        {
            double mid = (*it1 + *(it1+1))/2;
            double t = std::abs(func(mid) - mySpline(mid)[0]);
            if(t > max)
                max = t;
        }
        std::cout << "While N = " << *it << ", the max-norm is " << max << std::endl;
    }
    out4map(path, t, 0, STRING("f(x)"), STRING("-k"));
    out_save(path, save_path2);

    return 0;
}