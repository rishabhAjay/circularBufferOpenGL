#include <GL/glut.h>
#include<iostream>
#include<string> 
#include<cstring>
#include<math.h>
#include <cstdlib>
using namespace std;

void reshape(int, int);
void display();

struct elem
{
	char c[20];

};

elem cqueue[20];
int front = 0, rear = 0, n = 5;

bool init() {
	glClearColor(0.8, 0.8, 0.8, 1.0); //set the color of the screen
	glViewport(0, 0, 500, 500); //Setting the viewport i.e. where the primitive should be displayed
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 800, -100, 100); //Set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLenum error = glGetError(); //Check for the error

	if (error != GL_NO_ERROR) //If error is there
	{
		return false; //return error has been detected
	}

	return true; //return everything is fine continue
	
}

void drawBitmap(const char* string, float x, float y)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	
	for (int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void insert() {
	if (front == 0 && rear == 0)
	{
		cout << "\nEnter the Element: ";
		cin >> cqueue[1].c;
		rear = 1;
		front = 1;
	}
	else
	{
		int next = (rear % n) + 1;
		if (next == front)
		{
			
			drawBitmap("QUEUE FULL", 300, 450);
			glutSwapBuffers();
			Sleep(2000);
			
		}
		else
		{
			cout << "\nEnter the Element: ";
			cin >> cqueue[next].c;
			rear = next;
		}
		display();
	}		
}

void delete1() {
	if (rear == 0 && front == 0)
	{
		drawBitmap("1. Enter i or I to Push", 300, 650);
		drawBitmap("2. Enter d or D to Pop", 300, 610);
		drawBitmap("3. Enter q or Q to Quit", 300, 570);
		drawBitmap("QUEUE EMPTY", 300, 450);
		glutSwapBuffers();
		Sleep(1000);
	}
	if (rear == front)
	{
		rear = 0;
		front = 0;
	}
	else
	{
		front = (front % n) + 1;
	}
}

void display() {
	drawBitmap("1. Enter i or I to Push", 300, 650);
	drawBitmap("2. Enter d or D to Pop", 300, 610);
	drawBitmap("3. Enter q or Q to Quit", 300, 570);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //reset any matrix transformations
	//clear the frame buffer first
	//frame buffer refers to the pixels on the window			
	for (int i = 0; i < 500; i += 100) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 0.5, 0.5);
		glBegin(GL_POLYGON);
			glVertex2f(200 + i, 200);
			glVertex2f(200 + i, 300);
			glVertex2f(300 + i, 300);
			glVertex2f(300 + i, 200);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3f(1,1,1);
		glVertex2f(200 + i, 200);
		glColor3f(1, 1, 1);
		glVertex2f(200 + i, 300);
		glColor3f(1, 1, 1);
		glVertex2f(300 + i, 300);
		glColor3f(1, 1, 1);
		glVertex2f(300 + i, 200);
		glColor3f(1, 1, 1);
		glEnd();
	}
		glBegin(GL_LINES);
			glColor3f(0, 0, 0);
			glVertex2f(650, 200);
			glColor3f(0, 0, 0);
			glVertex2f(650, 150);
			glColor3f(0, 0, 0);
			glVertex2f(650, 150);
			glColor3f(0, 0, 0);
			glVertex2f(250, 150);
			glColor3f(0, 0, 0);
			glVertex2f(250, 150);
			glColor3f(0, 0, 0);
			glVertex2f(250, 200);
			glColor3f(0, 0, 0);
		glEnd();
		glColor3f(0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		glBegin(GL_POLYGON);
		
			glVertex2f(225, 175);
			glVertex2f(250, 200);
			glVertex2f(275, 175);
		glEnd();

		if (front != 0 && rear != 0)
		{
			
			int i = front;
			glColor3f(1, 1, 1);
			glRasterPos2f(140 + ((i) * 100), (250));

			for (int j = 0; j < strlen(cqueue[i].c); j++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cqueue[i].c[j]);
				while (i != rear)
				{
					i = (i % n) + 1;
					glColor3f(1, 1, 1);
					glRasterPos2f(140 + (i * 100), (250));

					for (int j = 0; j < strlen(cqueue[i].c); j++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cqueue[i].c[j]);
				}

		}
		else
		{
			
			drawBitmap("QUEUE EMPTY", 300, 450);
			glutSwapBuffers();
			Sleep(1000);
		}
	glutSwapBuffers(); //display the updated frame buffer(the pixels)
}

void render() //display function 
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	if (front == 0)
	{
		drawBitmap("1. Enter i or I to Push", 300, 650);
		drawBitmap("2. Enter d or D to Pop", 300, 610);
		drawBitmap("3. Enter q or Q to Quit", 300,570);
		drawBitmap("QUEUE EMPTY", 300, 450);
		glFlush();
		glutSwapBuffers();
		Sleep(1000);
	}
	else {
		glFlush();
		display();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i' | 'I': insert(); render();
		break;

	case 'd' | 'D':  delete1(); render();
		break;
	case 'q' | 'Q': exit(0);
	}
}

void reshape(int w, int h) {
	//By specifying (0,0) and (w,h) you make the whole window as the viewport when maximized or minimized
	glMatrixMode(GL_PROJECTION); //change to projection matrix to make the projections
	glLoadIdentity(); //reset any matrix transformations
	glViewport(0, 0, w, h); //takes 4 parameters. (x,y) coordinates of the start point and the end point
	glOrtho(0, 900, 0, 900, -100, 100); //specify the coordinate limits (check the screenshot)
	glMatrixMode(GL_MODELVIEW); //change back to MODEL view because it is important
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //initialise glut (boilerplate)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(500, 100); //Where will the window pop up on screen?(coordinates)
	glutInitWindowSize(500, 500); //width and height in pixels
	glutCreateWindow("Circular Buffer"); //THis will actully create the window with the name
	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render); //Display callback function
	glutReshapeFunc(reshape); //when window is maximized or minimized
	glutMainLoop(); //keeps the program on loop and terminates when we say so
	return 0;
}

