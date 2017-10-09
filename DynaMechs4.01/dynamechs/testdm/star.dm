# DynaMechs V 2.0.3 ascii
# tree parameter file

Graphics_Models {
	Number_Graphics_Models  1
	"star.cmb"
}

System {
    DynamicRefMember {
	Graphics_Model_Index	 0

	Mass			 1.5
	Inertia			 1.7   0.0  0.0
				 0.0   1.7  0.0
				 0.0   0.0  1.7
	Center_of_Gravity	 0.0 0.0 0.0

	Number_of_Contact_Points	6
	Contact_Locations	-3.0  0.0  0.0
				 3.0  0.0  0.0
				 0.0 -3.0  0.0
				 0.0  3.0  0.0
				 0.0  0.0 -3.0
				 0.0  0.0  3.0

	Position	  10.0   10.0   15.0
	Orientation_Quat  0.0 0.0 0.0 1.0
	Velocity	  0.0 10.0 0.0  0.0 0.0 0.0
    }
}
