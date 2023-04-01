//////////////////////////////////////////
//										//
//	CPT205 Assignment 1					//
//	Shuchen Yuan						//
//	2036501                             //
//  Instruction: press three times      //
// 'w' or 'W' the card will get 'closer'//
//                                   	//
//	if the card is 'close' enough       //
//  the content of the middle picture   //
//  will 'POP UP!'    		        	//
//////////////////////////////////////////

#define FREEGLUT_STATIC
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#define MAX_CHAR 128
#include "windows.h"
#include <iostream>

//time
// the pseudo-3D frame
void fake_3d_frame();
void draw_the_ceiling();
void draw_the_floor();
void draw_the_left_arrow();
void draw_the_right_arrow();
void combine_the_arrow();

// the welcome door
void draw_the_doorplate_of_the_welcome_door();
void draw_the_left_pillar_of_the_door_in_2D();
void draw_the_left_curtain();
void draw_the_right_pillar_of_the_door_in_2D();
void draw_the_right_curtain();
void draw_the_welcome_door();
void centralized_the_welcome_door();

// the middle picture
  // the background
void frame();
// the castle
void uniRec();
void uniTriangle();
void uniCycle();
void mainpic();
void key_part_tower();
void tower1();
void tower2();
void tower3();
void tower4();
void key_part_tower();
void basebuilding();
// the flags
void flags();
void positionflags();
// the firework
void fire();
void firework();
void positionfirework();

// the font
void selectFont(int size, int charset, const char* face);
void drawString(const char* str);
void draw_the_banners();

// the interaction
void idleDisplay();


GLint scale = 3;
GLint stepx1 = 0;
GLint stepy1 = 0;
GLint width = 800;
GLint height = 450;
int timer = 0;

GLint stepx2 = 1.5; // the exploration distance of the fire work
GLint stepy2 = 1;

int time_interval1 = 80; // declare refresh interval in ms
typedef struct { GLfloat x, y; } point; // define a 2D point

point p0 = { 22.5,43 }; // set initial co-ordinate values of the flagg
point p1 = { 0.0, 0.0 };// set initial co-ordinate values of the firework
GLfloat stepx = 1; // declare incremental step
GLfloat stepy = 1; // declare incremental step
int time_interval = 800; // declare refresh interval in ms

void display(void)
{
    glClearColor(0.29, 0, 0.55, 0.7);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 450);

    glColor3f(0.29, 0, 0.55);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, 450);
    glVertex2f(800, 450);
    glVertex2f(800, 0);
    glEnd();

    glLineWidth(2.0f);
    // enable interaction
    idleDisplay();
    // create the fake-3D frame
    fake_3d_frame();
    //draw the welcome door
    centralized_the_welcome_door();
    // when the card is closest, pop up
    if (scale == 1) {
        draw_the_banners();
        glPushMatrix();
        glTranslated(161, 110, 0.0);
        glScalef(3.0, 1.99, 0.0);
        frame();
        glPopMatrix();
        mainpic();
        positionflags();
        positionfirework();
    }
    glutSwapBuffers();
}

// the fire work
void positionfirework()
{
    // the middle firework
    glPushMatrix();
    glTranslatef(270, 200, 0.0); // move the position of the origin
    glScalef(0.3, 0.3, 0.0);
    firework();
    glPopMatrix();

    // the second left firework
    glPushMatrix();
    glTranslatef(160, 160, 0.0); // move the position of the origin
    glScalef(0.3, 0.3, 0.0);
    firework();
    glPopMatrix();

    // the third right
    glPushMatrix();
    glTranslatef(400, 180, 0.0); // move the position of the origin
    glScalef(0.3, 0.3, 0.0);
    firework();
    glPopMatrix();

    // the third left 
    glPushMatrix();
    glTranslatef(260, 250, 0.0); // move the position of the origin
    glScalef(0.1, 0.1, 0.0);
    firework();
    glPopMatrix();

    // the rightmost
    glPushMatrix();
    glTranslatef(175, 130, 0.0); // move the position of the origin
    glScalef(0.2, 0.2, 0.0);
    firework();
    glPopMatrix();

    // the leftmost
    glPushMatrix();
    glTranslatef(460, 140, 0.0); // move the position of the origin
    glScalef(0.25, 0.25, 0.0);
    firework();
    glPopMatrix();

    // the second right
    glPushMatrix();
    glTranslatef(480, 145, 0.0); // move the position of the origin
    glScalef(0.1, 0.1, 0.0);
    firework();
    glPopMatrix();
}

