#shader vertex
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 color; 

out vec3 vertexColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = color;
}

#shader fragment
#version 460 core
 
 in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.7216, 0.6157, 0, 1.0);
}