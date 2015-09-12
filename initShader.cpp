//
//  initShader.cpp
//  Graphics
//
//  Created by Steve on 13/09/2015.
//  Copyright (c) 2015 Steve. All rights reserved.
//

#include <iostream>
#include "initShader.h"
#include <GLFW/glfw3.h>
#include <fstream>

using namespace std;

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

void CompileShaders(const char* vsFileName,const char* fsFileName){
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
