cmake_minimum_required(VERSION 3.11)

project(novo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(glbinding REQUIRED)
find_package(assimp REQUIRED)

add_subdirectory(extern/fmt EXCLUDE_FROM_ALL)
add_subdirectory(extern/entityx EXCLUDE_FROM_ALL)

string(TOUPPER ${CMAKE_SYSTEM_NAME} OS_NAME)
configure_file("${CMAKE_SOURCE_DIR}/src/novo/config.h.in" "${CMAKE_SOURCE_DIR}/src/novo/config.h")

file(GLOB_RECURSE SOURCES src/*.h src/*.cpp)
file(GLOB_RECURSE SHADERS res/shaders/*.glsl)

# Shaders here only for listing in qtCreator
add_executable(${PROJECT_NAME} ${SOURCES} ${SHADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		INTERPROCEDURAL_OPTIMIZATION $<IF:$<CONFIG:Debug>,OFF,ON>
)
target_compile_features(${PROJECT_NAME}
		PUBLIC "cxx_std_17"
)
target_compile_options(${PROJECT_NAME}
		PUBLIC "-Wall" # "-fno-rtti"
)
target_compile_definitions(${PROJECT_NAME}
		PUBLIC "_POSIX_C_SOURCE=200809L"
)


target_include_directories(${PROJECT_NAME}
	PRIVATE
		"${CMAKE_SOURCE_DIR}/src"
		"${CMAKE_SOURCE_DIR}/extern/include"

		${X11_INCLUDE_DIRS}
		${OPENGL_INCLUDE_DIRS}
		${GLBINDING_INCLUDE_DIRS}

		${GLM_INCLUDE_DIRS}
		${ENTITYX_INCLUDE_DIRS}
		${ASSIMP_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		fmt
		entityx

		${OPENGL_LIBRARIES}
		${X11_LIBRARIES}
		glbinding
		glbinding-aux
		glfw
		${ASSIMP_LIBRARIES}
)
