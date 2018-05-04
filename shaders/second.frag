#version 330

// The normal map shader
uniform vec2 deplacement;
out vec4 outBuffer;

uniform sampler2D heightmap;

in vec2 texpos;

float value(in vec4 c) {

	// gradient of what:

	return c.x;// the height is stored in all channels (take the first one)
}


void main() {

	vec4 height = 1.0 - texture(heightmap,texpos.xy);
	
	if (height.z > 0.7) {
		outBuffer = vec4(0.9*height.xyz, 0);
	} else if (height.z <= 0.7 && height.z > 0.3) {
		outBuffer = vec4(0.4*height.xyz, 0);
	} else if (height.z <= 0.3 && height.z > 0.0) {
		outBuffer = vec4(0, 0.6*height.y, 0, 0);
	}
}
