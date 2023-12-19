#version 400 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
	int vertexLayer;
} gs_in[];

out float zLayer;

void main() {
	zLayer = gs_in[0].vertexLayer;

	gl_Layer = gs_in[0].vertexLayer;
	gl_Position = vec4(-1, -1, 0, 1);
	EmitVertex();

	gl_Layer = gs_in[0].vertexLayer;
	gl_Position = vec4(1, -1, 0, 1);
	EmitVertex();

	gl_Layer = gs_in[0].vertexLayer;
	gl_Position = vec4(-1, 1, 0, 1);
	EmitVertex();

	gl_Layer = gs_in[0].vertexLayer;
	gl_Position = vec4(1, 1, 0, 1);
	EmitVertex();
	EndPrimitive();
}