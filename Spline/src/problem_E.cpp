/**
 * @file problem_E.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief for solving problem E
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Spline.h"
#include "InterpConditions.h"
#include "output.h"

const double s3 = std::sqrt(3);

double func(double _x, int _sign)
{
    if(_x > s3) _x = s3;
    if(_x < -s3) _x = -s3;
    return 2/3.0*(std::sqrt(std::abs(_x))+_sign*std::sqrt(3-_x*_x));
}

int main(int argc, char** argv)
{
    STRING path = "../octave/problem_E.m";
    
    clean_file(path);

    int fig = 1;
    vector_int list_N = {10, 40, 160};
    
    /**
     * @brief Linear fitCurve.
     */
    for(auto it = list_N.begin() ; it < list_N.end(); it ++)
    {
        vector_Vec2 points;
        Spline<2, 1, ppForm> mySpline;
        double step = 2 * s3 / (*it / 2.0);
        for(double i = -s3; i <= s3 + EPSILON; i += step) ///< upper half
            points.push_back(Vec2{i, func(i, 1)});
        for(double i = s3 - step; i >= -s3 - EPSILON; i -= step) ///< lowwer half
            points.push_back(Vec2{i, func(i, -1)});
        mySpline = fitCurve<1>(points);
        auto t = mySpline.scanning();

        STRING title = "Linear fitCurve with N = ";
        title.append(std::to_string(*it));
        out_new_fig(path, fig++, true, title);

        out4map<2>(path, t, *it, NULL_str, STRING("-"));

        STRING save_path = "./images/E";
        save_path.append("_linear_N_"); save_path.append(std::to_string(*it)); save_path.append(".png");
        out_save(path, save_path);
    }

    /**
     * @brief Cubic fitCurve.
     */
    for(auto it = list_N.begin() ; it < list_N.end(); it ++)
    {
        vector_Vec2 points;
        Spline<2, 3, ppForm> mySpline;
        double step = 2 * s3 / (*it / 2.0);
        for(double i = -s3; i <= s3 + EPSILON; i += step) ///< upper half
            points.push_back(Vec2{i, func(i, 1)});
        for(double i = s3 - step; i >= -s3 - EPSILON; i -= step) ///< lowwer half
            points.push_back(Vec2{i, func(i, -1)});
        mySpline = fitCurve<3>(points);
        auto t = mySpline.scanning();

        STRING title = "Cubic fitCurve with N = ";
        title.append(std::to_string(*it));
        out_new_fig(path, fig++, true, title);

        out4map<2>(path, t, *it, NULL_str, STRING("-"));

        STRING save_path = "./images/E";
        save_path.append("_cubic_N_"); save_path.append(std::to_string(*it)); save_path.append(".png");
        out_save(path, save_path);
    }
    return 0;
}