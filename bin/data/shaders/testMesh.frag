#version 330

float shadow;
// Directional Light

struct DirLight {
  vec3 direction;
  vec3 positionForShadow;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
#define NR_DIR_LIGHTS 1
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

// Point Light
struct PointLight {
  vec3 position;
  
  float constant;
  float linear;
  float quadratic;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float attenuationFactor;
};
#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// Color material

struct Material {
//  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
  int  useDiffuseTexture;
  sampler2D diffuseTexture;
};

uniform Material material;
uniform vec3 viewPos;
uniform float time;
in vec2 TexCoords;
// in vec3 Normal;
// in vec3 FragPos;
uniform float near;
uniform float far;

// For shadow

uniform sampler2D  shadowMap;

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
  vec4 FragPosLightSpace;
} fs_in;

uniform float shadowIntensity;

float ShadowCalculation(vec4 fragPosLightSpace)
{
  // perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;
  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(shadowMap, vec2(projCoords.x, 1.0 - projCoords.y)).r;
  // get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  float bias = 0.00015;
  vec3 lightDir = normalize(dirLight.positionForShadow - fs_in.FragPos);
  bias = max(0.0005 * (1.0 - dot(fs_in.Normal, lightDir)), 0.0009);
  float shadow = 0.0;
  // smooth shadow
  vec2 texelSize = 2.0 / textureSize(shadowMap, 0);
  for(int x = -1; x <= 1; ++x)
  {
    for(int y = -1; y <= 1; ++y)
    {
      float pcfDepth = texture(shadowMap, vec2(projCoords.x, 1.0 - projCoords.y) + vec2(x, 1.0 - y) * texelSize).r;
      shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
    }
  }
  shadow /= (1.0 - shadowIntensity) * 500.0; // intensity
  
  //  shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
  //  shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
  if(projCoords.z > 1.0)
    shadow = 0.0;
  return shadow;
}

// End for shadow

float LinearizeDepth(float depth)
{
  float z = depth * 2.0 - 1.0; // back to NDC
  return (2.0 * near * far) / (far + near - z * (far - near));
}

// Variables

out vec4 FragColor;

// Start main function

void main()
{
  shadow = ShadowCalculation(fs_in.FragPosLightSpace);
  // properties
  vec3 norm = normalize(fs_in.Normal);
  vec3 viewDir = normalize(viewPos - fs_in.FragPos);
  // phase 1: Directional lighting
  vec3 result = vec3(0.0);
  result += CalcDirLight(dirLight, norm, viewDir);
  // phase 2: Point lights
  for(int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(pointLights[i], norm, fs_in.FragPos, viewDir);
  // phase 3: Spot light
  //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
  FragColor = vec4(result, 1.0);
//  float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
//  FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
//  FragColor = vec4(vec3(depth), 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // combine results
  vec3 ambient  = light.ambient * material.diffuse;
  vec3 diffuse  = light.diffuse * diff * material.diffuse;
  if(material.useDiffuseTexture == 1)
    diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture, TexCoords));
  vec3 specular = light.specular * spec * material.specular;
  vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
  return lighting;
  return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  float constant = 1.0;
  float linear = 0.17;
  float quadratic = 0.192;
  
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // attenuation
  float dist    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * dist +
                             light.quadratic * (dist * dist));
  // combine results
  vec3 ambient  = light.ambient  * material.diffuse;
  vec3 diffuse  = light.diffuse  * diff * material.diffuse;
  if(material.useDiffuseTexture == 1)
    diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture, TexCoords));
  vec3 specular = light.specular * spec * material.specular;
  attenuation *= light.attenuationFactor*1000.0;
  
  ambient  *= attenuation;
  diffuse  *= attenuation;
  specular *= attenuation;
  vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
  return lighting;
  return (ambient + diffuse + specular);
}
