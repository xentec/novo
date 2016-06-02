cmake_minimum_required(VERSION 3.2)

project(Novo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(glbinding REQUIRED)
find_package(EntityX REQUIRED)
find_package(assimp REQUIRED)


include_directories(
	${X11_INCLUDE_DIRS}

	${OPENGL_INCLUDE_DIRS}
	${GLFW3_INCLUDE_DIRS}
	${GLBINDING_INCLUDE_DIRS}

	${GLM_INCLUDE_DIRS}
	${ENTITYX_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
)

list(APPEND LIBS
	${X11_LIBRARIES}

	${OPENGL_LIBRARY}
	${GLFW3_LIBRARY}
	${GLBINDING_LIBRARIES}
	glbinding

	${ENTITYX_LIBRARY}
	${ASSIMP_LIBRARY}
	cppformat
)

string(TOUPPER ${CMAKE_SYSTEM_NAME} OS_NAME)
configure_file("${CMAKE_SOURCE_DIR}/src/novo/config.h.in" "${CMAKE_SOURCE_DIR}/src/novo/config.h")

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/extern/include"
)
file(GLOB_RECURSE SOURCES src/*.h src/*.cpp)
file(GLOB_RECURSE SHADERS res/shaders/*.glsl)

# Shaders here only for listing in qtCreator
add_executable(novo ${SOURCES} ${SHADERS})
target_link_libraries(novo ${LIBS})


