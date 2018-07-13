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
  lib/libsimulator/edge/non_observable/HermiteEdge.cpp
  lib/libsimulator/edge/observable/Edge.cpp
  lib/libsimulator/edge/observable/LinearEdge.cpp
  lib/libsimulator/edge/observable/CubicBezierEdge.cpp

  lib/libsimulator/math/RootFinder.cpp
  lib/libsimulator/math/find_roots.cpp
  lib/libsimulator/math/Pose.cpp
  lib/libsimulator/math/Vec.cpp

  lib/libsimulator/misc/misc.cpp

  lib/libsimulator/observationpath/Ray.cpp
  lib/libsimulator/observationpath/Line.cpp
  lib/libsimulator/observationpath/LineSegment.cpp
  lib/libsimulator/observationpath/ObservationPath.cpp

  lib/libsimulator/path/non_observable/HermitePath.cpp
  lib/libsimulator/path/non_observable/Trajectory.cpp
  lib/libsimulator/path/observable/EdgePath.cpp

  lib/libsimulator/pathfinding/find_trajectory.cpp
  lib/libsimulator/pathfinding/MotionValidator.cpp
  lib/libsimulator/pathfinding/StateValidityChecker.cpp

  lib/libsimulator/simulation/Robot.cpp

  lib/libsimulator/world/parsing/SvgParser.cpp
  lib/libsimulator/world/parsing/SvgParser_parse.cpp
  lib/libsimulator/world/parsing/SvgTransformHandler.cpp
  lib/libsimulator/world/parsing/LengthFactory.cpp
  lib/libsimulator/world/World.cpp
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
