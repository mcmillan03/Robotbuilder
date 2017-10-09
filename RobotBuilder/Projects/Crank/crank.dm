# DynaMechs V 4.0 ascii

ClosedArticulation {
	Name		"slider_crank"
	Graphics_Model	""

	Position		1.375	2.25	0.5
	Orientation_Quat	0	0	0	1
	TreeStructure {
	Branch {
		StaticRootLink {
			Name		"base"
			Graphics_Model	"crank_base.rbm"

		}

		ZScrewTxLink {
			Name			""
			ZScrew_Parameters	0.275	0
		}

		RevoluteLink {
			Name		"crank"
			Graphics_Model	"crank_wheel.xan"

			Mass			2
			Inertia			0.02167	0	0
						0	0.02167	0
						0	0	0.04
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	0

			MDH_Parameters		0.25	1.5708	0.15	33.741	
			Initial_Joint_Velocity	5
			Joint_Limits			-1e+010	1e+010
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type		0
			Joint_Friction		0.001
		}

		SphericalLink {
			Name		"linkage"
			Graphics_Model	"crank_linkage.xan"

			Mass			0.25
			Inertia			7.8e-005	0	0
						0	0.03004	0
						0	0	0.03004
			Center_of_Gravity	0.3	0	0	
			Number_of_Contact_Points	0

			Position_From_Inboard_Link		0.2	0	0.075	
			Initial_Joint_Angles		-0.0038	-0.4761	-2.1758	
			Initial_Angular_Velocity		0	0	0	
			Axes_Limits		0	0	0	
			Joint_Limit_Spring_Constant		0
			Joint_Limit_Damper_Constant		0
			Joint_Friction		0
		}

		SphericalLink {
			Name		"piston"
			Graphics_Model	"crank_piston.xan"

			Mass			0.5
			Inertia			0.0003063	0	0
						0	0.003903	0
						0	0	0.003903
			Center_of_Gravity	0.075	0	0	
			Number_of_Contact_Points	0

			Position_From_Inboard_Link		0.6	0	0	
			Initial_Joint_Angles		-0.0722	0.471	-0.1655	
			Initial_Angular_Velocity		0	0	0	
			Axes_Limits		0	0	0	
			Joint_Limit_Spring_Constant		0
			Joint_Limit_Damper_Constant		0
			Joint_Friction		0
		}

	}
	}
	SecondaryJoints {
		SoftPrismaticJoint {
			Name		"secPrisJnt_1"
			Link_A_Name	"base"
			Link_B_Name	"piston"

			Joint_A_Position	0	-0.5	0.5	
			Rotation_Matrix_A	0	0	1	
						0	1	0	
						-1	0	0	

			Joint_B_Position	0	0	0	
			Rotation_Matrix_B	0	0	1	
						-1	0	0	
						0	-1	0	

			Joint_Friction	0

			Position_Constraint_Spring	100
			Position_Constraint_Damper	200
			Orientation_Constraint_Spring	100
			Orientation_Constraint_Damper	200
		}
	}
}