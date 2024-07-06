#include "renderer.hpp"
#include <iostream>

Manager::Manager(int w, int h) : width(w), height(h), mvp(1.0f) {
    glewExperimental = GL_TRUE;
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        exit(-1);
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w, h, "Straightedge and Compass", NULL, NULL);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window. Check whether GPU is 3.3 "
                     "compatible."
                  << std::endl;
        getchar();
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    if (w == 1 && h == 1) {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        std::cerr << "MODE " << mode->width << " " << mode->height << " "
                  << mode->refreshRate;
        width = mode->width;
        height = mode->height;
        glfwSetWindowSize(window, width, height);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height,
                             mode->refreshRate);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        exit(-1);
    }
    std::cerr << glGetString(GL_VERSION) << std::endl;
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(glm::vec3(0, 3, 10), glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    glm::mat4 Model = glm::mat4(1.0f);
    mvp = Projection * View * Model;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    load_shader();
    mvp_id = glGetUniformLocation(shader_program_id, "MVP");
    acctrans_id = glGetUniformLocation(shader_program_id, "acctrans");
    prev_state = new State();
}