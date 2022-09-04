/**
 * @file DiagonalIRK.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/RungeKutta/DiagonalIRK.h"
#include "RHSFunction.h"
#include "globals.h"
#include <cassert>
#include <vector>
#include <Eigen/Dense>
#include <iostream>

namespace TI{namespace RK{

using VecArray = std::vector<Vector>;

PointSet_t_U DiagonalIRK::solve(Vector Initials, RHSFunction* RHS)
{
    assert(T_end_ > 0 && time_step_ > 0); // 参数已设定
    
    int s = getStage(); // stage of RK
    int dim = Initials.size(); // dimension
    PointSet_t_U res;
    Vector Ut = Initials;
    bool FSAL = checkFSAL();
    Real t = 0;
    Real time_step = time_step_;
    Real MaxRes = 1e-15;
    while(t <= T_end_)
    {
        // std::cout << t << std::endl;
        // std::cout << t << std::endl;
        res.insert(Point_t_U(t, Ut));
        if(t == T_end_)
            break;
        if(t + time_step > T_end_)
            time_step = T_end_ - t;
        if(t + time_step_ > T_end_)
            break;

        VecArray z(s, Vector::Zero(dim));
        for(int i = 0 ; i < s ; i ++)
        {
            Vector Con = Ut;
            for(int j = 0 ; j < i ; j ++)
                Con += time_step*A_(i,j)*RHS->eval(z[j], t+c_[j]*time_step);
            if(A_(i,i) == 0) // Explicit
                z[i] = Con;
            else // implicit
            {
                Vector X = Ut;
                while(1)
                {
                    Vector residual = time_step*A_(i,i)*RHS->eval(X, t+c_[i]*time_step) + Con - X;
                    if(residual.norm() < MaxRes)
                        break;
                    Matrix Jacobi = time_step*A_(i,i)*RHS->Jacobi(X, t+c_[i]*time_step) - Matrix::Identity(dim, dim);
                    X -= Jacobi.colPivHouseholderQr().solve(residual);
                }
                z[i] = X;
            }
        }
        if(FSAL)
            Ut = z[s-1];
        else
        {
            Vector d = (A_.transpose()).colPivHouseholderQr().solve(b_);
            Vector tmp = Ut;
            for(int i = 0 ; i < s ; i ++)
                Ut = Ut + d(i) * (z[i]-tmp);
        }
        t = t + time_step;
    }
    return res;
}

};};