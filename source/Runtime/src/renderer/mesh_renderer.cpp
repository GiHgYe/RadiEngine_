#include "renderer/mesh_renderer.h"
#include "renderer/mesh_filter.h"
#include "renderer/material.h"
#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/camera.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "utils/debug.h"
#include <glad/glad.h>

MeshRenderer::MeshRenderer() {

}

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::SetMaterial(Material* material) {
    material_ = material;
}


void MeshRenderer::Render() 
{
    Camera* current_camera = Camera::current_camera();
    if (!current_camera) return;
    
    if ((current_camera->culling_mask() & game_object()->layer()) == 0x00) {
        return;
    }

    auto transform = game_object()->GetComponent<Transform>();
    if (!transform) return;

    Matrix4x4 mvp = current_camera->projection_mat4() * current_camera->view_mat4() * transform->GetMatrix();

    auto mesh_filter = game_object()->GetComponent<MeshFilter>();
    if (!mesh_filter) return;

    //��ȡ`Shader`��`gl_program_id`��ָ��ΪĿ��Shader����
    GLuint shader_program_handle = material_->shader()->shader_program_handle();

    if (vertex_array_object_ == 0) {
        GLint vpos_location = glGetAttribLocation(shader_program_handle, "a_pos");
        GLint vcol_location = glGetAttribLocation(shader_program_handle, "a_color");
        GLint a_uv_location = glGetAttribLocation(shader_program_handle, "a_uv");
        
        //��GPU�ϴ�������������
        glGenBuffers(1, &vertex_buffer_object_);
        //������������ָ��Ϊ���㻺��������
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
        //�ϴ��������ݵ�����������
        glBufferData(GL_ARRAY_BUFFER, mesh_filter->mesh()->vertex_num * sizeof(MeshFilter::Vertex), mesh_filter->mesh()->vertex_data, GL_STATIC_DRAW);

        //��GPU�ϴ�������������
        glGenBuffers(1, &element_buffer_object_);
        //������������ָ��Ϊ������������������
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        //�ϴ������������ݵ�����������
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter->mesh()->vertex_index_num * sizeof(unsigned short), mesh_filter->mesh()->vertex_index_data, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vertex_array_object_);
        
        //����VAO
        glBindVertexArray(vertex_array_object_);
        {
            //ָ����ǰʹ�õ�VBO
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
            //��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(MeshFilter::Vertex), 0); __CHECK_GL_ERROR__;
            //���ö���Shader����(a_normal)��ָ���붥����ɫ���ݽ��й���
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float) * 3)); __CHECK_GL_ERROR__;
            //��Shader����(a_uv)�Ͷ���UV����VBO������й���������0��ʾ����ƫ������
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float) * (3 + 4))); __CHECK_GL_ERROR__;

            glEnableVertexAttribArray(vpos_location); __CHECK_GL_ERROR__;
            glEnableVertexAttribArray(vcol_location); __CHECK_GL_ERROR__;
            glEnableVertexAttribArray(a_uv_location); __CHECK_GL_ERROR__;

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glUseProgram(shader_program_handle);
    {
        game_object()->ForeachComponent([](Component* component) {
            component->OnPreRender();
        });

        if (current_camera->camera_use_for() == Camera::CameraUseFor::SCENE) {
            glEnable(GL_DEPTH_TEST); __CHECK_GL_ERROR__;
        }
        else {
            glDisable(GL_DEPTH_TEST); __CHECK_GL_ERROR__;
        }
        glEnable(GL_CULL_FACE); __CHECK_GL_ERROR__; //���������޳�
        glEnable(GL_BLEND); __CHECK_GL_ERROR__;
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); __CHECK_GL_ERROR__;
        //�ϴ�mvp����
        glUniformMatrix4fv(glGetUniformLocation(shader_program_handle, "u_mvp"), 1, GL_TRUE, &mvp[0][0]); __CHECK_GL_ERROR__;

        //��Pass�ڵ��õ������Texture
        std::vector<std::pair<std::string, Texture2D*>> textures = material_->textures();
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            GLint u_texture_location = glGetUniformLocation(shader_program_handle, textures[texture_index].first.c_str());
            //��������Ԫ0
            glActiveTexture(GL_TEXTURE0 + texture_index);
            //�����ص�ͼƬ���������󶨵�����Ԫ0��Texture2D�ϡ�
            glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->texture_handle());
            //����Shader���������Ԫ0��ȡ��ɫ����
            glUniform1i(u_texture_location, texture_index);
        }

        glBindVertexArray(vertex_array_object_);
        {
            glDrawElements(GL_TRIANGLES, mesh_filter->mesh()->vertex_index_num, GL_UNSIGNED_SHORT, 0);//ʹ�ö����������л��ƣ�����0��ʾ����ƫ������
        }
        glBindVertexArray(0);

        game_object()->ForeachComponent([](Component* component) {
            component->OnPostRender();
        });
    }
}