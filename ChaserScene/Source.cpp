#include <windows.h>
#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>


#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define FPS 30
#define PI 3.141592653
int dx = 10;//velocity
int dy = 15;
int x = 30;
int y = 50;

int winWidth = 700, winHeight = 700, counter = 0;
time_t t;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

float elapsedTime = 0, base_time = 0, fps = 0, frames;
void calcFPS() {
	elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	if ((elapsedTime - base_time) > 1000.0) {
		fps = frames * 1000.0 / (elapsedTime - base_time);
		printf("fps: %f", fps);
		base_time = elapsedTime;
		frames = 0;
	}
	frames++;
}

void r_idle() {}

void MyTimerFunc(int value);

void triangles(int x, int y, int x1, int y1, int x2, int y2)
{
	glBegin(GL_TRIANGLES);
	glVertex2i(x, y);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}


void rectangle(int x, int y, int w, int h)
{
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

void straight_lines(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

void circle(int n, int x, int y, int r) {
	//draw round head
	double inc = 2 * PI / (double)n;
	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
		glVertex2i(r * cos(theta) + x, r * sin(theta) + y);
	}
	glEnd();
}



//-----BACKGROUND SCENE--------


void backgroundRoomLight()
{
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);
	//door
	glColor3ub(170, 120, 20);
	rectangle(590, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 610, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

}

void backgroundRoomDark()
{
	glColor3ub(138, 138, 138);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(132, 93, 16);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 117);
	rectangle(20, 100, 250, 100);
	//door
	glColor3ub(146, 103, 17);
	rectangle(590, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 610, 320, 10);

	//lamp
	glColor3ub(170, 90, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(132, 93, 16);
	rectangle(100, 200, 6, 130);

	//table
	glColor3ub(85, 43, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);
	/*
	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);*/

}

void backgroundChase(int x)
{
	int m1x1, m1x2, m1x3, m2x1, m2x2, m2x3, m3x1, m3x2, m3x3 = 0;

	//background
	glColor3ub(51, 52, 77);
	rectangle(0, 100, 700, 600);

	//land
	glColor3ub(186, 122, 89);
	rectangle(0, 0, 700, 100);

	if (x == 1) {
		m1x1 = 0, m1x2 = 175, m1x3 = 350, m2x1 = 350, m2x2 = 525, m2x3 = 700,
			m3x1 = 0, m3x2 = 0, m3x3 = 0;
	}

	else if (x == 2) {
		m1x1 = 0, m1x2 = 0, m1x3 = 175, m2x1 = 175, m2x2 = 350, m2x3 = 525,
			m3x1 = 525, m3x2 = 700, m3x3 = 700;
	}

	else if (x == 3) {
		m1x1 = 0, m1x2 = 0, m1x3 = 87, m2x1 = 87, m2x2 = 262, m2x3 = 437,
			m3x1 = 437, m3x2 = 700, m3x3 = 700;
	}

	else if (x == 4) {
		m1x1 = 0, m1x2 = 0, m1x3 = 30, m2x1 = 30, m2x2 = 205, m2x3 = 380,
			m3x1 = 380, m3x2 = 700, m3x3 = 700;
	}
	else if (x == 5) {
		m1x1 = 0, m1x2 = 100, m1x3 = 275, m2x1 = 275, m2x2 = 450, m2x3 = 625,
			m3x1 = 620, m3x2 = 700, m3x3 = 700;
	}

	//sun
	glColor3ub(254, 241, 2);
	circle(30, 350, 550, 50);

	//mountain
	glColor3ub(43, 84, 44);
	triangles(m1x1, 100, m1x2, 650, m1x3, 100);

	glColor3ub(43, 84, 44);
	triangles(m2x1, 100, m2x2, 650, m2x3, 100);

	glColor3ub(43, 84, 44);
	triangles(m3x1, 100, m3x2, 650, m3x3, 100);
}

void rock(int x) {
	glColor3ub(72, 69, 63);

	glBegin(GL_POLYGON);
	glVertex2i(x, 60);
	glVertex2i(x, 70);
	glVertex2i(x + 10, 75);
	glVertex2i(x + 15, 70);
	glVertex2i(x + 20, 65);
	glVertex2i(x + 20, 63);
	glVertex2i(x + 25, 60);
	glEnd();

}

void beware(int x, int y)
{
	int newX = x;

	for (int i = 0; i < 11; i++) {

		if (i == 0)
		{

			straight_lines(newX, y, newX + 40, y);
			straight_lines(newX + 40, y, newX + 40, y + 20);
			straight_lines(newX + 40, y + 20, newX, y + 35);
			straight_lines(newX, y + 35, newX + 40, y + 35);
			straight_lines(newX + 40, y + 35, newX + 40, y + 60);
			straight_lines(newX + 40, y + 60, newX, y + 60);
			straight_lines(newX, y + 60, newX, y);

		}

		else if (i == 1) {
			////E
			//straight_lines(65, 520, 65, 580);
			//straight_lines(65, 520, 105, 520);
			//straight_lines(65, 550, 105, 550);
			//straight_lines(65, 580, 105, 580);

			straight_lines(newX, y, newX, y + 60);
			straight_lines(newX, y, newX + 40, y);
			straight_lines(newX, y + 30, newX + 40, y + 30);
			straight_lines(newX, y + 60, newX + 40, y + 60);

		}

		else if (i == 2) {
			////W
			//straight_lines(115, 580, 125, 520);
			//straight_lines(125, 520, 145, 555);
			//straight_lines(145, 555, 165, 520);
			//straight_lines(165, 520, 175, 580);
			straight_lines(newX - 10, y + 60, newX, y);
			straight_lines(newX, y, newX + 20, y + 35);
			straight_lines(newX + 20, y + 35, newX + 40, y);
			straight_lines(newX + 40, y, newX + 50, y + 60);
		}

		else if (i == 3) {
			////A
			//straight_lines(185, 520, 195, 580);
			//straight_lines(195, 580, 215, 580);
			//straight_lines(215, 580, 225, 520);
			//straight_lines(190, 550, 220, 550);
			straight_lines(newX, y, newX + 10, y + 60);
			straight_lines(newX + 10, y + 60, newX + 30, y + 60);
			straight_lines(newX + 30, y + 60, newX + 40, y);
			straight_lines(newX + 5, y + 30, newX + 35, y + 30);
		}

		else if (i == 4) {
			////R
			//straight_lines(245, 520, 245, 580);
			//straight_lines(245, 580, 285, 580);
			//straight_lines(285, 580, 285, 555);
			//straight_lines(285, 555, 245, 555);
			//straight_lines(245, 555, 285, 520);

			straight_lines(newX, y, newX, y + 60);
			straight_lines(newX, y + 60, newX + 30, y + 60);
			straight_lines(newX + 30, y + 60, newX + 30, y + 35);
			straight_lines(newX + 30, y + 35, newX, y + 35);
			straight_lines(newX, y + 35, newX + 30, y);
		}

		else if (i == 5) {
			////E
			//straight_lines(65, 520, 65, 580);
			//straight_lines(65, 520, 105, 520);
			//straight_lines(65, 550, 105, 550);
			//straight_lines(65, 580, 105, 580);

			straight_lines(newX, y, newX, y + 60);
			straight_lines(newX, y, newX + 40, y);
			straight_lines(newX, y + 30, newX + 40, y + 30);
			straight_lines(newX, y + 60, newX + 40, y + 60);

		}
		else if (i == 6) {
			newX = newX + 35;
			//O
			/*straight_lines(385, 520, 425, 520);
			straight_lines(425, 520, 425, 580);
			straight_lines(425, 580, 385, 580);
			straight_lines(385, 580, 385, 520);*/

			straight_lines(newX, y, newX + 40, y);
			straight_lines(newX + 40, y, newX + 40, y + 60);
			straight_lines(newX + 40, y + 60, newX, y + 60);
			straight_lines(newX, y + 60, newX, y);

		}

		else if (i == 7) {

			straight_lines(newX, y, newX, y + 60);
			straight_lines(newX, y + 60, newX + 40, y + 60);
			straight_lines(newX, y + 40, newX + 35, y + 40);
		}

		else if (i == 8) {
			y = y - 80;
			newX = x + 200;
			straight_lines(newX, y + 60, newX + 40, y + 60);
			straight_lines(newX + 20, y + 60, newX + 20, y);

		}

		else if (i == 9) {
			straight_lines(newX, y + 60, newX, y);
			straight_lines(newX, y + 30, newX + 40, y + 30);
			straight_lines(newX + 40, y, newX + 40, y + 60);
		}

		else if (i == 10) {
			////E
			//straight_lines(65, 520, 65, 580);
			//straight_lines(65, 520, 105, 520);
			//straight_lines(65, 550, 105, 550);
			//straight_lines(65, 580, 105, 580);

			straight_lines(newX, y, newX, y + 60);
			straight_lines(newX, y, newX + 40, y);
			straight_lines(newX, y + 30, newX + 40, y + 30);
			straight_lines(newX, y + 60, newX + 40, y + 60);

		}

		newX = newX + 60;

	}

}

void killer(int x, int y) {
	int newX = x;

	for (int i = 0; i < 7; i++) {
		if (i == 0) {
			straight_lines(newX, y, newX, y + 80);
			straight_lines(newX, y + 40, newX + 50, y + 80);
			straight_lines(newX, y + 40, newX + 50, y);
		}

		else if (i == 1) {
			straight_lines(newX, y, newX, y + 80);

		}

		else if (i == 2) {
			newX -= 50;
			straight_lines(newX, y, newX, y + 80);
			straight_lines(newX, y, newX + 50, y);
		}

		else if (i == 3) {
			straight_lines(newX, y, newX, y + 80);
			straight_lines(newX, y, newX + 50, y);
		}

		else if (i == 4) {
			straight_lines(newX, y, newX, y + 80);
			straight_lines(newX, y, newX + 50, y);
			straight_lines(newX, y + 80, newX + 50, y + 80);
			straight_lines(newX, y + 40, newX + 50, y + 40);
		}

		else if (i == 5) {
			straight_lines(newX, y, newX, y + 80);
			straight_lines(newX, y + 80, newX + 50, y + 80);
			straight_lines(newX + 50, y + 80, newX + 50, y + 40);
			straight_lines(newX + 50, y + 40, newX, y + 40);
			straight_lines(newX, y + 40, newX + 50, y);
		}


		newX = newX + 80;
	}
}

//----------SCENE-------------------------
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 530, 150);//right foot
	straight_lines(530, 150, 530, 100);//right foot down
	straight_lines(600, 200, 610, 100);//left foot 
	glFlush();
	glutSwapBuffers();
}

