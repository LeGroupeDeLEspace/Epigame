#include <cmath>
#include <Shapes.hpp>
#include <Graphics.hpp>

int main()
{
    gr::RectangleShape rec(glm::vec2(-0.5, -0.5), glm::vec2(0.1, 0.1));
    gr::CircleShape cir(glm::vec2(0.5, 0.5), 0.5, 60);
    gr::Graphics graph;
    GLFWwindow *window = gr::mainWindow.getWindow();

    graph.shapesManager.loadShapes({&cir, &rec});
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        graph.test();
    }
    graph.waitForIdle();
    return 0;
}

// simple index test
// int main()
// {
//     std::vector<gr::Vertex> vertices = {   //tmp test data
//         {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//         {{0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
//         {{-0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},

//         {{0.0f, 0.5f}, {1.0f, 0.0f, 0.0f}},
//     };

//     std::vector<uint16_t> index = {
//         0, 1, 2, 3, 2, 1,
//     };

//     gr::Graphics graph;
//     GLFWwindow *window = gr::mainWindow.getWindow();
//     gr::Buffer &buffer = graph.newBuffer(vertices.size(), index.size());
//     buffer.copyData(vertices.data());
//     buffer.copyIndexData(index.data());
//     bool r = true;

//     float a = 0;

//     while (!glfwWindowShouldClose(window)) {
//         glfwPollEvents();
//         graph.test();
//     }
//     graph.waitForIdle();
//     return 0;
// }