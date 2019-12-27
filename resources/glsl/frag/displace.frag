#version 330


uniform sampler2D input_a;
uniform sampler2D input_b;

in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform float fade_position;



void main()
{
    vec4 color_a = texture(input_a, pos);
    vec4 color_b = texture(input_b, pos);
    output_color = mix(color_a, color_b, fade_position);
}
