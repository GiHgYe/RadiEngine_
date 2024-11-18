#include "ui/ui_text.h"
#include "component/game_object.h"
#include "renderer/mesh_renderer.h"
#include "renderer/mesh_filter.h"
#include "renderer/material.h"
#include "renderer/texture2d.h"

UIText::UIText() : color_({ 1,1,1,1 }) {

}

UIText::~UIText() {

}

void UIText::set_text(std::string text) {
    if (text_ == text) {
        return;
    }
    text_ = text;
    dirty_ = true;
}

void UIText::Update() {
    Component::Update();

    if (font_ == nullptr || font_->font_texture() == nullptr) {
        return;
    }

    MeshFilter* mesh_filter = game_object()->GetComponent<MeshFilter>();
    if (mesh_filter == nullptr) {
        //���� MeshFilter ���
        mesh_filter = game_object()->AddComponent<MeshFilter>();

        //���� Material
        auto material = new Material();//���ò���
        material->Parse("../asset/material/ui_text.mat");

        //���� MeshRenderer ���
        auto mesh_renderer = game_object()->AddComponent<MeshRenderer>();
        mesh_renderer->SetMaterial(material);

        //ʹ��������ͼ
        material->SetTexture("u_diffuseMap0", font_->font_texture());
    }

    if (dirty_) {
        dirty_ = false;

        std::vector<Font::Character*> character_vec = font_->LoadStr(text_);
        //����ÿ���ַ����л���
        std::vector<MeshFilter::Vertex> vertex_vector;
        std::vector<unsigned short> index_vector(character_vec.size() * 6);

        int x = 0;
        std::vector<unsigned short> index = { 0, 1, 2, 0, 2, 3 };
        //�ϲ�Mesh
        for (int i = 0; i < character_vec.size(); ++i) {
            auto character = character_vec[i];
            unsigned short width = (character->right_bottom_x_ - character->left_top_x_) * font_->font_texture()->width();
            unsigned short height = (character->right_bottom_y_ - character->left_top_y_) * font_->font_texture()->height();
            //��ΪFreeType���ɵ�bitmap�����µߵ��ģ���������UV����ҲҪ����Ӧ��ת�������Ͻ���Ϊ��㡣
            vertex_vector.insert(vertex_vector.end(), {
                {{(float)x, 0.0f, 0.0f},                         color_, {character->left_top_x_,     character->right_bottom_y_}},
                {{(float)x + (float)width, 0.0f, 0.0f},          color_, {character->right_bottom_x_, character->right_bottom_y_}},
                {{(float)x + (float)width, (float)height, 0.0f}, color_, {character->right_bottom_x_, character->left_top_y_}},
                {{(float)x, (float)height, 0.0f},                color_, {character->left_top_x_,     character->left_top_y_}}
            });
            x += width;

            for (int j = 0; j < index.size(); ++j) {
                index_vector[i * index.size() + j] = index[j] + i * 4;
            }
        }
        mesh_filter->CreateMesh(vertex_vector, index_vector);
    }
}

void UIText::OnPreRender() {
    Component::OnPreRender();
}

void UIText::OnPostRender() {
    Component::OnPostRender();
}