#version 330

// The normal map shader

layout(location = 0) in vec3 vertex;

out vec2 texcoord;

uniform mat4 mdvMat;
uniform mat4 projMat;

void main() {

	gl_Position = projMat*mdvMat*vec4(vertex, 1);

	texcoord = vertex.xy*0.5+0.5;
}
