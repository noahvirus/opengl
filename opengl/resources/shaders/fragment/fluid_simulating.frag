 #version 330 core

in vec2 texCoord;

uniform sampler2D fluidTexture;
    
out vec4 FragColor;

void main()
{
    // Sample the texture and display the result
    FragColor = texture(fluidTexture, texCoord);
}