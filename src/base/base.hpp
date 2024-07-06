/**
 * @file base.hpp
 * @author Sirawit Pongnakintr (sirawit@pongnakin.com)
 * @brief Base classes
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef BASE_HPP_INCLUDED
#define BASE_HPP_INCLUDED

#include <array>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Triangle : public std::array<glm::vec4, 3> {};

class Object {
  protected:
    std::string name;
    GLfloat* vertexbuffer_data;
    GLuint vertexbuffer_id;
    GLfloat *colorbuffer_data;
    GLuint colorbuffer_id;
    glm::vec4 centroid;
    std::vector<Triangle> mesh_vertices;
    std::vector<Triangle> mesh_colors;

  public:
    Object() : vertexbuffer_data(nullptr), colorbuffer_data(nullptr) {}
    virtual ~Object() {
        if(vertexbuffer_data)
            delete[] vertexbuffer_data;
        if(colorbuffer_data)
            delete[] colorbuffer_data;
    }
    Object(std::string st, std::vector<Triangle> mvtx,
           std::vector<Triangle> mcol);
    GLuint get_vertexbuffer_id() const { return vertexbuffer_id; }
    GLuint get_colorbuffer_id() const { return colorbuffer_id; }
    size_t triangles_count() const { return mesh_vertices.size(); }
    virtual glm::vec4 get_centroid() const { return centroid; }
    void update_data();
    virtual void apply_transformation(glm::mat4 trans);
    virtual std::pair<Triangle, Triangle> operator[](size_t idx);
    void replace_by(std::vector<Triangle> mvtx, std::vector<Triangle> mcol);
};

#endif