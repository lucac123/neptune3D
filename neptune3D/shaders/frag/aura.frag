#version 400 core
in vec3 vTexel;
in vec3 vGlobalPosition;

out vec4 fColor;

uniform sampler3D uField;

uniform vec3 uCameraPos;

uniform vec3 uBoxCorner;
uniform vec3 uBoxVector;

uniform float uStepSize;
uniform float uParticleBrightness;

vec3 globalToTexel(vec3 coord);
bool isTexelInBounds(vec3 texel);

void main() {
	vec3 rayDirection = normalize(vGlobalPosition - uCameraPos);
	vec4 rayColor = vec4(0);

	vec3 raySample = vGlobalPosition;
	while (isTexelInBounds(globalToTexel(raySample))) {
		vec3 color = uParticleBrightness * texture(uField, globalToTexel(raySample)).rgb;
		color = abs(color);
		rayColor += vec4(color, (color.r+color.g+color.b)/3);

		raySample += uStepSize * rayDirection;
	}

	fColor = rayColor;
}

vec3 globalToTexel(vec3 coord) {
	return (coord - uBoxCorner) / uBoxVector;
}

bool isTexelInBounds(vec3 texel) {
	return (texel.x >= 0 && texel.x <= 1) &&
			(texel.y >= 0 && texel.y <= 1) &&
			(texel.z >= 0 && texel.z <= 1);
}
