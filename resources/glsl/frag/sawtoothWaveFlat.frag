#version 330


in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform vec4 color_a;
uniform vec4 color_b;
uniform float peak_position;
uniform mat3 transformation;


void main()
{
    vec3 p = transformation * vec3(pos, 1);

    float value = fract(p.x / 6.28318530718);

    if (value > peak_position)
    {
        float full_distance = 1 - peak_position;
        float value_distance = value - peak_position;
        float ratio = value_distance / full_distance;
        output_color = mix(color_a, color_b, ratio);
    }
    else
    {
        float ratio = value / peak_position;
        output_color = mix(color_b, color_a, ratio);
    }
}
