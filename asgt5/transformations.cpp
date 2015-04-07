// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// Procedural module that implements transformations used in
// the homework assignment.
//
// $Id: transformations.cpp 5554 2015-02-19 06:59:50Z mshafae $
//
// STUDENTS _MUST_ ADD THEIR CODE INTO THIS FILE
//

#include "transformations.h"

#ifndef __SOLUTION__

void rotateCameraLeft(float degrees, Vec3& eyePosition, Vec3& centerPosition, Vec3& upVector){
  // Please implement this function.
	Mat4 check;
	Vec4 checkvec;
	check = rotate(degrees,upVector[0],upVector[1],upVector[2]);
	checkvec[0] = eyePosition[0];
	checkvec[1] = eyePosition[1];
	checkvec[2] = eyePosition[2];
	checkvec[3] = 0;
	checkvec = check * checkvec;
	
	eyePosition[0] = checkvec[0];
	eyePosition[1] = checkvec[1];
	eyePosition[2] = checkvec[2];
}

void rotateCameraUp(float degrees, Vec3& eyePosition, Vec3& centerPosition, Vec3& upVector){
  // Please implement this function.
	Mat4 check;
	Vec4 checkvec;
	check = rotate(degrees,upVector[1],upVector[0],upVector[2]);
	checkvec[0] = eyePosition[0];
	checkvec[1] = eyePosition[1];
	checkvec[2] = eyePosition[2];
	checkvec[3] = 0;
	checkvec = check * checkvec;
	
	eyePosition[0] = checkvec[0];
	eyePosition[1] = checkvec[1];
	eyePosition[2] = checkvec[2];
}

#else
#include "transformations_solution.cpp"
#endif
