#version 330

in vec2 texcoord;

out vec4 outBuffer;

void main(){
	outBuffer = vec4(texcoord,0.5,1);
}
