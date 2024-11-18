#include "ui/ui_mask.h"
#include "component/game_object.h"
#include "renderer/mesh_filter.h"
#include "renderer/mesh_renderer.h"
#include "renderer/material.h"
#include "renderer/texture2d.h"
#include "render_device/render_device.h"
#include "utils/debug.h"


UIMask::UIMask() {

}

UIMask::~UIMask() {

}

void UIMask::Update() {
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
		material->Parse("../asset/material/ui_mask.mat");
		material->SetTexture("u_diffuseMap0", texture2D_);

		auto mesh_renderer = game_object()->AddComponent<MeshRenderer>();
		mesh_renderer->SetMaterial(material);
	}
}

void UIMask::OnPreRender() {
	Component::OnPreRender();
	RenderDevice::instance()->Enable(RenderDevice::STENCIL_TEST);//����ģ�����
	glClearStencil(0); __CHECK_GL_ERROR__; //����Ĭ��ģ��ֵ 0
	glStencilFunc(GL_NEVER, 0x0, 0xFF); __CHECK_GL_ERROR__; //ͨͨ��ͨ��ģ����ԡ�
	glStencilOp(GL_INCR, GL_INCR, GL_INCR); __CHECK_GL_ERROR__; //���ص�ģ��ֵ 0+1 = 1
}

void UIMask::OnPostRender() {
    Component::OnPostRender();
}

void UIMask::OnEnable() {

}

void UIMask::OnDisable() {
    RenderDevice::instance()->Disable(RenderDevice::STENCIL_TEST);
}

