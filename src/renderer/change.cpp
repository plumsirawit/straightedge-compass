#include "renderer.hpp"
#include <iostream>
void Manager::handle_change(State &prev, State &cur) {
    glm::mat4 Translation(1.0f);
    if (prev.is_mouse_pressing && cur.is_mouse_pressing) {
        Translation =
            glm::translate(glm::vec3(cur.mouse_pos.x - prev.mouse_pos.x, 0.0f,
                                     cur.mouse_pos.y - prev.mouse_pos.y) /
                           100.0f);
    }
    double delta_time = cur.timestamp - prev.timestamp;
    if (cur.rotation_time_left > 0.0) {
        double rtime = std::min(delta_time, cur.rotation_time_left);
        cur.rotation_time_left -= delta_time;
        glm::mat4 Rotation(1.0f);
        switch (cur.rotation_dir) {
        case UP:
            Rotation = glm::rotate(
                glm::mat4(1.0f),
                glm::radians(-45.0f * (float)(rtime / ROTATION_TIME)),
                glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case DOWN:
            Rotation = glm::rotate(
                glm::mat4(1.0f),
                glm::radians(45.0f * (float)(rtime / ROTATION_TIME)),
                glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case LEFT:
            Rotation = glm::rotate(
                glm::mat4(1.0f),
                glm::radians(45.0f * (float)(rtime / ROTATION_TIME)),
                glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case RIGHT:
            Rotation = glm::rotate(
                glm::mat4(1.0f),
                glm::radians(-45.0f * (float)(rtime / ROTATION_TIME)),
                glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        }
        float cx = cur.focus->get_centroid().x;
        float cy = cur.focus->get_centroid().y;
        float cz = cur.focus->get_centroid().z;
        glm::mat4 TranslateOrigin = glm::translate(glm::vec3(-cx, -cy, -cz));
        glm::mat4 UntranslateOrigin = glm::translate(glm::vec3(cx, cy, cz));
        glm::mat4 Transform = UntranslateOrigin * Rotation * TranslateOrigin;
        cur.focus->apply_transformation(Transform);
    }
    cur.focus->apply_transformation(Translation);
    float mny = 1e9;
    for (int tri = 0; tri < cur.focus->triangles_count(); tri++) {
        for (int vt = 0; vt < 3; vt++) {
            mny = std::min(mny, (*cur.focus)[tri].first[vt].y);
        }
    }
    glm::mat4 LiftTranslation =
        glm::translate(glm::vec3(0.0f, -mny + 0.01f, 0.0f));
    cur.focus->apply_transformation(LiftTranslation);
    if (cur.t_pressed == PRESS_LIFTED) {
        cur.t_pressed = PRESS_NOT_PRESSED;
    }
}