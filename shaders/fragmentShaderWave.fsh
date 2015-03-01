//#version 440

varying vec3 lightDir,normal;
uniform sampler2D tex;

uniform float blur_radius;

uniform sampler2D s_texture;

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[14];



 uniform sampler2D RTScene; // the texture with the scene you want to blur
varying vec2 vTexCoord;
 
float blurSize = 1.0/512.0; // I've chosen this size because this will result in that every step will be one pixel wide if the RTScene texture is of size 512x512
 
 
 
 
 
varying vec2 uv;
const float sampleDist = 1.0;
const float sampleStrength = 2.2; 

void main()
{
	
    vec3 ct;
    vec4 texel;
    float intensity,at;
	
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a;
    gl_FragColor = vec4(ct, at);
 
}