#version 330


in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform vec4 color_a;
uniform vec4 color_b;
uniform float duty_cycle;
uniform float frequency;
uniform mat3 transformation;


void main()
{
    vec3 p = transformation * vec3(pos, 1);

    float angle = atan(p.y, p.x) * frequency;

    if (sin(angle) > duty_cycle)
    {
        output_color = color_a;
    }
    else
    {
        output_color = color_b;
    }
    output_color = vec4(1, 0, 0, 1);
}
