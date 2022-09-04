/**
 * @file TimeIntegratorFactory.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator.h"
#include "TimeIntegratorFactory.h"
#include "TimeIntegrator/RungeKutta/ClassicalRK.h"
#include "TimeIntegrator/LinearMultistep/AdamsBashforth.h"
#include "TimeIntegrator/LinearMultistep/AdamsMoulton.h"
#include "TimeIntegrator/LinearMultistep/BDF.h"
#include "TimeIntegrator/RungeKutta/Fehlberg.h"
#include "TimeIntegrator/RungeKutta/DormandPrince.h"
#include "TimeIntegrator/RungeKutta/GaussLegendre.h"
#include "TimeIntegrator/RungeKutta/ESDIRK.h"

namespace
{
    /**
     * @brief Classical RK
     */
    TimeIntegrator* createClassicalRK()
    {
        return new TI::RK::ClassicalRK;
    }
    const bool _ClassicalRK_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("ClassicalRK", 0), createClassicalRK);
    
    TimeIntegrator* createFehlberg()
    {
        return new TI::RK::Fehlberg;
    }
    const bool _Fehlberg_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("Fehlberg", 0), createFehlberg);

    TimeIntegrator* createDormandPrince()
    {
        return new TI::RK::DormandPrince;
    }
    const bool _DormandPrince_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("DormandPrince", 0), createDormandPrince);

    /**
     * @brief AdamsBashforth
     * 
     */
    TimeIntegrator* createAB1()
    {
        return new TI::LM::AB1;
    }
    const bool _AB1_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsBashforth", 1), createAB1);

    TimeIntegrator* createAB2()
    {
        return new TI::LM::AB2;
    }
    const bool _AB2_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsBashforth", 2), createAB2);

    TimeIntegrator* createAB3()
    {
        return new TI::LM::AB3;
    }
    const bool _AB3_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsBashforth", 3), createAB3);

    TimeIntegrator* createAB4()
    {
        return new TI::LM::AB4;
    }
    const bool _AB4_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsBashforth", 4), createAB4);

    /**
     * @brief AdamsMoulton
     * 
     */
    TimeIntegrator* createAM2()
    {
        return new TI::LM::AM2;
    }
    const bool _AM2_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsMoulton", 2), createAM2);

    TimeIntegrator* createAM3()
    {
        return new TI::LM::AM3;
    }
    const bool _AM3_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsMoulton", 3), createAM3);

    TimeIntegrator* createAM4()
    {
        return new TI::LM::AM4;
    }
    const bool _AM4_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsMoulton", 4), createAM4);

    TimeIntegrator* createAM5()
    {
        return new TI::LM::AM5;
    }
    const bool _AM5_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("AdamsMoulton", 5), createAM5);

    /**
     * @brief BDF
     * 
     */
    TimeIntegrator* createBDF1()
    {
        return new TI::LM::BDF1;
    }
    const bool _BDF1_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("BDF", 1), createBDF1);

    TimeIntegrator* createBDF2()
    {
        return new TI::LM::BDF2;
    }
    const bool _BDF2_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("BDF", 2), createBDF2);

    TimeIntegrator* createBDF3()
    {
        return new TI::LM::BDF3;
    }
    const bool _BDF3_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("BDF", 3), createBDF3);

    TimeIntegrator* createBDF4()
    {
        return new TI::LM::BDF4;
    }
    const bool _BDF4_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("BDF", 4), createBDF4);

    /**
     * @brief GaussLegendre
     * 
     */
    TimeIntegrator* createGL1()
    {
        return new TI::RK::GL1;
    }
    const bool _GL1_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("GaussLegendre", 1), createGL1);

    TimeIntegrator* createGL2()
    {
        return new TI::RK::GL2;
    }
    const bool _GL2_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("GaussLegendre", 2), createGL2);

    TimeIntegrator* createGL3()
    {
        return new TI::RK::GL3;
    }
    const bool _GL3_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("GaussLegendre", 3), createGL3);

    /**
     * @brief ESDIRK
     * 
     */
    TimeIntegrator* createESDIRK()
    {
        return new TI::RK::ESDIRK;
    }
    const bool _ESDIRK_registered = 
        TimeIntegratorFactory::Instance().
        Register(TimeIntegratorIdentifier("ESDIRK", 0), createESDIRK);

};