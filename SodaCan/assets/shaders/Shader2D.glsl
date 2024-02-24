@vertex
#version 410 core
			
layout(location = 0) in vec3 a_vrtxPosition;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_texCoord;

uniform mat4 u_PVMat;
uniform mat4 u_ModelMat;

void main()
{
	gl_Position = u_PVMat * u_ModelMat * vec4(a_vrtxPosition, 1.0);
	v_texCoord = a_texCoord;
}



@fragment
#version 410 core

layout(location = 0) out vec4 Color;

in vec2 v_texCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	Color = texture(u_Texture, v_texCoord) * u_Color;
}