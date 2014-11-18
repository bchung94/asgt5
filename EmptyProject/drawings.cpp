#include "drawings.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void drawground()
{
	glBegin(GL_TRIANGLES);

	glColor3f(0.0,0.1,0.8);

	glVertex3f(50.0,-2.0,50.0);
	glVertex3f(-50.0,-2.0,50.0);
	glVertex3f(50.0,-2.0,-50.0);

	glVertex3f(-50.0,-2.0,-50.0);
	glVertex3f(-50.0,-2.0,50.0);
	glVertex3f(50.0,-2.0,-50.0);

	glEnd();

}

void drawskybox()
{
	glBegin(GL_TRIANGLES);

	glColor3f(0.6,0.1,0.1);

	//front
	glVertex3f(0.0f, 15.0f,15.0f);
    glVertex3f(15.0f,15.0f, 0.0f);
    glVertex3f(15.0f,-15.0f, 0.0f);

	glVertex3f(0.0f,15.0f, 15.0f);
    glVertex3f(0.0f,-15.0f, 15.0f);
	glVertex3f(15.0f,-15.0f, 0.0f);

	//back
	glVertex3f(0.0f, 15.0f,-15.0f);
    glVertex3f(-15.0f,15.0f, 0.0f);
    glVertex3f(-15.0f,-15.0f, 0.0f);

	glVertex3f(0.0f,15.0f, -15.0f);
    glVertex3f(0.0f,-15.0f, -15.0f);
	glVertex3f(-15.0f,-15.0f, 0.0f);
	
	//top
	glVertex3f(15.0f, 15.0f,0.0f);
    glVertex3f(-15.0f,15.0f, 0.0f);
    glVertex3f(0.0f,15.0f, 15.0f);

	glVertex3f(-15.0f,15.0f, 0.0f);
    glVertex3f(0.0f,15.0f, 15.0f);
	glVertex3f(0.0f,15.0f, -15.0f);

	//bottom
	glVertex3f(15.0f, -15.0f,0.0f);
    glVertex3f(-15.0f,-15.0f, 0.0f);
    glVertex3f(0.0f,-15.0f, 15.0f);

	glVertex3f(-15.0f,-15.0f, 0.0f);
    glVertex3f(0.0f,-15.0f, 15.0f);
	glVertex3f(0.0f,-15.0f, -15.0f);

	//side1
	glVertex3f(0.0f, 15.0f, 15.0f);
    glVertex3f(0.0f,-15.0f, 15.0f);
    glVertex3f(-15.0f,-15.0f, 0.0f);

	glVertex3f(-15.0f,-15.0f, 0.0f);
    glVertex3f(-15.0f,15.0f, 0.0f);
	glVertex3f(0.0f,15.0f, 15.0f);
	
	//side2
	glVertex3f(0.0f, 15.0f, -15.0f);
    glVertex3f(0.0f,-15.0f, -15.0f);
    glVertex3f(15.0f,-15.0f, 0.0f);

	glVertex3f(15.0f,-15.0f, 0.0f);
    glVertex3f(15.0f,15.0f, 0.0f);
	glVertex3f(0.0f,15.0f, -15.0f);

	glEnd();
}

