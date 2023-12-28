#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out vec3 vectorOut;

uniform sampler3D uVectorField;
uniform sampler3D uScalarField;
uniform float uCellSize;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	float right = texelFetch(uScalarField, cell + ivec3(1,0,0), 0).x;
	float left = texelFetch(uScalarField, cell + ivec3(-1,0,0), 0).x;
	
	float top = texelFetch(uScalarField, cell + ivec3(0,1,0), 0).x;
	float bottom = texelFetch(uScalarField, cell + ivec3(0,-1,0), 0).x;

	float front = texelFetch(uScalarField, cell + ivec3(0,0,1), 0).x;
	float back = texelFetch(uScalarField, cell + ivec3(0,0,-1), 0).x;

	vectorOut = texelFetch(uVectorField, cell, 0).xyz - vec3(right-left, top-bottom, front-back) / (2 * uCellSize);
}