#include "scripting/renderer_binder.h"
#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/material.h"
#include "renderer/mesh_filter.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"
#include "renderer/font.h"
#include "renderer/animation_clip.h"

void LuaRendererBinder::binding(sol::state& sol_state_)
{
	auto cpp_ns_table = sol_state_["Cpp"].get_or_create<sol::table>();

	cpp_ns_table.new_usertype<AnimationClip>("AnimationClip", sol::call_constructor, sol::constructors<AnimationClip()>(),
		"LoadFromFile", &AnimationClip::LoadFromFile,
		"duration", &AnimationClip::duration,
		"Play", &AnimationClip::Play,
		"Stop", &AnimationClip::Stop,
		"Update", &AnimationClip::Update
	);

	cpp_ns_table.new_usertype<Material>("Material", sol::call_constructor, sol::constructors<Material()>(),
		"Parse", &Material::Parse,
		"SetUniform1i", &Material::SetUniform1i,
		"SetTexture", &Material::SetTexture
	);

	cpp_ns_table.new_usertype<MeshFilter>("MeshFilter", sol::call_constructor, sol::constructors<MeshFilter()>(),
		sol::base_classes, sol::bases<Component>(),
		"LoadMesh", &MeshFilter::LoadMesh,
		"CreateMesh", &MeshFilter::CreateMesh
	);

	cpp_ns_table.new_usertype<MeshRenderer>("MeshRenderer", sol::call_constructor, sol::constructors<MeshRenderer()>(),
		sol::base_classes, sol::bases<Component>(),
		"SetMaterial", &MeshRenderer::SetMaterial,
		"material", &MeshRenderer::material,
		"Render", &MeshRenderer::Render
	);

	cpp_ns_table.new_usertype<Shader>("Shader", sol::call_constructor, sol::constructors<Shader()>(),
		"Parse", &Shader::Parse,
		"CreateShaderProgram", &Shader::CreateShaderProgram,
		"Active", &Shader::Active,
		"InActive", &Shader::InActive,
		"shader_program_handle", &Shader::shader_program_handle,
		"Find", &Shader::Find
	);

	cpp_ns_table.new_usertype<Texture2D>("Texture2D",
		"mipmap_level", &Texture2D::mipmap_level,
		"width", &Texture2D::width,
		"height", &Texture2D::height,
		"gl_texture_format", &Texture2D::gl_texture_format,
		"texture_handle", &Texture2D::texture_handle,
		"LoadFromFile", &Texture2D::LoadFromFile
	);

	cpp_ns_table.new_usertype<Camera>("Camera", sol::call_constructor, sol::constructors<Camera()>(),
		sol::base_classes, sol::bases<Component>(),
		"SetView", &Camera::SetView,
		"SetPerspective", &Camera::SetPerspective,
		"SetOrthographic", &Camera::SetOrthographic,
		"view_mat4", &Camera::view_mat4,
		"projection_mat4", &Camera::projection_mat4,
		"set_clear_color", &Camera::set_clear_color,
		"set_clear_flag", &Camera::set_clear_flag,
		"Clear", &Camera::Clear,
		"depth", &Camera::depth,
		"set_depth", &Camera::set_depth,
		"culling_mask", &Camera::culling_mask,
		"set_culling_mask", &Camera::set_culling_mask,
		"Foreach", &Camera::Foreach,
		"current_camera", &Camera::current_camera,
		"Sort", &Camera::Sort
	);

}
