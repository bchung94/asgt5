#ifndef _PICKER_H_
#define _PICKER_H_

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <cassert>
#include <vector>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#pragma comment(lib,"glu32.lib")
#define msglError( ) _msglError( stderr, __FILE__, __LINE__ )

#define FP_SP_EPSILON 1e-6
#define FP_DP_EPSILON 1e-15

#define FP_EQUAL(a, b, delta) ( ((a) == (b)) || \
((a)-(delta) < (b) && \
  (a)+(delta) > (b)) )

#define FP_NOT_EQUAL(a, b, delta) ( ((a) != (b)) && \
((a)-(delta) > (b) || \
  (a)+(delta) < (b)) )

#define FP_LT(a, b, delta)  (fabs((a) - (b)) < (delta))

#define FP_GT(a, b, delta)  (fabs((a) - (b)) > (delta))

typedef struct ray3d{
  // origin
  double o[3];
  // direction
  double d[3];
}ray3d;

typedef struct triangle3d{
  double a[3];
  double b[3];
  double c[3];
}triangle3d;

typedef struct hitd{
  double t;
  double point[3];
}hitd;

void matCopy3d(double *dest, double *src);
void COPYvecCopy3d(double *dest, double *src);
void rayEval3d(double *p, ray3d *r, double t);
double vecDot3d(double *a, double *b);
void COPYvecCross3d(double *n, double *u, double *v);
void COPYvecDifference3d(double *c, double *a, double *b);
void matMultVec3d(double* vout, double* v, double* m);
bool rayTriangleIntersectiond(hitd *h, ray3d *r, triangle3d *t);
void msglPrintMatrix16dv( char *varName, double matrix[16] );
void printTopOfBothStacks( char *msg );
bool intersectionDemo(double* frontPlane, double* backPlane);
int pick( int x, int y );

#endif