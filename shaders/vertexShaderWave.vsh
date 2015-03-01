uniform float time;

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
	
		float scale = 2.0;
	float x = gl_Vertex.x;
	float y = gl_Vertex.y;

	// calculate a scale factor.
	float s = sin( (time+3.0*y)*scale );
	float c = cos( (time+5.0*x)*scale );
	float z = 0.05 * s * c;

	// offset the position along the normal.
	vec3 v = gl_Vertex.xyz + gl_Normal * z;

	// transform the attributes.
	gl_Position = gl_ModelViewProjectionMatrix * vec4( v, 1.0 );
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	/*
		float scale = 2.0;
	float x = gl_Vertex.x;
	float y = gl_Vertex.y;

	// calculate a scale factor.
	float s = sin( (time+3.0*y)*scale );
	float c = cos( (time+5.0*x)*scale );
	float z = 0.05 * s * c;

	// offset the position along the normal.
	vec3 v = gl_Vertex.xyz + gl_Normal * z;

	// transform the attributes.
	gl_Position = gl_ModelViewProjectionMatrix * vec4( v, 1.0 );
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;*/
}