#include "base.hpp"

Object::Object(std::string st, std::vector<Triangle> mvtx,
               std::vector<Triangle> mcol)
    : name(st), mesh_vertices(mvtx), mesh_colors(mcol),
      vertexbuffer_data(nullptr), colorbuffer_data(nullptr) {
    centroid = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < mesh_vertices.size(); i++) {
        centroid += mesh_vertices[i][0];
        centroid += mesh_vertices[i][1];
        centroid += mesh_vertices[i][2];
    }
    centroid = centroid / (3.0f * mesh_vertices.size());
    vertexbuffer_data = new GLfloat[mvtx.size() * 3 * 4];
    colorbuffer_data = new GLfloat[mcol.size() * 3 * 3];
    glGenBuffers(1, &vertexbuffer_id);
    glGenBuffers(1, &colorbuffer_id);
    for (size_t i = 0; i < mcol.size(); i++) {
        colorbuffer_data[9 * i + 0] = mesh_colors[i][0].x;
        colorbuffer_data[9 * i + 1] = mesh_colors[i][0].y;
        colorbuffer_data[9 * i + 2] = mesh_colors[i][0].z;
        colorbuffer_data[9 * i + 3] = mesh_colors[i][1].x;
        colorbuffer_data[9 * i + 4] = mesh_colors[i][1].y;
        colorbuffer_data[9 * i + 5] = mesh_colors[i][1].z;
        colorbuffer_data[9 * i + 6] = mesh_colors[i][2].x;
        colorbuffer_data[9 * i + 7] = mesh_colors[i][2].y;
        colorbuffer_data[9 * i + 8] = mesh_colors[i][2].z;
    }
    update_data();
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer_id);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * 9 * sizeof(GLfloat),
                 colorbuffer_data, GL_DYNAMIC_DRAW);
}

void Object::update_data() {
    for (size_t i = 0; i < mesh_vertices.size(); i++) {
        vertexbuffer_data[12 * i + 0] = mesh_vertices[i][0].x;
        vertexbuffer_data[12 * i + 1] = mesh_vertices[i][0].y;
        vertexbuffer_data[12 * i + 2] = mesh_vertices[i][0].z;
        vertexbuffer_data[12 * i + 3] = 0.0f;
        vertexbuffer_data[12 * i + 4] = mesh_vertices[i][1].x;
        vertexbuffer_data[12 * i + 5] = mesh_vertices[i][1].y;
        vertexbuffer_data[12 * i + 6] = mesh_vertices[i][1].z;
        vertexbuffer_data[12 * i + 7] = 0.0f;
        vertexbuffer_data[12 * i + 8] = mesh_vertices[i][2].x;
        vertexbuffer_data[12 * i + 9] = mesh_vertices[i][2].y;
        vertexbuffer_data[12 * i + 10] = mesh_vertices[i][2].z;
        vertexbuffer_data[12 * i + 11] = 0.0f;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_id);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * 12 * sizeof(GLfloat),
                 vertexbuffer_data, GL_DYNAMIC_DRAW);
}

void Object::apply_transformation(glm::mat4 trans) {
    for (size_t i = 0; i < mesh_vertices.size(); i++) {
        mesh_vertices[i][0] = trans * mesh_vertices[i][0];
        mesh_vertices[i][1] = trans * mesh_vertices[i][1];
        mesh_vertices[i][2] = trans * mesh_vertices[i][2];
    }
    centroid = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < mesh_vertices.size(); i++) {
        centroid += mesh_vertices[i][0];
        centroid += mesh_vertices[i][1];
        centroid += mesh_vertices[i][2];
    }
    centroid = centroid / (3.0f * mesh_vertices.size());
}

std::pair<Triangle, Triangle> Object::operator[](size_t idx) {
    return std::make_pair(mesh_vertices[idx], mesh_colors[idx]);
}
void Object::replace_by(std::vector<Triangle> mvtx,
                        std::vector<Triangle> mcol) {

    delete[] vertexbuffer_data;
    delete[] colorbuffer_data;
    std::swap(mesh_vertices, mvtx);
    std::swap(mesh_colors, mcol);
    centroid = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < mesh_vertices.size(); i++) {
        centroid += mesh_vertices[i][0];
        centroid += mesh_vertices[i][1];
        centroid += mesh_vertices[i][2];
    }
    centroid = centroid / (3.0f * mesh_vertices.size());
    vertexbuffer_data = new GLfloat[mvtx.size() * 3 * 4];
    colorbuffer_data = new GLfloat[mcol.size() * 3 * 3];
    for (size_t i = 0; i < mcol.size(); i++) {
        colorbuffer_data[9 * i + 0] = mesh_colors[i][0].x;
        colorbuffer_data[9 * i + 1] = mesh_colors[i][0].y;
        colorbuffer_data[9 * i + 2] = mesh_colors[i][0].z;
        colorbuffer_data[9 * i + 3] = mesh_colors[i][1].x;
        colorbuffer_data[9 * i + 4] = mesh_colors[i][1].y;
        colorbuffer_data[9 * i + 5] = mesh_colors[i][1].z;
        colorbuffer_data[9 * i + 6] = mesh_colors[i][2].x;
        colorbuffer_data[9 * i + 7] = mesh_colors[i][2].y;
        colorbuffer_data[9 * i + 8] = mesh_colors[i][2].z;
    }
    update_data();
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer_id);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * 9 * sizeof(GLfloat),
                 colorbuffer_data, GL_DYNAMIC_DRAW);
}