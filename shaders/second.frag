#version 330

// The normal map shader


out vec4 outBuffer;

<<<<<<< HEAD
uniform sampler2D normalmap;
uniform sampler2D heightmap;
=======
uniform sampler2D heightMap;

//layout(location = 0) in vec4 normal;
>>>>>>> 9a3d4fbffc7dce5e8d4d4704ffdfe1e12ae035c1

in vec2 texcoord;

float value(in vec4 c) {

	// gradient of what:

	return c.x;// the height is stored in all channels (take the first one)
}


void main() {
<<<<<<< HEAD
  	vec2 ps = 1./vec2(textureSize(heightmap,0));

	vec2 g = vec2(value(texture(heightmap,texcoord+vec2(ps.x,0.))) -
			value(texture(heightmap,texcoord-vec2(ps.x,0.))),
			value(texture(heightmap,texcoord+vec2(0.,ps.y))) -
			value(texture(heightmap,texcoord-vec2(0.,ps.y))))/2.;

	float scale = 100.;

	vec3 n1 = vec3(1.,0.,g.x*scale);

	vec3 n2 = vec3(0.,1.,-g.y*scale);

	vec3 n = normalize(cross(n1,n2));

	outBuffer = vec4(n, value(texture(heightmap, texcoord)));
=======
  	vec2 ps = 1./vec2(textureSize(heightMap, 0));

	vec2 g = vec2(value(texture(heightMap, texcoord+vec2(ps.x, 0.)))-
		value(texture(heightMap, texcoord-vec2(ps.x, 0.))), 
		value(texture(heightMap, texcoord+vec2(0., ps.y))) - 
		value(texture(heightMap, texcoord-vec2(0., ps.y))))/2.;

	float scale = 100.;

	vec3 n1 = vec3(1., 0., g.x*scale);

	vec3 n2 = vec3(0., 1., -g.y*scale);

	vec3 n = normalize(cross(n1, n2));

	outBuffer = vec4(n, value(texture(heightMap, texcoord)));
	//normal = outBuffer;
>>>>>>> 9a3d4fbffc7dce5e8d4d4704ffdfe1e12ae035c1
}
