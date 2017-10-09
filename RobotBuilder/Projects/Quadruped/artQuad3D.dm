# DynaMechs V 4.0 ascii

ClosedArticulation {
  Name 	     		"Quadruped"
  Graphics_Model    	""
  Position	     	0.0 0.0 0.0
  Orientation_Quat  	0.0 0.0 0.0 1.0

  TreeStructure {
    MobileBaseLink {
      Name 				"body"
      Graphics_Model			"body.xan"

      Mass				3.68184e+1

      Inertia				4.37266e-1 0.00000e+0 4.93588e-4
                                        0.00000e+0 5.89566e+0 0.00000e+0
                                        4.93588e-4 0.00000e+0 6.31265e+0

      Center_of_Gravity			0.0 0.0 0.0

      Number_of_Contact_Points		0

      Position	  			1.375 4.0 0.65
      Orientation_Quat  		0.0 0.0 0.0 1.0
      Velocity	  			0.0 0.0 0.0 0.0 0.0 0.0
    }

    ZScrewTxLink {
      Name                		""
      ZScrew_Parameters   		0.0 -1.570796328
    }

    Branch {
      RevoluteLink {
	Name 				"leg1Frame"

	Graphics_Model              	"frameFL.cmb"

	Mass				2.57942e+0

	Inertia		      		+8.09973e-2 +0.00000e+0 +1.55338e-7
					+0.00000e+0 +7.07660e-2 -1.10648e-6
					+1.55338e-7 -1.10648e-6 +1.35250e-2

	Center_of_Gravity           	-7.07794e-7 -3.96644e-2 -7.47672e-2

	Number_of_Contact_Points	0

	MDH_Parameters			-0.165 -1.570796328 
                                         0.370  1.570796328
	Initial_Joint_Velocity		0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant 	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg1Thigh"
	Graphics_Model              	"thigh.xan"

	Mass				1.60868e+0

	Inertia		        	+3.91354e-2 -1.30421e-2 -2.44760e-6
					-1.30421e-2 +2.17210e-2 +0.00000e+0
					-2.44760e-6 +0.00000e+0 +5.43520e-2

	Center_of_Gravity		+1.47815e-2 -9.07813e-2 0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 1.570796328 0.0 -1.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg1Shank"
	Graphics_Model              	"shank.cmb"

	Mass				7.36117e-1

	Inertia		        	+4.21232e-4 +0.00000e+0 +0.00000e+0
					+0.00000e+0 +2.96813e-2 +0.00000e+0
					+0.00000e+0 +0.00000e+0 +2.93835e-2 

	Center_of_Gravity		+5.35735e-2 +0.00000e+0 +0.00000e+0

	Number_of_Contact_Points	1
	Contact_Locations               0.500 0.000 0.000

	MDH_Parameters		 	0.240 0.0 0.0 1.55998
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	1000.0
	Joint_Limit_Damper_Constant  	  50.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg1Screw"
	Graphics_Model              	"ballscrew.cmb"

	Mass				1.68602e+0

	Inertia		        	+8.03440e-2 +0.00000e+0 -4.73216e-9
					+0.00000e+0 +5.48461e-4 +0.00000e+0
					-4.73216e-9 +0.00000e+0 +8.03073e-2

	Center_of_Gravity		+0.00000e+0 +1.45308e-1 +0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	-0.140 0.0 0.0 0.51239
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	0.0
	Joint_Limit_Damper_Constant  	0.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      PrismaticLink {
	Name 				"leg1Slide"
	Graphics_Model              	"slide.xan"

	Mass				1.22846e+0

	Inertia		        	+1.35129e-2 -4.71192e-6 -7.17383e-6
					-4.71192e-6 +1.35435e-2 -2.25828e-6
					-7.17383e-6 -2.25828e-6 +1.22477e-3

	Center_of_Gravity		-4.88692e-7 +0.00000e+0 -8.52699e-2

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 -1.570796328 0.412415 0.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	5000.0
	Joint_Limit_Damper_Constant  	 200.0

	Joint_Friction		 	250.0
      }
    }

    Branch {
      RevoluteLink {
	Name 				"leg2Frame"
	Graphics_Model              	"frameFR.cmb"

	Mass				2.57942e+0

	Inertia		        	+8.09973e-2 +0.00000e+0 -1.55338e-7
					+0.00000e+0 +7.07660e-2 +1.10648e-6
				        -1.55338e-7 +1.10648e-6 +1.35250e-2

	Center_of_Gravity		+7.07794e-7 +3.96644e-2 -7.47672e-2

	Number_of_Contact_Points	0

	MDH_Parameters			0.165 -1.570796328 
                                        0.370  1.570796328
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant 	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg2Thigh"
	Graphics_Model              	"thigh.xan"

	Mass				1.60868e+0

	Inertia		        	+3.91354e-2 -1.30421e-2 -2.44760e-6
					-1.30421e-2 +2.17210e-2 +0.00000e+0
					-2.44760e-6 +0.00000e+0 +5.43520e-2

	Center_of_Gravity		+1.47815e-2 -9.07813e-2 0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 1.570796328 0.0 -1.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg2Shank"
	Graphics_Model              	"shank.cmb"

	Mass				7.36117e-1

	Inertia		        	+4.21232e-4 +0.00000e+0 +0.00000e+0
					+0.00000e+0 +2.96813e-2 +0.00000e+0
					+0.00000e+0 +0.00000e+0 +2.93835e-2 

	Center_of_Gravity		+5.35735e-2 +0.00000e+0 +0.00000e+0

	Number_of_Contact_Points	1
	Contact_Locations               0.500 0.000 0.000

	MDH_Parameters		 	0.240 0.0 0.0 1.55998
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	1000.0
	Joint_Limit_Damper_Constant  	  50.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg2Screw"
	Graphics_Model              	"ballscrew.cmb"

	Mass				1.68602e+0

	Inertia		        	+8.03440e-2 +0.00000e+0 -4.73216e-9
					+0.00000e+0 +5.48461e-4 +0.00000e+0
					-4.73216e-9 +0.00000e+0 +8.03073e-2

	Center_of_Gravity		+0.00000e+0 +1.45308e-1 +0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	-0.140 0.0 0.0 0.51239
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	0.0
	Joint_Limit_Damper_Constant  	0.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      PrismaticLink {
	Name 				"leg2Slide"
	Graphics_Model              	"slide.xan"

	Mass				1.22846e+0

	Inertia		        	+1.35129e-2 -4.71192e-6 -7.17383e-6
					-4.71192e-6 +1.35435e-2 -2.25828e-6
					-7.17383e-6 -2.25828e-6 +1.22477e-3

	Center_of_Gravity		-4.88692e-7 +0.00000e+0 -8.52699e-2

	Number_of_Contact_Points	0

        MDH_Parameters		 	0.0 -1.570796328 0.412415 0.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	5000.0
	Joint_Limit_Damper_Constant  	 200.0

	Joint_Friction		 	250.0
      }
    }

    Branch {
      RevoluteLink {
	Name 				"leg3Frame"
	Graphics_Model              	"frameHL.cmb"

	Mass				2.57942e+0

	Inertia		        	+8.09973e-2 +0.00000e+0 +1.55338e-7
					+0.00000e+0 +7.07660e-2 +1.10648e-6
				        +1.55338e-7 +1.10648e-6 +1.35250e-2

	Center_of_Gravity		+7.07794e-7 -3.96644e-2 +7.47672e-2

	Number_of_Contact_Points	0

	MDH_Parameters		 	-0.165 -1.570796328
					-0.690 1.570796328
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant 	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg3Thigh"
	Graphics_Model              	"thigh.xan"

	Mass				1.60868e+0

	Inertia		        	+3.91354e-2 -1.30421e-2 -2.44760e-6
					-1.30421e-2 +2.17210e-2 +0.00000e+0
					-2.44760e-6 +0.00000e+0 +5.43520e-2

	Center_of_Gravity		+1.47815e-2 -9.07813e-2 0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 -1.570796328 0.0 -1.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      Branch {
	RevoluteLink {
	  Name 				"leg3Shank"
	  Graphics_Model              	"shank.cmb"

	  Mass				7.36117e-1

	  Inertia		        +4.21232e-4 +0.00000e+0 +0.00000e+0
					+0.00000e+0 +2.96813e-2 +0.00000e+0
					+0.00000e+0 +0.00000e+0 +2.93835e-2 

	  Center_of_Gravity		+5.35735e-2 +0.00000e+0 +0.00000e+0

	  Number_of_Contact_Points	1
	  Contact_Locations             0.500 0.000 0.000

	  MDH_Parameters		0.240 0.0 0.0 1.55998
	  Initial_Joint_Velocity	0.0
	  Joint_Limits			-1e10 1e10
	  Joint_Limit_Spring_Constant  	1000.0
	  Joint_Limit_Damper_Constant  	  50.0

	  Actuator_Type		 	0
	  Joint_Friction		0.0
        }
      }

      ZScrewTxLink {
        Name                		""
        ZScrew_Parameters   		0.0 -1.919862179
      }

      RevoluteLink {
	Name 				"leg3Screw"
	Graphics_Model              	"ballscrew.cmb"

	Mass				1.68602e+0

	Inertia		        	+8.03440e-2 +0.00000e+0 -4.73216e-9
					+0.00000e+0 +5.48461e-4 +0.00000e+0
					-4.73216e-9 +0.00000e+0 +8.03073e-2

	Center_of_Gravity		+0.00000e+0 +1.45308e-1 +0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.360 0.0 0.0 0.850654
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	0.0
	Joint_Limit_Damper_Constant  	0.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      PrismaticLink {
	Name 				"leg3Slide"
	Graphics_Model              	"slide.xan"

	Mass				1.22846e+0

	Inertia		        	+1.35129e-2 -4.71192e-6 -7.17383e-6
					-4.71192e-6 +1.35435e-2 -2.25828e-6
					-7.17383e-6 -2.25828e-6 +1.22477e-3

	Center_of_Gravity		-4.88692e-7 +0.00000e+0 -8.52699e-2

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 -1.570796328 0.412415 0.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	5000.0
	Joint_Limit_Damper_Constant  	 200.0

	Joint_Friction		 	250.0
      }
    }

    Branch {
      RevoluteLink {
	Name 				"leg4Frame"
	Graphics_Model              	"frameHR.cmb"

	Mass				2.57942e+0

	Inertia		      		+8.09973e-2 +0.00000e+0 -1.55338e-7
					+0.00000e+0 +7.07660e-2 -1.10648e-6
					-1.55338e-7 -1.10648e-6 +1.35250e-2

	Center_of_Gravity           	-7.07794e-7 +3.96644e-2 +7.47672e-2

	Number_of_Contact_Points	0

	MDH_Parameters		 	 0.165 -1.570796328
					-0.690  1.570796328
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant 	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      RevoluteLink {
	Name 				"leg4Thigh"
	Graphics_Model              	"thigh.xan"

	Mass				1.60868e+0

	Inertia		        	+3.91354e-2 -1.30421e-2 -2.44760e-6
					-1.30421e-2 +2.17210e-2 +0.00000e+0
					-2.44760e-6 +0.00000e+0 +5.43520e-2

	Center_of_Gravity		+1.47815e-2 -9.07813e-2 0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 -1.570796328 0.0 -1.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	2500.0
	Joint_Limit_Damper_Constant  	200.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      Branch {
	RevoluteLink {
	  Name 				"leg4Shank"
	  Graphics_Model              	"shank.cmb"

	  Mass				7.36117e-1

	  Inertia		        +4.21232e-4 +0.00000e+0 +0.00000e+0
					+0.00000e+0 +2.96813e-2 +0.00000e+0
					+0.00000e+0 +0.00000e+0 +2.93835e-2 

	  Center_of_Gravity		+5.35735e-2 +0.00000e+0 +0.00000e+0

	  Number_of_Contact_Points	1
	  Contact_Locations             0.500 0.000 0.000

	  MDH_Parameters		0.240 0.0 0.0 1.55998
	  Initial_Joint_Velocity	0.0
	  Joint_Limits			-1e10 1e10
	  Joint_Limit_Spring_Constant  	1000.0
	  Joint_Limit_Damper_Constant  	  50.0

	  Actuator_Type		 	0
	  Joint_Friction		0.0
        }
      }

      ZScrewTxLink {
         Name                		""
         ZScrew_Parameters   		0.0 -1.919862179
      }

      RevoluteLink {
	Name 				"leg4Screw"
	Graphics_Model              	"ballscrew.cmb"

	Mass				1.68602e+0

	Inertia		        	+8.03440e-2 +0.00000e+0 -4.73216e-9
					+0.00000e+0 +5.48461e-4 +0.00000e+0
					-4.73216e-9 +0.00000e+0 +8.03073e-2

	Center_of_Gravity		+0.00000e+0 +1.45308e-1 +0.00000e+0

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.360 0.0 0.0 0.850654
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	0.0
	Joint_Limit_Damper_Constant  	0.0

	Actuator_Type		 	0
	Joint_Friction		 	0.0
      }

      PrismaticLink {
	Name 				"leg4Slide"
	Graphics_Model              	"slide.xan"

	Mass				1.22846e+0

	Inertia		        	+1.35129e-2 -4.71192e-6 -7.17383e-6
					-4.71192e-6 +1.35435e-2 -2.25828e-6
					-7.17383e-6 -2.25828e-6 +1.22477e-3

	Center_of_Gravity		-4.88692e-7 +0.00000e+0 -8.52699e-2

	Number_of_Contact_Points	0

	MDH_Parameters		 	0.0 -1.570796328 0.412415 0.0
	Initial_Joint_Velocity	 	0.0
	Joint_Limits			-1e10 1e10
	Joint_Limit_Spring_Constant  	5000.0
	Joint_Limit_Damper_Constant  	 200.0

	Joint_Friction		 	250.0
      }
    }
  }

  SecondaryJoints {

    SoftSphericalJoint {
      Name 				"leg1SecJnt"

      Link_A_Name    			"leg1Thigh"
      Link_B_Name    			"leg1Slide"

      Joint_A_Position      		-0.123127 -0.338289 0.0
      Rotation_Matrix_A     		1.0  0.0  0.0
		               		0.0  1.0  0.0
		               		0.0  0.0  1.0

      Joint_B_Position      		0.0  0.0  0.0
      Rotation_Matrix_B     		1.0  0.0  0.0
			       		0.0  0.0 -1.0
			       		0.0  1.0  0.0

      Joint_Friction 			0

      Position_Constraint_Spring   	100000.0
      Position_Constraint_Damper     	  2000.0

#      Position_Constraint_Spring   	100.0
#      Position_Constraint_Damper     	20.0

#      Orientation_Constraint_Spring 	100.0
#      Orientation_Constraint_Damper 	20.0

    }

    SoftSphericalJoint {
      Name 				"leg2SecJnt"

      Link_A_Name    			"leg2Thigh"
      Link_B_Name    			"leg2Slide"

      Joint_A_Position      		-0.123127 -0.338289 0.0
      Rotation_Matrix_A     		1.0  0.0  0.0
		               		0.0  1.0  0.0
		               		0.0  0.0  1.0

      Joint_B_Position      		0.0  0.0  0.0
      Rotation_Matrix_B     		1.0  0.0  0.0
			       		0.0  0.0 -1.0
			       		0.0  1.0  0.0

      Joint_Friction 			0

      Position_Constraint_Spring   	100000.0
      Position_Constraint_Damper     	  2000.0

#      Position_Constraint_Spring   	100.0
#      Position_Constraint_Damper     	20.0

#      Orientation_Constraint_Spring 	100.0
#      Orientation_Constraint_Damper 	20.0
    }

    SoftSphericalJoint {
      Name 				"leg3SecJnt"

      Link_A_Name    			"leg3Shank"
      Link_B_Name    			"leg3Slide"

      Joint_A_Position      		-0.140 0.0 0.0
      Rotation_Matrix_A     		1.0  0.0  0.0
		               		0.0  1.0  0.0
		               		0.0  0.0  1.0

      Joint_B_Position      		0.0  0.0  0.0
      Rotation_Matrix_B     		1.0  0.0  0.0
			       		0.0  0.0 -1.0
			       		0.0  1.0  0.0

      Joint_Friction 			0

      Position_Constraint_Spring   	100000.0
      Position_Constraint_Damper     	  2000.0

#      Position_Constraint_Spring   	100.0
#      Position_Constraint_Damper     	20.0

#      Orientation_Constraint_Spring 	100.0
#      Orientation_Constraint_Damper 	20.0
    }

    SoftSphericalJoint {
      Name 				"leg4SecJnt"

      Link_A_Name    			"leg4Shank"
      Link_B_Name    			"leg4Slide"

      Joint_A_Position      		-0.140 0.0 0.0
      Rotation_Matrix_A     		1.0  0.0  0.0
		               		0.0  1.0  0.0
		               		0.0  0.0  1.0

      Joint_B_Position      		0.0  0.0  0.0
      Rotation_Matrix_B     		1.0  0.0  0.0
			       		0.0  0.0 -1.0
			       		0.0  1.0  0.0

      Joint_Friction 			0

      Position_Constraint_Spring   	100000.0
      Position_Constraint_Damper     	  2000.0

#      Position_Constraint_Spring   	100.0
#      Position_Constraint_Damper     	20.0

#      Orientation_Constraint_Spring 	100.0
#      Orientation_Constraint_Damper 	20.0


    }
  }
}
