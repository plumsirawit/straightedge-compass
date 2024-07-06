#include "renderer.hpp"
#include <deque>
#include <iostream>

static double sdelta = 0.0;
static int framecnt = 0;
void Manager::main_loop() {
    prev_state->focus = objects.front();
    std::deque<double> dq;
    int fc = 0;
    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(glm::vec3(0, 3, 10), glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    glm::mat4 Model = glm::translate(glm::vec3(2.0f, 0.0f, 2.0f));
    glm::mat4 phi_mvp = Projection * View * Model;
    do {
        State *current_state = new State(*prev_state);
        current_state->update_state(this);
        dq.push_back(current_state->timestamp - prev_state->timestamp);
        sdelta += dq.back();
        fc++;
        framecnt++;
        while (dq.size() > 30) {
            sdelta -= dq.front();
            dq.pop_front();
            framecnt--;
        }
        if (fc % 100 == 0) {
            std::cerr << "Average: " << framecnt / sdelta << " fps"
                      << std::endl;
        }
        handle_change(*prev_state, *current_state);
        delete prev_state;
        prev_state = current_state;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program_id);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
        for (size_t objidx = 0; objidx < objects.size(); objidx++) {
            objects[objidx]->update_data();
            glBindBuffer(GL_ARRAY_BUFFER,
                         objects[objidx]->get_vertexbuffer_id());
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glBindBuffer(GL_ARRAY_BUFFER,
                         objects[objidx]->get_colorbuffer_id());
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glDrawArrays(GL_TRIANGLES, 0,
                         objects[objidx]->triangles_count() * 3);
        }
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
    glfwTerminate();
}