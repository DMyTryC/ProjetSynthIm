#version 330

layout(location = 0) in vec3 position;

out vec2 texcoord;
uniform mat4 mdvMat;
uniform mat4 projMat;

void main(){
	gl_Position = projMat*mdvMat*vec4(position, 1);
	texcoord = position.xy*0.5+0.5;
}
