//
//  main.cpp
//  t5
//
//  Created by Steve on 12/09/2015.
//  Copyright (c) 2015 Steve. All rights reserved.
//

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <math.h>
#include <initShader.h>


using namespace::std;

GLuint VBO;
GLuint gScaleLocation;
static const GLfloat g_vertex_buffer_data [] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f , 0.0f,
    0.0f , 1.0f,  0.0f
};

static void CreateVertexBuffer(){
    
    
    glGenBuffers(1 , &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
}

const char* vsFileName = "/Users/steve/Documents/openGL/Graphics/t5/vs.vs";
const char* fsFileName = "/Users/steve/Documents/openGL/Graphics/t5/fs.fs";


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
static void render(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    static float Scale = 0.0f;
    
    Scale += 0.001f;
    
    glUniform1f(gScaleLocation, sinf(Scale));
    
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    glFlush();
}

int main(int argc,  char * argv[]) {
    // insert code here...
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if(!glfwInit()) exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    window = glfwCreateWindow(640, 480, "T5", NULL, NULL);
    if(!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    GLenum res =   glewInit();
    if(res != GLEW_OK){
        fprintf(stderr, "errors:'%s'\n",glewGetErrorString(res));
        return 1;
    }
    GLuint vaoId = 0;
    glGenVertexArrays(1,&vaoId);
    glBindVertexArray(vaoId);
    std::cout << "init end\n";
    
    CreateVertexBuffer();
    CompileShaders(vsFileName,fsFileName);
    render();
    
    while(!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}
