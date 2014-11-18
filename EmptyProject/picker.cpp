#include "picker.h"


int changecol = 0;

double cubebox[36][3] = {
	5.1f, 1.1f,3.9f,
    5.1f,-1.1f, 3.9f,
    2.9f,1.1f, 3.9f,
	5.1f,-1.1f, 3.9f,
    2.9f,1.1f, 3.9f,
	2.9f,-1.1f, 3.9f,
	5.1f, 1.1f,6.1f,
    5.1f,-1.1f, 6.1f,
    2.9f,1.1f, 6.1f,
	5.1f,-1.1f, 6.1f,
    2.9f,1.1f, 6.1f,
	2.9f,-1.1f, 6.1f,
	5.1f, 1.1f,3.9f,
    5.1f,1.1f, 6.1f,
    2.9f,1.1f, 3.9f,
	5.1f,1.1f, 6.1f,
    2.9f,1.1f, 3.9f,
	2.9f,1.1f, 6.1f,
	5.1f, -1.1f, 3.9f,
    5.1f,-1.1f, 6.1f,
    2.9f,-1.1f, 3.9f,
	5.1f,-1.1f, 6.1f,
    2.9f,-1.1f, 3.9f,
	2.9f,-1.1f, 6.1f,
	5.1f, 1.1f, 3.9f,
    5.1f,-1.1f, 3.9f,
    5.1f,1.1f, 6.1f,
	5.1f,1.1f, 6.1f,
    5.1f,-1.1f, 6.1f,
	5.1f,-1.1f, 3.9f,
	2.9f, 1.1f, 3.9f,
    2.9f,-1.1f, 3.9f,
    2.9f,1.1f, 6.1f,
	2.9f,1.1f, 6.1f,
    2.9f,-1.1f, 6.1f,
	2.9f,-1.1f, 3.9f
};

double pyrbox[36][3] = {
	-1.0, -1.2, 1.9,
-1.0, -1.2, 4.1,
1.0, -1.2, 1.9,
1.0, -1.2, 1.9,
1.0, -1.2, 4.1,
-1.0, -1.2, 4.1,
-1.0, 1.2, 1.9,
-1.0, 1.2, 4.1,
1.0, 1.2, 1.9,
1.0, 1.2, 1.9,
1.0, 1.2, 4.1,
-1.0, 1.2, 4.1,
-1.0, -1.2, 1.9,
-1.0, 1.2, 1.9,
-1.0, -1.2, 4.1,
-1.0, -1.2, 4.1,
-1.0, 1.2, 4.1,
-1.0, 1.2, 1.9,
1.0, -1.2, 1.9,
1.0, 1.2, 1.9,
1.0, -1.2, 4.1,
1.0, -1.2, 4.1,
1.0, 1.2, 4.1,
1.0, 1.2, 1.9,
-1.0, -1.2, 1.9,
-1.0, 1.2, 1.9,
1.0, 1.2, 1.9,
1.0, 1.2, 1.9,
1.0, -1.2, 1.9,
-1.0, -1.2, 1.9,
-1.0, -1.2, 4.1,
-1.0, 1.2, 4.1,
1.0, 1.2, 4.1,
1.0, 1.2, 4.1,
1.0, -1.2, 4.1,
-1.0, -1.2, 4.1
};

