#version 330
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform mat4 lightSpaceMatrix;
in vec4  position;

void main()
{
//  gl_Position = lightSpaceMatrix * modelMatrix * vec4(position);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position);
}
