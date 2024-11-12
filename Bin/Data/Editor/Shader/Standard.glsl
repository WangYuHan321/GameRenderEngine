#shader vertex
#version 430 core

layout (location = 0) in vec3 geo_Pos;
layout (location = 1) in vec2 geo_TexCoords;
layout (location = 2) in vec3 geo_Normal;
layout (location = 3) in vec3 geo_Tangent;
layout (location = 4) in vec3 geo_Bitangent;

/* Global information sent by the engine */
layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
};

/* Information passed to the fragment shader */
out VS_OUT
{
    vec3        FragPos;
    vec3        Normal;
    vec2        TexCoords;
    mat3        TBN;
    flat vec3   TangentViewPos;
    vec3        TangentFragPos;

    vec4 lightDepthPos0;
} vs_out;

uniform mat4 shadow_lightDepthMat0;

void main()
{
    vs_out.TBN = mat3
    (
        normalize(vec3(ubo_Model * vec4(geo_Tangent,   0.0))),
        normalize(vec3(ubo_Model * vec4(geo_Bitangent, 0.0))),
        normalize(vec3(ubo_Model * vec4(geo_Normal,    0.0)))
    );

    mat3 TBNi = transpose(vs_out.TBN);

    vs_out.FragPos          = vec3(ubo_Model * vec4(geo_Pos, 1.0));
    vs_out.Normal           = normalize(mat3(transpose(inverse(ubo_Model))) * geo_Normal);
    vs_out.TexCoords        = geo_TexCoords;
    vs_out.TangentViewPos   = TBNi * ubo_ViewPos;
    vs_out.TangentFragPos   = TBNi * vs_out.FragPos;

    vs_out.lightDepthPos0 =  shadow_lightDepthMat0 * vec4(vs_out.FragPos, 1.0);


    gl_Position = ubo_Projection * ubo_View * vec4(vs_out.FragPos, 1.0);
}

#shader fragment
#version 430 core

/* Global information sent by the engine */
layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
};

/* Information passed from the fragment shader */
in VS_OUT
{
    vec3        FragPos;
    vec3        Normal;
    vec2        TexCoords;
    mat3        TBN;
    flat vec3   TangentViewPos;
    vec3        TangentFragPos;

    vec4 lightDepthPos0;
    //vec4 lightDepthPos1;
} fs_in;

uniform vec2 shadow_poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

/* Light information sent by the engine */
layout(std430, binding = 0) buffer LightSSBO
{
    mat4 ssbo_Lights[];
};

/* Uniforms (Tweakable from the material editor) */
uniform vec2        u_TextureTiling           = vec2(1.0, 1.0);
uniform vec2        u_TextureOffset           = vec2(0.0, 0.0);
uniform vec4        u_Diffuse                 = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3        u_Specular                = vec3(1.0, 1.0, 1.0);
uniform float       u_Shininess               = 100.0;
uniform float       u_HeightScale             = 0.0;
uniform bool        u_EnableNormalMapping     = false;
uniform sampler2D   u_DiffuseMap;
uniform sampler2D   u_SpecularMap;
uniform sampler2D   u_NormalMap;
uniform sampler2D   u_HeightMap;
uniform sampler2D   u_MaskMap;

uniform sampler2D   shadow_LightDepthMap0;
uniform int shadow_shadowCast = 0;

/* Global variables */
vec3 g_Normal;
vec2 g_TexCoords;
vec3 g_ViewDir;
vec4 g_DiffuseTexel;
vec4 g_SpecularTexel;
vec4 g_HeightTexel;
vec4 g_NormalTexel;

out vec4 FRAGMENT_COLOR;

bool PointInAABB(vec3 p_Point, vec3 p_AabbCenter, vec3 p_AabbHalfSize)
{
    return
    (
        p_Point.x > p_AabbCenter.x - p_AabbHalfSize.x && p_Point.x < p_AabbCenter.x + p_AabbHalfSize.x &&
        p_Point.y > p_AabbCenter.y - p_AabbHalfSize.y && p_Point.y < p_AabbCenter.y + p_AabbHalfSize.y &&
        p_Point.z > p_AabbCenter.z - p_AabbHalfSize.z && p_Point.z < p_AabbCenter.z + p_AabbHalfSize.z
    );
}

