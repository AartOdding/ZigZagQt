#version 330


in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform vec4 color_a;
uniform vec4 color_b;
uniform float peak_position;
uniform float frequency;
uniform mat3 transformation;


void main()
{
    vec3 p = transformation * vec3(pos, 1);

    float angle = atan(p.y, p.x) * frequency;


    if (angle > 0)
    {
        float ratio = angle / 6.28318530718;

        if (ratio < peak_position)
        {
            float value = ratio / peak_position;
            output_color = mix(color_b, color_a, value);
        }
        else
        {

        }
    }
    else
    {

    }

    output_color = vec4(1, 0, 0, 1);
}
