#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out vec3 vectorOut;

uniform sampler3D uInputField;
uniform sampler3D uTransportField;

uniform float uDeltaTime;

void main() {
	vec3 dimensions = vec3(textureSize(uInputField, 0));
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	vec3 traceBackCoord = fragCoord - texelFetch(uTransportField, cell, 0).rgb * uDeltaTime;
	vectorOut = texture(uInputField, traceBackCoord/dimensions).rgb;
}