void firework() {
    int n = 0;
    // for -> shape then one of the 'for' shape do the moving is ok
    for (int i = 0; i <= 12; i++) {
        glPushMatrix();
        glTranslatef(400, 225, 0.0); // move the position of the origin
        glRotatef(i * 30, 0.0, 0.0, 1);
        fire();
        glPopMatrix();
    }
}

void fire()
{
    // the frame of the fire
    glColor3f(0.29, 0.55, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p1.x + 43, p1.y + 5);
    glVertex2f(p1.x + 63, p1.y + 0);
    glVertex2f(p1.x + 47, p1.y - 5);
    glVertex2f(p1.x, p1.y);
    glEnd();
    // coloring it
    glColor3f(1.0, 0.72, 0.75);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.72, 0.75);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p1.x + 43, p1.y + 5);
    glVertex2f(p1.x + 63, p1.y + 0);
    glVertex2f(p1.x + 47, p1.y - 5);
    glEnd();
}

// control the movement of the firework
void OnTimer1(int value)
{
    p1.y += stepy2;
    p1.x += stepx2;
    if (p1.x >= 17 || p1.y >= 20) {
        p1.x = 0;
        p1.y = 0;
    }
    glutTimerFunc(time_interval1, OnTimer1, 1);
}

// the castle
void uniRec()
{
    // the frame
    glColor3f(0.29, 0.55, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();
    // coloring
    glColor3f(1.0, 0.72, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glEnd();
}

void uniTriangle()
{
    // the frame
    glColor3f(0.29, 0.55, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glVertex2f(2, 0);
    glVertex2f(0, 0);
    glEnd();
    // coloring
    glColor3f(1.0, 0.71, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glVertex2f(2, 0);
    glVertex2f(0, 0);
    glEnd();
}

void uniCycle() {
    glClearColor(1.0, 1.0, 0.7, 0.7);
    glBegin(GL_LINE_STRIP);
    const int n = 100;
    const GLfloat R = 1.0f;
    const GLfloat Pi = 3.1415926536f;
    int i;
    for (i = 0; i < 51; ++i)
        glVertex2f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i));
    glEnd();
}

void fulluniCycle() {
    glClearColor(1.0, 1.0, 0.7, 0.7);
    glBegin(GL_LINE_STRIP);
    const int n = 100;
    const GLfloat R = 1.0f;
    const GLfloat Pi = 3.1415926536f;
    int i;
    for (i = 0; i < n; ++i)
        glVertex2f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i));
    glEnd();
}

