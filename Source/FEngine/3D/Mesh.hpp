//
//  Mesh.hpp
//  FEngine
//
//  Created by Fakhir Shaheen on 18/12/2016.
//  Copyright (c) 2016 Fakhir Shaheen. All rights reserved.
//

#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace FEngine
{

    class Mesh
    {
    public:
        Mesh();
        virtual ~Mesh();

        virtual bool    Init            ()  =   0;

        std::string     GetName         ();

    protected:

        std::string     _name;
    };

};


