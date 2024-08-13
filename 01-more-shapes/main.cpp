
#include "GLM/gtc/type_ptr.hpp"
#include <glad/gl.h>
#include "learnopengl/shader_4722.h"
#include "cs4722/artifact.h"
#include "cs4722/window.h"
#include "cs4722/buffer_utilities.h"

static std::vector<cs4722::artifact*> artifact_list;
static Shader *shader;

void init(void)
{
    shader = new Shader("../01-more-shapes/vertex_shader.glsl" ,
                        "../01-more-shapes/fragment_shader.glsl" );
    shader->use();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    cs4722::shape* b = new cs4722::block();

    //bottom left shape
    auto* artifact0 = new cs4722::artifact();
    artifact0->the_shape = b;
    artifact0->world_transform.translate = glm::vec3(-.5, -.5, 0);
    artifact0->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact0->world_transform.rotation_axis = glm::vec3(1, 0, 0);
    artifact0->world_transform.rotation_angle = (M_PI / 4);
    artifact_list.push_back(artifact0);

    //top left shape
    auto* artifact1 = new cs4722::artifact();
    artifact1->the_shape = b;
    artifact1->world_transform.translate = glm::vec3(-.5, .5, 0);
    artifact1->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact1->world_transform.rotation_axis = glm::vec3(0, 1, 0);
    artifact1->world_transform.rotation_angle = (7*M_PI / 4);
    artifact_list.push_back(artifact1);

    //bottom right shape
    auto* artifact2 = new cs4722::artifact();
    artifact2->the_shape = b;
    artifact2->world_transform.translate = glm::vec3(.5, -.5, 0);
    artifact2->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact2->world_transform.rotation_axis = glm::vec3(0, 0, 1);
    artifact2->world_transform.rotation_angle = (M_PI / 2);
    artifact_list.push_back(artifact2);

    //top right shape
    auto* artifact3 = new cs4722::artifact();
    artifact3->the_shape = b;
    artifact3->world_transform.translate = glm::vec3(.5, .5, 0);
    artifact3->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact3->world_transform.rotation_axis = glm::vec3(1, 0, 0);
    artifact3->world_transform.rotation_angle = (3*M_PI / 2);
    artifact_list.push_back(artifact3);

    cs4722::init_buffers(shader->ID, artifact_list, "b_position", "b_color");
}


void render()
{
    for (auto artf : artifact_list) {
        auto model_matrix = artf->animation_transform.matrix()
                            * artf->world_transform.matrix();
        shader->setMat4("u_transform", model_matrix);
        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);
    }
}

int
main(int argc, char** argv)
{
    glfwInit();
    cs4722::set_opengl_version(3,3);
    GLFWwindow* window = cs4722::setup_window("More Shapes", .6, 1);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    init();
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float_array());
        glClear(GL_DEPTH_BUFFER_BIT);
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
