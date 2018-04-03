#version 330

// The normal map shader

out vec4 outBuffer;
uniform sampler2D heightMap;
uniform sampler2D normalMap

in vec2 texcoord;

float value(in vec4 c) {

// gradient of what:

return c.x;// the height is stored in all channels (take the first one)

}


void main() {

  vec2 ps = 1./vec2(textureSize(heightMap,0));

  vec2 g = vec2(value(texture(heightMap, texcoord+vec2(ps.x, 0.)))-
		value(texture(heightMap, texcoord-vec2(ps.x, 0.))), 
		value(texture(heightMap, texcoord+vec2(0., ps.y))) - 
		value(texture(heightMap, texcoord-vec2(0., ps.y))))/2.;

float scale = 100.;

vec3 n1 = vec3(1., 0., g.x*scale);

vec3 n2 = vec3(0., 1., -g.y*scale);

vec3 n = normalize(cross(n1, n2));

outBuffer = vec4(n, value(texture(heightMap, texcoord)));
}
