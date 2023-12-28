#version 400 core

out VS_OUT {
	int vertexLayer;
} vs_out;

void main() {
	float vertID = gl_VertexID;
	gl_Position = vec4(0, 0, 0, 1);
	vs_out.vertexLayer = gl_VertexID;
}