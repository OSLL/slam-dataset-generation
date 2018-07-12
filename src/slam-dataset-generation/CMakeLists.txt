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

find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

if(NOT ${PYTHONLIBS_FOUND})
  message(FATAL_ERROR "PythonLibs cannot be found")
else()
  message("Found PythonLibs ${PYTHONLIBS_VERSION_STRING}")
  message("\t${PYTHON_LIBRARIES}")
endif()

include_directories(
  lib
  lib/svgpp/include
  lib/svgpp/third_party
  lib/libsimulator
  src
  ${catkin_INCLUDE_DIRS}
)

# libsimulator contains all helper code that makes writing the nodes simple
add_library(libsimulator
  lib/libsimulator/pathfinding/find_trajectory.cpp
  lib/libsimulator/pathfinding/motionvalidator.cpp
  lib/libsimulator/pathfinding/find_critical_poses.cpp
  lib/libsimulator/pathfinding/statevaliditychecker.cpp

  lib/libsimulator/simulation/robot.cpp

  lib/libsimulator/misc/misc.cpp
  lib/libsimulator/misc/pose.cpp
  lib/libsimulator/misc/vec.cpp

  lib/libsimulator/misc/find_roots.cpp

  lib/libsimulator/world/generate_world.cpp
  lib/libsimulator/world/parsing/SvgParser.cpp
  lib/libsimulator/world/parsing/SvgParser_parse.cpp
  lib/libsimulator/world/parsing/SvgTransformHandler.cpp
  lib/libsimulator/world/parsing/LengthFactory.cpp
  lib/libsimulator/world/world.cpp
  lib/libsimulator/world/edgepath.cpp

  lib/libsimulator/trajectory/hermiteedge.cpp
  lib/libsimulator/trajectory/hermitepath.cpp
  lib/libsimulator/trajectory/trajectory.cpp

  lib/libsimulator/observationpath/ray.cpp
  lib/libsimulator/observationpath/line.cpp
  lib/libsimulator/observationpath/linesegment.cpp
  lib/libsimulator/observationpath/observationpath.cpp

  lib/libsimulator/math/root_finder.cpp

  lib/libsimulator/edge/linearedge.cpp
  lib/libsimulator/edge/edge.cpp
  lib/libsimulator/edge/cubicbezieredge.cpp
)

catkin_package(
	INCLUDE_DIRS 
	LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS roscpp tf rosbag std_msgs sensor_msgs
	DEPENDS
)

add_executable(simulate_world src/simulate_world/main.cpp)
target_link_libraries(simulate_world libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES})

add_executable(draw_world src/draw_world/main.cpp src/draw_world/draw_world.cpp)
target_link_libraries(draw_world libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES} ${PYTHON_LIBRARIES})

add_executable(test_roots src/test_roots/main.cpp src/test_roots/test_roots.cpp)
target_link_libraries(test_roots libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES})

add_executable(test_app src/test_app/main.cpp)
target_link_libraries(test_app libsimulator ${rosbag_LIBRARIES} ${tf_LIBRARIES})
