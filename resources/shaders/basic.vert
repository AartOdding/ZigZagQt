#version 330

layout(location = 0) in vec2 vertex;

uniform vec2 output_range_x;
uniform vec2 output_range_y;

out vec2 pos;


vec2 map(vec2 value, vec2 input_min, vec2 input_max, vec2 output_min, vec2 output_max)
{
  return output_min + (output_max - output_min) * (value - input_min) / (input_max - input_min);
}


void main()
{
    pos = map(vertex, vec2(-1, -1), vec2(1, 1), vec2(output_range_x.x, output_range_y.x), vec2(output_range_x.y, output_range_y.y));
    gl_Position = vec4(vertex, 0.0, 1.0);
}
