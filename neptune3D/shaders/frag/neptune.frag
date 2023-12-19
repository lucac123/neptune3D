#version 400 core
layout (pixel_center_integer) in vec4 gl_FragCoord;
in float zLayer;

out vec3 texelColor;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);

	texelColor = vec3(fragCoord/128);
}