/**
 * @file RungeKutta.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __RUNGE_KUTTA_H__
#define __RUNGE_KUTTA_H__

#include "TimeIntegrator.h"
#include "globals.h"
#include <vector>

namespace TI
{

class RungeKutta : public TimeIntegrator
{
protected: 
    Matrix A_;
    Vector b_, c_;
    virtual void resizeParam(int s);
public:
    int getStage(){return b_.size();};
    bool checkFSAL();
};

}

#endif