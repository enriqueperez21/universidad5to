#version 330 core
out vec4 FragColor;

in vec3 ourColor;//1
in vec2 TexCoord;//*****

uniform sampler2D textureSampler;
uniform bool useTexture;
uniform float visibility; //visibilidad de la textura

void main()
{
   //FragColor = texture(textureSampler, TexCoord);//****
    if (useTexture) {
        //FragColor = texture(textureSampler, TexCoord)*visibility;
        FragColor = mix(texture(textureSampler, TexCoord), vec4(ourColor, 1.0), 1.0 - visibility);
    } else {
        //FragColor = vec4(ourColor, 1.0) * (1.0 - visibility);;
        FragColor = vec4(ourColor, 1.0);
    }
}