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

#pragma once

#include <string>

#include <tbb/concurrent_hash_map.h>
#include "utility/crc_hash_compare.hpp"

typedef tbb::concurrent_hash_map<std::string,std::string,crc_hash_compare> var_hashmap;

class var
{
public:
    var();
    ~var();
    std::string operator()(std::string variable);
    void init_from_file(std::string path);
    
   var_hashmap _varmap;
};



//this relates internal variable names to the names in met files/other input
//namespace variables
//{
//  const  std::string RH = "RH";
//  const  std::string Tair = "t";
//  const  std::string datetime = "datetime";
//};


//#define RH "rh"
//#define TAIR "t"
//#define DATE "datetime"