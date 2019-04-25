#version 410

in vec3 vertNormal;
in vec3 vertDir;


out vec4 fragColor;

uniform samplerCube skyBoxTexture; 

void main() { 

	float air = 1.00;
	float glass = 1.52;
	float water = 1.33;

	float ratio = air / glass;

	vec3 Re = reflect(vertDir, vertNormal);
	vec3 Ra = refract(vertDir, vertNormal, ratio);

	vec4 ReC = texture(skyBoxTexture, Re);
	vec4 RaC = texture(skyBoxTexture, Ra);

	float t = dot(vertDir, -vertNormal);
	
	vec4 final = mix(ReC, RaC, t );

	fragColor = final;
} 