double pentbox[36][3] = {
	-5.2f,3.1f,5.1f,
	-2.8f,3.1f,5.1f,
	-2.8f,0.9f,5.1f,
	-5.2f,3.1f,5.1f,
	-2.8f,0.9f,5.1f,
	-5.2f,0.9f,5.1f,
	-5.2f,3.1f,2.9f,
	-2.8f,3.1f,2.9f,
	-2.8f,0.9f,2.9f,
	-5.2f,3.1f,2.9f,
	-2.8f,0.9f,2.9f,
	-5.2f,0.9f,2.9f,
	-5.2f,3.1f,5.1f,
	-5.2f,3.1f,2.9f,
	-2.8f,3.1f,2.9f,
	-5.2f,3.1f,5.1f,
	-2.8f,3.1f,2.9f,
	-2.8f,3.1f,5.1f,
	-5.2f,0.9f,5.1f,
	-5.2f,0.9f,2.9f,
	-2.8f,0.9f,2.9f,
	-5.2f,0.9f,5.1f,
	-2.8f,0.9f,2.9f,
	-2.8f,0.9f,5.1f,
	-5.2f,3.1f,2.9f,
	-5.2f,0.9f,2.9f,
	-5.2f,0.9f,5.1f,
	-5.2f,0.9f,5.1f,
	-5.2f,3.1f,2.9f,
	-5.2f,3.1f,5.1f,
	-2.8f,3.1f,2.9f,
	-2.8f,0.9f,2.9f,
	-2.8f,0.9f,5.1f,
	-2.8f,0.9f,5.1f,
	-2.8f,3.1f,2.9f,
	-2.8f,3.1f,5.1f
};

void matCopy3d(double *dest, double *src){
  memcpy(dest, src, sizeof(double) * 9);
}

void COPYvecCopy3d(double *dest, double *src){
  int i;
  for(i = 0; i < 3; i++){
    dest[i] = src[i];
  }
}

void rayEval3d(double *p, ray3d *r, double t){
  int i;
  for(i = 0; i < 3; i++){
    p[i] = r->o[i] + (t * r->d[i]); 
  }
}

double vecDot3d(double *a, double *b){
  double accumulate = 0.0;
  int i;
  for(i = 0; i < 3; i++){
    accumulate += a[i] * b[i];
  }
  return( accumulate );
}

void COPYvecCross3d(double *n, double *u, double *v){
  n[0] = u[1] * v[2] - u[2] * v[1];
  n[1] = u[2] * v[0] - u[0] * v[2];
  n[2] = u[0] * v[1] - u[1] * v[0]; 
}

void COPYvecDifference3d(double *c, double *a, double *b){
  int i;
  for(i = 0; i < 3; i++){
    c[i] = a[i] - b[i];
  }
}

void matMultVec3d(double* vout, double* v, double* m){
  double c[3];
  COPYvecCopy3d(c, v);
  vout[0] = m[0] * c[0] + m[3] * c[1] + m[6] * c[2];
  vout[1] = m[1] * c[0] + m[4] * c[1] + m[7] * c[2];  
  vout[2] = m[2] * c[0] + m[5] * c[1] + m[8] * c[2];  
}

bool rayTriangleIntersectiond(hitd *h, ray3d *r, triangle3d *t){
  // Real Time Rendering p.581
  double e1[3], e2[3];
  double p[3], s[3], q[3];
  double a, f, u, v, _t;
  COPYvecDifference3d(e1, t->b, t->a);
  COPYvecDifference3d(e2, t->c, t->a);
  COPYvecCross3d(p, r->d, e2);
  a = vecDot3d(e1, p);
  if(FP_EQUAL(a, 0.0, FP_DP_EPSILON)){
    //puts("first");
    return(false);
  }
  f = 1.0/a;
  COPYvecDifference3d(s, r->o, t->a);
  u = vecDot3d(s, p) * f;
  if(u < 0 || u > 1){
    //fprintf(stderr, "second, %.10f\n", u);
    return(false);
  }
  COPYvecCross3d(q, s, e1);
  v = vecDot3d(r->d, q) * f;
  if(v < 0 || (u+v) > 1){
    //fprintf(stderr, "third %.7f %.7f %.7f\n", u, v, u+v);
    return(false);
  }
  _t = vecDot3d(e2, q) * f;
  h->t = _t;
  rayEval3d(h->point, r, _t);
  return(true);  
}

