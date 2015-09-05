
#include <iostream>
#include <GL/glew.h>
#include <GLUT/GLUT.h>



void render(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    
    glFlush();
}

int main (int argc,char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("t1");
    //    glutDisplayFunc(void);
    GLenum res = glewInit();
    if(res != GLEW_OK)
    {
        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(res));
        return 1;
    }
    glutDisplayFunc(render);
    
    glutMainLoop();
    
}