void drawcube()
{
	glPushMatrix();
	glTranslatef(4.0,0.0,5.0);
	glRotatef(float(glfwGetTime( )) * 10.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(float(glfwGetTime( )) * 15.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-4.0,0.0,-5.0);

	//cube
	glBegin(GL_TRIANGLES);
	
	//front
	glVertex3f(5.0f, 1.0f,4.0f);
    glVertex3f(5.0f,-1.0f, 4.0f);
    glVertex3f(3.0f,1.0f, 4.0f);

	glVertex3f(5.0f,-1.0f, 4.0f);
    glVertex3f(3.0f,1.0f, 4.0f);
	glVertex3f(3.0f,-1.0f, 4.0f);

	//back
	glVertex3f(5.0f, 1.0f,6.0f);
    glVertex3f(5.0f,-1.0f, 6.0f);
    glVertex3f(3.0f,1.0f, 6.0f);

	glVertex3f(5.0f,-1.0f, 6.0f);
    glVertex3f(3.0f,1.0f, 6.0f);
	glVertex3f(3.0f,-1.0f, 6.0f);
	
	//top
	glVertex3f(5.0f, 1.0f,4.0f);
    glVertex3f(5.0f,1.0f, 6.0f);
    glVertex3f(3.0f,1.0f, 4.0f);

	glVertex3f(5.0f,1.0f, 6.0f);
    glVertex3f(3.0f,1.0f, 4.0f);
	glVertex3f(3.0f,1.0f, 6.0f);

	//bottom
	glVertex3f(5.0f, -1.0f, 4.0f);
    glVertex3f(5.0f,-1.0f, 6.0f);
    glVertex3f(3.0f,-1.0f, 4.0f);

	glVertex3f(5.0f,-1.0f, 6.0f);
    glVertex3f(3.0f,-1.0f, 4.0f);
	glVertex3f(3.0f,-1.0f, 6.0f);

	//side1
	glVertex3f(5.0f, 1.0f, 4.0f);
    glVertex3f(5.0f,-1.0f, 4.0f);
    glVertex3f(5.0f,1.0f, 6.0f);

	glVertex3f(5.0f,1.0f, 6.0f);
    glVertex3f(5.0f,-1.0f, 6.0f);
	glVertex3f(5.0f,-1.0f, 4.0f);
	
	//side2
	glVertex3f(3.0f, 1.0f, 4.0f);
    glVertex3f(3.0f,-1.0f, 4.0f);
    glVertex3f(3.0f,1.0f, 6.0f);

	glVertex3f(3.0f,1.0f, 6.0f);
    glVertex3f(3.0f,-1.0f, 6.0f);
	glVertex3f(3.0f,-1.0f, 4.0f);

	glEnd();
	glPopMatrix();
}

void cubeBB()
{
	glPushMatrix();
	glTranslatef(4.0,0.0,5.0);
	glRotatef(float(glfwGetTime( )) * 10.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(float(glfwGetTime( )) * 15.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-4.0,0.0,-5.0);

	glBegin(GL_LINES);
	glVertex3f(5.1f,1.1f,6.1f);
	glVertex3f(5.1f,-1.1f,6.1f);
	glVertex3f(5.1f,1.1f,6.1f);
	glVertex3f(2.9f,1.1f,6.1f);
	glVertex3f(2.9f,1.1f,6.1f);
	glVertex3f(2.9f,-1.1f,6.1f);
	glVertex3f(2.9f,-1.1f,6.1f);
	glVertex3f(5.1f,-1.1f,6.1f);

	glVertex3f(5.1f,1.1f,3.9f);
	glVertex3f(5.1f,-1.1f,3.9f);
	glVertex3f(5.1f,1.1f,3.9f);
	glVertex3f(2.9f,1.1f,3.9f);
	glVertex3f(2.9f,1.1f,3.9f);
	glVertex3f(2.9f,-1.1f,3.9f);
	glVertex3f(2.9f,-1.1f,3.9f);
	glVertex3f(5.1f,-1.1f,3.9f);

	glVertex3f(2.9f,1.1f,6.1f);
	glVertex3f(2.9f,1.1f,3.9f);
	glVertex3f(2.9f,-1.1f,6.1f);
	glVertex3f(2.9f,-1.1f,3.9f);
	glVertex3f(5.1f,1.1f,6.1f);
	glVertex3f(5.1f,1.1f,3.9f);
	glVertex3f(5.1f,-1.1f,6.1f);
	glVertex3f(5.1f,-1.1f,3.9f);
	glEnd();
	glPopMatrix();
}

void pyrBB()
{
	glBegin(GL_LINES);
	glVertex3f(-1.0f,1.2f,4.1f);
	glVertex3f(1.0f,1.2f,4.1f);
	glVertex3f(1.0f,1.2f,4.1f);
	glVertex3f(1.0f,-1.2f,4.1f);
	glVertex3f(1.0f,-1.2f,4.1f);
	glVertex3f(-1.0f,-1.2f,4.1f);
	glVertex3f(-1.0f,-1.2f,4.1f);
	glVertex3f(-1.0f,1.2f,4.1f);

	glVertex3f(-1.0f,1.2f,1.9f);
	glVertex3f(1.0f,1.2f,1.9f);
	glVertex3f(1.0f,1.2f,1.9f);
	glVertex3f(1.0f,-1.2f,1.9f);
	glVertex3f(1.0f,-1.2f,1.9f);
	glVertex3f(-1.0f,-1.2f,1.9f);
	glVertex3f(-1.0f,-1.2f,1.9f);
	glVertex3f(-1.0f,1.2f,1.9f);

	glVertex3f(-1.0f,1.2f,4.1f);
	glVertex3f(-1.0f,1.2f,1.9f);
	glVertex3f(1.0f,1.2f,1.9f);
	glVertex3f(1.0f,1.2f,4.1f);
	glVertex3f(1.0f,-1.2f,1.9f);
	glVertex3f(1.0f,-1.2f,4.1f);
	glVertex3f(-1.0f,-1.2f,1.9f);
	glVertex3f(-1.0f,-1.2f,4.1f);

	glEnd();
}

void pentBB()
{
	glBegin(GL_LINES);
	glVertex3f(-5.2f,3.1f,5.1f);
	glVertex3f(-2.8f,3.1f,5.1f);
	glVertex3f(-2.8f,3.1f,5.1f);
	glVertex3f(-2.8f,0.9f,5.1f);
	glVertex3f(-2.8f,0.9f,5.1f);
	glVertex3f(-5.2f,0.9f,5.1f);
	glVertex3f(-5.2f,0.9f,5.1f);
	glVertex3f(-5.2f,3.1f,5.1f);

	glVertex3f(-5.2f,3.1f,2.9f);
	glVertex3f(-2.8f,3.1f,2.9f);
	glVertex3f(-2.8f,3.1f,2.9f);
	glVertex3f(-2.8f,0.9f,2.9f);
	glVertex3f(-2.8f,0.9f,2.9f);
	glVertex3f(-5.2f,0.9f,2.9f);
	glVertex3f(-5.2f,0.9f,2.9f);
	glVertex3f(-5.2f,3.1f,2.9f);

	glVertex3f(-5.2f,3.1f,5.1f);
	glVertex3f(-5.2f,3.1f,2.9f);
	glVertex3f(-2.8f,3.1f,2.9f);
	glVertex3f(-2.8f,3.1f,5.1f);
	glVertex3f(-2.8f,0.9f,2.9f);
	glVertex3f(-2.8f,0.9f,5.1f);
	glVertex3f(-5.2f,0.9f,2.9f);
	glVertex3f(-5.2f,0.9f,5.1f);
	glEnd();
}
