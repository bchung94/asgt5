// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// A really simple GLFW3 demo that renders an animated and
// colored tetrahedron which the edges outlined in black.
//
// $Id: hello_glfw.cpp 4758 2014-01-23 07:42:39Z mshafae $
//

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#pragma comment(lib,"glu32.lib")
#define msglError( ) _msglError( stderr, __FILE__, __LINE__ )

#include "Shader.h"
#include "ply.h"
#include "drawings.h"
#include "transformation.h"
#include "picker.h"

const GLdouble PI = 3.14159265;
double xpos, ypos;
FaceList *pentModel;
FaceList *pyrModel;
GLSLProgram *prog;
float checker[18][3];
float checker2[48][3];
int marker;
int colorer = 0;
float angle = 0.0f;
float deltaAngle = 0.0f;
float lx = 0.0f;
float ly = 0.0f;
int xOrigin = -1;
int yOrigin = -1;
int shift_down = 0;

unsigned int uIsLightOn; 
unsigned int uLight0_position;
unsigned int uLight0_color;
unsigned int uLight1_position;
unsigned int uLight1_color;
unsigned int uLight2_position;
unsigned int uLight2_color;
unsigned int uAmbient;
unsigned int uDiffuse;
unsigned int uSpecular;
unsigned int uShininess;

float light0_position[] = {0,1,-9,1};
float light1_position[] = {0,5,-14,1};
float light2_position[] = {0,1,-5,1};
const float light0_specular[] = {0,0.1,0.9,1};
const float light1_specular[] = {0.7,0.5,0.4,1};
const float light2_specular[] = {0.9,0.7,0.7,1};
// specular on teapot
const float one[] = {1,1,1,1};
// diffuse on teapot
const float medium[] = {0.5,0.5,0.5,1};
// ambient on teapot
const float small[] = {0.2,0.2,0.2,1};
// shininess of teapot
const float high[] = {100};

// lights
float light0[4];
float light1[4];
float light2[4];

// arcball
glm::vec3 arc;
glm::vec3 va, vb;


void msglVersion(void){  
  fprintf(stderr, "Vendor: %s\n", glGetString(GL_VENDOR));
  fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stderr, "OpenGL Version: %s\n", glGetString(GL_VERSION));
  fprintf(stderr, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}



static void errorCallback(int error, const char* description){
  fprintf(stderr, "GLFW Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if( action == GLFW_PRESS ){
    switch( key ){
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
      break;
	  case GLFW_KEY_Q:
        glfwSetWindowShouldClose(window, GL_TRUE);
      break;
	  case GLFW_KEY_LEFT_SHIFT:
		  break;
	  case GLFW_KEY_RIGHT_SHIFT:
		  break;
	  case GLFW_KEY_B:
		  if (marker == 0)
			  marker = 1;
		  else
			  marker = 0;
		  break;
      default:
        fprintf(stderr, "Key pressed: %c:%d\n", key, key);
      break;
    }
  }
  if (action == GLFW_REPEAT) {
	  switch(key) {
	  case GLFW_KEY_LEFT_SHIFT:
		  shift_down = 1;
		  break;
	  case GLFW_KEY_RIGHT_SHIFT:
		  shift_down = 1;
		  break;
	  default:
			break;
	  }
  }
  if (action == GLFW_RELEASE) {
	  switch(key) {
	  case GLFW_KEY_LEFT_SHIFT:
		  shift_down = 0;
		  break;
	  case GLFW_KEY_RIGHT_SHIFT:
		  shift_down = 0;
		  break;
	  default:
			break;
	  }
  }
}

void vset(float *pos,float posx,float posy, float posz)
{
	pos[0] = posx;
	pos[1] = posy;
	pos[2] = posz;
}

void vcross(float *n, float *u, float *v){
  n[0] = u[1] * v[2] - u[2] * v[1];
  n[1] = u[2] * v[0] - u[0] * v[2];
  n[2] = u[0] * v[1] - u[1] * v[0]; 
}

void vsub(float *result, float *p1, float *p2)
{
	result[0] = p2[0] - p1[0];
	result[1] = p2[1] - p1[1];
	result[2] = p2[2] - p1[2];
}

float vlength(float *length)
{
	float g;
	g = sqrt(length[0] * length[0] + length[1] * length[1] + length[2] * length[2]);

	return g;
}

float sphereproject(float r, float x, float y)
{
	float d,t,z;
	d = sqrt(x*x + y*y);
	if (d < r * 0.7071017) // M_SQRTH (1/ sqrt of 2)
	{
		z = sqrt(r*r - d*d);
	}
	else {
		t = r/1.414213582; // M_SQRTTWO sqrt of 2
		z = t*t /d;
	}
	return z;
}

void arcball(int x, int y) {

	arc.x = 1.0*x/1000 - 1.0;
	arc.y = 1.0*y/1000 - 1.0;
	arc.z = 0;

	arc.y = -arc.y;

	float OP = arc.x * arc.x + arc.y * arc.y;
	if (OP <= 1)
	{
		arc.z = sqrt(1 - OP);
	}
	else
	{
		arc = glm::normalize(arc);
	}
}

