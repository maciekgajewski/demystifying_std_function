set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(..)

add_executable(function_benchmark
	benchmark.cc
	other.cc
)

target_link_libraries(function_benchmark
	benchmark
	pthread
)