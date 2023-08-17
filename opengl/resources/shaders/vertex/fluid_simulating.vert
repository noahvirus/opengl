#version 330 core

layout (location = 0) in vec2 position;

out vec2 texCoord;

void main()
{
    // Pass the vertex position to the fragment shader
    texCoord = position * 0.5 + 0.5; // Convert to [0, 1] range
    gl_Position = vec4(position, 0.0, 1.0);
}