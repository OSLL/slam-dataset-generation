cmake_minimum_required(VERSION 2.8.3)
project(slam-dataset-generation)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  rosbag
  std_msgs
  sensor_msgs
)

message("Before finding it, ${PYTHONLIBS_FOUND} ${PYTHONLIBS_VERSION_STRING} ${PYTHON_LIBRARIES}")

find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

if(NOT ${PYTHONLIBS_FOUND})
  message(FATAL_ERROR "PythonLibs cannot be found")
else()
  message("Found PythonLibs ${PYTHONLIBS_VERSION_STRING}")
  message("\t${PYTHON_LIBRARIES}")
endif()

include_directories(
  lib/svgpp/include
  lib/svgpp/third_party
  lib
  src
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(libsimulator
  src/pathfinding/find_trajectory.cpp
  src/pathfinding/motionvalidator.cpp
  src/pathfinding/find_critical_poses.cpp
  src/pathfinding/statevaliditychecker.cpp

  src/simulation/robot.cpp

  src/misc/misc.cpp
  src/misc/pose.cpp
  src/misc/vec.cpp

  src/misc/find_roots.cpp

  src/world/generate_world.cpp
  src/world/parsing/SvgParser.cpp
  src/world/parsing/SvgParser_parse.cpp
  src/world/parsing/SvgTransformHandler.cpp
  src/world/parsing/LengthFactory.cpp
  src/world/world.cpp
  src/world/edgepath.cpp

  src/trajectory/hermiteedge.cpp
  src/trajectory/hermitepath.cpp
  src/trajectory/trajectory.cpp

  src/observationpath/ray.cpp
  src/observationpath/line.cpp
  src/observationpath/linesegment.cpp
  src/observationpath/observationpath.cpp

  src/math/root_finder.cpp

  src/edge/linearedge.cpp
  src/edge/edge.cpp
  src/edge/cubicbezieredge.cpp
)

catkin_package(
	INCLUDE_DIRS 
	LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS roscpp tf rosbag std_msgs sensor_msgs
	DEPENDS
)

add_executable(simulate_world src/nodes/simulate_world/main.cpp)
target_link_libraries(simulate_world libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES})

add_executable(draw_world src/nodes/draw_world/main.cpp src/nodes/draw_world/draw_world.cpp)
target_link_libraries(draw_world libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES} ${PYTHON_LIBRARIES})

add_executable(test_roots src/nodes/test_roots/main.cpp src/nodes/test_roots/test_roots.cpp)
target_link_libraries(test_roots libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES})

add_executable(test_app src/nodes/test_app/main.cpp)
target_link_libraries(test_app libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES})
