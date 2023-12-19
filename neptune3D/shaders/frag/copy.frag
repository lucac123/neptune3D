#version 400 core
layout (pixel_center_integer) in vec4 gl_FragCoord;
in float zLayer;

out vec3 fOut;

uniform sampler3D uIn;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);

	fOut = texelFetch(uIn, ivec3(fragCoord), 0).rgb;
}