project(Novo)
cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

find_package(Boost COMPONENTS system thread filesystem program_options REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

include_directories(
	${Boost_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${GLFW_INCLUDE_PATH}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
)

list(APPEND LIBS
	${Boost_LIBRARIES}
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
	${OPENGL_LIBRARIES}
)

string(TOUPPER ${CMAKE_SYSTEM_NAME} OS_NAME)
configure_file("${CMAKE_SOURCE_DIR}/src/novo/config.h.in" "${CMAKE_SOURCE_DIR}/src/novo/config.h")


include_directories(src)
file(GLOB_RECURSE SOURCES src/*.h src/*.cpp)
file(GLOB_RECURSE SHADERS res/shaders/*)


# Shaders here only for listing in qtCreator
add_executable(novo ${SOURCES} ${SHADERS})
target_link_libraries(novo ${LIBS})


