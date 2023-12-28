#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out float divergenceOut;

uniform sampler3D uVectorField;
uniform float uCellSize;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	float right = texelFetch(uVectorField, cell + ivec3(1,0,0), 0).x;
	float left = texelFetch(uVectorField, cell + ivec3(-1,0,0), 0).x;
	
	float top = texelFetch(uVectorField, cell + ivec3(0,1,0), 0).y;
	float bottom = texelFetch(uVectorField, cell + ivec3(0,-1,0), 0).y;

	float front = texelFetch(uVectorField, cell + ivec3(0,0,1), 0).z;
	float back = texelFetch(uVectorField, cell + ivec3(0,0,-1), 0).z;


	divergenceOut = ((right-left) + (top-bottom) + (front-back)) / (2 * uCellSize);
}