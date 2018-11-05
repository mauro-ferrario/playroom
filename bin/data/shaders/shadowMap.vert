#version 330
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform mat4 lightSpaceMatrix;
uniform mat4  u_ShadowTransMatrix;
uniform vec3  u_lightPosInWorldSpace;
in vec4  position;
in vec3 normal;

out vec3  v_Normal;
out vec4  v_VertInLightSpace;
out vec3  v_LightDir;


void main()
{
  vec4 vertInViewSpace = modelViewMatrix * position;
  
  v_Normal = (inverse(transpose(modelMatrix)) * vec4(normal, 0.0)).xyz;
  v_LightDir = ( u_lightPosInWorldSpace - vertInViewSpace.xyz );
  
  v_VertInLightSpace = u_ShadowTransMatrix * vertInViewSpace;
  
//  gl_Position = lightSpaceMatrix * modelMatrix * vec4(position);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position);
}