void display2() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 400, 320, 40);//head
	glLineWidth(10);
	straight_lines(400, 300, 400, 200);//body
	straight_lines(400, 300, 340, 190);//left hand
	straight_lines(400, 300, 460, 200);//right hand
	straight_lines(400, 200, 330, 150);//right foot
	straight_lines(330, 150, 330, 100);//right foot down
	straight_lines(400, 200, 410, 100);//left foot 

	glFlush();
	glutSwapBuffers();
}

//sit on the bed edge
void display3() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 250, 320, 40);//head
	glLineWidth(10);
	straight_lines(250, 300, 250, 200);//body
	straight_lines(250, 300, 270, 200);//left hand
	straight_lines(220, 200, 250, 290);//left hand down
	straight_lines(220, 200, 250, 190);//right hand
	straight_lines(300, 200, 250, 200);//right foot
	straight_lines(300, 200, 350, 100);//right foot down
	straight_lines(300, 180, 250, 200);//left foot 
	straight_lines(302, 180, 320, 100);//left foot down


	glFlush();
	glutSwapBuffers();
}

//play phone
void display4() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 260, 320, 40);//head
	glLineWidth(10);
	straight_lines(260, 300, 250, 260);//body
	straight_lines(250, 260, 250, 200);

	/*
	straight_lines(260, 300, 290, 260);//left hand
	straight_lines(290, 260, 260, 220);

	straight_lines(230, 260, 260, 290);//left hand down
	straight_lines(230, 260, 240, 210);//right hand
	straight_lines(300, 200, 250, 200);//right foot
	straight_lines(300, 200, 350, 100);//right foot down

	straight_lines(300, 180, 250, 200);//left foot
	straight_lines(302, 180, 320, 100);//left foot down
*/
	straight_lines(260, 300, 300, 230); //hand 1
	straight_lines(247, 290, 200, 250); //hand 2
	straight_lines(200, 250, 275, 230);

	straight_lines(250, 200, 290, 190);
	straight_lines(290, 190, 310, 100);

	straight_lines(250, 200, 270, 180);
	straight_lines(270, 180, 280, 100);
	//phone
	glColor3ub(195, 195, 195);
	rectangle(277, 225, 24, 40);

	glFlush();
	glutSwapBuffers();
}

void display5() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 260, 320, 40);//head
	glLineWidth(10);
	straight_lines(260, 300, 250, 260);//body
	straight_lines(250, 260, 250, 200);

	straight_lines(260, 300, 300, 230); //hand 1
	straight_lines(247, 290, 200, 250); //hand 2
	straight_lines(200, 250, 275, 230);

	straight_lines(250, 200, 290, 190);
	straight_lines(290, 190, 310, 100);

	straight_lines(250, 200, 270, 180);
	straight_lines(270, 180, 280, 100);
	//phone
	glColor3ub(195, 195, 195);
	rectangle(277, 225, 24, 40);

	glColor3ub(42, 42, 42);
	glRasterPos3f(280, 360, 0);
	char text[] = "!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

//NEWS 
void display6() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(229, 229, 229);
	rectangle(0, 0, 700, 700);


	glLineWidth(5);
	glColor3ub(0, 0, 0);
	straight_lines(10, 10, 690, 10);
	straight_lines(690, 10, 690, 690);
	straight_lines(690, 690, 10, 690);
	straight_lines(10, 690, 10, 10);

	//bg killer
	glColor3ub(255, 255, 106);
	rectangle(100, 350, 500, 330);

	//killer
	glColor3ub(255, 0, 0);
	circle(30, 350, 560, 120);

	//body
	glColor3ub(255, 0, 0);
	glLineWidth(10);
	straight_lines(350, 560, 350, 350);

	//hand 1
	straight_lines(350, 500, 450, 370);

	//hand 2
	straight_lines(345, 500, 250, 350);

	//knife
	straight_lines(450, 370, 550, 540);

	glColor3ub(161, 161, 161);
	straight_lines(500, 360, 550, 540);

	glColor3ub(48, 48, 48);
	triangles(450, 370, 500, 360, 550, 540);

	//beware
	glColor3ub(0, 0, 0);
	glLineWidth(7);
	beware(70, 250);

	glColor3ub(255, 0, 0);
	glLineWidth(15);
	killer(150, 50);
	glFlush();
	glutSwapBuffers();
}

void display7() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 260, 320, 40);//head
	glLineWidth(10);
	straight_lines(260, 300, 250, 260);//body
	straight_lines(250, 260, 250, 200);

	straight_lines(260, 300, 300, 230); //hand 1
	straight_lines(247, 290, 200, 250); //hand 2
	straight_lines(200, 250, 275, 230);

	straight_lines(250, 200, 290, 190);
	straight_lines(290, 190, 310, 100);

	straight_lines(250, 200, 270, 180);
	straight_lines(270, 180, 280, 100);
	//phone
	glColor3ub(195, 195, 195);
	rectangle(277, 225, 24, 40);


	glFlush();
	glutSwapBuffers();
}

void display8() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 250, 320, 40);//head
	glLineWidth(10);
	straight_lines(250, 300, 260, 200);//body
	straight_lines(260, 290, 290, 200);//left hand
	straight_lines(220, 200, 255, 290);//left hand down
	straight_lines(220, 200, 260, 190);//right hand

	straight_lines(260, 200, 290, 190);
	straight_lines(290, 190, 310, 100);

	straight_lines(260, 200, 270, 180);
	straight_lines(270, 180, 280, 100);


	glFlush();
	glutSwapBuffers();
}
//scene 1
void display9() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(150, 200, 180, 190);//right foot
	straight_lines(180, 190, 210, 110);
	straight_lines(150, 200, 130, 180);
	straight_lines(130, 180, 136, 100);


	glColor3ub(42, 42, 42);
	glRasterPos3f(100, 360, 0);
	char text[] = "I'm sleepy....";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}


//boy sleep
void display10() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomDark();

	glColor3ub(255, 245, 245);//boy 
	circle(25, 60, 240, 40);//head
	glLineWidth(10);
	straight_lines(100, 230, 160, 200);//body
	straight_lines(100, 230, 120, 200);//left hand
	straight_lines(120, 200, 150, 170);//right hand
	straight_lines(220, 190, 160, 200);//right foot
	straight_lines(220, 190, 275, 110);
	straight_lines(160, 200, 230, 110);
	glFlush();
	glutSwapBuffers();

}

