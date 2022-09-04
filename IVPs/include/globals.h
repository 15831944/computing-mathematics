/**
 * @file globals.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <Eigen/Core>

using Vector = Eigen::VectorXd;
using Matrix = Eigen::MatrixXd;

using Real = double;

#define SQUARE(X) ((X)*(X))

const double DBL_EPSILON = 1e-10;

const Real MaxRes = 1e-5;

#endif