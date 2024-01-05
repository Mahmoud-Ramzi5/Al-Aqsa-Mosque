#shader vertex
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 textures;

out vec3 FragPos;
out vec3 Normal;
out vec2 fragmentTextures;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragmentTextures = textures;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 fragmentTextures;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture0;

void main()
{
    vec4 objectColor = texture(texture0, fragmentTextures);
    // ambient    
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(Normal/*vec3(0.0f, 1.0f, 0.0f)*/);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 result = (vec4(ambient,1.0f) + vec4(diffuse,1.0f) + vec4(specular,1.0f)) * objectColor;
    FragColor = result;
}

//texture(texture1, fragmentTextures)* * vec4(lightcolor*fragmentColors,1.0f)