//cloud 1
void display11() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomDark();
	//cloud dream
	glColor3ub(255, 255, 255);
	circle(50, 100, 380, 50);
	circle(50, 150, 430, 65);
	circle(50, 210, 400, 55);
	circle(50, 160, 350, 45);

	glColor3ub(255, 245, 245);//boy 
	circle(25, 60, 240, 40);//head
	glLineWidth(10);
	straight_lines(100, 230, 160, 200);//body
	straight_lines(100, 230, 120, 200);//left hand
	straight_lines(120, 200, 150, 170);//right hand
	straight_lines(220, 190, 160, 200);//right foot
	straight_lines(220, 190, 275, 110);
	straight_lines(160, 200, 230, 110);
	glFlush();
	glutSwapBuffers();
}

//cloud 2
void display12() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomDark();
	//cloud dream
	glColor3ub(255, 255, 255);
	circle(50, 120, 350, 100);
	circle(50, 150, 430, 130);
	circle(50, 100, 400, 110);
	circle(50, 190, 300, 90);
	//circle(100(idk), 160(lr), 350(height), 200(size));

	glColor3ub(255, 245, 245);//boy 
	circle(25, 60, 240, 40);//head
	glLineWidth(10);
	straight_lines(100, 230, 160, 200);//body
	straight_lines(100, 230, 120, 200);//left hand
	straight_lines(120, 200, 150, 170);//right hand
	straight_lines(220, 190, 160, 200);//right foot
	straight_lines(220, 190, 275, 110);
	straight_lines(160, 200, 230, 110);
	glFlush();
	glutSwapBuffers();
}

//cloud 3
void display13() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomDark();
	//cloud dream
	glColor3ub(255, 255, 255);
	circle(50, 120, 350, 250);
	circle(50, 200, 430, 300);
	circle(50, 240, 400, 350);
	circle(50, 300, 300, 400);
	//circle(100(idk), 160(lr), 350(height), 200(size));

	glColor3ub(255, 245, 245);//boy 
	circle(25, 60, 240, 40);//head
	glLineWidth(10);
	straight_lines(100, 230, 160, 200);//body
	straight_lines(100, 230, 120, 200);//left hand
	straight_lines(120, 200, 150, 170);//right hand
	straight_lines(220, 190, 160, 200);//right foot
	straight_lines(220, 190, 275, 110);
	straight_lines(160, 200, 230, 110);
	glFlush();
	glutSwapBuffers();
}

//square
void display14()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(51, 52, 77);
	rectangle(0, 0, 700, 700);

	glutSwapBuffers();
}

//dream
void display15() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(1);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 60, 240, 37);//head

	glLineWidth(10);
	straight_lines(60, 240, 60, 110);//body

	straight_lines(65, 210, 90, 160); //hand 1
	straight_lines(90, 160, 110, 180);

	straight_lines(65, 230, 30, 160); //hand 2
	straight_lines(30, 160, 66, 130);

	straight_lines(60, 110, 90, 50); //leg 1
	straight_lines(60, 110, 30, 50); //leg 2

	glFlush();
	glutSwapBuffers();
}

void display16() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 240, 37);//head

	glLineWidth(10);
	straight_lines(150, 240, 150, 110);//body

	straight_lines(155, 210, 170, 160); //hand 1
	straight_lines(170, 160, 210, 180);

	straight_lines(155, 230, 130, 160); //hand 2
	straight_lines(130, 160, 166, 130);

	straight_lines(150, 110, 180, 50); //leg 1
	straight_lines(150, 110, 120, 50); //leg 2

	glFlush();
	glutSwapBuffers();
}

//killer appear
void display17() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(3);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 170, 240, 37);//head

	glLineWidth(10);
	straight_lines(170, 240, 170, 110);//body

	straight_lines(175, 210, 200, 160); //hand 1
	straight_lines(200, 160, 220, 180);

	straight_lines(175, 230, 140, 160); //hand 2
	straight_lines(140, 160, 176, 130);

	straight_lines(170, 110, 200, 50); //leg 1
	straight_lines(170, 110, 140, 50); //leg 2

	glRasterPos3f(250, 290, 0);
	char text[] = "???";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	//killer
	glColor3ub(254, 11, 2);//boy 
	circle(25, 0, 240, 37);//head

	straight_lines(0, 240, 0, 110);//body

	straight_lines(0, 210, 0, 160); //hand 1
	straight_lines(0, 160, 25, 180);

	straight_lines(0, 110, 30, 50); //leg 1

	glFlush();
	glutSwapBuffers();
}

//killer with knife
void display18() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(3);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 190, 240, 37);//head

	glLineWidth(10);
	straight_lines(190, 240, 190, 110);//body

	straight_lines(195, 210, 220, 160); //hand 1
	straight_lines(220, 160, 240, 180);

	straight_lines(195, 210, 170, 160); //hand 2
	straight_lines(170, 160, 150, 208);

	straight_lines(190, 110, 220, 50); //leg 1
	straight_lines(190, 110, 160, 50); //leg 2

	glRasterPos3f(250, 300, 0);
	char text[] = "!!!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	//killer
	glColor3ub(254, 11, 2);//boy 
	circle(25, 0, 240, 37);//head

	straight_lines(0, 240, 0, 110);//body

	straight_lines(0, 210, 0, 160); //hand 1

	straight_lines(0, 110, 30, 50); //leg 1


	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(0, 160, 45, 200);

	glLineWidth(5);
	straight_lines(45, 200, 22, 120);
	straight_lines(22, 120, 0, 160);

	glColor3ub(48, 48, 48);
	triangles(0, 160, 45, 200, 22, 120);

	glFlush();
	glutSwapBuffers();
}

void display19() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(4);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 230, 240, 37);//head

	glLineWidth(10);
	straight_lines(230, 240, 230, 110);//body

	straight_lines(235, 210, 265, 160); //hand 1
	straight_lines(265, 160, 270, 210);

	straight_lines(235, 210, 170, 160); //hand 2
	straight_lines(170, 160, 200, 140);

	straight_lines(230, 110, 290, 110); //leg 1
	straight_lines(290, 110, 290, 60);


	straight_lines(230, 110, 215, 60); //leg 2
	straight_lines(215, 60, 200, 110);


	//killer
	glColor3ub(254, 11, 2);
	circle(25, 1, 240, 37);//head

	straight_lines(1, 240, 0, 110);//body

	straight_lines(0, 210, 0, 160); //hand 1
	straight_lines(0, 110, 30, 50); //leg 1

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(0, 160, 45, 200);

	glLineWidth(5);
	straight_lines(45, 200, 22, 120);
	straight_lines(22, 120, 0, 160);

	//knife fill
	glColor3ub(48, 48, 48);
	triangles(0, 160, 45, 200, 22, 120);
	straight_lines(0, 160, 45, 200);


	glFlush();
	glutSwapBuffers();
}

void display20() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(5);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 300, 240, 37);//head

	glLineWidth(10);
	straight_lines(300, 240, 300, 110);//body

	straight_lines(305, 210, 345, 160); //hand 1
	straight_lines(345, 160, 380, 210);

	straight_lines(305, 210, 240, 220); //hand 2
	straight_lines(240, 220, 220, 160);

	straight_lines(300, 110, 450, 100); //leg 1

	straight_lines(300, 110, 200, 60); //leg 2
	straight_lines(200, 60, 160, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 50, 240, 37);//head

	straight_lines(50, 240, 50, 110);//body

	straight_lines(55, 210, 100, 160); //hand 1


	straight_lines(55, 210, 0, 160); //hand 2

	straight_lines(50, 110, 150, 120); //leg 1
	straight_lines(150, 120, 150, 60);

	straight_lines(50, 110, 0, 60); //leg 2

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(100, 160, 150, 200);
	straight_lines(150, 200, 125, 120);
	straight_lines(125, 120, 100, 160);

	glColor3ub(48, 48, 48);
	triangles(100, 160, 150, 200, 125, 120);

	glFlush();
	glutSwapBuffers();
}

void display21() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(1);

	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 404, 240, 37);//head

	glLineWidth(10);
	straight_lines(400, 240, 380, 110);//body

	straight_lines(385, 210, 440, 160); //hand 1
	straight_lines(440, 160, 480, 210);

	straight_lines(385, 210, 340, 220); //hand 2
	straight_lines(340, 220, 320, 160);

	straight_lines(380, 110, 440, 150);
	straight_lines(440, 150, 460, 60); //leg 1

	straight_lines(380, 110, 350, 60); //leg 2
	straight_lines(350, 60, 300, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 150, 160); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2
	straight_lines(50, 160, 80, 120);

	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(150, 160, 200, 200);
	straight_lines(200, 200, 175, 120);
	straight_lines(175, 120, 150, 160);

	glColor3ub(48, 48, 48);
	triangles(150, 160, 200, 200, 175, 120);

	glFlush();
	glutSwapBuffers();
}

