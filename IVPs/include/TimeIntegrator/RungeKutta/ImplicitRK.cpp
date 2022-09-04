/**
 * @file ImplicitRK.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 实现class ImplicitRK
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/RungeKutta/ImplicitRK.h"
#include "RHSFunction.h"
#include "globals.h"
#include <cassert>
#include <vector>
#include <Eigen/KroneckerProduct>
#include <Eigen/Dense>

namespace TI{namespace RK{

using VecArray = std::vector<Vector>;

Vector combine(const VecArray &z)
{
    assert(z.size() > 0);
    int len = (z[0]).size();
    int N = z.size();
    Vector res(N * len);
    for(int i = 0 ; i < N ; i ++)
        for(int j = 0 ; j < len ; j ++)
        {
            res(i*len+j) = z[i](j);
        }
    return res;
}

VecArray split(const Vector &Z, int len)
{
    assert(Z.size() % len == 0);
    int N = Z.size() / len;
    VecArray res(N, Vector(len));
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0 ; j < len ; j ++)
            res[i](j) = Z(i*len+j);
    }
    return res;
}

PointSet_t_U ImplicitRK::solve(Vector Initials, RHSFunction* RHS)
{
    assert(T_end_ > 0 && time_step_ > 0); // 参数已设定
    
    int s = getStage(); // stage of RK
    int dim = Initials.size(); // dimension
    PointSet_t_U res;
    Vector Ut = Initials;
    Real time_step = time_step_;
    Real t = 0;
    Matrix tmp = Eigen::KroneckerProduct(A_, Matrix::Identity(dim,dim));
    Real MaxRes = 1e-12;
    while(t <= T_end_)
    {
        // std::cout << t << std::endl;
        res.insert(Point_t_U(t, Ut));
        if(t == T_end_)
            break;
        if(t + time_step > T_end_)
            time_step = T_end_ - t;
        // VecArray y(s, Vector::Zero(dim));
        // y[0] = RHS -> eval(Ut, t);

        // 解非线性方程组
        Vector Z = Vector::Zero(dim*s);
        Matrix Jacobi = RHS -> Jacobi(Ut, t);
        Matrix Coeff = Matrix::Identity(dim*s, dim*s) 
                - time_step*Eigen::KroneckerProduct(A_, Jacobi);
        
        VecArray z;
        while(1)
        {
            // 计算 F
            z = split(Z, dim);
            VecArray f; 
            // std::cout << "1" << std::endl;
            for(int i = 0; i < s ; i ++)
                f.push_back(RHS->eval(Ut+z[i], t+c_[i]*time_step));
            // std::cout << "22" << std::endl;
            Vector F = combine(f);
            // std::cout << "2" << std::endl;
            // 计算留数
            Vector residual = Z - time_step*tmp*F;
            // std::cout << "3" << std::endl;
            if(residual.norm() < MaxRes) // 解是否达到给定精度
                break;
            // 牛顿迭代
            
            // std::cout << "4" << std::endl;
            Z -= Coeff.colPivHouseholderQr().solve(residual);
            // std::cout << "5" << std::endl;
        }
        // std::cout << "6" << std::endl;
        Vector d = (A_.transpose()).colPivHouseholderQr().solve(b_);
        // std::cout << "7" << std::endl;
        for(int i = 0 ; i < s ; i ++)
            Ut = Ut + d(i) * z[i];
        t = t + time_step;
    }
    return res;
}

};};