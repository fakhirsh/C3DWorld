//
//  Mesh.cpp
//  FEngine
//
//  Created by Fakhir Shaheen on 18/12/2016.
//  Copyright (c) 2016 Fakhir Shaheen. All rights reserved.
//

#include "Mesh.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace FEngine
{

    Mesh::Mesh(){
    }

    Mesh::~Mesh(){
    }

    std::string Mesh::GetName(){
        return _name;
    }


};