void display22() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(605, 210, 620, 160); //hand 1
	straight_lines(620, 160, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 580, 150);
	straight_lines(580, 150, 590, 60); //leg 1

	straight_lines(540, 110, 510, 60); //leg 2
	straight_lines(510, 60, 490, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 200, 240, 37);//head

	straight_lines(200, 240, 200, 110);//body

	straight_lines(205, 210, 250, 160); //hand 1
	straight_lines(205, 210, 150, 160); //hand 2
	straight_lines(150, 160, 180, 120);

	straight_lines(200, 110, 250, 120); //leg 1
	straight_lines(250, 120, 280, 60);

	straight_lines(200, 110, 150, 60); //leg 2
	straight_lines(150, 60, 130, 100);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(250, 160, 300, 200);
	straight_lines(300, 200, 275, 120);
	straight_lines(275, 120, 250, 160);

	glColor3ub(48, 48, 48);
	triangles(250, 160, 300, 200, 275, 120);

	glFlush();
	glutSwapBuffers();
}

void display23() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(3);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 560, 110);//body

	straight_lines(600, 210, 620, 140); //hand 1
	straight_lines(620, 140, 640, 160);

	straight_lines(600, 210, 560, 200); //hand 2
	straight_lines(560, 200, 580, 140);

	straight_lines(560, 110, 580, 110);
	straight_lines(580, 110, 600, 60); //leg 1

	straight_lines(560, 110, 540, 60); //leg 2
	straight_lines(540, 60, 490, 110);

	glRasterPos3f(400, 300, 0);
	char text[] = "Erghh! I need to run faster!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 250, 240, 37);//head

	straight_lines(250, 240, 250, 110);//body

	straight_lines(255, 210, 300, 160); //hand 1
	straight_lines(255, 210, 200, 160); //hand 2
	straight_lines(200, 160, 230, 120);

	straight_lines(250, 110, 300, 120); //leg 1
	straight_lines(300, 120, 330, 60);

	straight_lines(250, 110, 200, 60); //leg 2
	straight_lines(200, 60, 180, 100);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(300, 160, 350, 200);
	straight_lines(350, 200, 325, 120);
	straight_lines(325, 120, 300, 160);

	glColor3ub(48, 48, 48);
	triangles(300, 160, 350, 200, 325, 120);

	glFlush();
	glutSwapBuffers();
}

void display24() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(4);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(600, 210, 620, 150); //hand 1
	straight_lines(620, 150, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 580, 150);
	straight_lines(580, 150, 590, 60); //leg 1

	straight_lines(540, 110, 510, 60); //leg 2
	straight_lines(510, 60, 490, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 200, 240, 37);//head

	straight_lines(200, 240, 200, 110);//body

	straight_lines(205, 210, 250, 160); //hand 1
	straight_lines(205, 210, 150, 160); //hand 2
	straight_lines(150, 160, 180, 120);

	straight_lines(200, 110, 250, 120); //leg 1
	straight_lines(250, 120, 280, 60);

	straight_lines(200, 110, 150, 60); //leg 2
	straight_lines(150, 60, 130, 100);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(250, 160, 300, 200);
	straight_lines(300, 200, 275, 120);
	straight_lines(275, 120, 250, 160);

	glColor3ub(48, 48, 48);
	triangles(250, 160, 300, 200, 275, 120);

	glFlush();
	glutSwapBuffers();
}

void display25() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(5);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(605, 210, 620, 160); //hand 1
	straight_lines(620, 160, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 560, 150);
	straight_lines(560, 150, 620, 60); //leg 1

	straight_lines(540, 110, 500, 80); //leg 2
	straight_lines(500, 80, 450, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 150, 160); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2
	straight_lines(150, 160, 180, 120);

	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(150, 160, 200, 200);
	straight_lines(200, 200, 175, 120);
	straight_lines(175, 120, 150, 160);

	glColor3ub(48, 48, 48);
	triangles(150, 160, 200, 200, 175, 120);

	glFlush();
	glutSwapBuffers();
}

void display26() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(1);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 560, 110);//body

	straight_lines(600, 210, 620, 140); //hand 1
	straight_lines(620, 140, 640, 160);

	straight_lines(600, 210, 560, 200); //hand 2
	straight_lines(560, 200, 580, 140);

	straight_lines(560, 110, 580, 110);
	straight_lines(580, 110, 600, 60); //leg 1

	straight_lines(560, 110, 540, 60); //leg 2
	straight_lines(540, 60, 490, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 50, 240, 37);//head

	straight_lines(50, 240, 50, 110);//body

	straight_lines(55, 210, 100, 160); //hand 1


	straight_lines(55, 210, 0, 160); //hand 2
	straight_lines(0, 160, 30, 120);

	straight_lines(50, 110, 100, 120); //leg 1
	straight_lines(100, 120, 130, 60);

	straight_lines(50, 110, 0, 60); //leg 2

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(100, 160, 150, 200);
	straight_lines(150, 200, 125, 120);
	straight_lines(125, 120, 100, 160);

	glColor3ub(48, 48, 48);
	triangles(100, 160, 150, 200, 125, 120);

	glFlush();
	glutSwapBuffers();
}

void display27() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(4);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(605, 210, 620, 160); //hand 1
	straight_lines(620, 160, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 560, 150);
	straight_lines(560, 150, 620, 60); //leg 1

	straight_lines(540, 110, 500, 80); //leg 2
	straight_lines(500, 80, 450, 110);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 10, 240, 37);//head

	straight_lines(10, 240, 0, 110);//body

	straight_lines(0, 210, 0, 160); //hand 1
	straight_lines(0, 160, 25, 180);

	straight_lines(0, 110, 40, 120); //leg 1
	straight_lines(40, 120, 10, 50);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(0, 160, 45, 200);

	glLineWidth(5);
	straight_lines(45, 200, 22, 120);
	straight_lines(22, 120, 0, 160);

	glColor3ub(48, 48, 48);
	triangles(0, 160, 45, 200, 22, 120);

	glFlush();
	glutSwapBuffers();
}

void display28() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 560, 110);//body

	straight_lines(600, 210, 620, 140); //hand 1
	straight_lines(620, 140, 640, 160);

	straight_lines(600, 210, 560, 200); //hand 2
	straight_lines(560, 200, 580, 140);

	straight_lines(560, 110, 580, 110);
	straight_lines(580, 110, 600, 60); //leg 1

	straight_lines(560, 110, 540, 60); //leg 2
	straight_lines(540, 60, 490, 110);
	glFlush();
	glutSwapBuffers();
}

void display29() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(3);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(600, 210, 620, 150); //hand 1
	straight_lines(620, 150, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 580, 150);
	straight_lines(580, 150, 590, 60); //leg 1

	straight_lines(540, 110, 510, 60); //leg 2
	straight_lines(510, 60, 490, 110);
	glFlush();
	glutSwapBuffers();
}

void display30() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(4);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(605, 210, 620, 160); //hand 1
	straight_lines(620, 160, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 560, 150);
	straight_lines(560, 150, 620, 60); //leg 1

	straight_lines(540, 110, 500, 80); //leg 2
	straight_lines(500, 80, 450, 110);

	glFlush();
	glutSwapBuffers();
}

void display31() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(5);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head


	glLineWidth(10);
	straight_lines(600, 240, 560, 110);//body

	straight_lines(600, 210, 620, 140); //hand 1
	straight_lines(620, 140, 640, 160);

	straight_lines(600, 210, 560, 200); //hand 2
	straight_lines(560, 200, 580, 140);

	straight_lines(560, 110, 580, 110);
	straight_lines(580, 110, 600, 60); //leg 1

	straight_lines(560, 110, 540, 60); //leg 2
	straight_lines(540, 60, 490, 110);
	glFlush();
	glutSwapBuffers();
}

void display32() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(1);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head


	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(600, 210, 620, 150); //hand 1
	straight_lines(620, 150, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 580, 150);
	straight_lines(580, 150, 590, 60); //leg 1

	straight_lines(540, 110, 510, 60); //leg 2
	straight_lines(510, 60, 490, 110);
	glFlush();
	glutSwapBuffers();
}

void display33() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(605, 210, 620, 160); //hand 1
	straight_lines(620, 160, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 560, 150);
	straight_lines(560, 150, 620, 60); //leg 1

	straight_lines(540, 110, 500, 80); //leg 2
	straight_lines(500, 80, 450, 110);
	glFlush();
	glutSwapBuffers();
}

