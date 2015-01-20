
#include </usr/include/GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float sw = 0;

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

void Keyboard (unsigned char key, int q, int s)
{
    switch (key)  {
       case 's' :  sw += 3;  glutPostRedisplay();   break;
       case  27 :  exit(0);
       default  : printf ("   Keyboard %c == %d\n", key, key);
    }
}

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
//-----------------------------  Radar_Pattern  --------------------------------

void Radar_Pattern (void)
{
    int i, n = 120;
    float da, ga, gb, a, b;
    const float TWOPI = M_PI * 2.0;

    da = TWOPI / (float)n;

    glBegin (GL_TRIANGLE_FAN);
    for (i = 0; i < n; i++)
    {
		  a = (float)i * da;
		  b = a + da;
		  ga = 0.90 * (float)(i  ) / (float)n;
		  gb = 0.90 * (float)(i+1) / (float)n;
		  glColor3f  (0, ga, 0);
		  glVertex2i (0, 0); glVertex2f (cos(a), sin(a));
		  glColor3f  (0, gb, 0);
          glVertex2f (cos(b), sin(b)); glVertex2i (0, 0);
    }
    glEnd ();
}


//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
//--------------------------------  myDisplay  ---------------------------------

void myDisplay()
{
    glMatrixMode   (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho        (-2.0,2.0, -1.5,1.5, -1.0,1.0);

    glMatrixMode   (GL_MODELVIEW);
    glLoadIdentity ();

    glClearColor (0, 0, 0, 0);
    glClear (GL_COLOR_BUFFER_BIT);

    glRotatef (sw, 0,0,1);
    Radar_Pattern ();

    glutSwapBuffers();
}

void IdleFunc()
{
	sw += 0.5;
	glutPostRedisplay();
}

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
//----------------------------------  main  ------------------------------------

int main (int argc, char **argv)
{
    printf ("\n   Hold 's' key down to sweep radar pattern.\n");

    glutInit               (&argc, argv);
    glutInitWindowSize     (800, 600);
    glutInitWindowPosition (400, 100);
    glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE);

    glutCreateWindow ("Radar Pattern - MaxH - March 2011");
    glutDisplayFunc  ( myDisplay );
    glutKeyboardFunc ( Keyboard  );
    glutIdleFunc(IdleFunc);

    glutMainLoop   ();

    return 1;
}

//******************************************************************************
//******************************************************************************
