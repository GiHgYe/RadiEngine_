#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_uv;

uniform mat4 u_mvp;

out vec4 v_color;
out vec2 v_uv;

void main()
{
	v_color = a_color;
	v_uv = a_uv;
	gl_Position = u_mvp * vec4(a_pos, 1.0);
}