void display34() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(3);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 560, 110);//body

	straight_lines(600, 210, 620, 140); //hand 1
	straight_lines(620, 140, 640, 160);

	straight_lines(600, 210, 560, 200); //hand 2
	straight_lines(560, 200, 580, 140);

	straight_lines(560, 110, 580, 110);
	straight_lines(580, 110, 600, 60); //leg 1

	straight_lines(560, 110, 540, 60); //leg 2
	straight_lines(540, 60, 490, 110);

	glFlush();
	glutSwapBuffers();
}

void display35() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(3);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(600, 210, 620, 150); //hand 1
	straight_lines(620, 150, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 580, 150);
	straight_lines(580, 150, 590, 60); //leg 1

	straight_lines(540, 110, 510, 60); //leg 2
	straight_lines(510, 60, 490, 110);
	glFlush();
	glutSwapBuffers();
}

void display36() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(5);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head

	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(605, 210, 620, 160); //hand 1
	straight_lines(620, 160, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 560, 150);
	straight_lines(560, 150, 620, 60); //leg 1

	straight_lines(540, 110, 500, 80); //leg 2
	straight_lines(500, 80, 450, 110);

	glRasterPos3f(325, 300, 0);
	char text[] = "Phew! I think he is far away from me";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display37() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(1);

	rock(600);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 600, 240, 37);//head


	glLineWidth(10);
	straight_lines(600, 240, 540, 110);//body

	straight_lines(600, 210, 620, 150); //hand 1
	straight_lines(620, 150, 640, 210);

	straight_lines(605, 210, 560, 220); //hand 2
	straight_lines(560, 220, 520, 160);

	straight_lines(540, 110, 580, 150);
	straight_lines(580, 150, 590, 60); //leg 1

	straight_lines(540, 110, 510, 60); //leg 2
	straight_lines(510, 60, 490, 110);
	glFlush();
	glutSwapBuffers();
}

void display38() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(5);
	glLineWidth(10);
	rock(605);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 693, 220, 37);//head



	straight_lines(693, 220, 620, 120);//body

	straight_lines(673, 210, 700, 150); //hand 1

	straight_lines(673, 205, 617, 180); //hand 2
	straight_lines(617, 180, 685, 125);

	straight_lines(624, 120, 655, 90); //leg 1
	straight_lines(655, 90, 585, 60);

	straight_lines(624, 120, 590, 110); //leg 2
	straight_lines(590, 110, 540, 140);

	//killer
	glColor3ub(254, 11, 2);
	circle(25, 10, 240, 37);//head

	straight_lines(10, 240, 0, 110);//body

	straight_lines(0, 210, 0, 160); //hand 1
	straight_lines(0, 160, 25, 180);

	straight_lines(0, 110, 40, 120); //leg 1
	straight_lines(40, 120, 10, 50);

	//knife line
	glColor3ub(161, 161, 161);
	straight_lines(0, 160, 45, 200);

	glLineWidth(5);
	straight_lines(45, 200, 22, 120);
	straight_lines(22, 120, 0, 160);

	glColor3ub(48, 48, 48);
	triangles(0, 160, 45, 200, 22, 120);

	glFlush();
	glutSwapBuffers();
}

void display39() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	glLineWidth(10);
	rock(300);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 540, 150, 37);//head

	straight_lines(540, 150, 420, 100); //body

	straight_lines(500, 135, 520, 80); //hand 1
	straight_lines(520, 80, 570, 60);

	straight_lines(500, 135, 420, 140); //hand 2
	straight_lines(420, 140, 480, 63);

	straight_lines(420, 100, 415, 60); //leg 1
	straight_lines(415, 60, 346, 50);

	straight_lines(420, 100, 380, 90); //leg 2
	straight_lines(380, 90, 320, 95);



	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 150, 160); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2
	straight_lines(150, 160, 180, 120);

	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);
	straight_lines(150, 160, 200, 200);
	straight_lines(200, 200, 175, 120);
	straight_lines(175, 120, 150, 160);

	glColor3ub(48, 48, 48);
	triangles(150, 160, 200, 200, 175, 120);

	glFlush();
	glutSwapBuffers();
}

void display40() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	glLineWidth(10);
	rock(300);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 540, 150, 37);//head

	straight_lines(540, 150, 510, 60); //body

	straight_lines(510, 60, 490, 110); //leg 1
	straight_lines(490, 110, 460, 40);

	straight_lines(510, 60, 430, 60); //leg 2
	straight_lines(430, 60, 400, 50);

	straight_lines(545, 120, 570, 90); //hand 1
	straight_lines(570, 90, 480, 50);

	straight_lines(520, 120, 460, 115); //hand 2
	straight_lines(460, 115, 465, 85);



	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 150, 160); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2
	straight_lines(150, 160, 180, 120);

	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);


	glColor3ub(48, 48, 48);
	triangles(150, 160, 200, 200, 175, 120);

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 100, 240, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 100, 250, 20);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);
	straight_lines(150, 160, 200, 200);
	straight_lines(200, 200, 175, 120);
	straight_lines(175, 120, 150, 160);


	glRasterPos3f(100, 360, 0);
	char text[] = "heh!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display41() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	glLineWidth(10);
	rock(300);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 540, 150, 37);//head

	straight_lines(540, 150, 510, 60); //body

	straight_lines(510, 60, 490, 110); //leg 1
	straight_lines(490, 110, 460, 40);

	straight_lines(510, 60, 430, 60); //leg 2
	straight_lines(430, 60, 400, 50);

	straight_lines(545, 120, 570, 90); //hand 1
	straight_lines(570, 90, 480, 50);

	straight_lines(520, 120, 460, 115); //hand 2
	straight_lines(460, 115, 465, 85);



	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 180, 250); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2


	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 100, 240, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 100, 250, 20);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);
	straight_lines(250, 200, 200, 240);
	straight_lines(200, 240, 230, 290);
	straight_lines(230, 290, 250, 200);

	//knife
	glColor3ub(48, 48, 48);
	triangles(250, 200, 200, 240, 230, 290);

	glColor3ub(255, 255, 255);
	glRasterPos3f(540, 360, 0);
	char text[] = "Aaaaaaaahhhhh!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display42() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	glLineWidth(10);
	rock(300);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 540, 150, 37);//head

	straight_lines(540, 150, 510, 60); //body

	straight_lines(510, 60, 490, 110); //leg 1
	straight_lines(490, 110, 460, 40);

	straight_lines(510, 60, 430, 60); //leg 2
	straight_lines(430, 60, 400, 50);

	straight_lines(545, 120, 570, 90); //hand 1
	straight_lines(570, 90, 480, 50);

	straight_lines(520, 120, 460, 115); //hand 2
	straight_lines(460, 115, 465, 85);



	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 180, 250); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2


	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 100, 240, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 100, 250, 20);

	//knife
	glColor3ub(48, 48, 48);
	//triangles(250, 200, 200, 240, 230, 290);
	triangles(350, 250, 250, 290, 280, 340);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);
	straight_lines(350, 250, 250, 290);
	straight_lines(250, 290, 280, 340);
	straight_lines(280, 340, 350, 250);

	glFlush();
	glutSwapBuffers();
}

void display43() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);
	glLineWidth(10);
	rock(300);
	//circle
	glColor3ub(255, 255, 255);//boy 
	circle(25, 540, 150, 37);//head

	straight_lines(540, 150, 510, 60); //body

	straight_lines(510, 60, 490, 110); //leg 1
	straight_lines(490, 110, 460, 40);

	straight_lines(510, 60, 430, 60); //leg 2
	straight_lines(430, 60, 400, 50);

	straight_lines(545, 120, 570, 90); //hand 1
	straight_lines(570, 90, 480, 50);

	straight_lines(520, 120, 460, 115); //hand 2
	straight_lines(460, 115, 465, 85);



	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 180, 250); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2


	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 100, 240, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 100, 250, 20);

	//knife
	glColor3ub(48, 48, 48);
	//triangles(250, 200, 200, 240, 230, 290);
	triangles(450, 200, 400, 240, 430, 290);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);
	straight_lines(450, 200, 400, 240);
	straight_lines(400, 240, 430, 290);
	straight_lines(430, 290, 450, 200);

	glFlush();
	glutSwapBuffers();
}

