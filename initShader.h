//
//  initShader.h
//  Graphics
//
//  Created by Steve on 13/09/2015.
//  Copyright (c) 2015 Steve. All rights reserved.
//

#ifndef __Graphics__initShader__
#define __Graphics__initShader__

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>

void CompileShaders(const char* vsFileName,const char* fsFileName);
//void ShaderManager(GLuint ShaderProgram,const char* fname,GLenum ShaderType);
//const char* file_DIR = "/Users/steve/Documents/openGL/Graphics/";
#endif /* defined(__Graphics__initShader__) */
