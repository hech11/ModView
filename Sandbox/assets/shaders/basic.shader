#type vertex
#version 330 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoords;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_View = mat4(1.0f);
uniform mat4 u_Proj = mat4(1.0f);

out vec2 v_TexCoords;

void main() {
	gl_Position =  u_Proj * u_View * u_Model * aPos;
	v_TexCoords = aTexCoords;
}


#type fragment
#version 330 core



uniform vec4 u_Color;

out vec4 FragColor;
in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main() {

	FragColor = texture2D(u_Texture, v_TexCoords);
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}