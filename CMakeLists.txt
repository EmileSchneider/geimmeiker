cmake_minimum_required(VERSION 3.10)
project(Geimmeiker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_executable(Geimmeiker src/main.cpp src/GMApp.cpp src/Shader.cpp src/objloader.cpp src/Controls.cpp src/texture.cpp src/Model.cpp)

target_link_libraries(Geimmeiker ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw ${GLM_LIBRARIES} ${SDL2_LIBRARIES})
