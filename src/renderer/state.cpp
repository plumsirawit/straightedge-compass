#include "renderer.hpp"

void State::update_state(Manager *manager) {
    timestamp = glfwGetTime();
    glfwGetCursorPos(manager->window, &mouse_pos.x, &mouse_pos.y);
    is_mouse_pressing =
        glfwGetMouseButton(manager->window, GLFW_MOUSE_BUTTON_LEFT) ==
        GLFW_PRESS;
    if (glfwGetKey(manager->window, 'W') == GLFW_PRESS) {
        if (rotation_time_left <= 0.0) {
            rotation_dir = UP;
            rotation_time_left = ROTATION_TIME;
        }
    } else if (glfwGetKey(manager->window, 'A') == GLFW_PRESS) {
        if (rotation_time_left <= 0.0) {
            rotation_dir = LEFT;
            rotation_time_left = ROTATION_TIME;
        }
    } else if (glfwGetKey(manager->window, 'S') == GLFW_PRESS) {
        if (rotation_time_left <= 0.0) {
            rotation_dir = DOWN;
            rotation_time_left = ROTATION_TIME;
        }
    } else if (glfwGetKey(manager->window, 'D') == GLFW_PRESS) {
        if (rotation_time_left <= 0.0) {
            rotation_dir = RIGHT;
            rotation_time_left = ROTATION_TIME;
        }
    }
    if (glfwGetKey(manager->window, 'T') == GLFW_PRESS) {
        if (t_pressed == PRESS_NOT_PRESSED)
            t_pressed = PRESS_INITIALIZED;
    } else {
        if (t_pressed == PRESS_INITIALIZED)
            t_pressed = PRESS_LIFTED;
    }
}