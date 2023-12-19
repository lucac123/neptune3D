#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out vec3 velocityOut;

uniform sampler3D uVelocity;

uniform float uDeltaTime;

uniform vec3 uForce;
uniform vec3 uForcePos;
uniform float uForceRadius;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	velocityOut = texelFetch(uVelocity, cell, 0).rgb;

	vec3 force = uForce * uDeltaTime;
	float splat = exp(-1*pow(distance(fragCoord, uForcePos), 2) / uForceRadius);

	velocityOut += force * splat;
}