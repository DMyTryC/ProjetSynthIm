#version 330

uniform mat4 mvp;
uniform mat4 mdvMat;

layout(location = 0) in vec3 vertices;
//layout(location = 1) in vec4 Color;

in vec4 color;

out vec4 mColor;
out vec4 mVertex;
out vec3 eyeView;

void main(void)
{
    mColor = color;
    mVertex = vec4(vertices,1.0);
    gl_Position = mvp*vec4(vertices,1.0);
    eyeView = normalize((mdvMat*vec4(vertices,1.0)).xyz);
}

