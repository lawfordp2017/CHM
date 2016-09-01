#pragma once

#include <boost/shared_ptr.hpp>
#include <constants/Atmosphere.h>
#include "module_base.hpp"
#include <boost/shared_ptr.hpp>
#include "logger.hpp"
#include "face.hpp"
#include <string>

/**
 * \addtogroup modules
 * @{
 * \class scale_wind_vert
 * \brief Scales wind speed from reference height to defined heights
 *
 * Depends:
 * - U_R [m/s]
 * - Z_R [m] - Height of wind speed measurement/model layer
 *
 */

class scale_wind_vert : public module_base {
public:
    scale_wind_vert(config_file cfg);

    ~scale_wind_vert();

    virtual void run(mesh_elem &face, boost::shared_ptr<global> global_param);

    virtual void init(mesh domain, boost::shared_ptr<global> global_param);
};