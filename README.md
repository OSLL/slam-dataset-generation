# Dataset generation tool for SLAM in ROS

This tools could help you to make a dataset for testing SLAM algorithms in ROS

How do I use this tool?


## Step 1: Create a map file
- Map files are svg files populated with [paths](https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Paths) that can be given ids
- Every map file must contain **at least two** special paths
    * **world_boundary** = a closed path that represents the outermost boundary of an environment
        + Must be given "world_boundary" as an ID or it will not be recognized
    * **robot_trajectory** = a path that represents the intermediate positions on the robot's trajectory through the environment
        + Must be given "robot_trajectory" as an ID or it will not be recognized
- In addition to those two paths, additional obstacles can be created
    * Obstacles must be closed (*i.e.* the beginning and the end of the path must be the same)
- Any path other than the robot_trajectory can be given a trajectory that describes the motion of the obstacle
    * To give an obstacle a trajectory
        1) Associate the obstacle path with a unique id(inkscape typically does this by default)
        2) Create the trajectory path and give it an id in the form of "${obstacle_id}_trajectory"
            + If a trajectory is detected but a corresponding obstacle to be associated with couldn't be found, then the parsing will fail with an error

## Step 2: Build the project
- Note that this project depends on boost
- Steps:
    1) Navigate to the base of the repo
    2) Issue `catkin_make`

## Step 3: Run the tool on the map file
- Steps:
    1) Navigate to the base of the repo
    2) Issue `source ./devel/setup.bash`
    3) Issue `rosrun slam-dataset-generation simulate_world <path_to_map_file>`
        * The bag file will be written to ${REPO_ROOT}/data.bag
