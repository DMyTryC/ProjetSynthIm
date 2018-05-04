#version 330

//uniform vec4 FogColor;

in vec4 mVertex;
in vec4 mColor;
in vec3 eyeView;

float getFogFactor(float d)
{
    const float FogMax = 20.0;
    const float FogMin = 10.0;

    if (d>=FogMax) return 1.0;
    if (d<=FogMin) return 0.0;

    return (1 - (FogMax - d) / (FogMax - FogMin));
}

void main(void)
{
    vec4 FogColor = vec4(0.5f,0.5f,0.5f,1.0f);
    vec4 eye = vec4(eyeView,1.0);
    float d = distance(eye, mVertex);
    d = normalize(d);
    float alpha = getFogFactor(d);
    gl_FragColor = mix(mColor,FogColor, alpha);
}
