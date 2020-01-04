#version 330 core
out vec4 FragColor;
in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
}fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace,vec3 normal,vec3 lightDir)
{
	//【1】获取标准设备坐标
	vec3 projCoords = fragPosLightSpace.xyz/fragPosLightSpace.w;
	//【2】转换到[0,1]的范围
	projCoords = projCoords*0.5+0.5;
	//【3】计算深度映射纹理的最近深度
	float closestDepth = texture(shadowMap,projCoords.xy).r;
	//【4】计算灯光坐标系，片段的深度值
	float currentDepth = projCoords.z;
	//【5】比较得出阴影的值
	float bias = max(0.05*(1.0-dot(normal,lightDir)),0.005);
	//float shadow = currentDepth-bias > closestDepth ? 1.0:0.0;
	//去除边缘锯齿
	float shadow = 0.0;
	vec2 texelSize = 1.0/textureSize(shadowMap,0);
	for(int i = -1;i<= 1;++i)
	{
		for(int j = -1;j <= 1;++j)
		{
			float pcfDepth = texture(shadowMap,projCoords.xy + vec2(i,j)*texelSize).r;
			shadow += currentDepth-bias > pcfDepth ? 1.0:0.0;
		}
	}
	if(projCoords.z > 1.0)
		shadow = 0.0;
	return shadow/9.0;
}

void main()
{
	vec3 color = texture(diffuseTexture,fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(1.0);
	//环境光
	vec3 ambient = 0.3*lightColor;
	//漫反射
	vec3 lightDir = normalize(lightPos-fs_in.FragPos);
	float diff = max(dot(lightDir,fs_in.Normal),0.0);
	vec3 diffuse = diff*lightColor;
	//镜面反射光
	vec3 viewDir = normalize(viewPos-fs_in.FragPos);
	vec3 halfwayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(normal,halfwayDir),0.0),64.0);
	vec3 specular = spec*lightColor;
	//计算阴影
	float shadow = ShadowCalculation(fs_in.FragPosLightSpace,normal,lightDir);
	vec3 lighting = (ambient+(1.0-shadow)*(diffuse+specular))*color;
	FragColor = vec4(lighting,1.0);
}