/**
 * @file problem_F.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief for solving problem F
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Spline.h"
#include "InterpConditions.h"
#include "output.h"

int main(int argc, char** argv)
{
    STRING path = "../octave/problem_F.m";
    STRING save_path = "./images/F.png";
    clean_file(path);
    out_new_fig(path);

    InterpConditions cond1({1,2,5,6,7,8,10,13,17}, ///< Curve I
        {{3,1},{3.7},{3.9},{4.2},{5.7},{6.6},{7.1},{6.7},{4.5,-0.67}});
    InterpConditions cond2({17,20,23,24,25,27,27.7}, ///< Curve II
        {{4.5,3},{7},{6.1},{5.6},{5.8},{5.2},{4.1,-4.0}});
    InterpConditions cond3({27.7, 28, 29, 30},{{4.1, 0.33}, {4.3}, {4.1}, {3.0, -1.5}}); 
    /**
     * Curnve I
     */
    Spline<1, 3, ppForm> spline1;
    spline1 = interpolate<3, ppForm>(cond1, complete);
    std::map<double, Vec<double,1>> t = spline1.scanning(1, 17);
    out4map<1>(path, t, 1, STRING("Curve I"), STRING("-"));
    /**
     * Curnve II
     */
    Spline<1, 3, ppForm> spline2;
    spline2 = interpolate<3, ppForm>(cond2, complete);
    t = spline2.scanning(17, 27.7);
    out4map<1>(path, t, 2, STRING("Curve II"), STRING("-"));
    /**
     * Curnve III
     */
    Spline<1, 3, ppForm> spline3;
    spline3 = interpolate<3, ppForm>(cond3, complete);
    t = spline3.scanning(27.7, 30);
    out4map<1>(path, t, 3, STRING("Curve III"), STRING("-"));

    out_other_settings(path, {STRING("daspect([1 1])")}); ///< make x and y have same tick.

    out_save(path, save_path);
    return 0;
}