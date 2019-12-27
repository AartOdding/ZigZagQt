#version 330

layout(location = 0) in vec2 vertex;

out vec2 relative_position;

void main()
{
    relative_position = 0.5 * (vertex + vec2(1, 1));
    gl_Position = vec4(vertex, 0.0, 1.0);
}
