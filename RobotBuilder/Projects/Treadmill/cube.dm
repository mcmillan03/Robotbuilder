# DynaMechs V 4.0 ascii

Articulation {
	Name		"Articulation"
	Graphics_Model	""

	Position		0	0	0
	Orientation_Quat	0	0	0	0
	Branch {
		MobileBaseLink {
			Name		"Mobile Base Link"
			Graphics_Model	"obj_cube_center.xan"

			Mass			1
			Inertia			1	0	0
						0	1	0
						0	0	1
			Center_of_Gravity	0	0	0	
			Number_of_Contact_Points	8
			Contact_Locations	-1	-1	-1	
						-1	1	-1	
						1	-1	-1	
						1	1	-1	
						1	1	1	
						1	-1	1	
						-1	1	1	
						-1	-1	1	

			Position		0	0	2
			Orientation_Quat	0	0	0	0	
			Velocity		0	0	0	0	0	0	

		}

	}
}