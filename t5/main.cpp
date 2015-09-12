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
using namespace::std;

GLuint VBO;
GLuint gScaleLocation;

bool ReadFile(const char* pFileName, string& outFile)
{
    
    ifstream f;
    printf("%s\n",pFileName);
    f.open(pFileName);
    
    bool ret = false;
    
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
    else {
        fprintf(stderr, "read error");
    }
    
    return ret;
}
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

void ShaderManager(GLuint ShaderProgram,const char* fname,GLenum ShaderType){
    GLuint ShaderObj = glCreateShader(ShaderType);
    if(ShaderObj == 0){
        fprintf(stderr, "errror in create shader.. type %d\n",ShaderType);
        exit(0);
    }
    
    const GLchar* p[1];
    p[0] = fname;
    GLint Lengths[1];
    Lengths[0] = strlen(fname);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj,GL_COMPILE_STATUS,&success);
    if(!success){
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj,sizeof(InfoLog),NULL,InfoLog);
        fprintf(stderr, "error in complie shader type %d: '%s'\n",ShaderType,InfoLog);
    }
    glAttachShader(ShaderProgram,ShaderObj);
}
static void CompileShaders(){
    GLuint ShaderProgram = glCreateProgram();
    
    if(ShaderProgram == 0){
        fprintf(stderr, "Error create shader program...\n");
        exit(1);
    }
    
    string vs,fs;
    
    if(!ReadFile(vsFileName,vs)){
        exit(1);
    }
    if(!ReadFile(fsFileName,fs)){
        exit(1);
    }
    
    ShaderManager(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    ShaderManager(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
    
    GLint success = 0;
    GLchar ErrorLog[1024] = {0};
    
    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&success);
    if(success == 0){
        glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr, "error linking shader program...'%s'\n",ErrorLog);
        exit(1);
    }
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram,GL_VALIDATE_STATUS,&success);
    
    if(success == 0){
        glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog), NULL,ErrorLog);
        fprintf(stderr, "error validate shader program....'%s'\n",ErrorLog);
        exit(1);
    };
    glUseProgram(ShaderProgram);
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
    CompileShaders();
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
