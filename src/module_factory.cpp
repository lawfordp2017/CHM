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


#include "module_factory.hpp"



module_base* module_factory::get(std::string ID, pt::ptree config)
{
    LOG_DEBUG << "Module ID=" << ID;
    
    module_base* mod = nullptr;

    try
    {
        if (ID == "iswr")
            mod = new iswr(config);
        else if (ID == "Marsh_shading_iswr")
            mod = new Marsh_shading_iswr(config);
        else if (ID == "const_llra_ta")
            mod = new const_llra_ta(config);
        else if (ID == "Liston_monthly_llra_ta")
            mod = new Liston_monthly_llra_ta(config);
        else if (ID == "Kunkel_monthlyTd_rh")
            mod = new Kunkel_monthlyTd_rh(config);
        else if (ID == "Sicart_ilwr")
            mod = new Sicart_ilwr(config);
        else if (ID == "Liston_wind")
            mod = new Liston_wind(config);
        else if (ID == "PenmanMonteith_evaporation")
            mod = new PenmanMonteith_evaporation(config);
        else if (ID == "Walcek_cloud")
            mod = new Walcek_cloud(config);
        else if (ID == "Harder_precip_phase")
            mod = new Harder_precip_phase(config);
        else if (ID == "Burridge_iswr")
            mod = new Burridge_iswr(config);
        else if (ID == "Iqbal_iswr")
            mod = new Iqbal_iswr(config);
        else if (ID == "iswr_from_obs")
            mod = new iswr_from_obs(config);
        else if (ID == "Dodson_NSA_ta")
            mod = new Dodson_NSA_ta(config);
        else if (ID == "Thornton_p")
            mod = new Thornton_p(config);
        else if (ID == "Thornton_var_p")
            mod = new Thornton_var_p(config);
        else if (ID == "rh_from_obs")
            mod = new rh_from_obs(config);
        else if (ID == "kunkel_rh")
            mod = new kunkel_rh(config);
        else if (ID == "snobal")
            mod = new snobal(config);
        else if (ID == "Richard_albedo")
            mod = new Richard_albedo(config);
        else if (ID == "snowpack")
            mod = new Lehning_snowpack(config);
        else if (ID == "point_mode")
            mod = new point_mode(config);
        else if (ID == "threshold_p_phase")
            mod = new threshold_p_phase(config);
        else if (ID == "Gray_inf")
            mod = new Gray_inf(config);
        else if (ID == "Longwave_from_obs")
            mod = new Longwave_from_obs(config);
        else if (ID == "Simple_Canopy")
            mod = new Simple_Canopy(config);
        else if (ID == "Dist_tlapse")
            mod = new Dist_tlapse(config);
        else if (ID == "scale_wind_vert")
            mod = new scale_wind_vert(config);
        else if (ID == "solar")
            mod = new solar(config);
        else if (ID == "rh_no_lapse")
            mod = new rh_no_lapse(config);
        else if (ID == "t_no_lapse")
            mod = new t_no_lapse(config);
        else if (ID == "p_no_lapse")
            mod = new p_no_lapse(config);
        else if (ID == "lw_no_lapse")
            mod = new lw_no_lapse(config);
        else if (ID == "uniform_wind")
            mod = new uniform_wind(config);
        else if (ID == "fast_shadow")
            mod = new fast_shadow(config);
        else if (ID == "deform_mesh")
            mod = new deform_mesh(config);
        else if (ID == "crop_rotation")
            mod = new crop_rotation(config);
        else if (ID == "sub_grid")
            mod = new sub_grid(config);
        else if (ID == "t_monthly_lapse")
            mod = new t_monthly_lapse(config);
  	    else if (ID == "snow_slide")
	        mod = new snow_slide(config);
        else if (ID == "PBSM3D")
            mod = new PBSM3D(config);
        else if (ID == "fetchr")
            mod = new fetchr(config);
        else if (ID == "MS_wind")
            mod = new MS_wind(config);
        else if (ID == "Cullen_monthly_llra_ta")
            mod = new Cullen_monthly_llra_ta(config);
    }
    catch(module_error& e)
    {
        //ctors can potentially raise an exception. But ID hasn't be initiated yet, so just have to catch to add in that detail before bailing
        BOOST_THROW_EXCEPTION(module_error()
                                      << errstr_info( std::string("Module = ") + ID + ": " + boost::diagnostic_information(e))
        );

    }


    if(mod == nullptr)
    {
        BOOST_THROW_EXCEPTION(module_not_found() 
                              << errstr_info( std::string("Module not found ") + ID)
                        );
    }

    mod->ID = ID;
    mod->cfg = config;
    
    return mod;

}
