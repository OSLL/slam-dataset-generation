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

# DEPENDS: system dependencies of this project that dependent projects also need
#catkin_package(
#  INCLUDE_DIRS include lib
#  LIBRARIES slam-dataset-generation
#  CATKIN_DEPENDS rosbag roscpp std_msgs
#  DEPENDS system_lib
#)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  lib/svgpp/include
  ${PYTHON_INCLUDE_DIRS}
  lib/svgpp/third_party
  lib
  src
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(helper
 src/pathfinding/find_trajectory.cpp
 src/pathfinding/motionvalidator.cpp
 src/pathfinding/find_critical_poses.cpp
 src/pathfinding/statevaliditychecker.cpp
 src/simulation/robot.cpp
 src/misc/misc.cpp
 src/misc/pose.cpp
 src/misc/vec.cpp
 src/misc/find_roots.cpp
 src/math/root_finder.cpp
 src/world/generate_world.cpp
 src/world/parsing/parsingcontext.cpp
 src/world/parsing/lengthfactory.cpp
 src/world/world.cpp
 src/world/edgepath.cpp
 src/trajectory/hermiteedge.cpp
 src/trajectory/hermitepath.cpp
 src/trajectory/trajectory.cpp
 src/observationpath/ray.cpp
 src/observationpath/line.cpp
 src/observationpath/linesegment.cpp
 src/observationpath/observationpath.cpp
 src/edge/linearedge.cpp
 src/edge/edge.cpp
 src/edge/cubicbezieredge.cpp
)

add_executable(simulate_world src/nodes/simulate_world/main.cpp)
target_link_libraries(simulate_world helper ${rosbag_LIBRARIES} ${tf_LIBRARIES})

add_executable(draw_world src/nodes/draw_world/main.cpp src/nodes/draw_world/draw_world.cpp)
target_link_libraries(draw_world helper ${rosbag_LIBRARIES} ${tf_LIBRARIES} ${PYTHON_LIBRARIES})

add_executable(test_app src/nodes/test_app/main.cpp)
target_link_libraries(test_app helper ${rosbag_LIBRARIES} ${tf_LIBRARIES})
