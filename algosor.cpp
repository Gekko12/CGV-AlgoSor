#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/gl.h>

using namespace std;

#define SORT_NO 2		// Number of sorting algorithms
#define MAX_SIZE 30 // Number of values in the array
#define SPEED 2000	// High val means slow

int a[MAX_SIZE];
int swapflag = 0; // Flag to check if swapping has occured
int i = 0, j = 0;
int flag = 0;
int k = 0;			 // To Switch from Welcome screen to Main Screen
int sorting = 0; // 1 if Sorted
const char *sort_string[] = {"Insertion Sort", "Bubble Sort"};
int sort_count = 0; // To cycle through the string
int esc_key = 0;
unsigned int speed_strength = 5; //sorting_speed = SPEED/speed_strength ....

// Function to display text on screen char by char
void bitmap_output(int x, int y, const char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;
	while (start < end)
	{
		swap(*(str + start), *(str + end));
		start++;
		end--;
	}
}

// Implementation of itoa()
char *itoa(int num, char *str, int base)
{
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled only with
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	// If number is negative, append '-'
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);

	return str;
}

// Function to integer to string
void int_str(int rad, char r[])
{
	itoa(rad, r, 10);
}

void display_text()
{
	glColor3f(0, 0, 1);
	bitmap_output(170, 750, "SIMULATION OF INSERTION AND BUBBLE SORT ALGORITHMS", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();

	glColor3f(1, 0.2, 1);
	glBegin(GL_POLYGON);
	glVertex2i(150, 740);
	glVertex2i(560, 740);
	glVertex2i(560, 735);
	glVertex2i(150, 735);
	glEnd();

	if (sorting == 0) // if not sorting display menu
	{
		glColor3f(1, 0, 0);
		bitmap_output(10, 700, "MENU", GLUT_BITMAP_9_BY_15);
		glColor3f(0, 0, 0);
		bitmap_output(10, 670, "Press s to SORT", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 650, "Press c to SELECT the sort algorithm", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 630, "Press r to RANDOMISE", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 610, "Esc to QUIT", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 590, "Selected sort: ", GLUT_BITMAP_9_BY_15);
		glColor3f(1, 0, 1);
		bitmap_output(80, 590, *(sort_string + sort_count), GLUT_BITMAP_9_BY_15);
		glColor3f(0, 0, 0);
		bitmap_output(10, 570, "Speed l(low) and h(high): ", GLUT_BITMAP_9_BY_15);
		glColor3f(1, 0, 1);
		char text[10];
		int_str(speed_strength, text);
		bitmap_output(130, 570, text, GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1) // while sorting
	{
		glColor3f(0, 0, 0);
		bitmap_output(10, 690, "Selected sort: ", GLUT_BITMAP_9_BY_15);
		glColor3f(1, 0, 1);
		bitmap_output(80, 690, *(sort_string + sort_count), GLUT_BITMAP_9_BY_15);
		glColor3f(0.5, 0.5, 0.5);
		bitmap_output(10, 650, "Sorting in progress...", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 630, "Press p to PAUSE", GLUT_BITMAP_9_BY_15);
		glColor3f(0.0, 0.0, 0.0);
	}
}

void front()
{
	glColor3f(0, 0, 1);
	bitmap_output(318, 470, "WELCOME", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();
	bitmap_output(340, 430, "TO", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();
	bitmap_output(165, 390, "SIMULATION OF INSERTION AND BUBBLE SORT ALGORITHMS", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();

	glColor3f(1, 0, 1);
	bitmap_output(550, 17, "Press Enter to continue.......", GLUT_BITMAP_HELVETICA_18);
}

void Contributors()
{
	glColor3f(1, 0.2, 1);
	glBegin(GL_POLYGON);
	glVertex2i(200, 540);
	glVertex2i(500, 540);
	glVertex2i(500, 580);
	glVertex2i(200, 580);
	glEnd();

	glColor3f(0, 0, 0.5);
	bitmap_output(320, 470, "Made by -", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();

	glColor3f(0, 0, 1);
	bitmap_output(280, 430, "Gaurav Sharma (1AT18CS128)", GLUT_BITMAP_HELVETICA_18);
	glEnd();

	bitmap_output(280, 390, "Sumukha Hegde (1AT18CS129)", GLUT_BITMAP_HELVETICA_18);
	glEnd();

	glColor3f(1, 0.2, 1);
	glBegin(GL_POLYGON);
	glVertex2i(200, 320);
	glVertex2i(500, 320);
	glVertex2i(500, 280);
	glVertex2i(200, 280);
	glEnd();

	glutTimerFunc(SPEED * 2, exit, 0);
}

void Initialize()
{
	int temp1;

	// Reset the array
	for (temp1 = 0; temp1 < MAX_SIZE; temp1++)
	{
		a[temp1] = rand() % 100 + 1;
		// printf("%d ", a[temp1]);
	}

	// Reset all values
	i = j = 0;
	flag = 0;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 699, 0, 799);
}

// Return 1 if not sorted
int notsorted()
{
	int q;
	for (q = 0; q < MAX_SIZE - 1; q++)
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
	else if (k == 1 && !esc_key)
	{
		display_text();
		char text[10];

		for (ix = 0; ix < MAX_SIZE; ix++)
		{
			glColor3f(1, 0, 0);
			glBegin(GL_POLYGON);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * ix, 50);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * (ix + 1), 50);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * (ix + 1), 50 + a[ix] * 5);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * ix, 50 + a[ix] * 5);
			glEnd();

			glColor3f(1, 1, 0);
			glLineWidth(3);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * ix, 50);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * (ix + 1), 50);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * (ix + 1), 50 + a[ix] * 5);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * ix, 50 + a[ix] * 5);
			glEnd();
			glLineWidth(1);

			int_str(a[ix], text);
			glColor3f(1, 0, 1);
			bitmap_output(12 + (700 / (MAX_SIZE + 1)) * ix, 30, text, GLUT_BITMAP_HELVETICA_12);
		}

		if (swapflag || sorting == 0)
		{
			glColor3f(1, 1, 0);
			glBegin(GL_POLYGON);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * j, 50);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * (j + 1), 50);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * (j + 1), 50 + a[j] * 5);
			glVertex2f(10 + (700 / (MAX_SIZE + 1)) * j, 50 + a[j] * 5);
			glEnd();
			swapflag = 0;
		}
	}
	else
		Contributors();

	glFlush();
}

