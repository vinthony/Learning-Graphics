#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

GLBatch triangleBatch;
GLShaderManager triangleManager;

void
ChangeSize (int w,int h){
    glViewport(0, 0, w, h);
}

void
setUpRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    
    triangleManager.InitializeStockShaders();
    
    GLfloat vVerts[] = {
        -0.5f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,
         0.0f, 0.5f, 0.0f
    };

    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    
}

void
RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = { 1.0f , 0.0f , 0.0f , 1.0f };
    triangleManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    triangleBatch.Draw();
    glutSwapBuffers();
}

int main(int argc,char * argv[]){

    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(600, 800);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    GLenum err = glewInit();
    if (GLEW_OK != err){
        fprintf(stderr, "glew error %s.\n",glewGetErrorString(err));
        return 1;
    }
    
    setUpRC();
    glutMainLoop();
    return 0;

}