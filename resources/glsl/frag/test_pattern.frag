#version 330

layout(location = 0) out vec4 output_color;


void main()
{
	output_color = vec4(mod(gl_FragCoord.x, 20.0f), mod(gl_FragCoord.y, 20.0f), 1.0f, 1.0f);
}