// Insertion Sort
void insertionsort()
{
	int temp;

	while (i < MAX_SIZE)
	{
		if (flag == 0)
		{
			j = i;
			flag = 1;
		}
		while (j < MAX_SIZE - 1)
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
			if (j == MAX_SIZE - 1)
			{
				flag = 0;
			}
			// printf("swap %d and %d\n", a[j], a[j + 1]);
		}
		i++;
	}
	sorting = 0;
A:
	i = j = 0;
}

//Bubble Sort
void bubblesort()
{
	int temp;
	while (notsorted())
	{
		while (j < MAX_SIZE - 1)
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
			if (j == MAX_SIZE - 1)
				j = 0;
			// printf("swap %d and %d\n", a[j], a[j + 1]);
		}
	}
	sorting = 0;
A:;
}

// Timer Function, takes care of sort selection
void makedelay(int)
{
	if (sorting)
	{
		switch (sort_count)
		{
		case 0:
			insertionsort();
			break;
		case 1:
			bubblesort();
			break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED / speed_strength, makedelay, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 13)
		k = 1;
	if (k == 1 && sorting != 1)
	{
		switch (key)
		{
		case 27:
			esc_key = 1;
			Contributors();
			break;
			// exit(0); // 27 is the ascii code for the ESC key
		case 's':
			sorting = 1;
			break;
		case 'r':
			Initialize();
			break;
		case 'c':
			sort_count = (sort_count + 1) % SORT_NO;
			break;
		case 'h':
			speed_strength++;
			break;
		case 'l':
			if (speed_strength > 1)
				speed_strength--;
			break;
		}
	}
	if (k == 1 && sorting == 1)
		if (key == 'p')
			sorting = 0;
}

// Main Function
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("AlgoSor - Sorting Algorithm Simulator");
	Initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, makedelay, 1);
	glutMainLoop();
}
