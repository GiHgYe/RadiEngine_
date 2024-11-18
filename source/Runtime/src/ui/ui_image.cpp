#include "ui/ui_image.h"
#include "component/game_object.h"
#include "renderer/mesh_filter.h"
#include "renderer/mesh_renderer.h"
#include "renderer/material.h"
#include "renderer/texture2d.h"
#include "render_device/render_device.h"

UIImage::UIImage() : texture2D_(nullptr), width_(0), height_(0) {

}

UIImage::~UIImage() {

}

void UIImage::Awake()
{
	Component::Awake();
}

void UIImage::Update()
{
	Component::Update();
	if (texture2D_ == nullptr) {
		return;
	}
	MeshFilter* mesh_filter = game_object()->GetComponent<MeshFilter>();
	if (mesh_filter == nullptr) {
		std::vector<MeshFilter::Vertex> vertex_vector = {
			{ {0.f, 0.0f, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {0.f, 0.f} },
			{ {(float)texture2D_->width(), 0.0f, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {1.f, 0.f} },
			{ {(float)texture2D_->width(), (float)texture2D_->height(), 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {1.f, 1.f} },
			{ {0.f, (float)texture2D_->height(), 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {0.f, 1.f} }
		};
		std::vector<unsigned short> index_vector = {
			0,1,2,
			0,2,3
		};
		mesh_filter = game_object()->AddComponent<MeshFilter>();
		mesh_filter->CreateMesh(vertex_vector, index_vector);

		Material* material = new Material();
		material->Parse("../asset/material/ui_image.mat");
		material->SetTexture("u_diffuseMap0", texture2D_);

		auto mesh_renderer = game_object()->AddComponent<MeshRenderer>();
		mesh_renderer->SetMaterial(material);
	}

}

void UIImage::OnPreRender() {
	Component::OnPreRender();
	glStencilFunc(GL_EQUAL, 0x1, 0xFF);//����1 ͨ������ ,�����ϴλ��Ƶ�ͼ �ķ�Χ ��ͨ�����ԡ�
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);//û��ͨ�����Եģ�����ԭ���ģ�Ҳ���Ǳ�����һ�ε�ֵ��
}

void UIImage::OnPostRender() {
	Component::OnPostRender();
	RenderDevice::instance()->Disable(RenderDevice::STENCIL_TEST);
}

