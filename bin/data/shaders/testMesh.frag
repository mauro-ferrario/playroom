#version 330

float shadow;
// Directional Light

struct DirLight {
  vec3 direction;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
#define NR_DIR_LIGHTS 1
uniform DirLight dirLights[NR_DIR_LIGHTS];

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
in vec3 Normal;
in vec3 FragPos;
uniform float near;
uniform float far;

// For shadow

in vec4 v_VertInLightSpace;
uniform float u_bias;
uniform float u_width;
uniform float u_height;
uniform float u_shadowIntensity;
uniform sampler2D  tShadowMap;

vec2 poissonDisk[16];

// End for shadow

// For shadow 2

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
  vec4 FragPosLightSpace;
} fs_in;

float ShadowCalculation(vec4 fragPosLightSpace)
{
  // perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;
  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(tShadowMap, vec2(projCoords.x, 1.0 - projCoords.y)).r;
  // get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  float bias = 0.00015;
  vec3 lightDir = normalize(pointLights[0].position - fs_in.FragPos);
  bias = max(0.0005 * (1.0 - dot(Normal, lightDir)), 0.0009);
  float shadow = 0.0;
  // smooth shadow
  vec2 texelSize = 4.0 / textureSize(tShadowMap, 0);
  for(int x = -1; x <= 1; ++x)
  {
    for(int y = -1; y <= 1; ++y)
    {
      float pcfDepth = texture(tShadowMap, vec2(projCoords.x, 1.0 - projCoords.y) + vec2(x, 1.0 - y) * texelSize).r;
      shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
    }
  }
  shadow /= 9.0; // intensity
  
//  shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
// shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
  if(projCoords.z > 1.0)
    shadow = 0.0;
  return shadow;
}

// End for shadow 2

float getShadowMultipler(){
  
  //                                       poissonDisk[0] = vec2( -0.94201624, -0.39906216 );
  //                                       poissonDisk[1] = vec2( 0.94558609, -0.76890725 );
  //                                       poissonDisk[2] = vec2( -0.094184101, -0.92938870 );
  //                                       poissonDisk[3] = vec2( 0.34495938, 0.29387760 );
  
  poissonDisk[0] = vec2( -0.94201624, -0.39906216 );
  poissonDisk[1] = vec2( 0.94558609, -0.76890725 );
  poissonDisk[2] = vec2( -0.094184101, -0.92938870 );
  poissonDisk[3] = vec2( 0.34495938, 0.29387760 );
  poissonDisk[4] = vec2( -0.91588581, 0.45771432 );
  poissonDisk[5] = vec2( -0.81544232, -0.87912464 );
  poissonDisk[6] = vec2( -0.38277543, 0.27676845 );
  poissonDisk[7] = vec2( 0.97484398, 0.75648379 );
  poissonDisk[8] = vec2( 0.44323325, -0.97511554 );
  poissonDisk[9] = vec2( 0.53742981, -0.47373420 );
  poissonDisk[10] = vec2( -0.26496911, -0.41893023 );
  poissonDisk[11] = vec2( 0.79197514, 0.19090188 );
  poissonDisk[12] = vec2( -0.24188840, 0.99706507 );
  poissonDisk[13] = vec2( -0.81409955, 0.91437590 );
  poissonDisk[14] = vec2( 0.19984126, 0.78641367 );
  poissonDisk[15] = vec2( 0.14383161, -0.14100790 );
  vec3 normal     = normalize(Normal);
  vec3 tdepth = v_VertInLightSpace.xyz / v_VertInLightSpace.w;
  vec4 depth  = vec4( tdepth.xyz, v_VertInLightSpace.w );
  
  depth.y = 1.0 - depth.y;
  
  float shadow = 1.0;
  vec2 UVCoords = depth.xy;
  
  float stexel = texture( tShadowMap, depth.xy ).r;
  int numSamples = 16;
  float shadowDec = 1.0/float(numSamples);
  for( int i = 0; i < numSamples; i++ ) {
    float texel = texture( tShadowMap, UVCoords.xy + (poissonDisk[i]/(u_width*0.75)) ).r;
    if( texel < depth.z - u_bias ) {
      shadow -= shadowDec * u_shadowIntensity;
    }
  }
  shadow = clamp( shadow, 0.0, 1.0 );
  
  // are you behind the shadow view? //
  if( v_VertInLightSpace.z < 1.0) {
    shadow = 1.0;
  }
  return shadow;
}

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
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  
  // phase 1: Directional lighting
  vec3 result = vec3(0.0);
  for(int i = 0; i < NR_DIR_LIGHTS; i++)
    result += CalcDirLight(dirLights[i], norm, viewDir);
  // phase 2: Point lights
  for(int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
  // phase 3: Spot light
  //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
  
  FragColor = vec4(result*getShadowMultipler(), 1.0);
  FragColor = vec4(result, 1.0);
//  float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
//  FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
//  FragColor = vec4(vec3(depth), 1.0);
  
  // For shadow 2
  
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


