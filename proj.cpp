#include <string>
#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <stdio.h>
#include <vector>

using namespace std;

vector <string> INPUT = {""};
int lineHeight = 24;
int lineNumber = 0;

void typingText() {
	glPointSize(1);		// change point size back to 1

	glColor3f(0, 0, 1);
	if ((INPUT[lineNumber].length() % 50 == 0 && INPUT[lineNumber].length() != 0) || lineNumber == 0) {
		//if statement characters in line does not = 0; each line is 50 characters, or line number is 0;
		lineNumber++;
		INPUT.push_back("");
	}

	for (int h = 0; h <= lineNumber; h++){
		glRasterPos2i(0, 600 - (lineHeight * h));
		for (int i = 0; i < INPUT[h].length(); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, INPUT[h][i]);
		}
	}
}

void myInit()
{
	glClearColor(0, 0, 0, 0);			// specify a background clor: white 
	  // specify a viewing area
	gluOrtho2D(0, 600, 0, 600);
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	typingText();
	glFlush(); // flush out the buffer contents
}

//***********************************************************************************

void type(unsigned char key, int x, int y){
	if (key == 13){
		lineNumber++;
		INPUT.push_back("");
	}
	else if (key == 8){
		if (INPUT[lineNumber].length() == 0 && lineNumber != 1){
				lineNumber--;
				INPUT.pop_back();
		}
		else if (INPUT[lineNumber].length() == 0 && lineNumber == 1){
			cout << "System Sound\n";
		}
		else {
			INPUT[lineNumber].pop_back();
			//if none of the other conditions are met, 
			//then pop the last char and continue. 
		}
	}
	else {
		INPUT[lineNumber] += key;
	}
	
	glutPostRedisplay();
}

void menuFunctions(int option){
	cout << INPUT.size() - 1 << endl;
}

void main()
{
	glutInitWindowSize(600, 650);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Text Writing");	// create a titled window

	int mainMenu = glutCreateMenu(menuFunctions);
	glutAddMenuEntry("Get Size", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	myInit();									// setting up
	glutKeyboardFunc(type);
	glutDisplayFunc(myDisplayCallback);		// register a callback

	glutMainLoop();							// get into an infinite loop
}