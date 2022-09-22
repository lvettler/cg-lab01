#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#define TAMANHO_JANELA 500

// Posições
float gX = 0;
float gY = 0;

// Estato de cada tecla
int keyStatus[256];

void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 1.0, 1.0);
   
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (0.25+gX, 0.25+gY, 0.0); 
      glVertex3f (0.75+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.75+gY, 0.0);
      glVertex3f (0.25+gX, 0.75+gY, 0.0);
   glEnd();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init (void) 
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de visualizacao */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/* Call-back de teclado */
void keyPress(unsigned char key, int x, int y){

   keyStatus[(int) key] = 1;

   //redesenhar
   glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
   keyStatus[(int) key] = 0;

   //redesenhar
   glutPostRedisplay();
}

void idle(void){
   if(keyStatus[(int)'w'] || keyStatus[(int)'W']){
      gY+=0.001; 
   } 
   if(keyStatus[(int)'s'] || keyStatus[(int)'S']){
      gY-=0.001;
   }
   if(keyStatus[(int)'a'] || keyStatus[(int)'A']){
      gX-=0.001; 
   } 
   if(keyStatus[(int)'d'] || keyStatus[(int)'D']){
      gX+=0.001;
   }

   //redesenhar
   glutPostRedisplay();
}

/* Call-back do mouse */
void mouse(int button, int state, int x, int y){
   y = TAMANHO_JANELA - y;

   if(state == GLUT_DOWN){
      gX = (float) x/TAMANHO_JANELA - 0.25;
      gY = (float) y/TAMANHO_JANELA - 0.25;
   }

   //redesenhar
   glutPostRedisplay();
}

void arraste(int x, int y){
   y = TAMANHO_JANELA - y;

   gX = (float) x/TAMANHO_JANELA - 0.25;
   gY = (float) y/TAMANHO_JANELA - 0.25;

   //redesenhar
   glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello world");
    init ();
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(arraste);

    glutMainLoop();

    return 0;
}
