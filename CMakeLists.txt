cmake_minimum_required(VERSION 3.21)

# set the project name
project(mesh_arrangement)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(TBB_TEST OFF CACHE BOOL " " FORCE)
set(TBB_EXAMPLES OFF CACHE BOOL " " FORCE)

add_subdirectory(external/oneTBB)

# add the executable
add_executable(${PROJECT_NAME} 
	main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
	./
	code/
	public/
	)

target_compile_definitions(${PROJECT_NAME} PUBLIC TBB_PARALLEL=1)

target_link_libraries(${PROJECT_NAME} tbb)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/external/abseil-cpp/)

set(cinolib_DIR ${PROJECT_SOURCE_DIR}/external/Cinolib)
set(CINOLIB_USES_OPENGL_GLFW_IMGUI ON)
set(CINOLIB_USES_SHEWCHUK_PREDICATES ON)
set(CINOLIB_USES_INDIRECT_PREDICATES ON)

find_package(cinolib REQUIRED)
target_link_libraries(${PROJECT_NAME} cinolib)

option(PYBIND "Turn this ON to enable pybind" OFF)
if (PYBIND)
	# Python bindings
	add_subdirectory("3rd/pybind11")
	include_directories("python")
	pybind11_add_module(meshArrange python/meshArrange/meshArrange.cpp public/meshArrange.cpp)
	target_include_directories(meshArrange PUBLIC
		./
		code/
		public/
		)

	target_compile_definitions(meshArrange PUBLIC TBB_PARALLEL=1)
	target_link_libraries(meshArrange PUBLIC tbb)
	target_include_directories(meshArrange PUBLIC ${PROJECT_SOURCE_DIR}/external/abseil-cpp/)
	target_link_libraries(meshArrange PUBLIC cinolib)
endif()
