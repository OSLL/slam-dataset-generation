WORLD_FILE := res/map4.svg

.PHONY: build simulate draw test test_roots

build :
	catkin_make

simulate : build
	rosrun slam-dataset-generation simulate_world $(WORLD_FILE)

draw : build
	rosrun slam-dataset-generation draw_world $(WORLD_FILE)

test : build
	rosrun slam-dataset-generation test_app $(WORLD_FILE)

test_roots : build
	rosrun slam-dataset-generation test_roots $(WORLD_FILE)
