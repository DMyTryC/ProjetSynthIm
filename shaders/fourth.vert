#version 330

uniform mat4 mvp;
uniform mat4 mdvMat;

layout(location = 0) in vec3 vertice;
//layout(location = 1) in vec4 Color;

//out vec4 mColor;
out vec3 mVertex;
out vec3 eyeView;

void main(void)
{
    //mColor = Color;
    //mVertex = vec4(vertice,1.0);
	mVertex = vertice;
    gl_Position = mvp*vec4(vertice,1.0);
	eyeView = normalize((mdvMat*vec4(vertice,1.0)).xyz);
}

