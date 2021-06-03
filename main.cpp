#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL/glut.h>
#include <bits/stdc++.h>
#include "GL/freeglut.h"
#define SORT_NO 2	// Number of sorting algorithms
#define MAX 50		// Number of values in the array
#define SPEED 700	// Speed of sorting, must be greater than MAX always
int a[MAX];			// Array
int swapflag = 0;		// Flag to check if swapping has occured
int i = 0, j = 0;		// To iterate through the array
int flag = 0;			// For Insertion Sort
int k = 0;			// To Switch from Welcome screen to Main Screen
int sorting = 0;		// 1 if Sorted
const char* sort_string[] = { "Insertion Sort","Bubble Sort" };
int sort_count = 0;	// To cycle through the string

// Function to display text on screen char by char
void bitmap_output(int x, int y, const char* string, void* font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

// Function to integer to string
void int_str(int rad, char r[])
{
	_itoa_s(rad, r, 10, 10);
}

void display_text()
{
	glColor3f(0, 1, 0);
	bitmap_output(100, 750, "SIMULATION OF INSERTION AND BUBBLE SORT ALGORITHMS", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();

	// other text small font
	bitmap_output(10, 710, "Made by:", GLUT_BITMAP_9_BY_15);
	glColor3f(1, 1, 0);
	bitmap_output(10, 690, "Mohammed Imran Mohsin ", GLUT_BITMAP_9_BY_15);
	glColor3f(1, 1, 1);
	bitmap_output(150, 690, "( 1RG17CS900 )", GLUT_BITMAP_9_BY_15);
	glColor3f(1, 1, 0);
	bitmap_output(10, 670, "Aayush Singh ", GLUT_BITMAP_9_BY_15);
	glColor3f(1, 1, 1);
	bitmap_output(90, 670, "( 1RG17CS002 )", GLUT_BITMAP_9_BY_15);

	if (sorting == 0)	// if not sorting display menu
	{
		glColor3f(1, 0, 0);
		bitmap_output(10, 565 + 75, "MENU", GLUT_BITMAP_9_BY_15);
		glColor3f(0, 1, 0);
		bitmap_output(10, 545 + 75, "Press s to SORT", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 525 + 75, "Press c to SELECT the sort algorithm", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 505 + 75, "Press r to RANDOMISE", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 485 + 75, "Esc to QUIT", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 465 + 75, "Selected sort: ", GLUT_BITMAP_9_BY_15);
		glColor3f(1, 1, 0);
		bitmap_output(150, 465 + 75, *(sort_string + sort_count), GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)	// while sorting
	{
		bitmap_output(10, 600, "Selected sort: ", GLUT_BITMAP_9_BY_15);
		glColor3f(1, 1, 0);
		bitmap_output(150, 600, *(sort_string + sort_count), GLUT_BITMAP_9_BY_15);
		glColor3f(0.5, 0.5, 0.5);
		bitmap_output(10, 545, "Sorting in progress...", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 525, "Press p to PAUSE", GLUT_BITMAP_9_BY_15);
		glColor3f(0.0, 0.0, 0.0);
	}
}

void front()
{
	glColor3f(0, 1, 0);
	bitmap_output(300, 565, "WELCOME", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();
	bitmap_output(330, 525, "TO", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();
	bitmap_output(100, 475, "SIMULATION OF INSERTION AND BUBBLE SORT ALGORITHMS", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();

	glColor3f(1, 0, 0);
	bitmap_output(300, 350, "Made by:", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1, 1, 0);
	bitmap_output(190, 310, "Mohammed Imran Mohsin ", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1, 1, 1);
	bitmap_output(390, 310, "( 1RG17CS900 )", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1, 1, 0);
	bitmap_output(240, 270, "Aayush Singh ", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1, 1, 1);
	bitmap_output(345, 270, "( 1RG17CS002 )", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1, 0, 0);
	bitmap_output(530, 125, "Press Enter to continue.......", GLUT_BITMAP_HELVETICA_18);

}

void Initialize() {
	int temp1;

	// Reset the array
	for (temp1 = 0; temp1 < MAX; temp1++) {
		a[temp1] = rand() % 100 + 1;
		printf("%d ", a[temp1]);
	}

	// Reset all values
	i = j = 0;
	flag = 0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 699, 0, 799);
}

// Return 1 if not sorted
int notsorted() {
	int q;
	for (q = 0; q < MAX - 1; q++)
	{
		if (a[q] > a[q + 1])
			return 1;
	}
	return 0;
}

// Main function for display
void display()
{
	int ix, temp;
	glClear(GL_COLOR_BUFFER_BIT);

	if (k == 0)
		front();
	else {
		display_text();
		char text[10];

		for (ix = 0; ix < MAX; ix++)
		{
			glColor3f(1, 0, 0);
			glBegin(GL_POLYGON);
			glVertex2f(10 + (700 / (MAX + 1)) * ix, 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 5);
			glVertex2f(10 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 5);
			glEnd();

			glColor3f(1, 1, 0);
			glLineWidth(3);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10 + (700 / (MAX + 1)) * ix, 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 5);
			glVertex2f(10 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 5);
			glEnd();
			glLineWidth(1);

			int_str(a[ix], text);
			glColor3f(0, 1, 0);
			bitmap_output(12 + (700 / (MAX + 1)) * ix, 35, text, GLUT_BITMAP_TIMES_ROMAN_10);
		}

		if (swapflag || sorting == 0)
		{
			glColor3f(0, 1, 0);
			glBegin(GL_POLYGON);
			glVertex2f(10 + (700 / (MAX + 1)) * j, 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (j + 1), 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (j + 1), 50 + a[j] * 4);
			glVertex2f(10 + (700 / (MAX + 1)) * j, 50 + a[j] * 4);
			glEnd();
			swapflag = 0;
		}
	}
	glFlush();
}

// Insertion Sort
void insertionsort()
{
	int temp;

	while (i < MAX)
	{
		if (flag == 0) { j = i; flag = 1; }
		while (j < MAX - 1)
		{
			if (a[j] > a[j + 1])
			{
				swapflag = 1;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;

				goto A;
			}
			j++;
			if (j == MAX - 1) { flag = 0; }
			printf("swap %d and %d\n", a[j], a[j + 1]);
		}
		i++;
	}
	sorting = 0;
	A:i = j = 0;
}

//Bubble Sort
void bubblesort()
{
	int temp;
	while (notsorted())
	{
		while (j < MAX - 1)
		{
			if (a[j] > a[j + 1])
			{
				swapflag = 1;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;

				goto A;
			}
			j++;
			if (j == MAX - 1) j = 0;
			printf("swap %d and %d\n", a[j], a[j + 1]);
		}
	}
	sorting = 0;
A: printf("");
}

// Timer Function, takes care of sort selection
void makedelay(int)
{
	if (sorting)
	{
		switch (sort_count)
		{
		case 0: insertionsort();	break;
		case 1:	bubblesort();		break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED / MAX, makedelay, 1);
}

// Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
	if (key == 13)
		k = 1;
	if (k == 1 && sorting != 1)
	{
		switch (key)
		{
		case 27:	exit(0); // 27 is the ascii code for the ESC key
		case 's':	sorting = 1; break;
		case 'r':	Initialize(); break;
		case 'c':	sort_count = (sort_count + 1) % SORT_NO;	break;
		}
	}
	if (k == 1 && sorting == 1)
		if (key == 'p')	sorting = 0;
}

// Main Function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("SIMULATION OF INSERTION AND BUBBLE SORT ALGORITHMS");
	Initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, makedelay, 1);
	glutMainLoop();
}