vec2 ParallaxMapping(vec3 p_ViewDir)
{
    const vec2 parallax = p_ViewDir.xy * u_HeightScale * texture(u_HeightMap, g_TexCoords).r;
    return g_TexCoords - vec2(parallax.x, 1.0 - parallax.y);
}

vec3 BlinnPhong(vec3 p_LightDir, vec3 p_LightColor, float p_Luminosity)
{
    const vec3  halfwayDir          = normalize(p_LightDir + g_ViewDir);
    const float diffuseCoefficient  = max(dot(g_Normal, p_LightDir), 0.0);
    const float specularCoefficient = pow(max(dot(g_Normal, halfwayDir), 0.0), u_Shininess * 2.0);

    return p_LightColor * g_DiffuseTexel.rgb * diffuseCoefficient * p_Luminosity + ((p_Luminosity > 0.0) ? (p_LightColor * g_SpecularTexel.rgb * specularCoefficient * p_Luminosity) : vec3(0.0));
}

float LuminosityFromAttenuation(mat4 p_Light)
{
    const vec3  lightPosition   = p_Light[0].rgb;
    const float constant        = p_Light[0][3];
    const float linear          = p_Light[1][3];
    const float quadratic       = p_Light[2][3];

    const float distanceToLight = length(lightPosition - fs_in.FragPos);
    const float attenuation     = (constant + linear * distanceToLight + quadratic * (distanceToLight * distanceToLight));
    return 1.0 / attenuation;
}

vec3 CalcPointLight(mat4 p_Light)
{
    /* Extract light information from light mat4 */
    const vec3 lightPosition  = p_Light[0].rgb;
    const vec3 lightColor     = vec3(p_Light[2][0], p_Light[2][1], p_Light[2][2]);
    const float intensity     = p_Light[3][3];

    const vec3  lightDirection  = normalize(lightPosition - fs_in.FragPos);
    const float luminosity      = LuminosityFromAttenuation(p_Light);

    return BlinnPhong(lightDirection, lightColor, intensity * luminosity);
}

vec3 CalcDirectionalLight(mat4 light)
{
    return BlinnPhong(-light[1].rgb, vec3(light[2][0], light[2][1], light[2][2]), light[3][3]);
}

vec3 CalcSpotLight(mat4 p_Light)
{
    /* Extract light information from light mat4 */
    const vec3  lightPosition   = p_Light[0].rgb;
    const vec3  lightForward    = p_Light[1].rgb;
    const vec3  lightColor      = vec3(p_Light[2][0], p_Light[2][1], p_Light[2][2]);
    const float intensity       = p_Light[3][3];
    const float cutOff          = cos(radians(p_Light[3][1]));
    const float outerCutOff     = cos(radians(p_Light[3][1] + p_Light[3][2]));

    const vec3  lightDirection  = normalize(lightPosition - fs_in.FragPos);
    const float luminosity      = LuminosityFromAttenuation(p_Light);

    /* Calculate the spot intensity */
    const float theta           = dot(lightDirection, normalize(-lightForward)); 
    const float epsilon         = cutOff - outerCutOff;
    const float spotIntensity   = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
    
    return BlinnPhong(lightDirection, lightColor, intensity * spotIntensity * luminosity);
}

vec3 CalcAmbientBoxLight(mat4 p_Light)
{
    const vec3  lightPosition   = p_Light[0].rgb;
    const vec3  lightColor      = vec3(p_Light[2][0], p_Light[2][1], p_Light[2][2]);
    const float intensity       = p_Light[3][3];
    const vec3  size            = vec3(p_Light[0][3], p_Light[1][3], p_Light[2][3]);

    return PointInAABB(fs_in.FragPos, lightPosition, size) ? g_DiffuseTexel.rgb * lightColor * intensity : vec3(0.0);
}

