@vertex
#version 410 core
			
layout(location = 0) in vec3 a_vrtxPosition;
layout(location = 1) in vec2 a_texCoordinates;

out vec2 o_texCoordinates;

uniform mat4 u_PVMat;
uniform mat4 u_ModelMat;

void main()
{
	gl_Position = u_PVMat * u_ModelMat * vec4(a_vrtxPosition, 1.0);
	o_texCoordinates = a_texCoordinates;
}



@fragment
#version 410 core

layout(location = 0) out vec4 Color;

in vec2 o_texCoordinates;

uniform sampler2D u_Texture;

void main()
{
	Color = texture(u_Texture, o_texCoordinates);
}