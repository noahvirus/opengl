#version 330 core
layout (location = 0) in vec2 position;
uniform mat4 projection;

void main()
{
   vec4 centeredPosition = vec4(position, 0.0, 1.0) + vec4(0.5, 0.5, 0.0, 0.0);
   gl_Position = projection * centeredPosition;
}