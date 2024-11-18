#version 330 core

uniform sampler2D u_diffuseMap0;


in vec4 v_color;
in vec2 v_uv;

out vec4 fragColor;

void main()
{
	vec4 pixColor = texture(u_diffuseMap0, v_uv);

    fragColor = vec4(v_color.x, v_color.y, v_color.z, pixColor.r);
}