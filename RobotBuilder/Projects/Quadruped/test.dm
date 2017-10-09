# DynaMechs V 4.0 ascii

ClosedArticulation {
	Name		"Quadruped"
	Graphics_Model	""

	Position		0	0	0
	Orientation_Quat	0	0	0	1
	TreeStructure {
	Branch {
		MobileBaseLink {
			Name		"body"
			Graphics_Model	"body.xan"

			Mass			36.8184
			Inertia			0.437266	0	0.000493588
						0	5.89566	0
						0.000493588	0	6.31265
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	0

			Position		1.375	4	0.65
			Orientation_Quat	0	0	0	1	
			Velocity		0	0	0	0	0	0	

		}

		ZScrewTxLink {
			Name			""
			ZScrew_Parameters	0	-1.5708
		}

		Branch {
			RevoluteLink {
				Name		"leg1Frame"
				Graphics_Model	"frameFL.cmb"

				Mass			2.57942
				Inertia			0.0809973	0	1.55338e-007
							0	0.070766	-1.10648e-006
							1.55338e-007	-1.10648e-006	0.013525
				Center_of_Gravity	-7.07794e-007	-0.0396644	-0.0747672	
				Number_of_Contact_Points	0

				MDH_Parameters		-0.165	-1.5708	0.37	1.5708	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	2500
				Joint_Limit_Damper_Constant	200
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg1Thigh"
				Graphics_Model	"thigh.xan"

				Mass			1.60868
				Inertia			0.0391354	-0.0130421	-2.4476e-006
							-0.0130421	0.021721	0
							-2.4476e-006	0	0.054352
				Center_of_Gravity	0.0147815	-0.0907813	0	
				Number_of_Contact_Points	0

				MDH_Parameters		0	1.5708	0	-1	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	2500
				Joint_Limit_Damper_Constant	200
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg1Shank"
				Graphics_Model	"shank.cmb"

				Mass			0.736117
				Inertia			0.000421232	0	0
							0	0.0296813	0
							0	0	0.0293835
				Center_of_Gravity	0.0535735	0	0	
				Number_of_Contact_Points	1
				Contact_Locations	0.5	0	0	

				MDH_Parameters		0.24	0	0	1.55998	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	1000
				Joint_Limit_Damper_Constant	50
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg1Screw"
				Graphics_Model	"ballscrew.cmb"

				Mass			1.68602
				Inertia			0.080344	0	-4.73216e-009
							0	0.000548461	0
							-4.73216e-009	0	0.0803073
				Center_of_Gravity	0	0.145308	0	
				Number_of_Contact_Points	0

				MDH_Parameters		-0.14	0	0	0.51239	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

			PrismaticLink {
				Name		"leg1Slide"
				Graphics_Model	"slide.xan"

				Mass			1.22846
				Inertia			0.0135129	-4.71192e-006	-7.17383e-006
							-4.71192e-006	0.0135435	-2.25828e-006
							-7.17383e-006	-2.25828e-006	0.00122477
				Center_of_Gravity	-4.88692e-007	0	-0.0852699	
				Number_of_Contact_Points	0

				MDH_Parameters		0	-1.5708	0.412415	0	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	5000
				Joint_Limit_Damper_Constant	200
				Joint_Friction		250
			}

		}
		Branch {
			RevoluteLink {
				Name		"leg2Frame"
				Graphics_Model	"frameFR.cmb"

				Mass			2.57942
				Inertia			0.0809973	0	-1.55338e-007
							0	0.070766	1.10648e-006
							-1.55338e-007	1.10648e-006	0.013525
				Center_of_Gravity	7.07794e-007	0.0396644	-0.0747672	
				Number_of_Contact_Points	0

				MDH_Parameters		0.165	-1.5708	0.37	1.5708	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	2500
				Joint_Limit_Damper_Constant	200
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg2Thigh"
				Graphics_Model	"thigh.xan"

				Mass			1.60868
				Inertia			0.0391354	-0.0130421	-2.4476e-006
							-0.0130421	0.021721	0
							-2.4476e-006	0	0.054352
				Center_of_Gravity	0.0147815	-0.0907813	0	
				Number_of_Contact_Points	0

				MDH_Parameters		0	1.5708	0	-1	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	2500
				Joint_Limit_Damper_Constant	200
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg2Shank"
				Graphics_Model	"shank.cmb"

				Mass			0.736117
				Inertia			0.000421232	0	0
							0	0.0296813	0
							0	0	0.0293835
				Center_of_Gravity	0.0535735	0	0	
				Number_of_Contact_Points	1
				Contact_Locations	0.5	0	0	

				MDH_Parameters		0.24	0	0	1.55998	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	1000
				Joint_Limit_Damper_Constant	50
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg2Screw"
				Graphics_Model	"ballscrew.cmb"

				Mass			1.68602
				Inertia			0.080344	0	-4.73216e-009
							0	0.000548461	0
							-4.73216e-009	0	0.0803073
				Center_of_Gravity	0	0.145308	0	
				Number_of_Contact_Points	0

				MDH_Parameters		-0.14	0	0	0.51239	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

			PrismaticLink {
				Name		"leg2Slide"
				Graphics_Model	"slide.xan"

				Mass			1.22846
				Inertia			0.0135129	-4.71192e-006	-7.17383e-006
							-4.71192e-006	0.0135435	-2.25828e-006
							-7.17383e-006	-2.25828e-006	0.00122477
				Center_of_Gravity	-4.88692e-007	0	-0.0852699	
				Number_of_Contact_Points	0

				MDH_Parameters		0	-1.5708	0.412415	0	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	5000
				Joint_Limit_Damper_Constant	200
				Joint_Friction		250
			}

		}
		Branch {
			RevoluteLink {
				Name		"leg3Frame"
				Graphics_Model	"frameHL.cmb"

				Mass			2.57942
				Inertia			0.0809973	0	1.55338e-007
							0	0.070766	1.10648e-006
							1.55338e-007	1.10648e-006	0.013525
				Center_of_Gravity	7.07794e-007	-0.0396644	0.0747672	
				Number_of_Contact_Points	0

				MDH_Parameters		-0.165	-1.5708	-0.69	1.5708	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	2500
				Joint_Limit_Damper_Constant	200
				Actuator_Type		0
				Joint_Friction		0
			}

			RevoluteLink {
				Name		"leg3Thigh"
				Graphics_Model	"thigh.xan"

				Mass			1.60868
				Inertia			0.0391354	-0.0130421	-2.4476e-006
							-0.0130421	0.021721	0
							-2.4476e-006	0	0.054352
				Center_of_Gravity	0.0147815	-0.0907813	0	
				Number_of_Contact_Points	0

				MDH_Parameters		0	-1.5708	0	-1	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	2500
				Joint_Limit_Damper_Constant	200
				Actuator_Type		0
				Joint_Friction		0
			}

			Branch {
				RevoluteLink {
					Name		"leg3Shank"
					Graphics_Model	"shank.cmb"

					Mass			0.736117
					Inertia			0.000421232	0	0
								0	0.0296813	0
								0	0	0.0293835
					Center_of_Gravity	0.0535735	0	0	
					Number_of_Contact_Points	1
					Contact_Locations	0.5	0	0	

					MDH_Parameters		0.24	0	0	1.55998	
					Initial_Joint_Velocity	0
					Joint_Limits			-1e+010	1e+010
					Joint_Limit_Spring_Constant	1000
					Joint_Limit_Damper_Constant	50
					Actuator_Type		0
					Joint_Friction		0
				}

			}
			ZScrewTxLink {
				Name			""
				ZScrew_Parameters	0	-1.91986
			}

			RevoluteLink {
				Name		"leg3Screw"
				Graphics_Model	"ballscrew.cmb"

				Mass			1.68602
				Inertia			0.080344	0	-4.73216e-009
							0	0.000548461	0
							-4.73216e-009	0	0.0803073
				Center_of_Gravity	0	0.145308	0	
				Number_of_Contact_Points	0

				MDH_Parameters		0.36	0	0	0.850654	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

			PrismaticLink {
				Name		"leg3Slide"
				Graphics_Model	"slide.xan"

				Mass			1.22846
				Inertia			0.0135129	-4.71192e-006	-7.17383e-006
							-4.71192e-006	0.0135435	-2.25828e-006
							-7.17383e-006	-2.25828e-006	0.00122477
				Center_of_Gravity	-4.88692e-007	0	-0.0852699	
				Number_of_Contact_Points	0

				MDH_Parameters		0	-1.5708	0.412415	0	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	5000
				Joint_Limit_Damper_Constant	200
				Joint_Friction		250
			}

		}
		RevoluteLink {
			Name		"leg4Frame"
			Graphics_Model	"frameHR.cmb"

			Mass			2.57942
			Inertia			0.0809973	0	-1.55338e-007
						0	0.070766	-1.10648e-006
						-1.55338e-007	-1.10648e-006	0.013525
			Center_of_Gravity	-7.07794e-007	0.0396644	0.0747672	
			Number_of_Contact_Points	0

			MDH_Parameters		0.165	-1.5708	-0.69	1.5708	
			Initial_Joint_Velocity	0
			Joint_Limits			-1e+010	1e+010
			Joint_Limit_Spring_Constant	2500
			Joint_Limit_Damper_Constant	200
			Actuator_Type		0
			Joint_Friction		0
		}

		RevoluteLink {
			Name		"leg4Thigh"
			Graphics_Model	"thigh.xan"

			Mass			1.60868
			Inertia			0.0391354	-0.0130421	-2.4476e-006
						-0.0130421	0.021721	0
						-2.4476e-006	0	0.054352
			Center_of_Gravity	0.0147815	-0.0907813	0	
			Number_of_Contact_Points	0

			MDH_Parameters		0	-1.5708	0	-1	
			Initial_Joint_Velocity	0
			Joint_Limits			-1e+010	1e+010
			Joint_Limit_Spring_Constant	2500
			Joint_Limit_Damper_Constant	200
			Actuator_Type		0
			Joint_Friction		0
		}

		Branch {
			RevoluteLink {
				Name		"leg4Shank"
				Graphics_Model	"shank.cmb"

				Mass			0.736117
				Inertia			0.000421232	0	0
							0	0.0296813	0
							0	0	0.0293835
				Center_of_Gravity	0.0535735	0	0	
				Number_of_Contact_Points	1
				Contact_Locations	0.5	0	0	

				MDH_Parameters		0.24	0	0	1.55998	
				Initial_Joint_Velocity	0
				Joint_Limits			-1e+010	1e+010
				Joint_Limit_Spring_Constant	1000
				Joint_Limit_Damper_Constant	50
				Actuator_Type		0
				Joint_Friction		0
			}

		}
		ZScrewTxLink {
			Name			""
			ZScrew_Parameters	0	-1.91986
		}

		RevoluteLink {
			Name		"leg4Screw"
			Graphics_Model	"ballscrew.cmb"

			Mass			1.68602
			Inertia			0.080344	0	-4.73216e-009
						0	0.000548461	0
						-4.73216e-009	0	0.0803073
			Center_of_Gravity	0	0.145308	0	
			Number_of_Contact_Points	0

			MDH_Parameters		0.36	0	0	0.850654	
			Initial_Joint_Velocity	0
			Joint_Limits			-1e+010	1e+010
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type		0
			Joint_Friction		0
		}

		PrismaticLink {
			Name		"leg4Slide"
			Graphics_Model	"slide.xan"

			Mass			1.22846
			Inertia			0.0135129	-4.71192e-006	-7.17383e-006
						-4.71192e-006	0.0135435	-2.25828e-006
						-7.17383e-006	-2.25828e-006	0.00122477
			Center_of_Gravity	-4.88692e-007	0	-0.0852699	
			Number_of_Contact_Points	0

			MDH_Parameters		0	-1.5708	0.412415	0	
			Initial_Joint_Velocity	0
			Joint_Limits			-1e+010	1e+010
			Joint_Limit_Spring_Constant	5000
			Joint_Limit_Damper_Constant	200
			Joint_Friction		250
		}

	}
	}
	SecondaryJoints {
		SoftSphericalJoint {
			Name		"leg1SecJnt"
			Link_A_Name	"leg1Thigh"
			Link_B_Name	"leg1Slide"

			Joint_A_Position	-0.123127	-0.338289	0	
			Rotation_Matrix_A	1	0	0	
						0	1	0	
						0	0	1	

			Joint_B_Position	0	0	0	
			Rotation_Matrix_B	1	0	0	
						0	0	-1	
						0	1	0	

			Joint_Friction	0

			Position_Constraint_Spring	100000
			Position_Constraint_Damper	2000
		}
		SoftSphericalJoint {
			Name		"leg2SecJnt"
			Link_A_Name	"leg2Thigh"
			Link_B_Name	"leg2Slide"

			Joint_A_Position	-0.123127	-0.338289	0	
			Rotation_Matrix_A	1	0	0	
						0	1	0	
						0	0	1	

			Joint_B_Position	0	0	0	
			Rotation_Matrix_B	1	0	0	
						0	0	-1	
						0	1	0	

			Joint_Friction	0

			Position_Constraint_Spring	100000
			Position_Constraint_Damper	2000
		}
		SoftSphericalJoint {
			Name		"leg3SecJnt"
			Link_A_Name	"leg3Shank"
			Link_B_Name	"leg3Slide"

			Joint_A_Position	-0.14	0	0	
			Rotation_Matrix_A	1	0	0	
						0	1	0	
						0	0	1	

			Joint_B_Position	0	0	0	
			Rotation_Matrix_B	1	0	0	
						0	0	-1	
						0	1	0	

			Joint_Friction	0

			Position_Constraint_Spring	100000
			Position_Constraint_Damper	2000
		}
		SoftSphericalJoint {
			Name		"leg4SecJnt"
			Link_A_Name	"leg4Shank"
			Link_B_Name	"leg4Slide"

			Joint_A_Position	-0.14	0	0	
			Rotation_Matrix_A	1	0	0	
						0	1	0	
						0	0	1	

			Joint_B_Position	0	0	0	
			Rotation_Matrix_B	1	0	0	
						0	0	-1	
						0	1	0	

			Joint_Friction	0

			Position_Constraint_Spring	100000
			Position_Constraint_Damper	2000
		}
	}
}