/**
 * @file RHSFunction.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __RHS_FUNCTION__
#define __RHS_FUNCTION__

#include "globals.h"

class RHSFunction
{
public:
    // virtual Vec operator()(Vec u, Real t) = 0;
    virtual Vector eval(Vector u, Real t) = 0;
    virtual Matrix Jacobi(Vector u, Real t)
    {
        return Matrix();    
    }
};

#endif