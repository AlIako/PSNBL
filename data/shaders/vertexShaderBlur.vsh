//#version 330 core

uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;
attribute vec4 gl_Vertex;


varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[14];
attribute vec4 a_position;
attribute vec2 a_texCoord;



varying vec2 vTexCoord;




varying vec2 uv;



void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	
	
	
	
	
	
	/*v_texCoord = a_texCoord;
    v_blurTexCoords[ 0] = v_texCoord + vec2(0.0, -0.028);
    v_blurTexCoords[ 1] = v_texCoord + vec2(0.0, -0.024);
    v_blurTexCoords[ 2] = v_texCoord + vec2(0.0, -0.020);
    v_blurTexCoords[ 3] = v_texCoord + vec2(0.0, -0.016);
    v_blurTexCoords[ 4] = v_texCoord + vec2(0.0, -0.012);
    v_blurTexCoords[ 5] = v_texCoord + vec2(0.0, -0.008);
    v_blurTexCoords[ 6] = v_texCoord + vec2(0.0, -0.004);
    v_blurTexCoords[ 7] = v_texCoord + vec2(0.0,  0.004);
    v_blurTexCoords[ 8] = v_texCoord + vec2(0.0,  0.008);
    v_blurTexCoords[ 9] = v_texCoord + vec2(0.0,  0.012);
    v_blurTexCoords[10] = v_texCoord + vec2(0.0,  0.016);
    v_blurTexCoords[11] = v_texCoord + vec2(0.0,  0.020);
    v_blurTexCoords[12] = v_texCoord + vec2(0.0,  0.024);
    v_blurTexCoords[13] = v_texCoord + vec2(0.0,  0.028);*/
	
	
	/*
   // Clean up inaccuracies
   vec2 Pos;
   Pos = sign(gl_Vertex.xy);
 
   gl_Position = vec4(Pos, 0.0, 1.0);
   
   // Image-space
   vTexCoord = Pos * 0.5 + 0.5;
   
   */
   
   
   /*
   
   gl_Position = vec4( gl_Vertex.xy, 0.0, 1.0 );
    gl_Position =  gl_ProjectionMatrix * gl_ModelViewMatrix *sign( gl_Position );
    uv = (vec2( gl_Position.x, - gl_Position.y ) + vec2(1.0) ) / vec2(2.0);*/
 
}