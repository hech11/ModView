#type vertex
#version 330 core

layout(location = 0) in vec4 aPos;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_View = mat4(1.0f);
uniform mat4 u_Proj = mat4(1.0f);

void main() {
	gl_Position =  u_Proj * u_View * u_Model * aPos;
}


#type fragment
#version 330 core



out vec4 FragColor;
uniform vec4 u_Color;


void main() {
	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}