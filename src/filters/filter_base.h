/* * Canadian Hydrological Model - The Canadian Hydrological Model (CHM) is a novel
 * modular unstructured mesh based approach for hydrological modelling
 * Copyright (C) 2018 Christopher Marsh
 *
 * This file is part of Canadian Hydrological Model.
 *
 * Canadian Hydrological Model is free software: you can redistribute it and/or
 * modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Canadian Hydrological Model is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Canadian Hydrological Model.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "station.hpp"

namespace pt = boost::property_tree;

class filter_base
{
public:
    filter_base(){};
    virtual ~filter_base(){};

    virtual void init(boost::shared_ptr<station>& station){};
    virtual void process(boost::shared_ptr<station>& station){};

    bool is_nan(double variable)
    {
        if( variable == -9999.0)
            return true;

        if( std::isnan(variable) )
            return true;

        if( std::isinf(variable) )
            return true;

        return false;
    }
    /**
     * Configuration file. If filter does not need one, then this will contain nothing
     */
    pt::ptree cfg;

    /**
    * ID of the module
    */
    std::string ID;
};