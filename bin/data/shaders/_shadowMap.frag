#version 330

out vec4 FragColor;

in vec3 v_Normal;
in vec4 v_VertInLightSpace;
in vec3 v_LightDir;

uniform float       u_bias;
uniform float       u_width;
uniform float       u_height;

uniform float u_shadowIntensity;
uniform sampler2D  tShadowMap;

vec2 poissonDisk[16];


void main( void ) {
  
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
  
  vec3 normal     = normalize(v_Normal);
//  vec3 lightDir   = v_LightDir;
  
//  float lambert = max(dot(normal, normalize(lightDir) ), 0.0);
  
  // get projected shadow value
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
  
  FragColor.a = 1.0;
  
  vec4 diffuse = vec4(0.7,0.0,0.0, 1.0) * shadow;
  
  FragColor.xyz = diffuse.xyz;
  
}
