#ifndef SHADER_H
#define SHADER_H

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);

GLuint loadShaders1(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
#endif