static void mouse( GLFWwindow* window, int button, int state, int mods ){
  switch( state ){
	  case GLFW_PRESS:
	  if (shift_down) 
	  {
		switch(button){
			case GLFW_MOUSE_BUTTON_LEFT:
			case GLFW_MOUSE_BUTTON_MIDDLE:
			case GLFW_MOUSE_BUTTON_RIGHT:
				glfwGetCursorPos(window, &xpos, &ypos);
				xOrigin = xpos;
				yOrigin = ypos;
				fprintf( stderr, "\nA mouse button is down.\n" );
				break;
			default:
				fprintf( stderr, "An unknown mouse button is down.\n" );
				break;
			  }
	  }
	  else {
			switch( button ){
				case GLFW_MOUSE_BUTTON_LEFT:
				case GLFW_MOUSE_BUTTON_MIDDLE:
				case GLFW_MOUSE_BUTTON_RIGHT:
				glfwGetCursorPos(window, &xpos, &ypos);
				colorer = pick( xpos, ypos );
				fprintf( stderr, "\nA mouse button is down.\n" );
				break;
				default:
				fprintf( stderr, "An unknown mouse button is down.\n" );
				break;
			}
			break;
	  }
	  break;
			case GLFW_REPEAT:
			switch( button ){
				case GLFW_MOUSE_BUTTON_LEFT:
				case GLFW_MOUSE_BUTTON_MIDDLE:
				case GLFW_MOUSE_BUTTON_RIGHT:
						
					break;
				default:
				break;
			}
			case GLFW_RELEASE:
			switch( button ){
				case GLFW_MOUSE_BUTTON_LEFT:
				case GLFW_MOUSE_BUTTON_MIDDLE:
				case GLFW_MOUSE_BUTTON_RIGHT:
				glfwGetCursorPos(window, &xpos, &ypos);
				
				arcball(xOrigin,yOrigin);
				va = arc;
				printf("%f %f %f \n", va.x,va.y,va.z);
				arcball(xpos,ypos);
				vb = arc;
				printf("%f %f %f \n", vb.x,vb.y,vb.z);
				if (shift_down)
				{
					angle = acos(glm::min(1.0f, glm::dot(va, vb)));

				//update camera's direction
				deltaAngle = (xpos - xOrigin) * 0.01f;
				lx = cos(angle + deltaAngle);
				deltaAngle = (ypos - yOrigin) * 0.01f;
				ly = sin(angle + deltaAngle);

				//angle += deltaAngle;

				printf("Y: %f \nyOrigin: %i \nX: %f \n",ypos, yOrigin,xpos);
				printf("xOrigin: %i \nangle: %f\ndeltaAngle: %f\nlx: %f\nly: %f\n", xOrigin,angle,deltaAngle,lx,ly);
				}
				xOrigin = -1;
				fprintf( stderr, "A mouse button is up.\n" );
				break;
				default:
				fprintf( stderr, "An unknown mouse button is down.\n" );
				break;
			}
    }
}

bool fileExists(const char *f){
  FILE *fh;
  bool rv = true;
  if( (fh = fopen(f, "r")) == NULL ){
    fprintf( stderr, "Opening file %s encountered an error.\n", f );
    rv = false;
  }else{
    fclose( fh );
  }
  return( rv );
}

void vecCopy4f(float *dest, float *src){
  int i;
  for(i = 0; i < 4; i++){
    dest[i] = src[i];
  }
}

void matMultVec4f(float* vout, float* v, float* m){
  float c[4];
  vecCopy4f(c, v);
  vout[0] = m[0] * c[0] + m[4] * c[1] + m[8]  * c[2] + m[12] * c[3];
  vout[1] = m[1] * c[0] + m[5] * c[1] + m[9]  * c[2] + m[13] * c[3];
  vout[2] = m[2] * c[0] + m[6] * c[1] + m[10] * c[2] + m[14] * c[3];
  vout[3] = m[3] * c[0] + m[7] * c[1] + m[11] * c[2] + m[15] * c[3];
}

void transformVecByModelView(float outVec[4], float inVec[4]){
  float modelview[16];
  glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
  matMultVec4f( outVec, inVec, modelview );
}

