#version 330


in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform vec4 color_a;
uniform vec4 color_b;
uniform float frequency;
uniform mat3 transformation;


void main()
{
    vec3 p = transformation * vec3(pos, 1);

    float angle = atan(p.y, p.x) * frequency;

    float ratio = 0.5 * (sin(angle) + 1);

    output_color = mix(color_b, color_a, ratio);
}
