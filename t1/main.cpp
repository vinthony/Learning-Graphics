
#include <iostream>
#include <GL/glew.h>
#include <GLUT/GLUT.h>

#include "math_3d.h"


void render(){
    
    Vector3f Vertices[1];
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableVertexAttribArray(0);
    
   
    glutSwapBuffers();
    
}

int main (int argc,char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("t2");
    //    glutDisplayFunc(void);
    GLenum res = glewInit();
    if(res != GLEW_OK)
    {
        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(res));
        return 1;
    }
    glutDisplayFunc(render);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    
    
}