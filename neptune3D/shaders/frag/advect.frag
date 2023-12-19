#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out vec3 velocityOut;

uniform sampler3D uVelocity;

uniform float uDeltaTime;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	ivec3 traceBackCoord = ivec3(fragCoord - texelFetch(uVelocity, cell, 0).rgb * uDeltaTime);
	velocityOut = texelFetch(uVelocity, traceBackCoord, 0).rgb;
}