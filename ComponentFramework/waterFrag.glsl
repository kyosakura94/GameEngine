#version 410
in vec3 vertNormal;
in vec3 vertDir;

out vec4 fragColor;

uniform samplerCube skyBoxTexture; 

void main() { 

	float air = 1.00;
	float glass = 1.52;
	float water = 1.33;

	float ratio = air / water;

	float m = dot(vertDir, -vertNormal);

	//float f = pow(1 - ratio, 2.0) / pow (1 + ratio, 2.0);

	//float F = f + (1 - f) * pow( 1 - m, 5.0);

	vec3 Re = reflect(vertDir, vertNormal);
	vec3 Ra = refract(vertDir, vertNormal, ratio);

	vec4 ReC = texture(skyBoxTexture, Re);
	vec4 RaC = texture(skyBoxTexture, Ra);


	vec4 final = mix(ReC, RaC, m);
	
	fragColor = final;


} 

