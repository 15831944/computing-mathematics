/**
 * @file RHSFunctionFactory.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __RHS_FUNCTION_FACTORY_CPP__
#define __RHS_FUNCTION_FACTORY_CPP__

#include "RHSFunctionFactory.h"
#include "./RHSFunction/ThreeBody.h"

namespace
{
    RHSFunction* createThreeBody()
    {
        return new RHS::ThreeBody();
    }
    const bool _ThreeBody_registered = RHSFunctionFactory::Instance().Register("ThreeBody", createThreeBody);
}

#endif