@vertex
#version 410 core
			
layout(location = 0) in vec3 a_vrtxPosition;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_PVMat;
uniform mat4 u_ModelMat;

void main()
{
	gl_Position = u_PVMat * u_ModelMat * vec4(a_vrtxPosition, 1.0);
}



@fragment
#version 410 core

layout(location = 0) out vec4 Color;

uniform vec4 u_Color;

void main()
{
	Color = u_Color;
}