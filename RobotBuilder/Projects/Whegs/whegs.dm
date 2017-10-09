# DynaMechs V 4.0 ascii

Articulation {
	Name		"Articulation"
	Graphics_Model	""

	Position		0	0	0
	Orientation_Quat	0	0	0	1
	Branch {
		StaticRootLink {
			Name		"Whegs"
			Graphics_Model	""

		}

		MobileBaseLink {
			Name		"Body"
			Graphics_Model	"whegs_body.rbm"

			Mass			2.6
			Inertia			7.37396e-008	0	0
						0	5.29125e-008	0
						0	0	7.37396e-008
			Center_of_Gravity	2.00161e-018	-1.66801e-018	0	
			Number_of_Contact_Points	9
			Contact_Locations	-0.25	0.2	-0.03	
						0	0.2	-0.03	
						0.25	0.2	-0.03	
						-0.25	0	-0.03	
						0	0	-0.03	
						0.25	0	-0.03	
						-0.25	-0.2	-0.03	
						0	-0.2	-0.03	
						0.25	-0.2	-0.03	

			Position		0.2	0.4	0.1
			Orientation_Quat	0	0	0	1	
			Velocity		0	0	0	0	0	0	

		}

		Branch {
			RevoluteLink {
				Name		"Wheg 1"
				Graphics_Model	"wheg.rbm"

				Mass			0.0500001
				Inertia			5.25477e-005	2.42842e-005	0
							2.42842e-005	4.534e-005	0
							0	0	5.61515e-005
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	3
				Contact_Locations	0.1	0	0	
							-0.05	0.09	0	
							-0.05	-0.09	0	

				MDH_Parameters		0.23	-1.5708	0.25	0	
				Initial_Joint_Velocity	0
				Joint_Limits			0	0
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

		}
		Branch {
			RevoluteLink {
				Name		"Wheg 2"
				Graphics_Model	"wheg.rbm"

				Mass			0.0500001
				Inertia			5.25477e-005	2.42842e-005	0
							2.42842e-005	4.534e-005	0
							0	0	5.61515e-005
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	3
				Contact_Locations	0.1	0	0	
							-0.05	0.09	0	
							-0.05	-0.09	0	

				MDH_Parameters		0.23	-1.5708	-0.25	1.0472	
				Initial_Joint_Velocity	0
				Joint_Limits			0	0
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

		}
		Branch {
			RevoluteLink {
				Name		"Wheg 3"
				Graphics_Model	"wheg.rbm"

				Mass			0.0500001
				Inertia			5.25477e-005	2.42842e-005	0
							2.42842e-005	4.534e-005	0
							0	0	5.61515e-005
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	3
				Contact_Locations	0.1	0	0	
							-0.05	0.09	0	
							-0.05	-0.09	0	

				MDH_Parameters		0	-1.5708	0.25	1.0472	
				Initial_Joint_Velocity	0
				Joint_Limits			0	0
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

		}
		Branch {
			RevoluteLink {
				Name		"Wheg 4"
				Graphics_Model	"wheg.rbm"

				Mass			0.0500001
				Inertia			5.25477e-005	2.42842e-005	0
							2.42842e-005	4.534e-005	0
							0	0	5.61515e-005
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	3
				Contact_Locations	0.1	0	0	
							-0.05	-0.09	0	
							-0.05	0.09	0	

				MDH_Parameters		0	-1.5708	-0.25	0	
				Initial_Joint_Velocity	0
				Joint_Limits			0	0
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

		}
		Branch {
			RevoluteLink {
				Name		"Wheg 5"
				Graphics_Model	"wheg.rbm"

				Mass			0.0500001
				Inertia			5.25477e-005	2.42842e-005	0
							2.42842e-005	4.534e-005	0
							0	0	5.61515e-005
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	3
				Contact_Locations	0.1	0	0	
							-0.05	-0.09	0	
							-0.05	0.09	0	

				MDH_Parameters		-0.23	-1.5708	0.25	0	
				Initial_Joint_Velocity	0
				Joint_Limits			0	0
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0
			}

		}
		RevoluteLink {
			Name		"Wheg 6"
			Graphics_Model	"wheg.rbm"

			Mass			0.0500001
			Inertia			5.25477e-005	2.42842e-005	0
						2.42842e-005	4.534e-005	0
						0	0	5.61515e-005
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	3
			Contact_Locations	0.1	0	0	
						-0.05	-0.09	0	
						-0.05	0.09	0	

			MDH_Parameters		-0.23	-1.5708	-0.25	1.0472	
			Initial_Joint_Velocity	0
			Joint_Limits			0	0
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type		0
			Joint_Friction		0
		}

	}
}