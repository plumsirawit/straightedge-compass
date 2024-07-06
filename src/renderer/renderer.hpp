/**
 * @file renderer.hpp
 * @author Sirawit Pongnakintr (sirawit@pongnakin.com)
 * @brief Object renderer and OpenGL manager
 * @version 0.1
 * @date 2024-06-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

enum RotationDirection { UP, DOWN, LEFT, RIGHT };

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#ifndef CMAKE_CURRENT_SOURCE_DIR
#define CMAKE_CURRENT_SOURCE_DIR "Unknown Directory"
#endif

#include "base.hpp"
#include "loadShader.hpp"

const double ROTATION_TIME = 0.5; // seconds

class Manager;

enum KeyboardState { PRESS_NOT_PRESSED, PRESS_INITIALIZED, PRESS_LIFTED };

class State {
  public:
    glm::dvec2 mouse_pos;
    double timestamp;
    double rotation_time_left;
    RotationDirection rotation_dir;
    bool is_mouse_pressing;
    Object *focus;
    KeyboardState t_pressed;
    State()
        : mouse_pos(0.0, 0.0), timestamp(glfwGetTime()),
          rotation_time_left(0.0), rotation_dir(UP), is_mouse_pressing(false),
          focus(nullptr), t_pressed(PRESS_NOT_PRESSED) {}
    void update_state(Manager *manager);
};

class Manager {
  public:
    int width, height;
    GLFWwindow *window;
    glm::mat4 mvp;
    GLuint shader_program_id;
    GLuint mvp_id;
    GLuint acctrans_id;
    State *prev_state;
    std::vector<Object *> objects;
    Manager(int w, int h);
    ~Manager() {
        for (Object *ptr : objects)
            delete ptr;
    }
    void add_object(std::string name, std::vector<Triangle> mesh_vertices,
                    std::vector<Triangle> mesh_colors) {
        Object *obj = new Object(name, mesh_vertices, mesh_colors);
        objects.push_back(obj);
    }
    void load_shader();
    void handle_change(State &prev, State &cur);
    void main_loop();
};
#endif