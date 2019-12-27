#version 330


in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform vec4 color_a;
uniform vec4 color_b;
uniform mat3 transformation;


void main()
{
    vec3 p = transformation * vec3(pos, 1);
    output_color = mix(color_b, color_a, 0.5 * (sin(p.x) + 1));
}