vec3 CalcAmbientSphereLight(mat4 p_Light)
{
    const vec3  lightPosition   = p_Light[0].rgb;
    const vec3  lightColor      = vec3(p_Light[2][0], p_Light[2][1], p_Light[2][2]);
    const float intensity       = p_Light[3][3];
    const float radius          = p_Light[0][3];

    return distance(lightPosition, fs_in.FragPos) <= radius ? g_DiffuseTexel.rgb * lightColor * intensity : vec3(0.0);
}

bool whithinRange(vec2 texCoord)
{
	return texCoord.x >= 0.0 && texCoord.x <= 1.0 && texCoord.y >= 0.0 && texCoord.y <= 1.0;
}

float getShadowVisibility(int i, vec3 rawNormal)
{
    vec3 lightDir = -ssbo_Lights[i][1].rgb;
    float visible = 1.0;
	float shadow = 1.0;
    float bias = 0.01;

	// Check first the highest resolution (but smaller) map
    vec3 ndcXYZ = fs_in.lightDepthPos0.xyz / fs_in.lightDepthPos0.w;
    vec2 uvCoord = ndcXYZ.xy;
	uvCoord.x = (uvCoord.x + 1) * 0.5;
    uvCoord.y = (uvCoord.y + 1) * 0.5;
	ndcXYZ.z = (ndcXYZ.z + 1) * 0.5;

	if(whithinRange(uvCoord))
	{
        float curDepth = ndcXYZ.z;
        vec2 texelSize = 1.0 / textureSize(shadow_LightDepthMap0, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadow_LightDepthMap0, uvCoord).r; 
                shadow += curDepth - bias > pcfDepth  ? 1.0 : 0.0;        
            }    
        }
        shadow /= 9.0;
        visible = 1.0 - shadow;
	}
	return visible;
}

void main()
{
    g_TexCoords = u_TextureOffset + vec2(mod(fs_in.TexCoords.x * u_TextureTiling.x, 1), mod(fs_in.TexCoords.y * u_TextureTiling.y, 1));

    /* Apply parallax mapping */
    if (u_HeightScale > 0)
        g_TexCoords = ParallaxMapping(normalize(fs_in.TangentViewPos - fs_in.TangentFragPos));

    /* Apply color mask */
    if (texture(u_MaskMap, g_TexCoords).r != 0.0)
    {
        g_ViewDir           = normalize(ubo_ViewPos - fs_in.FragPos);
        g_DiffuseTexel      = texture(u_DiffuseMap,  g_TexCoords) * u_Diffuse;
        g_SpecularTexel     = texture(u_SpecularMap, g_TexCoords) * vec4(u_Specular, 1.0);

        if (u_EnableNormalMapping)
        {
            g_Normal = texture(u_NormalMap, g_TexCoords).rgb;
            g_Normal = normalize(g_Normal * 2.0 - 1.0);   
            g_Normal = normalize(fs_in.TBN * g_Normal);
        }
        else
        {
            g_Normal = normalize(fs_in.Normal);
        }

        vec3 lightSum = vec3(0.0);
		float visible = 1.0f;
        
		for (int i = 0; i < ssbo_Lights.length(); ++i)
        {
            visible = getShadowVisibility(i, fs_in.Normal);
            switch(int(ssbo_Lights[i][3][0]))
            {
                case 0: lightSum += CalcPointLight(ssbo_Lights[i]) * visible;         break;
                case 1: lightSum += CalcDirectionalLight(ssbo_Lights[i]) * visible;   break;
                case 2: lightSum += CalcSpotLight(ssbo_Lights[i]) * visible;          break;
                case 3: lightSum += CalcAmbientBoxLight(ssbo_Lights[i]);    break;
                case 4: lightSum += CalcAmbientSphereLight(ssbo_Lights[i]); break;
            }
        }
        vec3 mapped = lightSum / (lightSum + vec3(1.0));	
        FRAGMENT_COLOR = vec4(mapped , g_DiffuseTexel.a);
    }
    else
    {
        FRAGMENT_COLOR = vec4(0.0);
    }
}