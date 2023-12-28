#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out vec3 xOut;

uniform sampler3D uXField;
uniform sampler3D uBField;

uniform float uAlpha;
uniform float uBeta;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	vec3 xLeft = texelFetch(uXField, cell + ivec3(-1,0,0), 0).rgb;
	vec3 xRight = texelFetch(uXField, cell + ivec3(1,0,0), 0).rgb;
	vec3 xTop = texelFetch(uXField, cell + ivec3(0,1,0), 0).rgb;
	vec3 xBottom = texelFetch(uXField, cell + ivec3(0,-1,0), 0).rgb;
	vec3 xFront = texelFetch(uXField, cell + ivec3(0,0,1), 0).rgb;
	vec3 xBack = texelFetch(uXField, cell + ivec3(0,0,-1), 0).rgb;

	vec3 bCenter = texelFetch(uBField, cell, 0).rgb;

	xOut = (xLeft + xRight + xTop + xBottom + xBack + uAlpha*bCenter) / uBeta;
}

/*
	x_{i,j,k}'=( x_{i-1,j,k} + x_{i+1,j,k} + x_{i,j-1,k} + x_{i,j+1,k} + x_{i,j,k-1} + x_{i,j,k+1} + alpha*b_{i,j,k} )/ beta
					* one iteration of jacobi iteration *

	DIFFUSION JACOBI SOLVER
	x = velocity
	b = velocity
	alpha = (cellSize)^2/(viscosity*deltaTime)
	beta = 6 + alpha

	PRESSURE JACOBI SOLVER
	x = pressure
	b = div(velocity)
	alpha = -(cellSize)^2
	beta = 6
*/