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
	//texel.x+=1;
	//texel.y+=1;
	//texel.z+=1;
 
    ct = texel.rgb;
    at = texel.a;
    gl_FragColor = vec4(ct, at);
	
	sampler2D texture=tex;
	
	blur_radius=2;
	
	vec2 offx = vec2(blur_radius, 0.0);
	vec2 offy = vec2(0.0, blur_radius);

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * 4.0 +
				 texture2D(texture, gl_TexCoord[0].xy - offx)        * 2.0 +
				 texture2D(texture, gl_TexCoord[0].xy + offx)        * 2.0 +
				 texture2D(texture, gl_TexCoord[0].xy - offy)        * 2.0 +
				 texture2D(texture, gl_TexCoord[0].xy + offy)        * 2.0 +
				 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 +
				 texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 +
				 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 +
				 texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0;
				 
				 
	//pixel=texture2D(tex,gl_TexCoord[0].st);
    gl_FragColor =  gl_Color * (pixel / 16.0);
    gl_FragColor = vec4(pixel.rgb, at);
    gl_FragColor = vec4(ct, at);
	
	
	//sampler2D s_texture=texel;
    /*gl_FragColor = vec4(texel.rgb, at/2);
	//gl_FragColor = vec4(0.0);
	gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 0])*0.0044299121055113265*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 1])*0.00895781211794*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 2])*0.0215963866053*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 3])*0.0443683338718*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 4])*0.0776744219933*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 5])*0.115876621105*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 6])*0.147308056121*blur_radius;
    gl_FragColor += texture2D(s_texture, v_texCoord         )*0.159576912161*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 7])*0.147308056121*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 8])*0.115876621105*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 9])*0.0776744219933*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[10])*0.0443683338718*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[11])*0.0215963866053*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[12])*0.00895781211794*blur_radius;
    gl_FragColor += texture2D(s_texture, v_blurTexCoords[13])*0.0044299121055113265*blur_radius;*/
	
	
	
	
	
	
	
	
	//blurSize=0.000000;
	/*vec4 sum = vec4(0.0);
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(RTScene, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * 0.05;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 3.0*blurSize, vTexCoord.y)) * 0.09;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 2.0*blurSize, vTexCoord.y)) * 0.12;
   sum += texture2D(RTScene, vec2(vTexCoord.x - blurSize, vTexCoord.y)) * 0.15;
   sum += texture2D(RTScene, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;
   sum += texture2D(RTScene, vec2(vTexCoord.x + blurSize, vTexCoord.y)) * 0.15;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 2.0*blurSize, vTexCoord.y)) * 0.12;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 3.0*blurSize, vTexCoord.y)) * 0.09;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 4.0*blurSize, vTexCoord.y)) * 0.05;
 */
   //gl_FragColor = sum;
	
	
	
	
	
	
	
	
	
	
	
	
	
	  float samples[10];
    samples[0] = -0.08;
    samples[1] = -0.05;
    samples[2] = -0.03;
    samples[3] = -0.02;
    samples[4] = -0.01;
    samples[5] =  0.01;
    samples[6] =  0.02;
    samples[7] =  0.03;
    samples[8] =  0.05;
    samples[9] =  0.08;

    vec2 dir = 0.5 - uv; 
    float dist = sqrt(dir.x*dir.x + dir.y*dir.y); 
    dir = dir/dist; 

    vec4 color = texture2D(tex,uv); 
    vec4 sum = color;

    for (int i = 0; i < 10; i++)
        sum += texture2D( tex, uv + dir * samples[i] * sampleDist );

    sum *= 1.0/11.0;
    float t = dist * sampleStrength;
    t = clamp( t ,0.0,1.0);

    gl_FragColor = mix( color, sum, t );
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
    /*vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
	
	intensity = max(dot(lightDir,normalize(normal)),0.0);
 
    cf = intensity * (gl_FrontMaterial.diffuse).rgb +
                  gl_FrontMaterial.ambient.rgb;
    af = gl_FrontMaterial.diffuse.a;
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a;
    gl_FragColor = vec4(ct * cf, at * af);*/
 
}