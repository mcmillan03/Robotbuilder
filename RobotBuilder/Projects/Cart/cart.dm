# DynaMechs V 4.0 ascii
# Create by Scott McMillan

Articulation {
	Name		"Articulation"
	Graphics_Model	""

	Position		0	0	0
	Orientation_Quat	0	0	0	0
	Branch {
		MobileBaseLink {
			Name		"CartBody"
			Graphics_Model	"cart_body.xan"

			Mass			2.5
			Inertia			2.2	0	0
						0	1.1	0
						0	0	2.2
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	8
			Contact_Locations	-1	0.25	0.9	
						1	0.25	0.9	
						-1	-0.25	0.9	
						1	-0.25	0.9	
						-1	0.25	-0.9	
						1	0.25	-0.9	
						-1	-0.25	-0.9	
						1	-0.25	-0.9	

			Position		7	10	5
			Orientation_Quat	0.7071	0	0	0.7071	
			Velocity		0	0	0	0	0	0	

		}

		Branch {
			ZScrewTxLink {
				Name			"ZScrew Transform"
				ZScrew_Parameters	1	0
			}

			RevoluteLink {
				Name		"Wheel1"
				Graphics_Model	"cart_wheel.xan"

				Mass			0.2
				Inertia			0.3	0	0
							0	0.3	0
							0	0	0.8
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	16
				Contact_Locations	0.5	0	0	
							0.4619	0.1913	0	
							0.3535	0.3535	0	
							0.1913	0.4619	0	
							0	0.5	0	
							-0.1913	0.4619	0	
							-0.3535	0.3535	0	
							-0.4619	0.1913	0	
							-0.5	0	0	
							-0.4619	-0.1913	0	
							-0.3535	-0.3535	0	
							-0.1913	-0.4619	0	
							0	-0.5	0	
							0.1913	-0.4619	0	
							0.3535	-0.3535	0	
							0.4619	-0.1913	0	

				MDH_Parameters		0.9	0	0	0	
				Initial_Joint_Velocity	0
				Joint_Limits			-1000.17	1000.17
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0.35
			}

		}
		Branch {
			ZScrewTxLink {
				Name			"ZScrew Transform"
				ZScrew_Parameters	-1	0
			}

			RevoluteLink {
				Name		"Wheel2"
				Graphics_Model	"cart_wheel.xan"

				Mass			0.2
				Inertia			0.3	0	0
							0	0.3	0
							0	0	0.8
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	16
				Contact_Locations	0.5	0	0	
							0.4619	0.1913	0	
							0.3535	0.3535	0	
							0.1913	0.4619	0	
							0	0.5	0	
							-0.1913	0.4619	0	
							-0.3535	0.3535	0	
							-0.4619	0.1913	0	
							-0.5	0	0	
							-0.4619	-0.1913	0	
							-0.3535	-0.3535	0	
							-0.1913	-0.4619	0	
							0	-0.5	0	
							0.1913	-0.4619	0	
							0.3535	-0.3535	0	
							0.4619	-0.1913	0	

				MDH_Parameters		0.9	0	0	0	
				Initial_Joint_Velocity	0
				Joint_Limits			-1000.17	1000.17
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0.35
			}

		}
		Branch {
			ZScrewTxLink {
				Name			"ZScrew Transform"
				ZScrew_Parameters	1	0
			}

			RevoluteLink {
				Name		"Wheel3"
				Graphics_Model	"cart_wheel.xan"

				Mass			0.2
				Inertia			0.3	0	0
							0	0.3	0
							0	0	0.8
				Center_of_Gravity	0	0	0	
				Number_of_Contact_Points	16
				Contact_Locations	0.5	0	0	
							0.4619	0.1913	0	
							0.3535	0.3535	0	
							0.1913	0.4619	0	
							0	0.5	0	
							-0.1913	0.4619	0	
							-0.3535	0.3535	0	
							-0.4619	0.1913	0	
							-0.5	0	0	
							-0.4619	-0.1913	0	
							-0.3535	-0.3535	0	
							-0.1913	-0.4619	0	
							0	-0.5	0	
							0.1913	-0.4619	0	
							0.3535	-0.3535	0	
							0.4619	-0.1913	0	

				MDH_Parameters		-0.9	0	0	0	
				Initial_Joint_Velocity	0
				Joint_Limits			-1000.17	1000.17
				Joint_Limit_Spring_Constant	0
				Joint_Limit_Damper_Constant	0
				Actuator_Type		0
				Joint_Friction		0.35
			}

		}
		ZScrewTxLink {
			Name			"ZScrew Transform"
			ZScrew_Parameters	-1	0
		}

		RevoluteLink {
			Name		"Wheel4"
			Graphics_Model	"cart_wheel.xan"

			Mass			0.2
			Inertia			0.3	0	0
						0	0.3	0
						0	0	0.8
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	16
			Contact_Locations	0.5	0	0	
						0.4619	0.1913	0	
						0.3535	0.3535	0	
						0.1913	0.4619	0	
						0	0.5	0	
						-0.1913	0.4619	0	
						-0.3535	0.3535	0	
						-0.4619	0.1913	0	
						-0.5	0	0	
						-0.4619	-0.1913	0	
						-0.3535	-0.3535	0	
						-0.1913	-0.4619	0	
						0	-0.5	0	
						0.1913	-0.4619	0	
						0.3535	-0.3535	0	
						0.4619	-0.1913	0	

			MDH_Parameters		-0.9	0	0	0	
			Initial_Joint_Velocity	0
			Joint_Limits			-1000.17	1000.17
			Joint_Limit_Spring_Constant	0
			Joint_Limit_Damper_Constant	0
			Actuator_Type		0
			Joint_Friction		0.35
		}

	}
}