void display44() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundChase(2);

	rock(300);
	//circle
	glLineWidth(10);
	glColor3ub(255, 255, 255);//boy 
	circle(25, 540, 150, 37);//head

	straight_lines(540, 150, 510, 60); //body

	straight_lines(510, 60, 490, 110); //leg 1
	straight_lines(490, 110, 460, 40);

	straight_lines(510, 60, 430, 60); //leg 2
	straight_lines(430, 60, 400, 50);

	straight_lines(545, 120, 570, 90); //hand 1
	straight_lines(570, 90, 480, 50);

	straight_lines(520, 120, 460, 115); //hand 2
	straight_lines(460, 115, 465, 85);



	//killer
	glColor3ub(254, 11, 2);
	circle(25, 100, 240, 37);//head

	straight_lines(100, 240, 100, 110);//body

	straight_lines(105, 210, 180, 250); //hand 1

	straight_lines(105, 210, 50, 160); //hand 2


	straight_lines(100, 110, 150, 120); //leg 1
	straight_lines(150, 120, 200, 60);

	straight_lines(100, 110, 50, 60); //leg 2
	straight_lines(50, 60, 30, 100);

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 100, 240, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 100, 250, 20);

	//knife
	glColor3ub(48, 48, 48);
	//triangles(250, 200, 200, 240, 230, 290);
	triangles(500, 150, 450, 190, 480, 240);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);
	straight_lines(500, 150, 450, 190);
	straight_lines(450, 190, 480, 240);
	straight_lines(480, 240, 500, 150);

	glFlush();
	glutSwapBuffers();
}

//wake up scene
void display45() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	backgroundRoomDark();

	glColor3ub(255, 245, 245);//boy 
	circle(25, 60, 240, 40);//head
	glLineWidth(10);

	straight_lines(100, 230, 160, 200);//body
	straight_lines(100, 230, 120, 200);//left hand
	straight_lines(120, 200, 150, 170);//right hand
	straight_lines(220, 190, 160, 200);//right foot
	straight_lines(220, 190, 275, 110);
	straight_lines(160, 200, 230, 110);
	glFlush();
	glutSwapBuffers();
}

void display46() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(150, 200, 180, 190);//right foot
	straight_lines(180, 190, 210, 110);
	straight_lines(150, 200, 130, 180);
	straight_lines(130, 180, 136, 100);

	glRasterPos3f(100, 360, 0);
	char text[] = "Fuhh!,I'm relieved it was just a dream";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}


void display47() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);



	backgroundRoomLight();

	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(150, 200, 180, 190);//right foot
	straight_lines(180, 190, 210, 110);
	straight_lines(150, 200, 130, 180);
	straight_lines(130, 180, 136, 100);

	glRasterPos3f(100, 360, 0);
	char text[] = "Fuhh!,I'm relieved it was just a dream";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}

void display48() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomLight();
	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 300, 40);//head
	glLineWidth(10);
	straight_lines(140, 280, 165, 200);//body
	straight_lines(140, 280, 200, 205);//left hand
	straight_lines(110, 200, 150, 300);//left hand down
	straight_lines(110, 200, 150, 180);//right hand

	straight_lines(165, 200, 213, 180);//right foot
	straight_lines(213, 180, 223, 110);//right foot down

	straight_lines(165, 200, 175, 180);//left foot 
	straight_lines(175, 180, 180, 111);

	glRasterPos3f(100, 360, 0);
	char text[] = "I'm still sleepy";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display49() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backgroundRoomDark();

	glColor3ub(255, 255, 255);
	circle(25, 65, 245, 40);

	glLineWidth(10);
	straight_lines(65, 230, 220, 204); //body

	//straight_lines(65, 230, 150, 250);
	straight_lines(100, 230, 120, 170); //hand
	straight_lines(120, 170, 150, 160);
	straight_lines(220, 204, 250, 210); //leg 1
	straight_lines(250, 210, 310, 150);

	straight_lines(220, 204, 235, 190);
	straight_lines(235, 190, 260, 120);
	glFlush();
	glutSwapBuffers();
}

void display50() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(138, 138, 138);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(132, 93, 16);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 117);
	rectangle(20, 100, 250, 100);

	//lamp
	glColor3ub(170, 90, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(132, 93, 16);
	rectangle(100, 200, 6, 130);

	//table
	glColor3ub(85, 43, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);
	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	glColor3ub(255, 255, 255);
	circle(25, 65, 245, 40);

	glLineWidth(10);
	straight_lines(65, 230, 220, 204); //body

	//straight_lines(65, 230, 150, 250);
	straight_lines(100, 230, 120, 170); //hand
	straight_lines(120, 170, 150, 160);
	straight_lines(220, 204, 250, 210); //leg 1
	straight_lines(250, 210, 310, 150);

	straight_lines(220, 204, 235, 190);
	straight_lines(235, 190, 260, 120);
	glFlush();
	glutSwapBuffers();
}

void display51() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(200, 200, 150, 200);//right foot
	straight_lines(200, 200, 250, 150);//right foot down
	straight_lines(200, 180, 150, 200);//left foot 
	straight_lines(202, 180, 220, 110);//left foot down

	glColor3ub(255, 255, 255);
	glRasterPos3f(100, 360, 0);
	char text[] = "?";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}


void display52() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 570, 100);//right foot

	straight_lines(600, 200, 610, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 600, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 600, 320, 20);

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(200, 200, 150, 200);//right foot
	straight_lines(200, 200, 250, 150);//right foot down
	straight_lines(200, 180, 150, 200);//left foot 
	straight_lines(202, 180, 220, 110);//left foot down

	glColor3ub(254, 11, 2);
	glRasterPos3f(460, 360, 0);
	char text[] = "there you are..*whisper*";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}

void display53() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 570, 100);//right foot

	straight_lines(600, 200, 610, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 600, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 600, 320, 20);

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(200, 200, 150, 200);//right foot
	straight_lines(200, 200, 250, 150);//right foot down
	straight_lines(200, 180, 150, 200);//left foot 
	straight_lines(202, 180, 220, 110);//left foot down

	glRasterPos3f(100, 360, 0);
	char text[] = "!!!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display54() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 570, 100);//right foot

	straight_lines(600, 200, 610, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 600, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 600, 320, 20);

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(120, 200, 150, 300);//left hand down
	straight_lines(120, 200, 150, 180);//right hand
	straight_lines(200, 200, 150, 200);//right foot
	straight_lines(200, 200, 250, 150);//right foot down
	straight_lines(200, 180, 150, 200);//left foot 
	straight_lines(202, 180, 220, 110);//left foot down

	glRasterPos3f(100, 360, 0);
	char text[] = "!!!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display55() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 570, 100);//right foot

	straight_lines(600, 200, 610, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 600, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 600, 320, 20);

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(170, 200, 150, 220);//left hand up
	straight_lines(120, 200, 150, 300);//right hand
	straight_lines(150, 200, 120, 100);//right foot
	straight_lines(150, 200, 180, 100);//left foot 

	glRasterPos3f(100, 360, 0);
	char text[] = "Oh no! Please don't kill me!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display56() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 570, 100);//right foot

	straight_lines(600, 200, 610, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 600, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 600, 320, 20);

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 300, 170, 200);//left hand
	straight_lines(170, 200, 150, 220);//left hand up
	straight_lines(120, 200, 150, 300);//right hand
	straight_lines(150, 200, 120, 100);//right foot
	straight_lines(150, 200, 180, 100);//left foot 

	glRasterPos3f(100, 360, 0);
	char text[] = "Oh no! Please don't kill me!";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display57() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 600, 320, 40);//head
	glLineWidth(10);
	straight_lines(600, 300, 600, 200);//body
	straight_lines(600, 300, 540, 190);//left hand
	straight_lines(600, 300, 660, 200);//right hand
	straight_lines(600, 200, 570, 100);//right foot

	straight_lines(600, 200, 610, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 600, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 600, 320, 20);


	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body
	straight_lines(150, 280, 220, 310);//left hand
	//straight_lines(170, 200, 150, 220);//left hand up
	//straight_lines(120, 220, 150, 300);//right hand
	straight_lines(150, 300, 120, 220);
	straight_lines(120, 220, 170, 200);

	straight_lines(150, 200, 120, 100);//right foot
	straight_lines(150, 200, 180, 100);//left foot 

	glRasterPos3f(100, 360, 0);
	char text[] = "	Stay there or I will call the police";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

	glFlush();
	glutSwapBuffers();
}

