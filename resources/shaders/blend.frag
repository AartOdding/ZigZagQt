#version 330


uniform sampler2D input_a;
uniform sampler2D input_b;

in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform int blend_mode;


const int BLEND_MODE_OVER       = 0;
const int BLEND_MODE_ADD        = 1;
const int BLEND_MODE_SUBTRACT   = 2;
const int BLEND_MODE_MULTIPLY   = 3;
const int BLEND_MODE_DIVIDE     = 4;
const int BLEND_MODE_AVERAGE    = 5;
const int BLEND_MODE_DIFFERENCE = 6;


void main()
{
    switch (blend_mode)
    {
        case BLEND_MODE_OVER:
            output_color = 0.5 * texture(input_a, pos) + 0.5 * texture(input_b, pos);
            return;
        case BLEND_MODE_ADD:
            output_color = texture(input_b, pos);
            return;
        case BLEND_MODE_SUBTRACT:
            output_color = vec4(0);
            return;
        case BLEND_MODE_MULTIPLY:
            output_color = vec4(0);
            return;
        case BLEND_MODE_DIVIDE:
            output_color = vec4(1);
            return;
        case BLEND_MODE_AVERAGE:
            output_color = 0.5 * texture(input_a, pos) + 0.5 * texture(input_b, pos);
            return;
        case BLEND_MODE_DIFFERENCE:
            output_color = abs(texture(input_a, pos) - texture(input_b, pos));
            return;
    }
    output_color = vec4(0);
    return;
}
