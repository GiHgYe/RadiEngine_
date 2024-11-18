#version 330 core


uniform sampler2D u_diffuseMap0;


in vec2 uv;


out vec4 fragColor;

void main()
{
	
	vec4 color = texture(u_diffuseMap0, uv).rgba;
	if (color.a <= 0.001){
		discard;
	}
    fragColor = vec4(1);
}