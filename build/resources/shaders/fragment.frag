#version 430 core
/** Outputs */
layout(location = 0) out vec4 out_color;

struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

/** Inputs */    
layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 vs_texcoords;
layout(location = 2) in vec3 fragPos;

/** Texture sampler */
layout(binding = 0) uniform sampler2D texture_diffuse;
uniform DirLight dirLight;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
  vec3 norm = normalize(normal);
  vec3 viewDir = normalize(-fragPos);

  vec3 result = CalculateDirLight(dirLight, norm, viewDir);
  out_color = vec4(result, 1.0);
}

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);

  vec3 ambient = light.ambient * vec3(texture(texture_diffuse, vs_texcoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse, vs_texcoords));
  vec3 specular = light.specular * spec * vec3(texture(texture_diffuse, vs_texcoords));
  return (ambient + diffuse + specular);
}
