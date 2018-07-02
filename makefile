all :
	catkin_make
	#-rm result.bag
	rosrun slam-dataset-generation app res/map1.svg
