#version 330

layout(location = 0) in vec3 position;

uniform mat4 mdvMat;
uniform mat4 projMat;

out vec2 texpos;

void main() {
	gl_Position = projMat*mdvMat*vec4(position, 1);
	texpos = position.xy*0.5+0.5;
}
