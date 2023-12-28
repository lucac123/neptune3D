#version 400 core
in vec4 gl_FragCoord;
in float zLayer;

layout (location = 0) out vec3 substanceOut;

uniform sampler3D uSubstance;

uniform float uDeltaTime;
uniform float uTime;

uniform float uAmount;
uniform vec3 uPosition;
uniform float uRadius;

void main() {
	vec3 fragCoord = vec3(gl_FragCoord.xy, zLayer);
	ivec3 cell = ivec3(fragCoord);

	substanceOut = texelFetch(uSubstance, cell, 0).rgb;

	float pi = 3.14159;
	float red = 0.5*sin(uTime)+0.6;
	float green = 0.5*sin(uTime+(2*pi/3))+0.6;
	float blue = 0.5*sin(uTime+(4*pi/3))+0.6;

	vec3 amount = uAmount * uDeltaTime * normalize(vec3(red, green, blue));
	float splat = exp(-1*pow(distance(fragCoord, uPosition), 2) / uRadius);

	substanceOut += amount * splat;
}