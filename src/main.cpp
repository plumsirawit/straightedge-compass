#include "renderer.hpp"
#include <iostream>

static std::vector<Triangle> cube_vertices = {
    Triangle({glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(1.0f, -1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),
              glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, -1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, -1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, -1.0f, 1.0f, 1.0f)})};

static std::vector<Triangle> cube_colors = {
    Triangle({glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
              glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)})};

static std::vector<Triangle> plane_vertices = {
    Triangle({glm::vec4(-5.0f, 0.0f, -5.0f, 1.0f),
              glm::vec4(-5.0f, 0.0f, 5.0f, 1.0f),
              glm::vec4(5.0f, 0.0f, -5.0f, 1.0f)}),
    Triangle({glm::vec4(5.0f, 0.0f, -5.0f, 1.0f),
              glm::vec4(5.0f, 0.0f, 5.0f, 1.0f),
              glm::vec4(-5.0f, 0.0f, 5.0f, 1.0f)})};
static std::vector<Triangle> plane_colors = {
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}),
    Triangle({glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
              glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)})};

int main() {
    Manager manager(1024, 768);
    manager.add_object("player", cube_vertices, cube_colors);
    manager.add_object("base_plane", plane_vertices, plane_colors);
    manager.main_loop();
    return 0;
}