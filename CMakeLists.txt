cmake_minimum_required(VERSION 3.8)
project(SugarBombEngine VERSION 0.2.6.0)

# Define available options
option(SBE_SINGLE_BINARY "Build everything as a single binary" OFF)
option(SBE_USE_SDL "Use SDL2 for crossplatform support" OFF)

# We want shared libraries (and modules) without any prefix in the name
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")

# Set compiled binaries output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Setup language standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find the required packages


if(SBE_USE_IMGUI)
	find_package(ImGui)
endif()
find_package(GLEW)
find_package(SDL2)

set(SBE_LIBS_PATH
	${CMAKE_SOURCE_DIR}/../SBE-libs
	CACHE PATH
	"Path to engine dependencies"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/libs
	${CMAKE_CURRENT_SOURCE_DIR}/include/sugarbomb
	${SBE_LIBS_PATH}
	${SBE_LIBS_PATH}/jpeg-6
	${SBE_LIBS_PATH}/png
	${SBE_LIBS_PATH}/glew/include
	${SBE_LIBS_PATH}/rapidjson/include
)

if(MINGW)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/mingw-hacks)
endif()

configure_file(
	SbVersion.hpp.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/sugarbomb/CoreLibs/SbSystem/SbVersion.hpp
)

# Add subdirectories

add_subdirectory(libs)

#add_subdirectory(src/components)

add_subdirectory(src)