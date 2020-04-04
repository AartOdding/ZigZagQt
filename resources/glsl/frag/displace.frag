#version 330


uniform sampler2D inputTexture;
uniform sampler2D displaceTexture;

in vec2 pos;

layout(location = 0) out vec4 output_color;


uniform float strength;
uniform float direction;
uniform float offset;
uniform int   channel;



void main()
{
    float str = strength * (texture(displaceTexture, pos)[channel] - offset);
    vec2 displacement = vec2(cos(direction) * str, sin(direction) * str);
    output_color = texture(inputTexture, pos + displacement);
    //output_color = vec4(str, str, str, 1);
    //vec4 color_a = texture(input_a, pos);
    //vec4 color_b = texture(input_b, pos);
    //output_color = mix(color_a, color_b, fade_position);
    //output_color = color_b;//mix(color_b, color_a, fade_position);
}
