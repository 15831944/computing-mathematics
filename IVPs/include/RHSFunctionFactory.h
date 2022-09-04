/**
 * @file RHSFunctionFactory.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __RHS_FUNCTION_FACTORY_H__
#define __RHS_FUNCTION_FACTORY_H__

#include "GeneralFactory.h"
#include "RHSFunction.h"

using RHSFunctionFactory = Factory<RHSFunction, std::string>;

#endif