int main(void){
  marker = 0;
  GLFWwindow* window;
  glfwSetErrorCallback(errorCallback);
  if( !glfwInit( ) ){
    exit(1);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(500, 500, "Hello OpenGL and GLFW", 0, NULL);
  if( !window ){
    glfwTerminate( );
    exit(1);
  }
  glfwMakeContextCurrent(window);
  
  glewExperimental = true;
  GLenum err = glewInit( );
  if( err != GLEW_OK ){
    fprintf(stderr, "GLEW: init failed: %s\n", glewGetErrorString(err));
    exit(1);
  }
    
  glfwSetKeyCallback(window, keyCallback);
  
  glfwSetMouseButtonCallback(window, mouse);

  glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_FLAT);
  
  if( fileExists("pentagon3d.txt") ){
    pentModel = readPlyModel( "pentagon3d.txt" );
  }else{
    exit(1);
  }
  if( fileExists("pyramid3d.txt") ){
    pyrModel = readPlyModel( "pyramid3d.txt" );
  }else{
    exit(1);
  }

  GLint posAttrib;
  prog = new GLSLProgram();
  VertexShader vertexShader("vertshader.vert");
  FragmentShader fragShader("fragshader.frag");

  //attach shaders
  prog->attach(vertexShader);
  prog->attach(fragShader);

  //Link and set program
  prog->link();
  prog->activate();

  //light variables
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  uIsLightOn = glGetUniformLocation(prog->id(),
                                    "isLightOn");
  uLight0_position = glGetUniformLocation(prog->id( ),
                                          "light0_position");
  uLight0_color = glGetUniformLocation(prog->id( ),
                                       "light0_color");
  uLight1_position = glGetUniformLocation(prog->id( ),
                                          "light1_position");
  uLight1_color = glGetUniformLocation(prog->id( ),
                                       "light1_color");
  uLight2_position = glGetUniformLocation(prog->id( ),
                                          "light2_position");
  uLight2_color = glGetUniformLocation(prog->id( ),
                                       "light2_color");
  uAmbient = glGetUniformLocation(prog->id( ), "ambient");
  uDiffuse = glGetUniformLocation(prog->id( ), "diffuse");
  uSpecular = glGetUniformLocation(prog->id( ), "specular");
  uShininess = glGetUniformLocation(prog->id( ), "shininess");

  //create data checkpoint
  for(int i=0;i<18;i++)
  {
	checker[i][0] = pyrModel->vertices[i][0];
	checker[i][1] = pyrModel->vertices[i][1];
	checker[i][2] = pyrModel->vertices[i][2];
  }

  //create data checkpoint
  for(int i=0;i<48;i++)
  {
	checker2[i][0] = pentModel->vertices[i][0];
	checker2[i][1] = pentModel->vertices[i][1];
	checker2[i][2] = pentModel->vertices[i][2];
  }

  //create vertex array obj
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //create vertex array buffer
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(checker),&checker[0],GL_STATIC_DRAW);

  GLuint vbo2;
  glGenBuffers(1, &vbo2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(checker2),&checker2[0],GL_STATIC_DRAW);

	transformVecByModelView(light0, light0_position); 
	transformVecByModelView(light1, light1_position); 
	transformVecByModelView(light2, light2_position); 

	glUniform4fv(uLight0_position, 1, light0); 
	glUniform4fv(uLight0_color, 1, light0_specular); 
	glUniform4fv(uLight1_position, 1, light1); 
	glUniform4fv(uLight1_color, 1, light1_specular); 
	glUniform4fv(uLight2_position, 1, light2); 
	glUniform4fv(uLight2_color, 1, light2_specular); 

	glUniform4fv(uAmbient, 1, small); 
	glUniform4fv(uDiffuse, 1, medium); 
	glUniform4fv(uSpecular, 1, one); 
	glUniform1fv(uShininess, 1, high); 
	glUniform1i(uIsLightOn, true);

  msglVersion( );


  while( !glfwWindowShouldClose(window) ){  
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / float(height);
    glViewport(0, 0, width, height);
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	glPushMatrix();
	glTranslatef(0.0,1.0,0.0);
	//glRotatef(float(glfwGetTime( )) * 50.0f, 0.0f, 0.0f, 1.0f);
	//glRotatef(float(glfwGetTime( )) * 10.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(float(glfwGetTime( )) * 15.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0,-1.0,0.0);
	glColor3f(0.3f,0.1f,0.5f);
	if (colorer == 2)
		glColor3f(0.0f,0.0f,0.0f);
	if (marker == 1)
		pyrBB();
	glDrawArrays(GL_TRIANGLES,0,18*3);
	glDisableVertexAttribArray(0);
	glPopMatrix();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	glPushMatrix();
	glTranslatef(-4.0,2.0,4.0);
	//glRotatef(float(glfwGetTime( )) * 60.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(4.0,-2.0,-4.0);
	glColor3f(0.2f,0.6f,0.2f);
	if (colorer == 1)
		glColor3f(0.0f,0.0f,0.0f);
	if (marker == 1)
		pentBB();
	glDrawArrays(GL_TRIANGLES,0,48*3);
	glDisableVertexAttribArray(0);
	glPopMatrix();

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity( );
	glFrustum(-ratio, ratio, -ratio, ratio, 1.0f, 40.0f);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );

	//glm::vec3 camaxis = glm::cross(va, vb);
	//glRotatef(angle,camaxis.x,camaxis.y,camaxis.z);
	
    gluLookAt(0.0f, 0.0f, -2.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
    glRotatef(angle*30,0.0f,lx,0.0f);

	glColor3f(0.5f,0.7f,0.2f);
	if (colorer == 3)
		glColor3f(0.0f,0.0f,0.0f);
    drawcube( );
	if (marker == 1)
		cubeBB();
    drawground();
	drawskybox();

    glfwSwapBuffers(window);
    glfwPollEvents( );
  }

  glfwDestroyWindow(window);
  glfwTerminate( );
  return 0;
}