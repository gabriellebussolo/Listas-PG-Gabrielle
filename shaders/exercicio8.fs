#version 400

in vec3 vertexColor;

//uniform vec4 inputColor;
out vec4 color;

void main()
{
	color = vec4(vertexColor,1.0);

}