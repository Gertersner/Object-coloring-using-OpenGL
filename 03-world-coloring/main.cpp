
#include "GLM/gtc/type_ptr.hpp"
#include <glad/gl.h>
#include "learnopengl/shader_4722.h"

#include <vector>
#include "cs4722/artifact.h"
#include "cs4722/window.h"
#include "cs4722/buffer_utilities.h"



static Shader *shader;
static std::vector<cs4722::artifact*> artifact_list;

void init(void)
{
    shader = new Shader("../03-world-coloring/vertex_shader.glsl" ,
                        "../03-world-coloring/fragment_shader.glsl" );


    glUseProgram(shader->ID);
    glEnable(GL_DEPTH_TEST);

    cs4722::shape* b = new cs4722::block();
    b->color_set_ = std::vector<cs4722::color>({cs4722::x11::gray95, cs4722::x11::gray100});


    /*
     * start of bottom left shape
    */
    auto* artifact0 = new cs4722::artifact_rotating();
    artifact0->the_shape = b;
    artifact0->world_transform.translate = glm::vec3(-.5, -.5, 0);
    artifact0->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact0->world_transform.rotation_axis = glm::vec3(1, 0, 0);
    artifact0->world_transform.rotation_angle = (M_PI / 4);

    //animation
    artifact0->animation_transform.rotation_axis = glm::vec3(0, 1, 0);
    artifact0->animation_transform.rotation_center =
            artifact0->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artifact0->rotation_rate = M_PI / 6;

    artifact_list.push_back(artifact0);

    /*
     * start of top left shape
    */
    auto* artifact1 = new cs4722::artifact_rotating();
    artifact1->the_shape = b;
    artifact1->world_transform.translate = glm::vec3(-.5, .5, 0);
    artifact1->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact1->world_transform.rotation_axis = glm::vec3(0, 1, 0);
    artifact1->world_transform.rotation_angle = (7*M_PI / 4);

    //animation
    artifact1->animation_transform.rotation_axis = glm::vec3(0, 0, 1);
    artifact1->animation_transform.rotation_center =
            artifact1->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artifact1->rotation_rate = M_PI / 3;

    artifact_list.push_back(artifact1);

    /*
     * start of bottom right shape
    */
    auto* artifact2 = new cs4722::artifact_rotating();
    artifact2->the_shape = b;
    artifact2->world_transform.translate = glm::vec3(.5, -.5, 0);
    artifact2->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact2->world_transform.rotation_axis = glm::vec3(0, 0, 1);
    artifact2->world_transform.rotation_angle = (M_PI / 2);

    //animation
    artifact2->animation_transform.rotation_axis = glm::vec3(1, 0, 0);
    artifact2->animation_transform.rotation_center =
            artifact2->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artifact2->rotation_rate = M_PI / 2;

    artifact_list.push_back(artifact2);

    /*
     * start of top right shape
    */
    auto* artifact3 = new cs4722::artifact_rotating();
    artifact3->the_shape = b;
    artifact3->world_transform.translate = glm::vec3(.5, .5, 0);
    artifact3->world_transform.scale = glm::vec3(.75, .25, .5);
    artifact3->world_transform.rotation_axis = glm::vec3(1, 0, 0);
    artifact3->world_transform.rotation_angle = (3*M_PI / 2);

    //animation
    artifact3->animation_transform.rotation_axis = glm::vec3(0, 1, 0);
    artifact3->animation_transform.rotation_center =
            artifact3->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artifact3->rotation_rate = 2*M_PI / 3;

    artifact_list.push_back(artifact3);

    cs4722::init_buffers(shader->ID, artifact_list, "b_position", "b_color");
}


void render()
{

    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;

    for (auto artf : artifact_list) {
        artf->animate(time, delta_time);
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
    GLFWwindow* window = cs4722::setup_window("World Coloring", .6, 1);
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