void display58() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	glLineWidth(10);
	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 500, 320, 40);//head
	glLineWidth(10);
	straight_lines(500, 300, 500, 200);//body
	straight_lines(500, 300, 450, 230);//left hand
	straight_lines(450, 230, 400, 300);

	straight_lines(500, 300, 560, 200);//right hand
	straight_lines(500, 200, 470, 100);//right foot

	straight_lines(500, 200, 510, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 500, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 500, 320, 20);

	glRasterPos3f(400, 360, 0);
	char text2[] = "Go ahead";
	for (int i = 0; i < strlen(text2); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
	}

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body

	straight_lines(150, 280, 180, 242);
	straight_lines(180, 242, 220, 320);//left hand

	straight_lines(150, 280, 120, 242);
	straight_lines(120, 242, 80, 320);


	straight_lines(150, 200, 120, 100);//right foot
	straight_lines(150, 200, 180, 100);//left foot 


	//knife
	glColor3ub(48, 48, 48);
	//triangles(250, 200, 200, 240, 230, 290);
	triangles(450, 230, 400, 300, 470, 270);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);

	straight_lines(450, 230, 400, 300);
	straight_lines(450, 230, 470, 270);
	straight_lines(470, 270, 400, 300);

	glColor3ub(255, 255, 255);
	glRasterPos3f(100, 360, 0);
	char text[] = "Please don't kill me";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}

void display59() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	glLineWidth(10);
	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 500, 320, 40);//head
	glLineWidth(10);
	straight_lines(500, 300, 500, 200);//body
	straight_lines(500, 300, 450, 230);//left hand
	straight_lines(450, 230, 400, 300);

	straight_lines(500, 300, 560, 200);//right hand
	straight_lines(500, 200, 470, 100);//right foot

	straight_lines(500, 200, 510, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 500, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 500, 320, 20);

	glRasterPos3f(400, 360, 0);
	char text2[] = "Any last word?";
	for (int i = 0; i < strlen(text2); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
	}

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body

	straight_lines(150, 280, 180, 242);
	straight_lines(180, 242, 220, 320);//left hand

	straight_lines(150, 280, 120, 242);
	straight_lines(120, 242, 80, 320);


	straight_lines(150, 200, 120, 100);//right foot
	straight_lines(150, 200, 180, 100);//left foot 


	//knife
	glColor3ub(48, 48, 48);
	//triangles(250, 200, 200, 240, 230, 290);
	triangles(450, 230, 400, 300, 470, 270);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);

	straight_lines(450, 230, 400, 300);
	straight_lines(450, 230, 470, 270);
	straight_lines(470, 270, 400, 300);

	glColor3ub(255, 255, 255);
	glRasterPos3f(100, 360, 0);
	char text[] = "Err..I...Why---";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}

void display60() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bg
	glColor3ub(170, 170, 170);
	rectangle(0, 100, 700, 600);//background
	glColor3ub(70, 70, 70);
	rectangle(0, 0, 700, 100);
	//bed
	glColor3ub(170, 120, 20);
	rectangle(0, 100, 20, 200);
	glColor3ub(0, 0, 170);
	rectangle(20, 100, 250, 100);

	//table
	glColor3ub(119, 60, 0);
	rectangle(450, 235, 100, 10);
	rectangle(452, 100, 5, 135);
	rectangle(543, 100, 5, 135);

	//door open
	glColor3ub(0, 0, 0);
	rectangle(590, 100, 110, 400);
	glColor3ub(170, 120, 20);

	glLineWidth(10);
	//killer behind door
	glColor3ub(254, 11, 2);
	circle(25, 500, 320, 40);//head
	glLineWidth(10);
	straight_lines(500, 300, 500, 200);//body
	straight_lines(500, 300, 450, 230);//left hand
	straight_lines(450, 230, 400, 300);

	straight_lines(500, 300, 560, 200);//right hand
	straight_lines(500, 200, 470, 100);//right foot

	straight_lines(500, 200, 510, 100);//left foot  

	//smile
	glColor3ub(233, 200, 11); //gold, the smile
	circle(22, 500, 310, 20);

	glColor3ub(255, 11, 2);//the overlapping circle,red so its invisible
	circle(22, 500, 320, 20);

	glRasterPos3f(400, 360, 0);
	char text2[] = "Ok bye";
	for (int i = 0; i < strlen(text2); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
	}

	//door
	glColor3ub(146, 103, 17);
	rectangle(610, 100, 110, 400);
	glColor3ub(0, 0, 0);
	circle(10, 630, 320, 10);

	//lamp
	glColor4ub(170, 90, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2i(50, 330);
	glVertex2i(150, 330);
	glVertex2i(134, 430);
	glVertex2i(66, 430);
	glEnd();

	glColor3ub(170, 120, 20);
	rectangle(100, 200, 6, 130);

	glColor4ub(245, 241, 188, 67);
	circle(20, 104, 400, 130);


	glColor3ub(255, 255, 255);//boy 
	circle(25, 150, 320, 40);//head
	glLineWidth(10);
	straight_lines(150, 300, 150, 200);//body

	straight_lines(150, 280, 190, 242);
	straight_lines(190, 242, 140, 320);//left hand

	straight_lines(150, 280, 120, 242);
	straight_lines(120, 242, 140, 320);


	straight_lines(150, 200, 120, 100);//right foot
	straight_lines(150, 200, 180, 100);//left foot 


	//knife
	glColor3ub(48, 48, 48);
	//triangles(250, 200, 200, 240, 230, 290);
	triangles(350, 230, 300, 300, 370, 270);

	//knife line
	glLineWidth(5);
	glColor3ub(161, 161, 161);

	straight_lines(350, 230, 300, 300);
	straight_lines(350, 230, 370, 270);
	straight_lines(370, 270, 300, 300);

	glColor3ub(255, 255, 255);
	glRasterPos3f(100, 360, 0);
	char text[] = "Noo ";
	for (int i = 0; i < strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glFlush();
	glutSwapBuffers();
}

//black screen
void display61()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(0, 0, 0);
	rectangle(0, 0, 700, 700);

	glutSwapBuffers();
}

void idle() {
	DWORD start = GetTickCount64();
	while (GetTickCount64() - start < 1000 / FPS);
	x += dx;
	y += dy;
	if (x < 0 || x > SCREEN_WIDTH) dx *= -1;
	if (y < 0 || y > SCREEN_HEIGHT) dy *= -1;
	glutPostRedisplay();
}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glPointSize(10.0);
	glPointSize(10.0);
	glLineWidth(10.0);
}

int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 30);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Test");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutTimerFunc(1000, MyTimerFunc, 0);
	srand(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initGL();
	glutMainLoop();
}

