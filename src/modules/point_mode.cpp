#include "point_mode.hpp"

point_mode::point_mode(config_file cfg)
        : module_base(parallel::data)
{

     t      = cfg.get<bool>("provide.t",true);
     rh     = cfg.get<bool>("provide.rh",true);
     u      = cfg.get<bool>("provide.u",true);
     p      = cfg.get<bool>("provide.p",true);
     ilwr   = cfg.get<bool>("provide.ilwr",true);
     iswr   = cfg.get<bool>("provide.iswr",true);
     vw_dir = cfg.get<bool>("provide.vw_dir",true);
     iswr_diffuse    = cfg.get<bool>("provide.iswr_diffuse ",true);
     iswr_direct     = cfg.get<bool>("provide.iswr_direct ",true);


    if(t)
    {
        depends_from_met("t");
        provides("t");
    }

    if(rh)
    {
        depends_from_met("rh");
        provides("rh");
    }

    if(u)
    {
        depends_from_met("u");
        provides("u");
    }

    if(vw_dir)
    {
        depends_from_met("vw_dir");
        provides("vw_dir");
    }

    if(p)
    {
        depends_from_met("p");
        provides("p");
    }

    if(ilwr)
    {
        depends_from_met("Qli");
        provides("ilwr");
    }

    if(iswr)
    {
        depends_from_met("Qsi");
        provides("iswr");
    }

    if(iswr_diffuse)
    {
        depends_from_met("iswr_diffuse");
        provides("iswr_diffuse");
    }

    if(iswr_direct)
    {
        depends_from_met("iswr_direct");
        provides("iswr_direct");
    }

}

point_mode::~point_mode()
{

}

void point_mode::run(mesh_elem &face, boost::shared_ptr <global> global_param)
{
    // at this point, if the user has provided more than 1 station, they've been stripped out.
    // we can safetly take the 1st (and only) station.

    if(t)
    {
        double st = global_param->stations().at(0)->get("t");
        face->set_face_data("t",st);
    }

    if(rh)
    {
        double srh = global_param->stations().at(0)->get("rh");
        face->set_face_data("rh", srh);
    }
    if(u)
    {
        double su = global_param->stations().at(0)->get("u");

        //make sure we don't have zero windpseeds
        su = std::max(su,0.1);
        face->set_face_data("u",su);
    }

    if(vw_dir)
    {
        double sdir = global_param->stations().at(0)->get("vw_dir");
        face->set_face_data("vw_dir",sdir);
    }

    if(p)
    {
        double sp = global_param->stations().at(0)->get("p");
        face->set_face_data("p", sp);
    }
    if(ilwr)
    {
        double silwr = global_param->stations().at(0)->get("Qli");
        face->set_face_data("ilwr", silwr);

    }
    if(iswr)
    {
        double iswr = global_param->stations().at(0)->get("Qsi");
        face->set_face_data("iswr", iswr);

    }
    if(iswr_diffuse)
    {
        double iswr_diffuse = global_param->stations().at(0)->get("iswr_diffuse");
        face->set_face_data("iswr_diffuse", iswr_diffuse);

    }
    if(iswr_direct)
    {
        double iswr_direct = global_param->stations().at(0)->get("iswr_direct");
        face->set_face_data("iswr_direct", iswr_direct);

    }

}

