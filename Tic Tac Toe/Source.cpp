#include<Windows.h>
#include<gl/GL.h>
#include<gl/glut.h>
#include <iostream>
#include <math.h>
#include <random>

int board[3][3];	// board for gameplay
int turn;			// current move
int result;			// Result of the game
bool over;			// Is the game Over?
int xwins = 1;
int owins = 1;

void Intialize()
{
	turn = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			board[i][j] = 0;
	}
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(4.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640, 0.0, 480);
}

/*
	Called when Mouse is clicked
*/
void OnMouseClick(int button, int state, int x, int y)
{
	if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (turn == 1)
		{
			if (board[(y - 50) / 100][x / 100] == 0)
			{
				board[(y - 50) / 100][x / 100] = 1;
				turn = 2;
			}
		}
		else if (turn == 2)
		{
			if (board[(y - 50) / 100][x / 100] == 0)
			{
				board[(y - 50) / 100][x / 100] = 2;
				turn = 1;
			}
		}
	}
}
/*
	Utility function to draw string
*/
void DrawString(void* font, const char s[], float x, float y)
{
	glColor3f(1, 0.2, 0.5);

	unsigned int i;
	glRasterPos2f(x, y); // specify the raster position for pixel operations
	for (i = 0; i < strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]); // renders the character at the required position and advances the current 
										 // raster position by the width of the character
	}
}

/*
	Function to draw up the horizontal and vertical lines
*/
void DrawLines()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

	glVertex2f(100, 50);
	glVertex2f(100, 340);
	glVertex2f(200, 340);
	glVertex2f(200, 50);

	glVertex2f(0, 150);
	glVertex2f(300, 150);
	glVertex2f(0, 250);
	glVertex2f(300, 250);

	glEnd();
}

/*
	Utility function to draw the circle
*/
void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

/*
	Function to draw the cross and circle of Tic Tac Toe
*/
void DrawXO()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// X 
			if (board[i][j] == 1)
			{
				glBegin(GL_LINES);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			// O
			else if (board[i][j] == 2)
			{

				DrawCircle(50 + j * 100, 100 + i * 100, 25, 15);
			}
		}
	}
}

/*
	Function to check if there is any winner
*/
bool CheckWinner()
{
	int i, j;
	// horizontal check
	for (i = 0; i < 3; i++)
	{
		for (j = 1; j < 3; j++)
		{
			if (board[i][0] != 0 && board[i][0] == board[i][j])
			{
				if (j == 2)
				{
					return true;
				}
			}
			else
				break;
		}
	}
	// vertical check
	for (i = 0; i < 3; i++)
	{
		for (j = 1; j < 3; j++)
		{
			if (board[0][i] != 0 && board[0][i] == board[j][i])
			{
				if (j == 2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if ((board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2])
		|| (board[2][0] != 0 && board[2][0] == board[1][1] && board[2][0] == board[0][2]))
		return true;
	return false;
}

/*
	function to check if there is draw
*/
bool CheckIfDraw()
{
	int i, j;
	bool draw;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				return false;
		}
	}
	return true;
}


/*
	Function to display up everything
*/

void OnKeyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'Y':
	case 'y':
		if (over == true)
		{
			over = false;
			Intialize();
			if (result == 1) {
				xwins++;
			}
			if (result == 2) {
				owins++;
			}
		}
		break;
	case 'N':
	case 'n':
		if (over == true)
		{
			exit(0);
		}
		break;
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	if (turn == 1)
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 400);
	else
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 400);
	
	DrawLines();
	DrawXO();
	
	if (CheckWinner() == true)
	{
		if (turn == 1)
		{
			over = true;
			result = 2;
		}
		else
		{
			over = true;
			result = 1;
		}
	}
	
	else if (CheckIfDraw() == true)
	{
		over = true;
		result = 0;
	}
	
	
	
	if (over == true)
	{
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);
		if (result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);
		if (result == 1) {
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);
		}
		if (result == 2) {
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);
		}
		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);
	}
	
	
	DrawString(GLUT_BITMAP_HELVETICA_18, "X", 10, 22);
	for (int i = 1; i < xwins; i++) {
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex2f(10 + 26 * (i % 10), 10 - 13 * (i / 10));
		glVertex2f(20 + 26 * (i % 10), 20 - 13 * (i / 10));
		glEnd();
	}

	DrawString(GLUT_BITMAP_HELVETICA_18, "O ", 10, 42);
	for (int i = 1; i < owins ; i++) {
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex2f(10 + 26 * (i % 10), 30 -13 * (i / 10));
		glVertex2f(20 + 26 * (i % 10), 40 -13 * (i / 10));
		glEnd();
	}

	if (xwins > owins) {
		DrawString(GLUT_BITMAP_HELVETICA_18, "x is wins", 100, 430);
	}
	else if(xwins < owins) {
		DrawString(GLUT_BITMAP_HELVETICA_18, "o is wins", 100, 430);
	}
	else {
		DrawString(GLUT_BITMAP_HELVETICA_18, "No one", 100, 430);

	}

	glutSwapBuffers();
}
/*
	Function to reshape
*/
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv)
{
	Intialize();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(550, 200);
	glutInitWindowSize(300, 450);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	myInit();
	glutMainLoop();

}
