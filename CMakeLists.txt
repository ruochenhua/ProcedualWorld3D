cmake_minimum_required(VERSION 3.19)

project(ProcedualWorld3D)

set(CMAKE_CXX_EXTENSIONS 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
set(SRC_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

add_subdirectory(${3RD_PARTY_DIR})

# imgui编译
set(IMGUI_DIR ${3RD_PARTY_DIR}/imgui)
file(GLOB IMGUI_SRC ${IMGUI_DIR}/*.cpp)
file(GLOB IMGUI_BACKEND_SRC ${IMGUI_DIR}/backends/*.cpp)

file(GLOB_RECURSE MAIN_SRC ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE MAIN_HEAD ${SRC_DIR}/*.h)

add_executable(ProcedualWorld3D ${MAIN_HEAD} ${MAIN_SRC} ${IMGUI_SRC} ${IMGUI_BACKEND_SRC})

include_directories(ProcedualWorld3D ${SRC_DIR})
include_directories(ProcedualWorld3D ${3RD_PARTY_DIR})

target_include_directories(ProcedualWorld3D PRIVATE ${IMGUI_DIR})
target_include_directories(ProcedualWorld3D PRIVATE ${IMGUI_DIR}/backends)

# link library
target_link_libraries(ProcedualWorld3D OpenGL::GL)
target_link_libraries(ProcedualWorld3D glfw)
target_link_libraries(ProcedualWorld3D glm_static)
target_link_libraries(ProcedualWorld3D glad)
target_link_libraries(ProcedualWorld3D assimp)
target_link_libraries(ProcedualWorld3D yaml-cpp)