void tower1() {
    // A hexagon + a rectangle + a triangle 

    //  the hexagon
    glColor3f(0.29, 0.55, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(17, 24);
    glVertex2f(20, 20);
    glVertex2f(20, 0);
    glVertex2f(25, 0);
    glVertex2f(25, 20);
    glVertex2f(28, 24);
    glVertex2f(17, 24);
    glEnd();

    // coloring it 
    glColor3f(1.0, 0.75, 0.72);
    glBegin(GL_POLYGON);
    glVertex2f(17, 24);
    glVertex2f(20, 20);
    glVertex2f(25, 20);
    glVertex2f(28, 24);
    glEnd();

    glColor3f(1.0, 0.75, 0.72);
    glBegin(GL_POLYGON);
    glVertex2f(20, 20);
    glVertex2f(25, 20);
    glVertex2f(25, 0);
    glVertex2f(20, 0);
    glEnd();

    // rectangle
    glPushMatrix();
    glTranslatef(21, 24, 0);
    glScalef(3.0, 8.0, 0.0);
    uniRec();
    glPopMatrix();
    // triangle
    glPushMatrix();
    glTranslatef(20.5, 32, 0);
    glScalef(2.0, 7.0, 0.0);
    uniTriangle();
    glPopMatrix();
}

void key_part_tower()
{
    // the down rectangle
    glColor3f(0.29, 0.55, 1.0);
    glPushMatrix();
    glTranslatef(16, 265, 0);
    glScalef(7, 30, 0.0);
    uniRec();
    glPopMatrix();

    // inverted trapezoid
    glColor3f(0.29, 0.55, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(11, 300);
    glVertex2f(28, 300);
    glVertex2f(23, 295);
    glVertex2f(16, 295);
    glVertex2f(11, 300);
    glEnd();
    // Orthotrapezoid, symmetric at y = 302.5 with the inverted trapezoid 
    glBegin(GL_LINE_STRIP);
    glVertex2f(11, 305);
    glVertex2f(28, 305);
    glVertex2f(23, 310);
    glVertex2f(16, 310);
    glVertex2f(11, 305);
    glEnd();
    // Rectangle
    glPushMatrix();
    glTranslatef(11, 300, 0);
    glScalef(17, 5, 0.0);
    uniRec();
    glPopMatrix();
}

void tower2()
{
    key_part_tower();
    // spire
    glPushMatrix();
    glTranslatef(16, 310, 0);
    glScalef(3.5, 14.0, 0.0);
    uniTriangle();
    glPopMatrix();
}

void tower3()
{
    tower2();
    glPushMatrix();
    glTranslatef(0, -45, 0);
    glScalef(1.0, 1.0, 0.0);
    key_part_tower();
    glPopMatrix();
}

void tower4()
{
    tower3();
    glPushMatrix();
    glTranslatef(0, -90, 0);
    glScalef(1.0, 1.0, 0.0);
    key_part_tower();
    glPopMatrix();
}

void basebuilding() {
    // Door (circle) + Rectangle + Rectangle + Triangle + circle(clock)

    // Rectangle
    glPushMatrix();
    glTranslatef(340, 225, 0);
    glScalef(190, 70.0, 0.0);
    uniRec();
    glPopMatrix();

    // Rectangle
    glPushMatrix();
    glTranslatef(420, 295, 0);
    glScalef(30, 30.0, 0.0);
    uniRec();
    glPopMatrix();

    // window
    glPushMatrix();
    glTranslatef(360, 250, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(360, 270, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(380, 250, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(380, 270, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400, 250, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400, 270, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(460, 270, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(460, 250, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(480, 270, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(480, 250, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(500, 270, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(500, 250, 0);
    glScalef(10, 10, 0.0);
    uniRec();
    glPopMatrix();
    // door
    glColor3f(0.29, 0.55, 1.0);
    glPushMatrix();
    glTranslatef(435, 225, 0);
    glScalef(10, 40.0, 0.0);
    uniCycle();
    glPopMatrix();
    // clock
    glColor3f(0.29, 0.55, 1.0);
    glPushMatrix();
    glTranslatef(434, 310, 0);
    glScalef(10, 10, 0.0);
    fulluniCycle();
    glPopMatrix();

    glBegin(GL_LINE_STRIP); //  Hour hand
    glVertex2f(434.5, 307);
    glVertex2f(434.5, 314);
    glEnd();

    glBegin(GL_LINE_STRIP);// Minute hand
    glVertex2f(434.5, 307);
    glVertex2f(434.5, 312);
    glEnd();

    // triangle
    glPushMatrix();
    glTranslatef(424, 325, 0);
    glScalef(10, 28, 0.0);
    uniTriangle();
    glPopMatrix();
}

void flags() {
    // three triangles 
    // flags
    glColor4f(0.0, 0.0, 0.0, 0.7);
    glBegin(GL_LINE_STRIP);
    glVertex2f(p0.x, p0.y + 7);
    glVertex2f(p0.x + 9.5, p0.y + 3.5);
    glVertex2f(p0.x, p0.y);
    glVertex2f(p0.x, p0.y + 7);
    glEnd();

    glColor4f(1.0, 0.0, 0.0, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(p0.x, p0.y);
    glVertex2f(p0.x + 9.5, p0.y + 3.5);
    glVertex2f(p0.x, p0.y + 7);
    glVertex2f(p0.x, p0.y);
    glEnd();

    // flaghole
    glColor4f(0.0, 0.0, 0.0, 0.7);
    glBegin(GL_LINE_STRIP);
    glVertex2f(22.5, 37);
    glVertex2f(22.5, 57);
    glEnd();
}

void positionflags() {

    // the middle flag
    glPushMatrix();
    glTranslatef(399, 220, 0.0);
    glScalef(2.0, 1.0, 0.0);
    flags();
    glPopMatrix();
    // the right flag
    glPushMatrix();
    glTranslatef(425, 150, 0.0);
    glScalef(2.0, 2.0, 0.0);
    flags();
    glPopMatrix();
    // the left flag
    glPushMatrix();
    glTranslatef(281.75, 150, 0.0);
    glScalef(2.0, 2.0, 0.0);
    flags();
    glPopMatrix();
}

void mainpic()
{
    // the third left tower
    glPushMatrix();
    glTranslatef(360, 25.5, 0);
    glScalef(0.7, 0.7, 0.0);
    tower3();
    glPopMatrix();

    // the basebuilding
    glPushMatrix();
    glTranslatef(94, -27, 0);
    glScalef(0.7, 0.7, 0.0);
    basebuilding();
    glPopMatrix();

    // the peak
    glPushMatrix();
    glTranslatef(410, 58, 0.0);
    glScalef(0.7, 0.7, 0.0);
    tower4();
    glPopMatrix();

    //// most left tower
    glPushMatrix();
    glTranslatef(282, 130, 0);
    glScalef(2.0, 2.4, 0.0);
    tower1();
    glPopMatrix();

    // the most right tower
    glPushMatrix();
    glTranslatef(425, 130, 0);
    glScalef(2.0, 2.4, 0.0);
    tower1();
    glPopMatrix();

    // the second right tower
    glPushMatrix();
    glTranslatef(390, 181, 0);
    glScalef(2.4, 2.0, 0.0);
    tower1();
    glPopMatrix();

    // second left tower
    glPushMatrix();
    glTranslatef(340, -5, 0);
    glScalef(0.7, 0.7, 0.0);
    tower2();
    glPopMatrix();
}


// the welcome door ↓
// checked
void centralized_the_welcome_door() {
    glPushMatrix();
    glTranslated(161, 110, 0.0);
    glScalef(3.0, 1.99, 0.0);
    draw_the_welcome_door();
    glPopMatrix();
}

void draw_the_welcome_door() {
    draw_the_doorplate_of_the_welcome_door();
    draw_the_left_pillar_of_the_door_in_2D();
    draw_the_right_pillar_of_the_door_in_2D();
}

void draw_the_doorplate_of_the_welcome_door(void) {
    // draw a rectangle
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 90);
    glVertex2f(0, 120);
    glVertex2f(160, 120);
    glVertex2f(160, 90);
    glVertex2f(0, 90);
    glEnd();

}

void draw_the_left_pillar_of_the_door_in_2D(void) {
    // a pentagon with the curtain on the top
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 90);
    glVertex2f(0, 0);
    glVertex2f(20, 0);
    glVertex2f(20, 60);
    glVertex2f(30, 90);
    glEnd();
    draw_the_left_curtain();
}

void draw_the_right_pillar_of_the_door_in_2D(void) {

    // a pentagon with the curtain on the top
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(160, 90);
    glVertex2f(160, 0);
    glVertex2f(140, 0);
    glVertex2f(140, 60);
    glVertex2f(130, 90);
    glEnd();
    draw_the_right_curtain();

}

void draw_the_left_curtain() {

    // the color of the upper part
    glBegin(GL_POLYGON);
    glColor3f(0.29, 0.55, 0.7);
    glVertex2f(1, 90);
    glColor3f(0.29, 0.55, 0.7);
    glVertex2f(27, 90);
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(15, 65);
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(3, 65);
    glEnd();

    // upper part of the curtain  (4 lines)
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);

    glVertex2f(1, 90);
    glVertex2f(3, 65);

    glVertex2f(14, 90);
    glVertex2f(7, 65);

    glVertex2f(21, 90);
    glVertex2f(11, 65);

    glVertex2f(27, 90);
    glVertex2f(15, 65);

    glEnd();

    // the color of the Lanyard of the curtain
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);

    glVertex2f(3, 65);

    glVertex2f(15, 65);

    glVertex2f(15, 60);

    glVertex2f(3, 60);
    glEnd();

    // draw the frame of the Lanyard

    glLineWidth(2.0f);

    glColor4f(0.49, 0.98, 0.0, 0.7);

    glBegin(GL_LINE_STRIP);

    glVertex2f(3, 65);
    glVertex2f(15, 65);
    glVertex2f(15, 60);
    glVertex2f(3, 60);
    glVertex2f(3, 65);

    glEnd();

    // the color of the down part

    glBegin(GL_POLYGON);
    glColor3f(0.49, 0.98, 0.0);

    glVertex2f(3, 60);
    glVertex2f(15, 60);

    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(15, 20);

    glVertex2f(7, 15);
    glVertex2f(11, 15);
    glVertex2f(3, 20);

    glEnd();

    // draw the down part of the curtain
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);

    glVertex2f(3, 60);
    glVertex2f(3, 20);

    glVertex2f(7, 15);
    glVertex2f(7, 60);
    glVertex2f(7, 15);

    glVertex2f(11, 15);
    glVertex2f(11, 60);
    glVertex2f(11, 15);

    glVertex2f(15, 20);
    glVertex2f(15, 60);

    glEnd();
}

void draw_the_right_curtain() {

    // the color of the upper part
    glBegin(GL_POLYGON);
    glColor3f(0.29, 0.55, 0.7);
    glVertex2f(159, 90);
    glColor3f(0.29, 0.55, 0.7);
    glVertex2f(133, 90);
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(145, 65);
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(157, 65);
    glEnd();

    glColor3f(1.0, 0.0, 1.0);
    // symmetric with the left part at x = 400
    glBegin(GL_LINES);
    // upper part of the curtain  (4 lines)
    glVertex2f(159, 90);
    glVertex2f(157, 65);

    glVertex2f(146, 90);
    glVertex2f(153, 65);

    glVertex2f(139, 90);
    glVertex2f(149, 65);

    glVertex2f(133, 90);
    glVertex2f(145, 65);

    glEnd();
    // draw the Lanyard of the curtainm
    glBegin(GL_POLYGON);

    glVertex2f(157, 65);

    glVertex2f(145, 65);

    glVertex2f(145, 60);

    glVertex2f(157, 60);
    glEnd();

    // draw the frame of it

    glLineWidth(1.7f);
    glColor4f(0.49, 0.98, 0.0, 0.7);

    glBegin(GL_LINE_STRIP);

    glVertex2f(157, 65);

    glVertex2f(145, 65);

    glVertex2f(145, 60);

    glVertex2f(157, 60);

    glVertex2f(157, 65);
    glEnd();

    // the color of the down part

    glBegin(GL_POLYGON);
    glColor3f(0.49, 0.98, 0.0);

    glVertex2f(157, 60);
    glVertex2f(145, 60);

    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(145, 20);

    glVertex2f(153, 15);
    glVertex2f(149, 15);
    glVertex2f(157, 20);

    glEnd();

    // draw the down part of the curtain
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(157, 60);
    glVertex2f(157, 20);

    glVertex2f(153, 15);
    glVertex2f(153, 60);
    glVertex2f(153, 15);

    glVertex2f(149, 15);
    glVertex2f(149, 60);
    glVertex2f(149, 15);

    glVertex2f(145, 20);
    glVertex2f(145, 60);

    glEnd();

}
// the welcom door ↑

// checked
void frame() {

    // fill the color
    glColor3f(1.0, 0.55, 0.0);
    //glColor3f(0.0 , 0.0 , 0.52);
    glBegin(GL_POLYGON);
    glVertex2f(20, 4.52);
    glVertex2f(20, 60);
    glVertex2f(30, 90);
    glVertex2f(130, 90);
    glVertex2f(140, 60);
    glVertex2f(140, 4.52);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 4.52);
    glVertex2f(29.7, 4.52);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(140, 0);
    glVertex2f(140, 4.52);
    glVertex2f(130.3, 4.52);

    glEnd();
}

// the pseudo-3D frame ↓
// checked
void fake_3d_frame() {
    // draw and adjust the ceiling and the floor 
    glColor3f(1.0, 0.0, 1.0);

    glPushMatrix();
    glScalef(1.0, 0.7, 0.0);
    draw_the_floor();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, 1.202, 0.0);
    draw_the_ceiling();
    glPopMatrix();
    // adjust the arrow on the side
    glPushMatrix();
    /*glScalef(1.0, 1.2, 0.0);*/
    glTranslatef(-60, 10, 0);
    combine_the_arrow();
    glPopMatrix();
}
// checked
void draw_the_ceiling() {
    glColor3f(1.0, 0.0, 1.0);
    // the left part
    glBegin(GL_LINE_STRIP);
    glVertex2f(60, 370);
    glVertex2f(250, 290); // l1
    glVertex2f(280, 290);
    glVertex2f(255, 370);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(60, 370);
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(250, 290); // l1
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(280, 290);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(255, 370);
    glEnd();
    // the right part (symmetric at x = 400) 
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(740, 370);
    glVertex2f(550, 290);
    glVertex2f(520, 290);
    glVertex2f(545, 370);
    glEnd();
    // coloring it 
    glBegin(GL_POLYGON);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(740, 370);
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(550, 290); // l1
    glColor3f(0.49, 0.98, 0.0);
    glVertex2f(520, 290);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(545, 370);
    glEnd();
}
// checked
void draw_the_floor() {
    // the left part
    glBegin(GL_LINES);
    glVertex2f(250, 170); // set the upper bound
    glVertex2f(60, 70); // Ð±ÂÊ

    glVertex2f(255, 170);
    glVertex2f(60, 40); // set the down bound

    glVertex2f(285, 170);
    glVertex2f(230, 40);

    glVertex2f(292, 170);
    glVertex2f(245, 40);

    glEnd();
    // coloring 
    glBegin(GL_POLYGON);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(255, 170);

    glColor3f(0.49, 0.98, 0);
    glVertex2f(285, 170);

    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(230, 40);

    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(60, 40);

    glEnd();
    //the right part (symmetric at x = 400)
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(550, 170); // set the upper bound
    glVertex2f(740, 70);

    glVertex2f(545, 170);
    glVertex2f(740, 40); // set the down bound

    glVertex2f(515, 170);
    glVertex2f(570, 40);

    glVertex2f(508, 170);
    glVertex2f(555, 40);
    glEnd();

    // coloring 
    glBegin(GL_POLYGON);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(545, 170);

    glColor3f(0.49, 0.98, 0);
    glVertex2f(515, 170);

    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(570, 40);

    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(740, 40);

    glEnd();
}
// checked
void draw_the_right_arrow() {
    // the left part 
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(800, 40);
    glVertex2f(800, 70);
    glVertex2f(787, 67);
    glVertex2f(787, 87);
    glVertex2f(770, 55);
    glVertex2f(787, 23);
    glVertex2f(787, 43);
    glVertex2f(800, 40);
    glEnd();
    // coloring it
    glBegin(GL_POLYGON);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(800, 40);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(800, 70);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(787, 67);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(787, 43);
    glEnd();

    glColor3f(0.49, 0.98, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(787, 87);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(770, 55);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(787, 23);
    glEnd();

}
// checked
void draw_the_left_arrow() {
    // the left part 
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 40);
    glVertex2f(0, 70);
    glVertex2f(13, 67);
    glVertex2f(13, 87);
    glVertex2f(30, 55);
    glVertex2f(13, 23);
    glVertex2f(13, 43);
    glVertex2f(0, 40);
    glEnd();
    // coloring it
    glBegin(GL_POLYGON);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(0, 40);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(0, 70);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(13, 67);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(13, 43);
    glEnd();

    glColor3f(0.49, 0.98, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(13, 87);
    glColor3f(0.49, 0.98, 0);
    glVertex2f(30, 55);
    glColor3f(0.29, 0.0, 0.55);
    glVertex2f(13, 23);
    glEnd();

}
// checked
void combine_the_arrow() {
    // firstly draw the inner arrow
    glPushMatrix();
    glTranslated(180, 170, 0.0);
    draw_the_left_arrow();
    glPopMatrix();
    // Then draw the outter arrow with the scale function
    glPushMatrix();
    glTranslated(80, 135, 0.0);
    glScalef(1.7, 1.7, 0);
    draw_the_left_arrow();
    glPopMatrix();

    glPointSize(7);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 1.0);
    // the left points
    glVertex2f(143, 227);
    glVertex2f(154, 227);
    glVertex2f(165, 227);

    // the right points 
    glVertex2f(777, 227);
    glVertex2f(766, 227);
    glVertex2f(755, 227);
    glEnd();

    glPushMatrix();
    glTranslatef(-60, 170.0, 0.0);
    draw_the_right_arrow();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-520.0, 135, 0.0);
    glScalef(1.7, 1.7, 0.0);
    draw_the_right_arrow();
    glPopMatrix();


}
// the pseudo-3D frame ↑

// draw the words
void draw_the_banners() {
    glColor3f(0.49, 0.98, 0.0);
    selectFont(27, ANSI_CHARSET, "Constantia");
    glRasterPos2f(300.0, 400.0);
    drawString("Happy New Year 2023!");
    selectFont(25, ANSI_CHARSET, "New Time Roma");
    glRasterPos2f(320.0, 310.0);
    drawString("Welcome to 2023!");
}
void drawString(const char* str) {
    int isFirstCall = 1;
    GLuint lists;
    if (isFirstCall) {
        isFirstCall = 0;
        lists = glGenLists(MAX_CHAR);
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    for (; *str != '\0'; ++str) {
        glCallList(lists + *str);
    }
}
void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

// control the movement of the flags
void OnTimer(int value)
{
    p0.y += stepy;
    if (p0.y >= 50)
        p0.y = 43;
    glutTimerFunc(time_interval, OnTimer, 1);
}
// interaction
void idleDisplay() {
    if (scale == 0)
        scale = 1;
    glViewport(stepx1, stepy1, width / scale, height / scale);
    glutPostRedisplay();

    if (scale == 2)
        glViewport(200, 125, width / scale, height / scale);
    glutPostRedisplay();

    if (scale == 3)
        glViewport(266.5, 160, width / scale, height / scale);
    glutPostRedisplay();

    if (scale > 3)
        glViewport(266.5, 160, width / 3, height / 3);
    glutPostRedisplay();

    if (scale < 1)
        glViewport(266.5, 120, width / scale, height / scale);
    glutPostRedisplay();
}
void keyboard_input(unsigned char key, int x, int y) // keyboard interactions
{
    if (key == 'q' || key == 'Q')
        exit(0);
    else if (key == 'j' || key == 'J') // move the viewport to the left
        stepx1--;
    else if (key == 'i' || key == 'I') // move the viewport up
        stepy1++;
    else if (key == 'l' || key == 'L') // move the viewport to the right
        stepx1++;
    else if (key == 'k' || key == 'K') // move the viewport down
        stepy1--;
    else if (key == 'w' || key == 'W') // make the card get 'near'
        scale--;
    else if (key == 's' || key == 'S') // make the card get 'far'
        scale++;
}

void when_in_mainloop()
{ // idle callback function
    glutPostRedisplay(); // force OpenGL to redraw the current window
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    // choose the display mode, we choose double depth and RGBA for animation and RGBA display
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    //initialized the position of the display window (centralized)
    int cx = glutGet(GLUT_SCREEN_WIDTH);
    int cy = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((cx - 800) / 2, (cy - 450) / 2);
    glutInitWindowSize(800, 450);
    glutCreateWindow("Happy New Year 2023!");
    // init(); // setting the back ground colour
    glutDisplayFunc(display);
    glutIdleFunc(when_in_mainloop);
    glutTimerFunc(time_interval, OnTimer, 1);
    glutTimerFunc(time_interval1, OnTimer1, 1);
    glutKeyboardFunc(keyboard_input); // keyboard callback function
    //glutMouseFunc(mouse_input);
    glutMainLoop();
    return 0;
}