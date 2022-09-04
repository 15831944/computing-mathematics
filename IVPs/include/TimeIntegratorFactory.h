/**
 * @file TimeIntegratorFactory.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 生成TimeIntegrator对象的工厂
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TIME_INTEGRATOR_FACTORY_H__
#define __TIME_INTEGRATOR_FACTORY_H__

#include "GeneralFactory.h"
#include "TimeIntegrator.h"

using TimeIntegratorIdentifier = std::pair<std::string, int>;
using TimeIntegratorFactory = Factory<TimeIntegrator, TimeIntegratorIdentifier>;

#endif
