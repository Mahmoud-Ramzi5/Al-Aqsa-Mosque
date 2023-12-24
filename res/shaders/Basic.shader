#shader vertex
#version 460 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec3 colors;
layout(location = 2) in vec2 textures;
out vec3 fragmentColors;
out vec2 fragmentTextures;
uniform mat4 trans;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;


//projection* model* view*

void main()
{
	gl_Position = projection *view * model * vec4(positions, 1.0f);
	fragmentColors = colors;
	fragmentTextures = textures;
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec3 fragmentColors;
in vec2 fragmentTextures;

uniform  vec3 lightcolor;
uniform sampler2D texture0;

void main()
{
	color = texture(texture0, fragmentTextures);
	//vec4(1.0, 0.0, 0.0, 1.0f);
};

//texture(texture1, fragmentTextures)* * vec4(lightcolor*fragmentColors,1.0f)