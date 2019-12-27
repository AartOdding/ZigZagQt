#version 330

uniform sampler2D tex;

in vec2 relative_position;

layout(location = 0) out vec4 output_color;

uniform vec2 framebuffer_resolution;
uniform vec3 color;

void main()
{
	vec2 sample_coord = gl_FragCoord.xy / framebuffer_resolution;
        output_color = texture(tex, relative_position);
        //output_color = vec4(relative_position, 0.0, 1.0);
}
