#version 330 core

uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;
attribute vec4 gl_Vertex;

layout(location = 0) in vec3 vertexPosition_modelspace;

void main()
{
	//gl_Position.xyz=vertexPosition_modelspace;
	//gl_Position.w=1.0;
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	
	vec4 v = vec4(gl_Vertex);
	//v.x = 0.0;

	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * v;
}