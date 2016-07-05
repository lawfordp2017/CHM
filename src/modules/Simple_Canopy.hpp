//#pragma once

#include <boost/shared_ptr.hpp>

#include "logger.hpp"
//#include "triangulation.hpp"
#include "module_base.hpp"
//#include "TPSpline.hpp"
#include <meteoio/MeteoIO.h>
#include "PhysConsts.h"
/*
 * @Brief Solves energy and mass equations for canopy states using parameterizations based on LAI and canopy closure.
 *
 */

#include <string>
class Simple_Canopy : public module_base
{
public:
    Simple_Canopy(config_file cfg);

    ~Simple_Canopy();

    virtual void run(mesh_elem &elem, boost::shared_ptr <global> global_param);

    virtual void init(mesh domain, boost::shared_ptr <global> global_param);

    double delta(double ta);

    double lambda(double ta);

    double gamma(double air_pressure, double ta);

    struct data : public face_info {
        //boost::shared_ptr<Snowpack> sp;

        // parameters
        double LAI;
        double CanopyHeight;

        // model states
        double rain_load;
        double Snow_load;

        // Output diagnostic variables
        double cum_net_snow;
        double cum_net_rain;
        double cum_Subl_Cpy;
        double cum_intcp_evap;
        double cum_SUnload_H2O;
    };


    double Qs(double pressure, double t1);
};



