@vertex
#version 450 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 vertexColor;
out vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_ModelMat;
uniform mat4 u_PVMat;

void main()
{
	FragPos = vec3(u_ModelMat * vec4(aPosition, 1.0));
	Normal = mat3(transpose(inverse(u_ModelMat))) * aNormal;

    gl_Position = u_PVMat * u_ModelMat * vec4(aPosition, 1.0);
    vertexColor = aColor;
    texCoord = aTexCoord;
}

@fragment
#version 450 core

struct DirectionalLight
{
	vec3 direction;
	
	vec3 color;
	float ambientStrength;
	float specularStrength;
};
uniform DirectionalLight u_DirLight;


#define MAX_POINT_LIGHTS 100
struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 color;
	float ambientStrength;
	float specularStrength;

	int nLight;
} pLight;
uniform PointLight u_PointLight[MAX_POINT_LIGHTS];


#define MAX_SPOT_LIGHTS 100
struct SpotLight
{
	vec3 position;
	vec3 direction;

	float constant;
	float linear;
	float quadratic;

	vec3 color;
	float ambientStrength;
	float specularStrength;
	
	float cutOff;
	float outerCutOff;

	int nLight;
} sLight;
uniform SpotLight u_SpotLight[MAX_SPOT_LIGHTS];

uniform vec3 u_ViewPos;


in vec4 vertexColor;
in vec2 texCoord;

in vec3 FragPos;
in vec3 Normal;

out vec4 fragColor;

uniform sampler2D u_DiffuseTexture;


vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);


void main()
{	

	vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 normal = normalize(Normal);

	vec3 Light = vec3(0.0);
	Light += CalcDirectionalLight(u_DirLight, normal, viewDir);

	// for(int i = 0; i < pLight.nLight; ++i)
	// 	Light += CalcPointLight(u_PointLight[i], Normal, viewDir);
	// 
	// for(int i = 0; i < sLight.nLight; ++i)
	// 	Light += CalcSpotLight(u_SpotLight[i], Normal, viewDir);

	fragColor = vec4(Light, 1.0);
}


vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.specularStrength);
	
	vec3 ambient = (light.ambientStrength * light.color) * texture(u_DiffuseTexture, texCoord).rgb;
	vec3 diffuse = diff * light.color * texture(u_DiffuseTexture, texCoord).rgb;
	vec3 specular = spec * (5.0 * light.color) * texture(u_DiffuseTexture, texCoord).rgb;
	
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.specularStrength);
	
	vec3 ambient = light.ambientStrength * light.color;
	vec3 diffuse = diff * light.color;
	vec3 specular = spec * 0.5 * light.color;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	ambient *= attenuation * light.constant;
	diffuse *= attenuation * light.constant;
	specular *= attenuation * light.constant;
	
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.specularStrength);
	
	vec3 ambient = light.ambientStrength * light.color;
	vec3 diffuse = diff * light.color;
	vec3 specular = spec * light.specularStrength * light.color;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	
	ambient *= attenuation * light.constant;
	diffuse *= attenuation * light.constant;
	specular *= attenuation * light.constant;
	
	return (ambient + diffuse + specular);
}