#ifndef LOAD_SHADER_HPP_INCLUDED
#define LOAD_SHADER_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path);

#endif