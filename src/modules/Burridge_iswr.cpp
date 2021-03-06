//
// Canadian Hydrological Model - The Canadian Hydrological Model (CHM) is a novel
// modular unstructured mesh based approach for hydrological modelling
// Copyright (C) 2018 Christopher Marsh
//
// This file is part of Canadian Hydrological Model.
//
// Canadian Hydrological Model is free software: you can redistribute it and/or
// modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Canadian Hydrological Model is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Canadian Hydrological Model.  If not, see
// <http://www.gnu.org/licenses/>.
//


#include "Burridge_iswr.h"

Burridge_iswr::Burridge_iswr(config_file cfg)
        :module_base(parallel::data)
{

    depends("cloud_frac");
    depends("solar_el");

    provides("iswr_diffuse_no_slope");
    provides("iswr_direct_no_slope");

    provides("atm_trans");
}

Burridge_iswr::~Burridge_iswr()
{

}

void Burridge_iswr::run(mesh_elem &face)
{
    double solar_el = face->face_data("solar_el");
    double cosZ = cos( (90.0-solar_el) *mio::Cst::to_rad);

//    double aspect_south0 = face->aspect() * mio::Cst::to_deg;
//    if (aspect_south0 >= 180.0)
//        aspect_south0 -=  180.0;
//    else
//        aspect_south0 += 180.0;
//    aspect_south0 *= mio::Cst::to_rad;
//
//    double slope = face->slope();
//    double sun_az = global_param->solar_az(); //* mio::Cst::to_rad;
//    if (sun_az >= 180.0)
//        sun_az -=  180.0;
//    else
//        sun_az += 180.0;
//    sun_az *= mio::Cst::to_rad;
//
//
//    double sinZ = sqrt(1.0 - cosZ*cosZ);
//    double cosi = cos(slope) * cosZ +
//              sin(slope) * sinZ *
//              cos(sun_az - aspect_south0);
//
//
//    if (cosi < 0.0)
//        cosi = 0.0;
//    if(cosZ <= 0.0)
//        cosZ=0.0;

    double S = 1375.0;
    double cf = face->face_data("cloud_frac");

    double dir = S  * (0.6+0.2*cosZ)*(1.0-cf);
    double diff = S * (0.3+0.1*cosZ)*(cf);

 //   dir = dir * cosi;
    diff = diff*cosZ;


    if (diff <0)
        diff = 0.0;
    if(dir <0)
        dir = 0.0;

    face->set_face_data("iswr_diffuse_no_slope",diff);
    face->set_face_data("iswr_direct_no_slope",dir);

    face->set_face_data("atm_trans", (dir+diff) / 1375.);
}
