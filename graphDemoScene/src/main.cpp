#include <cmath>
#include "Graphics.hpp"

int main()
{
    std::vector<gr::Vertex> vertices = {   //tmp test data
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},

        {{0.0f, 0.5f}, {1.0f, 0.0f, 0.0f}},
    };

    std::vector<uint16_t> index = {
        0, 1, 2, 3, 2, 1,
    };

    gr::Graphics graph;
    GLFWwindow *window = gr::mainWindow.getWindow();
    gr::Buffer &buffer = graph.newBuffer(vertices.size(), index.size());
    buffer.copyData(vertices.data());
    buffer.copyIndexData(index.data());
    bool r = true;

    float a = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // vertices[0].pos.x = std::cos(a);
        // vertices[3].pos.x = vertices[0].pos.x;
        // a += 0.004;
        // buffer.copyData(vertices.data());
        // if (r && glfwGetKey(window, GLFW_KEY_A)) {
        //     graph.removeBuffer(buffer);
        //     r = false;
        // }
        graph.test();
    }
    graph.waitForIdle();
    return 0;
}