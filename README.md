# Robotbuilder

Interface created by: Steven Rodenbaugh and David E. Orin

Simulation engine (Dynamechs) created by: Scott McMillan

Department of Electical Engineering \\
The Ohio State University \\
Columbus, OH 43210

Robot simulation environment from Ohio State. Includes Dynamechs simulation engine and Robotbuilder interface

## What is RobotBuilder?

RobotBuilder is a software application that can be used to rapidly develop robotic dynamic simulations. It has an intuitive Windows interface to make it easy to use, but can perform complex simulations. The dynamic calculations are performed by DynaMechs, developed by Scott McMillan. It can simulate tree structures and star topologies with O(n) complexity. It also efficiently simulates robotic articulations with closed-kinematic loops; this capability was developed by Duane Marhefka.

RobotBuilder operates in three main modes. The Build mode is used to define the robotic articulation. The user defines the links and their properties, and sees a 3D view of the current robot. The Simulate mode accurately simulates the created model. The control for the Simulate mode is provided by the user in a DLL. This provides a considerable amount of flexibility and enables the user to develop arbitrary control techniques. While the simulation is running, the 3D view shows the animated results. Finally, the Playback mode can be used to view the simulation results in approximately real time.

## Why should I use RobotBuilder?

RobotBuilder in useful in a variety of situations. It has been utilized in an introductory robotics course at The Ohio State University. Skeleton projects were provided to the students, which they completed for assignments. It provided them individual "hands-on" experience, which helped enable them to understand important concepts in robotics. RobotBuilderhas also been used in research. Its flexible control design has made it useful in robotics control research. The ease-of-use of RobotBuilder has enabled researchers to focus on the control techniques and immediately see graphical results.

## What is RobotModeler?

RobotModeler is a simple application to develop graphical models for RobotBuilder. It also has the ability to approximate the values of the dynamic (mass) parameters of the links modeled in RobotModeler.

## What is used to build RobotBuilder?

In short, I don't know.  The code has languished for a while.

The source that was used with Visual Studio 2003.NET in the hopes that a developer might someday upgrade to work with a "modern" build tool.

Here is a link to the orginal web page: http://www2.ece.ohio-state.edu/~orin/RobotBuilder/RobotBuilder.html