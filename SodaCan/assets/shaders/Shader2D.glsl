@vertex
#version 410 core
			
layout(location = 0) in vec3 a_vrtxPosition;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoord;

out vec2 v_texCoord;
out vec4 v_color;

uniform mat4 u_PVMat;

void main()
{
	gl_Position = u_PVMat * vec4(a_vrtxPosition, 1.0);
	v_texCoord = a_texCoord;
	v_color = a_color;
}



@fragment
#version 410 core

layout(location = 0) out vec4 Color;

in vec2 v_texCoord;
in vec4 v_color;

uniform vec4 u_Color;
uniform float u_TextureScale;
uniform sampler2D u_Texture;

void main()
{
	// Color = texture(u_Texture, v_texCoord * u_TextureScale) * u_Color;
	Color = v_color;
}