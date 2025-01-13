#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform int texturenum;

void main()
{
	if(texturenum == 0){
		// linearly interpolate between both textures (80% container, 20% awesomeface)
		FragColor = texture(texture1, TexCoord);
	}
	else if(texturenum == 1){
		// linearly interpolate between both textures (80% container, 20% awesomeface)
		FragColor = texture(texture2, TexCoord);
	}else if (texturenum == 2){
		// linearly interpolate between both textures (80% container, 20% awesomeface)
		FragColor = texture(texture3, TexCoord);
	}
	
}