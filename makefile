all :
	catkin_make
	#-rm result.bag
	rosrun slam-dataset-generation test-app res/map1.svg
