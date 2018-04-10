#version 330

// The noise generation


// input attributes
layout(location = 0) in vec3 position;

out vec2 pos;

uniform mat4 mdvMat;
uniform mat4 projMat;

void main() {
  // no need for any particular transformation (Identity matrices)
  pos = position.xy*0.5+0.5;
<<<<<<< HEAD
  gl_Position = projMat*mdvMat*vec4(position,1);
=======
  gl_Position = vec4(position, 1);
>>>>>>> 9a3d4fbffc7dce5e8d4d4704ffdfe1e12ae035c1
}
