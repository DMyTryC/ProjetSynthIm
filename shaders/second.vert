#version 330

// The normal map shader

<<<<<<< HEAD
layout(location = 0) in vec3 vertex;

out vec2 texcoord;

uniform mat4 mdvMat;
uniform mat4 projMat;

void main() {

	gl_Position = projMat*mdvMat*vec4(vertex, 1);

	texcoord = vertex.xy*0.5+0.5;
=======

layout(location = 0) in vec3 position;

out vec2 texcoord;

in vec2 vertex;

void main() {

	gl_Position = vec4(vertex, 0, 1);

	texcoord = position.xy*0.5+0.5;
>>>>>>> 9a3d4fbffc7dce5e8d4d4704ffdfe1e12ae035c1
}
