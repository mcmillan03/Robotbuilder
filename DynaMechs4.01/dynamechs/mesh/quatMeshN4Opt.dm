# DynaMechs V 4.0 ascii
# 4x4 quaternion joint mesh (optimized loops) parameter file

ClosedArticulation {
   Name 	     "meshN4Hardopt"
   Graphics_Model    ""
   Position	     0.5 2.0 4.0
   Orientation_Quat  0.70711 0.0 0.0 0.70711

   TreeStructure {

      StaticRootLink {
         Name                "base"
         Graphics_Model      "mesh_baseN4.xan"
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v12"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		-0.2706 -0.2706 -0.6533 0.6533
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v13"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	1.50 0.0 0.0
	    Orientation_Quat         		-0.2706 -0.2706 -0.6533 0.6533
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v14"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	2.25 0.0 0.0
	    Orientation_Quat         		-0.2706 -0.2706 -0.6533 0.6533
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v15"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	3.00 0.0 0.0
	    Orientation_Quat         		-0.2706 -0.2706 -0.6533 0.6533
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

     QuaternionLink {
	 Name 		         		"v11"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.0 0.0 0.0
	 Orientation_Quat         		-0.2706 -0.2706 -0.6533 0.6533
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v21"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

         Branch {
   	    QuaternionLink {
	       Name 		       		"h21"
	       Graphics_Model             	"mesh_link.xan"

	       Mass                     	2.0
	       Inertia				0.000625  0.0    0.0
				     		0.0       0.3753 0.0
						0.0       0.0    0.3753
	       Center_of_Gravity		0.375  0.0  0.0

	       Number_of_Contact_Points		0

	       Position_From_Inboard_Link   	0.75 0.0 0.0
	       Orientation_Quat         	0.0 0.0 0.7071 0.7071
	       Initial_Angular_Velocity     	0.0 0.0 0.0
	       Joint_Friction		 	0.0
	    }
	 }

   	 QuaternionLink {
	    Name 		         	"v31"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

         Branch {
   	    QuaternionLink {
	       Name 		       		"h31"
	       Graphics_Model             	"mesh_link.xan"

	       Mass                     	2.0
	       Inertia				0.000625  0.0    0.0
				     		0.0       0.3753 0.0
						0.0       0.0    0.3753
	       Center_of_Gravity		0.375  0.0  0.0

	       Number_of_Contact_Points		0

	       Position_From_Inboard_Link   	0.75 0.0 0.0
	       Orientation_Quat         	0.0 0.0 0.7071 0.7071
	       Initial_Angular_Velocity     	0.0 0.0 0.0
	       Joint_Friction		 	0.0
	    }
	 }

   	 QuaternionLink {
	    Name 		         	"v41"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

   	 QuaternionLink {
	    Name 		         	"h41"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.7071 0.7071
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      QuaternionLink {
	 Name 		         		"h11"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"h12"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

         Branch {
   	    QuaternionLink {
	       Name 		       		"v23"
	       Graphics_Model             	"mesh_link.xan"

	       Mass                     	2.0
	       Inertia				0.000625  0.0    0.0
				     		0.0       0.3753 0.0
						0.0       0.0    0.3753
	       Center_of_Gravity		0.375  0.0  0.0

	       Number_of_Contact_Points		0

	       Position_From_Inboard_Link   	0.75 0.0 0.0
	       Orientation_Quat         	0.0 0.0 -0.7071 0.7071
	       Initial_Angular_Velocity     	0.0 0.0 0.0
	       Joint_Friction		 	0.0
	    }
	 }

   	 QuaternionLink {
	    Name 		         	"h13"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

         Branch {
   	    QuaternionLink {
	       Name 		       		"v24"
	       Graphics_Model             	"mesh_link.xan"

	       Mass                     	2.0
	       Inertia				0.000625  0.0    0.0
				     		0.0       0.3753 0.0
						0.0       0.0    0.3753
	       Center_of_Gravity		0.375  0.0  0.0

	       Number_of_Contact_Points		0

	       Position_From_Inboard_Link   	0.75 0.0 0.0
	       Orientation_Quat         	0.0 0.0 -0.7071 0.7071
	       Initial_Angular_Velocity     	0.0 0.0 0.0
	       Joint_Friction		 	0.0
	    }
	 }

   	 QuaternionLink {
	    Name 		         	"h14"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

   	 QuaternionLink {
	    Name 		         	"v25"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 -0.7071 0.7071
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      QuaternionLink {
	 Name 		         		"v22"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 -0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v32"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

         Branch {
   	    QuaternionLink {
	       Name 		       		"h32"
	       Graphics_Model             	"mesh_link.xan"

	       Mass                     	2.0
	       Inertia				0.000625  0.0    0.0
				     		0.0       0.3753 0.0
						0.0       0.0    0.3753
	       Center_of_Gravity		0.375  0.0  0.0

	       Number_of_Contact_Points		0

	       Position_From_Inboard_Link   	0.75 0.0 0.0
	       Orientation_Quat         	0.0 0.0 0.7071 0.7071
	       Initial_Angular_Velocity     	0.0 0.0 0.0
	       Joint_Friction		 	0.0
	    }
	 }

   	 QuaternionLink {
	    Name 		         	"v42"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

   	 QuaternionLink {
	    Name 		         	"h42"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.7071 0.7071
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      QuaternionLink {
	 Name 		         		"h22"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"h23"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

         Branch {
   	    QuaternionLink {
	       Name 		       		"v34"
	       Graphics_Model             	"mesh_link.xan"

	       Mass                     	2.0
	       Inertia				0.000625  0.0    0.0
				     		0.0       0.3753 0.0
						0.0       0.0    0.3753
	       Center_of_Gravity		0.375  0.0  0.0

	       Number_of_Contact_Points		0

	       Position_From_Inboard_Link   	0.75 0.0 0.0
	       Orientation_Quat         	0.0 0.0 -0.7071 0.7071
	       Initial_Angular_Velocity     	0.0 0.0 0.0
	       Joint_Friction		 	0.0
	    }
	 }

   	 QuaternionLink {
	    Name 		         	"h24"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

   	 QuaternionLink {
	    Name 		         	"v35"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 -0.7071 0.7071
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      QuaternionLink {
	 Name 		         		"v33"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 -0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"v43"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

   	 QuaternionLink {
	    Name 		         	"h43"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.7071 0.7071
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      QuaternionLink {
	 Name 		         		"h33"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      Branch {
   	 QuaternionLink {
	    Name 		         	"h34"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 0.0 1.0
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }

  	 QuaternionLink {
	    Name 		         	"v45"
	    Graphics_Model               	"mesh_link.xan"

	    Mass                     	 	2.0
	    Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	    Center_of_Gravity		 	0.375  0.0  0.0

	    Number_of_Contact_Points	 	0

	    Position_From_Inboard_Link   	0.75 0.0 0.0
	    Orientation_Quat         		0.0 0.0 -0.7071 0.7071
	    Initial_Angular_Velocity     	0.0 0.0 0.0
	    Joint_Friction		 	0.0
	 }
      }

      QuaternionLink {
	 Name 		         		"v44"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 -0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

      QuaternionLink {
	 Name 		         		"h44"
	 Graphics_Model               		"mesh_link.xan"

	 Mass                     	 	2.0
	 Inertia			 	0.000625  0.0    0.0
				     	 	0.0       0.3753 0.0
					 	0.0       0.0    0.3753
	 Center_of_Gravity		 	0.375  0.0  0.0

	 Number_of_Contact_Points	 	0

	 Position_From_Inboard_Link   		0.75 0.0 0.0
	 Orientation_Quat         		0.0 0.0 0.7071 0.7071
	 Initial_Angular_Velocity     		0.0 0.0 0.0
	 Joint_Friction		 		0.0
      }

   }


   SecondaryJoints {

      HardSphericalJoint {
	 Name 				"h11v12"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h11"
         Link_B_Name			"v12"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h12v13"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h12"
         Link_B_Name			"v13"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h13v14"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h13"
         Link_B_Name			"v14"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h14v15"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h14"
         Link_B_Name			"v15"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h21v22"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h21"
         Link_B_Name			"v22"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h31v32"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h31"
         Link_B_Name			"v32"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h41v42"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h41"
         Link_B_Name			"v42"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

     HardSphericalJoint {
	 Name 				"h22v23"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h22"
         Link_B_Name			"v23"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h23v24"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h23"
         Link_B_Name			"v24"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h24v25"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h24"
         Link_B_Name			"v25"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h32v33"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h32"
         Link_B_Name			"v33"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h42v43"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h42"
         Link_B_Name			"v43"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h33v34"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h33"
         Link_B_Name			"v34"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h34v35"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h34"
         Link_B_Name			"v35"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h43v44"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h43"
         Link_B_Name			"v44"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

      HardSphericalJoint {
	 Name 				"h44v45"
	 Stabilization                  BAUMGARTE

         Link_A_Name			"h44"
         Link_B_Name			"v45"

         Joint_A_Position		0.75 0.0  0.0
	 Rotation_Matrix_A		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_B_Position		0.75 0.0  0.0
         Rotation_Matrix_B		1.0  0.0  0.0
					0.0  1.0  0.0
					0.0  0.0  1.0

	 Joint_Friction		 	0.0

	 Position_Constraint_Spring	100.0
	 Position_Constraint_Damper	20.0
      }

   }
}
