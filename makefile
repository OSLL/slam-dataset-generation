all :
	catkin_make
	#-rm result.bag
	rosrun slam-dataset-generation app res/svg_no_style/kirill.svg
	#rosrun slam-dataset-generation app res/svg/kirill.svg
