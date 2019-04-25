#version 410
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;

out vec3 vertNormal;
out vec3 vertDir;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform sampler3D sp3D; 

void main() {

	vec3 timetest = vec3(time, time, time);

	vec3 temp = vVertex.xyz * length(timetest);

	vec4 noise = texture3D(sp3D, temp);

	vertNormal = normalMatrix * (vNormal.xyz + noise.xyz);

	vec4 newVector = vVertex + (vNormal * noise * 2);

	vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); 

	vertDir = normalize(vertPos);

	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * newVector;  


}