void msglPrintMatrix16dv( char *varName, double matrix[16] ){
  int i = 0;
  if( varName != NULL ){
    fprintf( stderr, "%s = [\n", varName );
  }
  for( i = 0; i < 4; i++ ){
    fprintf( stderr, "%.5f %.5f %.5f %.5f\n", matrix[i + 0], matrix[i + 4],
    matrix[i + 8], matrix[i + 12] );
  }
  if( varName != NULL ){
    fprintf( stderr, " ]\n" );
  }
}

void printTopOfBothStacks( char *msg ){
  double m[16];
  //msglError( );
  if( msg != NULL ){
    fprintf( stderr, "%s\n", msg );
  }
  fprintf( stderr, "Top of Projection Stack:\n" );
  glGetDoublev( GL_PROJECTION_MATRIX, m );
  msglPrintMatrix16dv( "proj", m );
  fprintf( stderr, "\n\n" );
  glGetDoublev( GL_MODELVIEW_MATRIX, m );
  msglPrintMatrix16dv( "mv", m );
  //msglError( );
}

bool intersectionDemo(double* frontPlane, double* backPlane){
  ray3d r;
  double t;
  hitd h;
  triangle3d tri;
  int intersecting;
  
  intersecting = 0;

	for(int i=0;i<36;i=i+3)
	{
		tri.a[0] = pentbox[i][0];
		tri.a[1] = pentbox[i][1];
		tri.a[2] = pentbox[i][2];
  
		tri.b[0] = pentbox[i+1][0];
		tri.b[1] = pentbox[i+1][1];
		tri.b[2] = pentbox[i+1][2];
  
		tri.c[0] = pentbox[i+2][0];
		tri.c[1] = pentbox[i+2][1];
		tri.c[2] = pentbox[i+2][2];

		/*matMultVec3d(tri.a, tri.a, modelMatrix);
	  matMultVec3d(tri.b, tri.b, modelMatrix);
	  matMultVec3d(tri.c, tri.c, modelMatrix);*/
  
	  r.o[0] = frontPlane[0];
	  r.o[1] = frontPlane[1];
	  r.o[2] = frontPlane[2];
	  r.d[0] = backPlane[0] - frontPlane[0];
	  r.d[1] = backPlane[1] - frontPlane[1];
	  r.d[2] = backPlane[2] - frontPlane[2];
	  bool rv = rayTriangleIntersectiond(&h, &r, &tri);
	  if (rv)
	  {
		  intersecting = 1;
		  break;
	  }
	}
	if(intersecting != 1)
	{
	for(int i=0;i<36;i=i+3)
	{
		tri.a[0] = pyrbox[i][0];
		tri.a[1] = pyrbox[i][1];
		tri.a[2] = pyrbox[i][2];
  
		tri.b[0] = pyrbox[i+1][0];
		tri.b[1] = pyrbox[i+1][1];
		tri.b[2] = pyrbox[i+1][2];
  
		tri.c[0] = pyrbox[i+2][0];
		tri.c[1] = pyrbox[i+2][1];
		tri.c[2] = pyrbox[i+2][2];

		/*matMultVec3d(tri.a, tri.a, modelMatrix);
	  matMultVec3d(tri.b, tri.b, modelMatrix);
	  matMultVec3d(tri.c, tri.c, modelMatrix);*/
  
	  r.o[0] = frontPlane[0];
	  r.o[1] = frontPlane[1];
	  r.o[2] = frontPlane[2];
	  r.d[0] = backPlane[0] - frontPlane[0];
	  r.d[1] = backPlane[1] - frontPlane[1];
	  r.d[2] = backPlane[2] - frontPlane[2];
	  bool rv = rayTriangleIntersectiond(&h, &r, &tri);
	  if (rv)
	  {
		  intersecting = 2;
		  break;
	  }
	}
	}
	if((intersecting != 1)||(intersecting != 2))
	{
	for(int i=0;i<36;i=i+3)
	{
		tri.a[0] = cubebox[i][0];
		tri.a[1] = cubebox[i][1];
		tri.a[2] = cubebox[i][2];
  
		tri.b[0] = cubebox[i+1][0];
		tri.b[1] = cubebox[i+1][1];
		tri.b[2] = cubebox[i+1][2];
  
		tri.c[0] = cubebox[i+2][0];
		tri.c[1] = cubebox[i+2][1];
		tri.c[2] = cubebox[i+2][2];

		/*matMultVec3d(tri.a, tri.a, modelMatrix);
	  matMultVec3d(tri.b, tri.b, modelMatrix);
	  matMultVec3d(tri.c, tri.c, modelMatrix);*/
  
	  r.o[0] = frontPlane[0];
	  r.o[1] = frontPlane[1];
	  r.o[2] = frontPlane[2];
	  r.d[0] = backPlane[0] - frontPlane[0];
	  r.d[1] = backPlane[1] - frontPlane[1];
	  r.d[2] = backPlane[2] - frontPlane[2];
	  bool rv = rayTriangleIntersectiond(&h, &r, &tri);
	  if (rv)
	  {
		  intersecting = 3;
		  break;
	  }
	}
	}
  if(intersecting == 1){
    fprintf(stderr, "Intersection! %.5f\n", h.t);
	changecol = 1;
  }
  else if (intersecting == 2){
	  fprintf(stderr, "Intersection! %.5f\n", h.t);
	  changecol = 2;
  }
  else if (intersecting == 3){
	  fprintf(stderr, "Intersection! %.5f\n", h.t);
	  changecol = 3;
  }
  else{
    fprintf(stderr, "bummer no intersection.");
	changecol = 0;
  }
  return(intersecting);
}

