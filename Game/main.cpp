//
//  main.cpp
//  Asteroids
//
//  Created by Alexander Sukharev on 15.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#include "Common.h"

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Asteroids!");
	
	window_height = glutGet(GLUT_WINDOW_HEIGHT);
	window_width = glutGet(GLUT_WINDOW_WIDTH);
	
	callbacks();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
/*	gluPerspective(70.0, 1.0, 1.0, 40.0); */
	glOrtho(-5.0, 5.0, -5.0, 5.0, 1.0, 40.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	
	glShadeModel(GL_SMOOTH);
	
	glClearDepth(1.0);
	glClearColor(0.1, 0.1, 0.1, 0.1);
	glEnable(GL_DEPTH_TEST);
	
	glLineWidth(1.3);
	
	initLighting();
	
	scene = new Title();

	glutMainLoop();
}
