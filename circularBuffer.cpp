#include <GL/glut.h>
#include<iostream>
using namespace std;

void reshape(int, int);
void display();

struct elem
{
	char c;
};

elem cqueue[5];

int front = 0, rear = 0, n = 5;
char val;
void init() {
	glClearColor(0.8, 0.8, 0.8, 1.0); //set the color of the screen
}

void drawBitmap(void* font, const char* string, float x, float y)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	
	for (int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

void frontAndRear(int f, int r) {
	glFlush();
	drawBitmap(GLUT_BITMAP_HELVETICA_18 ,"F", 130 + f*100, 400);
	glLineWidth(3);
	glBegin(GL_LINES);
		glVertex2f(135 + f * 100, 390);
		glVertex2f(135 + f * 100, 320);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
		glVertex2f(120+ f * 100, 340);
		glVertex2f(135+ f * 100, 320);
		glVertex2f(150+ f * 100, 340);
	glEnd();
	drawBitmap(GLUT_BITMAP_HELVETICA_18, "R", 148 + r*100, 400);
	glLineWidth(3);
	glBegin(GL_LINES);
		glVertex2f(155 + r * 100, 390);
		glVertex2f(155 + r * 100, 320);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
		glVertex2f(140 + r * 100, 340);
		glVertex2f(155 + r * 100, 320);
		glVertex2f(170 + r * 100, 340);
	glEnd();
}

void insert() {
	string value;
	if (front == 0 && rear == 0)
	{
		cout << "\nEnter single character Element: ";
		cin >> value;
		while (value.length() != 1) {
			cout << "\nERROR: Enter single character Element: ";
			cin >> value;
		}
		val = value[0];
		cqueue[1].c = val;
		rear = 1;
		front = 1;
	}
	else
	{
		int next = (rear % n) + 1;
		if (next == front)
		{
			drawBitmap(GLUT_BITMAP_TIMES_ROMAN_24,"QUEUE OVERFLOW", 250, 470);
			glutSwapBuffers();
			Sleep(2000);
			
		}
		else
		{
			cout << "\nEnter single character Element: ";
			cin >> value;
			while (value.length() != 1) {
				cout << "\nERROR: Enter single character Element: ";
				cin >> value;
			}
			val = value[0];
			cqueue[next].c = val;
			rear = next;

		}
		
		display();
	}		
}

void delete1() {
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
	drawBitmap(GLUT_BITMAP_HELVETICA_18, "1. Enter i to Push", 325, 650);
	drawBitmap(GLUT_BITMAP_HELVETICA_18, "2. Enter d to Pop", 325, 610);
	drawBitmap(GLUT_BITMAP_HELVETICA_18, "3. Enter q to Quit", 325, 570);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //reset any matrix transformations
	//clear the frame buffer first
	//frame buffer refers to the pixels on the window			
	for (int i = 0; i < n * 100; i += 100) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 0.5, 0.5);

		glBegin(GL_POLYGON);
		glVertex2f(200 + i, 200);
		glVertex2f(200 + i, 300);
		glVertex2f(300 + i, 300);
		glVertex2f(300 + i, 200);
		glEnd();
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
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
	glLineWidth(2);
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
	frontAndRear(front, rear);
	if (front != 0 && rear != 0)
	{

		int i = front;
		glColor3f(1, 1, 1);
		glRasterPos2f(135 + ((i) * 100), (250));

			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cqueue[i].c);
		while (i != rear)
		{
			i = (i % n) + 1;
			glColor3f(1, 1, 1);
			glRasterPos2f(135 + (i * 100), (250));

				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cqueue[i].c);
		}
	}
	glutSwapBuffers(); //display the updated frame buffer(the pixels)

}


void render() //display function 
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	
	if (front == 0 && rear == 0)
	{
		drawBitmap(GLUT_BITMAP_HELVETICA_18, "1. Enter i to Push", 325, 650);
		drawBitmap(GLUT_BITMAP_HELVETICA_18, "2. Enter d to Pop", 325, 610);
		drawBitmap(GLUT_BITMAP_HELVETICA_18, "3. Enter q to Quit", 325,570);
		drawBitmap(GLUT_BITMAP_TIMES_ROMAN_24,"QUEUE UNDERFLOW", 250, 470);
		glutSwapBuffers();
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
	case 'i' : insert(); render();
		break;
	case 'd' :  delete1();  render();
		break;
	case 'q' : exit(0);
	}
}

void reshape(int w, int h) {
	//By specifying (0,0) and (w,h) you make the whole window as the viewport when maximized or minimized
	glMatrixMode(GL_PROJECTION); //change to projection matrix to make the projections
	glLoadIdentity(); //reset any matrix transformations
	glViewport(0, 0, w, h); //takes 4 parameters. (x,y) coordinates of the start point and the end point
	glOrtho(0, 900, 0, 900, -100, 100); //specify the coordinate limits
	glMatrixMode(GL_MODELVIEW); //change back to MODEL view because it is important
	glLoadIdentity(); //load the matrix changes 
}

int main(int argc, char** argv) {

	glutInit(&argc, argv); //initialise glut (boilerplate)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(1000, 100); //Where will the window pop up on screen?(coordinates)
	glutInitWindowSize(500, 500); //width and height in pixels
	glutCreateWindow("Circular Buffer"); //THis will actully create the window with the name
	init(); //check for the error
	glutKeyboardFunc(keyboard); //keyboard event callback
	glutDisplayFunc(render); //Display callback function
	glutReshapeFunc(reshape); //when window is maximized or minimized
	glutMainLoop(); //keeps the program on loop and terminates when we say so
	return 0;
}