int pick( int x, int y ){
  GLint viewport[4];
  GLdouble modelMatrix[16];
  GLdouble projMatrix[16];
  GLint wx = x;
  GLint wy;
  GLdouble xx, yy, zz;
  
  //printTopOfBothStacks("foo");
  fprintf( stderr, "--Starting Pick--\nmouse reports (%d, %d)\n", x, y );

  glGetDoublev( GL_PROJECTION_MATRIX, projMatrix );
  glGetDoublev( GL_MODELVIEW_MATRIX, modelMatrix );
  glGetIntegerv( GL_VIEWPORT, viewport );

  wy = viewport[3] - y - 1;
  fprintf( stderr, "real y = viewport[3] - y - 1\n%d = %d - %d - 1\n",
    wy, viewport[3], y );
  fprintf( stderr, "Coordinates at cursor are (%d, %d)\n", wx, wy );

  // origin at the lower left corner
  
  // Read the depth value for wx, wy; store in zz
  glReadPixels( wx, wy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zz );
  fprintf( stderr, "zz: %g\n", zz );

  // unproject wx, wy, zz; store in xx, yy, zz
  gluUnProject( double(wx), double(wy), zz, modelMatrix, projMatrix,
    viewport, &xx, &yy, &zz );
  fprintf( stderr, "pick at pixel wz: %g %g %g\n", xx, yy, zz );

  // unproject wx, wy, the near plane (z = 0); store in xx, yy, zz
  gluUnProject( double(wx), double(wy), 0.0, modelMatrix, projMatrix,
    viewport, &xx, &yy, &zz );
  fprintf( stderr, "pick at near plane: %g %g %g\n", xx, yy, zz );

  double nearz[3];
  nearz[0] = xx;
  nearz[1] = yy;
  nearz[2] = zz;

  // unproject wx, wy, the far plane (z = 1); store in xx, yy, zz
  gluUnProject( double(wx), double(wy), 1.0, modelMatrix, projMatrix,
    viewport, &xx, &yy, &zz );
  fprintf( stderr, "pick at far plane: %g %g %g\n", xx, yy, zz );
  
  double farz[3];
  farz[0] = xx;
  farz[1] = yy;
  farz[2] = zz;

  fprintf(stderr, "--Ending Pick--\n");
  
  if(intersectionDemo(nearz, farz)){
    fprintf(stderr, "There was an intersection!\n");
	return changecol;
  }else{
    fprintf(stderr, "You missed!.\n");
	return 0;
  }
}