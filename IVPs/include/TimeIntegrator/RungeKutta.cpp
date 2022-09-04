/**
 * @file RungeKutta.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/RungeKutta.h"

namespace TI
{

bool RungeKutta::checkFSAL()
{
    int s = getStage();
    if(c_[s - 1] != 1)
        return false;
    for(int j = 0 ; j < s ; j ++)
        if(b_[j] != A_(s-1, j))
            return false;
    return true;
}

void RungeKutta::resizeParam(int s)
{
    A_.resize(s, s);
    b_.resize(s);
    c_.resize(s);
}

};
