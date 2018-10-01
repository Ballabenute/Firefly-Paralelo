cmake_minimum_required (VERSION 2.8)

# projectname is the same as the main-executable
project(FF_Guilherme)
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(MPI REQUIRED)
add_definitions('-g')
add_definitions('-Wall')
add_definitions('-std=c++11')
include_directories(${MPI_INCLUDE_PATH})

add_executable(${PROJECT_NAME} HSVimg.cpp Image.cpp main_FF.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} ${MPI_LIBRARIES})

