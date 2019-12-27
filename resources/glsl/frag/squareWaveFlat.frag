#version 330


in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform vec4 color_a;
uniform vec4 color_b;
uniform float duty_cycle;
uniform mat3 transformation;


void main()
{
    vec3 p = transformation * vec3(pos, 1);

    float value = fract(p.x / 6.28318530718);

    if (duty_cycle > 0)
    {
        if (value < duty_cycle)
        {
            output_color = color_a;
        }
        else
        {
            output_color = color_b;
        }
    }
    else
    {
        if (value - 1 > duty_cycle)
        {
            output_color = color_a;
        }
        else
        {
            output_color = color_b;
        }
    }
}
