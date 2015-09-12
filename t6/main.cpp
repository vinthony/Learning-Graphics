//
//  main.cpp
//  t6
//
//  Created by Steve on 13/09/2015.
//  Copyright (c) 2015 Steve. All rights reserved.
//

#include <iostream>

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <initShader.h>
#include <math.h>

const char* vsFileName  =  "/Users/steve/Documents/openGL/Graphics/t6/vs.vs";
const char* fsFileName  =  "/Users/steve/Documents/openGL/Graphics/t6/fs.fs";

GLuint VBO;
GLuint gScaleLocation;
static float Scale = 0.0f;
struct Matrix4f {
    float m[4][4];
};
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
static void render(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLuint gWorldLocation;
    Matrix4f World;
    World.m[0][0] = 1.0f ;World.m[0][1]= 0.0f; World.m[0][2] =0.0f; World.m[0][3]= sinf(Scale);
    World.m[1][0] = 0.0f ;World.m[1][1]= 1.0f; World.m[1][2] =0.0f; World.m[1][3]= 0.0f;
    World.m[2][0] = 0.0f ;World.m[2][1]= 0.0f; World.m[2][2] =1.0f; World.m[2][3]= 0.0f;
    World.m[3][0] = 0.0f ;World.m[3][1]= 0.0f; World.m[3][2] =0.0f; World.m[3][3]= 1.0f;
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

    Scale += 0.001f;
    
    glUniform1f(gScaleLocation, sinf(Scale));
    
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    glFlush();
}
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char * argv[]) {
    // insert code here...
    
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if(!glfwInit()) exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(640, 480, "T6", NULL, NULL);
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
    std::cout << "Hello, World!\n";
    return 0;
}
