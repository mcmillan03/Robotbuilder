# DynaMechs V 4.0 ascii

Articulation {
	Name		"base"
	Graphics_Model	"base.rbm"

	Position		5	5	2.51
	Orientation_Quat	0	0	0	0
	Branch {
		RevoluteLink {
			Name		"body"
			Graphics_Model	"body.rbm"

			Mass			0.1
			Inertia			0.1	0	0
						0	0.1	0
						0	0	0.1
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	0

			MDH_Parameters		0	0	0	0	
			Initial_Joint_Velocity	0
			Joint_Limits			0	0
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type			1
			Motor_Torque_Constant		0.101
			Motor_BackEMF_Constant		0.101
			Motor_Armature_Resistance	0.75
			Motor_Inertia			0.000233
			Motor_Coulomb_Friction_Constant	0
			Motor_Viscous_Friction_Constant	0.000303
			Motor_Max_Brush_Drop		0
			Motor_Half_Drop_Value		0
			Motor_Gear_Ratio		102
		}

		RevoluteLink {
			Name		"upperarm"
			Graphics_Model	"upperarm.rbm"

			Mass			0.1
			Inertia			0.1	0	0
						0	0.1	0
						0	0	0.1
			Center_of_Gravity	1.1	0	0	
			Number_of_Contact_Points	0

			MDH_Parameters		0	-1.57	0	-0.62134	
			Initial_Joint_Velocity	0
			Joint_Limits			0	0
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type			1
			Motor_Torque_Constant		0.101
			Motor_BackEMF_Constant		0.101
			Motor_Armature_Resistance	0.75
			Motor_Inertia			0.000233
			Motor_Coulomb_Friction_Constant	0
			Motor_Viscous_Friction_Constant	0.000303
			Motor_Max_Brush_Drop		0
			Motor_Half_Drop_Value		0
			Motor_Gear_Ratio		102
		}

		RevoluteLink {
			Name		"forearm"
			Graphics_Model	"forearm.rbm"

			Mass			0.1
			Inertia			0.1	0	0
						0	0.1	0
						0	0	0.1
			Center_of_Gravity	0.8	0	0	
			Number_of_Contact_Points	8
			Contact_Locations	0	-0.4	-0.37	
						0	-0.4	0.37	
						0	0.4	0.37	
						0	0.4	-0.37	
						1.6	-0.45	-0.4	
						1.6	-0.45	0.4	
						1.6	0.45	-0.4	
						1.6	0.45	0.4	

			MDH_Parameters		2.2	0	0	1.5481	
			Initial_Joint_Velocity	0
			Joint_Limits			0	0
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type			1
			Motor_Torque_Constant		0.101
			Motor_BackEMF_Constant		0.101
			Motor_Armature_Resistance	0.75
			Motor_Inertia			0.000233
			Motor_Coulomb_Friction_Constant	0
			Motor_Viscous_Friction_Constant	0.000303
			Motor_Max_Brush_Drop		0
			Motor_Half_Drop_Value		0
			Motor_Gear_Ratio		102
		}

		RevoluteLink {
			Name		"wrist_pitch"
			Graphics_Model	"wrist_pitch.rbm"

			Mass			0.1
			Inertia			0.1	0	0
						0	0.1	0
						0	0	0.1
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	0

			MDH_Parameters		1.6	0	0	2.2161	
			Initial_Joint_Velocity	0
			Joint_Limits			0	0
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type			1
			Motor_Torque_Constant		0.101
			Motor_BackEMF_Constant		0.101
			Motor_Armature_Resistance	0.75
			Motor_Inertia			0.000233
			Motor_Coulomb_Friction_Constant	0
			Motor_Viscous_Friction_Constant	0.000303
			Motor_Max_Brush_Drop		0
			Motor_Half_Drop_Value		0
			Motor_Gear_Ratio		102
		}

		RevoluteLink {
			Name		"wrist_roll"
			Graphics_Model	"hand.rbm"

			Mass			0.1
			Inertia			0.1	0	0
						0	0.1	0
						0	0	0.1
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	4
			Contact_Locations	-0.44	0.21	1.13	
						0.44	0.21	1.13	
						0.44	-0.21	1.13	
						-0.44	-0.21	1.13	

			MDH_Parameters		0	1.57	0	0	
			Initial_Joint_Velocity	0
			Joint_Limits			0	0
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type			1
			Motor_Torque_Constant		0.101
			Motor_BackEMF_Constant		0.101
			Motor_Armature_Resistance	0.75
			Motor_Inertia			0.000233
			Motor_Coulomb_Friction_Constant	0
			Motor_Viscous_Friction_Constant	0.000303
			Motor_Max_Brush_Drop		0
			Motor_Half_Drop_Value		0
			Motor_Gear_Ratio		102
		}

		ZScrewTxLink {
			Name			""
			ZScrew_Parameters	1.13	1.57
		}

		Branch {
			PrismaticLink {
				Name		"gripper1"
				Graphics_Model	"mitsu_gripper.xan"

				Mass			0.01
				Inertia			0.1	0	0
							0	0.1	0
							0	0	0.1
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	1
				Contact_Locations	-0.37	0	0	

				MDH_Parameters		0	-1.57	0.05	1.57	
				Initial_Joint_Velocity	0
				Joint_Limits			0.0495	0.0505
				Joint_Limit_Spring_Constant	10
				Joint_Limit_Damper_Constant	6.3
				Joint_Friction		0
			}

		}
		PrismaticLink {
			Name		"gripper2"
			Graphics_Model	"mitsu_gripper.xan"

			Mass			0.01
			Inertia			0.1	0	0
						0	0.1	0
						0	0	0.1
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	1
			Contact_Locations	-0.37	0	0	

			MDH_Parameters		0	-1.57	-0.05	1.57	
			Initial_Joint_Velocity	0
			Joint_Limits			-0.0495	-0.0505
			Joint_Limit_Spring_Constant	10
			Joint_Limit_Damper_Constant	6.3
			Joint_Friction		0
		}

	}
}