void MyTimerFunc(int value)
{
	if (value == 0)
	{
		glutDisplayFunc(display);
		glutIdleFunc(display);
		glutTimerFunc(1000, MyTimerFunc, 1);
	}

	else if (value == 1)
	{
		glutDisplayFunc(display2);
		glutIdleFunc(display2);
		glutTimerFunc(1000, MyTimerFunc, 2);
	}

	else if (value == 2)
	{
		glutDisplayFunc(display3);
		glutIdleFunc(display3);
		glutTimerFunc(1000, MyTimerFunc, 3);
	}

	else if (value == 3)
	{
		glutDisplayFunc(display4);
		glutIdleFunc(display4);
		glutTimerFunc(1000, MyTimerFunc, 4);
	}

	else if (value == 4)
	{
		glutDisplayFunc(display5);
		glutIdleFunc(display5);
		glutTimerFunc(1000, MyTimerFunc, 5);
	}

	else if (value == 5)
	{
		glutDisplayFunc(display6);
		glutIdleFunc(display6);
		glutTimerFunc(2000, MyTimerFunc, 6);
	}

	else if (value == 6)
	{
		glutDisplayFunc(display7);
		glutIdleFunc(display7);
		glutTimerFunc(1000, MyTimerFunc, 7);
	}


	else if (value == 7)
	{
		glutDisplayFunc(display8);
		glutIdleFunc(display8);
		glutTimerFunc(1000, MyTimerFunc, 8);
	}

	else if (value == 8)
	{
		glutDisplayFunc(display9);
		glutIdleFunc(display9);
		glutTimerFunc(1000, MyTimerFunc, 9);
	}

	else if (value == 9)
	{
		glutDisplayFunc(display10);
		glutIdleFunc(display10);
		glutTimerFunc(1000, MyTimerFunc, 10);
	}


	else if (value == 10)
	{
		glutDisplayFunc(display11);
		glutIdleFunc(display11);
		glutTimerFunc(1000, MyTimerFunc, 11);
	}

	else if (value == 11)
	{
		glutDisplayFunc(display12);
		glutIdleFunc(display12);
		glutTimerFunc(1000, MyTimerFunc, 12);
	}


	else if (value == 12)
	{
		glutDisplayFunc(display13);
		glutIdleFunc(display13);
		glutTimerFunc(1000, MyTimerFunc, 13);
	}

	else if (value == 13)
	{
		glutDisplayFunc(display14);
		glutIdleFunc(display14);
		glutTimerFunc(1000, MyTimerFunc, 14);
	}

	else if (value == 14)
	{
		glutDisplayFunc(display15);
		glutIdleFunc(display15);
		glutTimerFunc(1000, MyTimerFunc, 15);
	}


	else if (value == 15)
	{
		glutDisplayFunc(display16);
		glutIdleFunc(display16);
		glutTimerFunc(1000, MyTimerFunc, 16);
	}

	else if (value == 16)
	{
		glutDisplayFunc(display17);
		glutIdleFunc(display17);
		glutTimerFunc(1000, MyTimerFunc, 17);
	}

	else if (value == 17)
	{
		glutDisplayFunc(display18);
		glutIdleFunc(display18);
		glutTimerFunc(1000, MyTimerFunc, 18);
	}

	else if (value == 18)
	{
		glutDisplayFunc(display19);
		glutIdleFunc(display19);
		glutTimerFunc(1000, MyTimerFunc, 19);
	}

	else if (value == 19)
	{
		glutDisplayFunc(display20);
		glutIdleFunc(display20);
		glutTimerFunc(1000, MyTimerFunc, 20);
	}

	else if (value == 20)
	{
		glutDisplayFunc(display21);
		glutIdleFunc(display21);
		glutTimerFunc(1000, MyTimerFunc, 21);
	}

	else if (value == 21)
	{
		glutDisplayFunc(display22);
		glutIdleFunc(display22);
		glutTimerFunc(1000, MyTimerFunc, 22);
	}

	else if (value == 22)
	{
		glutDisplayFunc(display23);
		glutIdleFunc(display23);
		glutTimerFunc(1000, MyTimerFunc, 23);
	}

	else if (value == 23)
	{
		glutDisplayFunc(display24);
		glutIdleFunc(display24);
		glutTimerFunc(1000, MyTimerFunc, 24);
	}

	else if (value == 24)
	{
		glutDisplayFunc(display25);
		glutIdleFunc(display25);
		glutTimerFunc(1000, MyTimerFunc, 25);
	}

	else if (value == 25)
	{
		glutDisplayFunc(display26);
		glutIdleFunc(display26);
		glutTimerFunc(1000, MyTimerFunc, 26);
	}

	else if (value == 26)
	{
		glutDisplayFunc(display27);
		glutIdleFunc(display27);
		glutTimerFunc(1000, MyTimerFunc, 27);
	}

	else if (value == 27)
	{
		glutDisplayFunc(display28);
		glutIdleFunc(display28);
		glutTimerFunc(1000, MyTimerFunc, 28);
	}

	else if (value == 28)
	{
		glutDisplayFunc(display29);
		glutIdleFunc(display29);
		glutTimerFunc(1000, MyTimerFunc, 29);
	}

	else if (value == 29)
	{
		glutDisplayFunc(display30);
		glutIdleFunc(display30);
		glutTimerFunc(1000, MyTimerFunc, 30);
	}

	else if (value == 30)
	{
		glutDisplayFunc(display31);
		glutIdleFunc(display31);
		glutTimerFunc(1000, MyTimerFunc, 31);
	}

	else if (value == 31)
	{
		glutDisplayFunc(display32);
		glutIdleFunc(display32);
		glutTimerFunc(1000, MyTimerFunc, 32);
	}

	else if (value == 32)
	{
		glutDisplayFunc(display33);
		glutIdleFunc(display33);
		glutTimerFunc(1000, MyTimerFunc, 33);
	}

	else if (value == 33)
	{
		glutDisplayFunc(display34);
		glutIdleFunc(display34);
		glutTimerFunc(1000, MyTimerFunc, 34);
	}

	else if (value == 34)
	{
		glutDisplayFunc(display35);
		glutIdleFunc(display35);
		glutTimerFunc(1000, MyTimerFunc, 35);
	}

	else if (value == 35)
	{
		glutDisplayFunc(display36);
		glutIdleFunc(display36);
		glutTimerFunc(1000, MyTimerFunc, 36);
	}

	else if (value == 36)
	{
		glutDisplayFunc(display37);
		glutIdleFunc(display37);
		glutTimerFunc(1000, MyTimerFunc, 37);
	}

	else if (value == 37)
	{
		glutDisplayFunc(display38);
		glutIdleFunc(display38);
		glutTimerFunc(1000, MyTimerFunc, 38);
	}

	else if (value == 38)
	{
		glutDisplayFunc(display39);
		glutIdleFunc(display39);
		glutTimerFunc(1000, MyTimerFunc, 39);
	}

	else if (value == 39)
	{
		glutDisplayFunc(display40);
		glutIdleFunc(display40);
		glutTimerFunc(1000, MyTimerFunc, 40);
	}

	else if (value == 40)
	{
		glutDisplayFunc(display41);
		glutIdleFunc(display41);
		glutTimerFunc(1000, MyTimerFunc, 41);
	}

	else if (value == 41)
	{
		glutDisplayFunc(display42);
		glutIdleFunc(display42);
		glutTimerFunc(1000, MyTimerFunc, 42);
	}

	else if (value == 42)
	{
		glutDisplayFunc(display43);
		glutIdleFunc(display43);
		glutTimerFunc(1000, MyTimerFunc, 43);
	}

	else if (value == 43)
	{
		glutDisplayFunc(display44);
		glutIdleFunc(display44);
		glutTimerFunc(1000, MyTimerFunc, 44);
	}

	else if (value == 44)
	{
		glutDisplayFunc(display45);
		glutIdleFunc(display45);
		glutTimerFunc(1000, MyTimerFunc, 45);
	}

	else if (value == 45)
	{
		glutDisplayFunc(display46);
		glutIdleFunc(display46);
		glutTimerFunc(1000, MyTimerFunc, 46);
	}

	else if (value == 46)
	{
		glutDisplayFunc(display47);
		glutIdleFunc(display47);
		glutTimerFunc(1000, MyTimerFunc, 47);
	}

	else if (value == 47)
	{
		glutDisplayFunc(display48);
		glutIdleFunc(display48);
		glutTimerFunc(1000, MyTimerFunc, 48);
	}

	else if (value == 48)
	{
		glutDisplayFunc(display49);
		glutIdleFunc(display49);
		glutTimerFunc(3000, MyTimerFunc, 49);
	}

	else if (value == 49)
	{
		glutDisplayFunc(display50);
		glutIdleFunc(display50);
		glutTimerFunc(1000, MyTimerFunc, 50);
	}

	else if (value == 50)
	{
		glutDisplayFunc(display51);
		glutIdleFunc(display51);
		glutTimerFunc(1000, MyTimerFunc, 51);
	}

	else if (value == 51)
	{
		glutDisplayFunc(display52);
		glutIdleFunc(display52);
		glutTimerFunc(1000, MyTimerFunc, 52);
	}

	else if (value == 52)
	{
		glutDisplayFunc(display53);
		glutIdleFunc(display53);
		glutTimerFunc(1000, MyTimerFunc, 53);
	}

	else if (value == 53)
	{
		glutDisplayFunc(display54);
		glutIdleFunc(display54);
		glutTimerFunc(1000, MyTimerFunc, 54);
	}

	else if (value == 54)
	{
		glutDisplayFunc(display55);
		glutIdleFunc(display55);
		glutTimerFunc(1000, MyTimerFunc, 55);
	}

	else if (value == 55)
	{
		glutDisplayFunc(display56);
		glutIdleFunc(display56);
		glutTimerFunc(1000, MyTimerFunc, 56);
	}

	else if (value == 56)
	{
		glutDisplayFunc(display57);
		glutIdleFunc(display57);
		glutTimerFunc(1000, MyTimerFunc, 57);
	}

	else if (value == 57)
	{
		glutDisplayFunc(display58);
		glutIdleFunc(display58);
		glutTimerFunc(1000, MyTimerFunc, 58);
	}

	else if (value == 58)
	{
		glutDisplayFunc(display59);
		glutIdleFunc(display59);
		glutTimerFunc(1000, MyTimerFunc, 59);
	}

	else if (value == 59)
	{
		glutDisplayFunc(display60);
		glutIdleFunc(display60);
		glutTimerFunc(1000, MyTimerFunc, 60);
	}

	else if (value == 60)
	{
		glutDisplayFunc(display61);
		glutIdleFunc(display61);
		glutTimerFunc(1000, MyTimerFunc, 61);
	}
}

