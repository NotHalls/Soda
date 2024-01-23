@vertex
#version 450 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 u_ModelMat;
uniform mat4 u_PVMat;

void main()
{
    gl_Position = u_PVMat * u_ModelMat * vec4(aPosition, 1.0);
    vertexColor = aColor;
    texCoord = aTexCoord;
}

@fragment
#version 450 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D u_DiffuseTexture;

void main()
{
	fragColor = texture(u_DiffuseTexture, texCoord) * vertexColor;
}