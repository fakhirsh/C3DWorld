//
//  Program.cpp
//  FEngine
//
//  Created by Fakhir Shaheen on 11/10/2016.
//  Copyright (c) 2016 Fakhir Shaheen. All rights reserved.
//

#include "Program.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace FEngine
{

    Program::Program()
    {
        
        _fragmentShader =   0;
        _vertexShader   =   0;
        _programID      =   0;
        
    }

    Program::~Program()
    {
    }

    /*!*****************************************************************************************************************************************
     @Function		InitialiseShaders
     @Output		fragmentShader              Handle to a fragment shader
     @Output		vertexShader                Handle to a vertex shader
     @Output		shaderProgram               Handle to a shader program containing the fragment and vertex shader
     @Input			nativeWindow                A native window, used to display error messages
     @Return		Whether the function succeeds or not.
     @Description	Initialises shaders, buffers and other state required to begin rendering with OpenGL ES
     *******************************************************************************************************************************************/
    bool Program::Link(std::string vertexShaderSource, std::string fragmentShaderSource)
    {
        
        //_vertexShader = LoadFromString(vertexShaderSource, GL_VERTEX_SHADER);
        _vertexShader = LoadFromFile(vertexShaderSource, GL_VERTEX_SHADER);
        if(_vertexShader == 0)
        {
            return false;
        }
        
        //_fragmentShader = LoadFromString(fragmentShaderSource, GL_FRAGMENT_SHADER);
        _fragmentShader = LoadFromFile(fragmentShaderSource, GL_FRAGMENT_SHADER);
        if(_fragmentShader == 0)
        {
            return false;
        }
        
        // Create the shader program
        _programID = glCreateProgram();
        
        // Attach the fragment and vertex shaders to it
        glAttachShader(_programID, _fragmentShader);
        glAttachShader(_programID, _vertexShader);
        
        // Bind the vertex attribute "myVertex" to location VERTEX_ARRAY (0)
        //glBindAttribLocation(_shaderProgram, VERTEX_ARRAY, "a_position");
        //glBindAttribLocation(_shaderProgram, TEXCOORD_ARRAY, "a_UV");
        //glBindAttribLocation(_shaderProgram, COLOR_ARRAY, "a_color");
        
        // Link the program
        glLinkProgram(_programID);
        
        // Check if linking succeeded in the same way we checked for compilation success
        GLint isLinked;
        glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
        if (!isLinked)
        {
            // If an error happened, first retrieve the length of the log message
            int infoLogLength, charactersWritten;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
            
            // Allocate enough space for the message and retrieve it
            char* infoLog = new char[infoLogLength];
            glGetProgramInfoLog(_programID, infoLogLength, &charactersWritten, infoLog);
            
            // Display the error in a dialog box
            //MessageBox(_hWnd, infoLogLength>1 ? infoLog : "Failed to link GL program object. (No information)",
            //           ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION);
            
            delete[] infoLog;
            return false;
        }
        
        //_positionAttrib = glGetAttribLocation(_shaderProgram, "a_position");
        //_colorAttrib = glGetAttribLocation(_shaderProgram, "a_color");
        
        //glUseProgram(_shaderProgram);
        
        return true;
    }
     
    unsigned int Program::LoadFromFile (std::string path, unsigned int shaderType)
    {
        //Open file
        GLuint shaderID = 0;
        std::string shaderString;
        std::ifstream sourceFile( path.c_str() );
        
        //Source file loaded
        if( sourceFile )
        {
            //Get shader source
            shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
            
            shaderID = LoadFromString(shaderString, shaderType);
            
        }
        else
        {
            //printf( "Unable to open file %s\n", path.c_str() );
            shaderID = 0;
        }
        
        return shaderID;
    }

    unsigned int Program::LoadFromString (std::string shaderString, unsigned int shaderType)
    {
        GLuint shaderID =   0;
        
        //Create shader ID
        shaderID    =   glCreateShader( shaderType );
        
        //Set shader source
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource( shaderID, 1, (const GLchar**)&shaderSource, NULL );
        
        //Compile shader source
        glCompileShader( shaderID );
        
        //Check shader for errors
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv( shaderID, GL_COMPILE_STATUS, &shaderCompiled );
        if( shaderCompiled != GL_TRUE )
        {
            //printf( "Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource );
            //printShaderLog( shaderID );
            glDeleteShader( shaderID );
            shaderID = 0;
        }
        
        return shaderID;
    }

    unsigned int Program::GetID()
    {
        return _programID;
    }

    std::string Program::GetName()
    {
        return _name;
    }
    
    void Program::Bind()
    {
        glUseProgram(_programID);
    }

    void Program::UnBind()
    {
        glUseProgram(0);
    }

    void Program::UnLoad()
    {
        glDeleteShader  (_fragmentShader);
        glDeleteShader  (_vertexShader);
        glDeleteProgram (_programID);
    }


};

