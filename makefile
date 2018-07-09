WORLD_FILE := res/map1.svg

.PHONY: build simulate print

build :
	catkin_make

simulate : build
	rosrun slam-dataset-generation simulate_world $(WORLD_FILE)

draw : build
	rosrun slam-dataset-generation draw_world $(WORLD_FILE)

test : build
	rosrun slam-dataset-generation test_app $(WORLD_FILE)
