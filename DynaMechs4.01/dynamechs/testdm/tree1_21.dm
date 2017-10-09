# DynaMechs V 2.1 ascii
# tree parameter file

Graphics_Models {
	Number_Graphics_Models  2
	"../models/obj_cube_center.xan"
	"../models/obj_cylinder_x.xan"
}

System {
    Name "tree1_21"

    DynamicRefMember {
	Name "ref_mem"
	Graphics_Model_Index	 0

	Mass			 1.5
	Inertia			 1.1   0.0  0.0
				 0.0   1.7  0.0
				 0.0   0.0  1.7
	Center_of_Gravity	 0.0 0.0 0.0

	Number_of_Contact_Points	8 
	Contact_Locations	-1.0  1.0  1.0
				 1.0  1.0  1.0
				-1.0 -1.0  1.0
				 1.0 -1.0  1.0
				-1.0  1.0 -1.0
				 1.0  1.0 -1.0
				-1.0 -1.0 -1.0
				 1.0 -1.0 -1.0

	Position	  10.0   10.0   15.0
	Orientation_Quat  0.7071 0.0 0.0 0.7071
	Velocity	  0.0 0.0 0.0 0.0 0.0 0.0
    }

    Articulation {
	Name "articulation1"

	RevoluteLink {
	    Name "link0"
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 1.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Name "link1"
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	Branch {
	    ZScrewTxLink {
		Name ""
		ZScrew_Parameters	 0.0 1.5708
	    }

	    RevoluteLink {
		Name "link3"
	        Graphics_Model_Index	 1

	        Mass			 0.5
	        Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	        Center_of_Gravity	 1.5 0.0 0.0

	        Number_of_Contact_Points	 1
		Contact_Locations		 3.0  0.0  0.0

	        MDH_Parameters		     0.0 1.5708 0.0 0.0
	        Initial_Joint_Velocity	     0.0
	        Joint_Limits		    -10.172 10.172 
	        Joint_Limit_Spring_Constant  50.0
	        Joint_Limit_Damper_Constant  5.0

	        Actuator_Type		 0
	        Joint_Friction		 0.35
	    }

	    RevoluteLink {
		Name "link4"
	        Graphics_Model_Index	 1

	        Mass			 0.5
	        Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	        Center_of_Gravity	 1.5 0.0 0.0

	        Number_of_Contact_Points	 1
		Contact_Locations		 3.0  0.0  0.0

	        MDH_Parameters		     3.0 1.5708 0.0 0.0
	        Initial_Joint_Velocity	     0.0
	        Joint_Limits		    -10.172 10.172 
	        Joint_Limit_Spring_Constant  50.0
	        Joint_Limit_Damper_Constant  5.0

	        Actuator_Type		 0
	        Joint_Friction		     0.35
	    }

	    Branch {
	        ZScrewTxLink {
		   Name "link5"
		   ZScrew_Parameters	 0.0 -1.5708
	        }

	        RevoluteLink {
		    Name "link6"
	            Graphics_Model_Index	 1

	            Mass			 0.5
	            Inertia			 0.1   0.0  0.0
					         0.0   1.7  0.0
					         0.0   0.0  1.7
	            Center_of_Gravity	         1.5 0.0 0.0

	            Number_of_Contact_Points	 1
		    Contact_Locations		 3.0  0.0  0.0

	            MDH_Parameters		 0.0 1.5708 0.0 0.0
	            Initial_Joint_Velocity	 0.0
	            Joint_Limits		-10.172 10.172 
	            Joint_Limit_Spring_Constant  50.0
	            Joint_Limit_Damper_Constant  5.0

	            Actuator_Type		 0
	            Joint_Friction		     0.35
	        }
	    }
	    RevoluteLink {
		Name "link7"
	        Graphics_Model_Index	 1

	        Mass			 0.5
	        Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	        Center_of_Gravity	 1.5 0.0 0.0

	        Number_of_Contact_Points	 1 
		Contact_Locations		 3.0  0.0  0.0

	        MDH_Parameters		     3.0 1.5708 0.0 0.0
	        Initial_Joint_Velocity	     0.0
	        Joint_Limits		    -10.172 10.172 
	        Joint_Limit_Spring_Constant  50.0
	        Joint_Limit_Damper_Constant  5.0

	        Actuator_Type		 0
	        Joint_Friction		     0.35
	    }
	}

	RevoluteLink {
	    Name "link8"
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	RevoluteLink {
	    Name "link9"
	    Graphics_Model_Index	 1

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 3.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}
    }
}
