#shader vertex
#version 460 core

layout(location = 0) in vec3 aPos;
out vec3 lightyColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 460 core

out vec4 FragColor;
//uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}