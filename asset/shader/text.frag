#version 330 core


uniform sampler2D u_diffuseMap0;


in vec4 v_color;
in vec2 v_uv;

out vec4 fragColor;

void main()
{
	vec4 color = texture(u_diffuseMap0, v_uv).rgba;
    fragColor = vec4(v_color.r, v_color.g, v_color.b, color.r);
}