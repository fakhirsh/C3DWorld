cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME C3DWorld)

project (${PROJECT_NAME})

# Remember to specify the path within quotes " "
include_directories("../../3rdParty/glm-0.9.9-a1")
include_directories("../../3rdParty/glew-1.13.0/include")
include_directories("../../3rdParty/glfw-3.1.2/include")


CONFIGURE_FILE(../../../Assets/Config/SystemConfig.xml Assets/Config/SystemConfig.xml COPYONLY)
CONFIGURE_FILE(../../../Assets/Effects/Basic.vs Assets/Effects/Basic.vs COPYONLY)
CONFIGURE_FILE(../../../Assets/Effects/Basic.fs Assets/Effects/Basic.fs COPYONLY)

add_subdirectory(../../3rdParty/glew-1.13.0 ${CMAKE_BINARY_DIR}/glew)
add_subdirectory(../../3rdParty/glfw-3.1.2 ${CMAKE_BINARY_DIR}/glfw)




set ( HDR
 #       ../../FEngine/3D/Mesh.hpp
        ../../FEngine/Renderer/GL30/Program.hpp
 #       ../../FEngine/Renderer/GL30/SimpleVertex2DProgram.hpp
    )

set ( SRC
        main.cpp
  #      ../../FEngine/3D/Mesh.cpp       
        ../../FEngine/Renderer/GL30/Program.cpp
  #      ../../FEngine/Renderer/GL30/SimpleVertex2DProgram.cpp
    )
	
# Executable
add_executable(${PROJECT_NAME}
                ${HDR} 
                ${SRC} 
            )


target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} GLEW ${OPENGL_glu_LIBRARY} )

