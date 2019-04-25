#version 410

in vec3 uvwCoords;

out vec4 fragColor;

uniform samplerCube skyBoxTexture; 

void main() { 

	fragColor = texture(skyBoxTexture, uvwCoords);	
} 

