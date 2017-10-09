# DynaMechs V 2.0.3 ascii
# tree parameter file

Graphics_Models {
	Number_Graphics_Models  2
	"../models/obj_cube_center.xan"
	"../models/obj_cylinder_x.xan"
}

System {
    DynamicRefMember {
	Graphics_Model_Index	 1

	Mass			 0.5
	Inertia			 0.1   0.0  0.0
				 0.0   1.7  0.0
				 0.0   0.0  1.7
	Center_of_Gravity	 1.5 0.0 0.0

	Number_of_Contact_Points 2 
	Contact_Locations	 0.0  0.0  0.0
				 3.0  0.0  0.0

	Position	  10.0   10.0   15.0
	Orientation_Quat  0.7071 0.0 0.0 0.7071
	Velocity	  0.0 0.0 0.0 0.0 0.0 0.0
    }

    Articulation {
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 1.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 1.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 1.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 1.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 1.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 1.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}
    }
}
