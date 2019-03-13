#version 330
//Default from OF::programmableRenderer
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 cubeModelMatrix;
uniform mat4 normalMatrix;
uniform int doTwist;
uniform float time;

//Default from OF::shader
in vec4  position;
in vec3 normal;
in vec2  texcoord;
out vec3 FragPos;
out vec3 Normal;

//Out for frag
out vec4 colorVarying;
out vec2 TexCoords;

//Uniform setup in ofApp
uniform mat4 modView;
uniform mat4 model;
// model o modelMatrix sono la stessa cosa

void addTwist(vec4 position);
vec4 DoTwist( vec4 pos, float t )
{
  float percDistortion = (pos.y + 15.0)/30.0;
//  percDistortion = 1.0;
  float st = sin(t*percDistortion);
  float ct = cos(t*percDistortion);
  vec4 new_pos;
  
  new_pos.x = (pos.x*ct - pos.z*st);
  new_pos.z = (pos.x*st + pos.z*ct);
  
  new_pos.y = pos.y;
  new_pos.w = pos.w;
  
//  if(pos.y < -10.0){
//    return pos;
//  }
  return( new_pos );
}

float angle_deg_max = 180.0;
float height = 30.0;


// Try to use the normalMatrix!!
void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
  FragPos = vec3(modelMatrix * vec4(position.xyz, 1.0));
  // Usre inverse(traspose...)  mi sembra più corretto che usare la normalMatrix
  Normal = ( inverse(transpose(modelMatrix)) * vec4(normal, 0.0)).xyz;
  if(doTwist == 1){
    addTwist(position);
  }
  
  //normal = gl_NormalMatrix * twistedNormal.xyz;
  

  TexCoords = texcoord;
}

void addTwist(vec4 position){
  float angle_deg = angle_deg_max*sin(time*0.001);
  float angle_rad = angle_deg * 3.14159 / 180.0;
  float ang = (height*0.5 + position.y)/height * angle_rad;
  vec4 twistedPosition = DoTwist(position, ang);
  vec4 twistedNormal = DoTwist(vec4(normal, 0.0), ang);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * twistedPosition;
  FragPos = vec3(modelMatrix * vec4(twistedPosition.xyz, 1.0));
  Normal = ( inverse(transpose(modelMatrix)) * vec4(twistedNormal)).xyz;
}
