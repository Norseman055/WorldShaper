#version 150

in vec4 vertexPos;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 UV;

varying vec2 surfaceUV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 interpColor;
out vec3 interpNormal;

void main(void)
{
	interpColor = vertexColor;
	interpNormal = transpose(inverse(mat3(viewMatrix) * mat3(modelMatrix))) * vertexNormal;
	surfaceUV = UV;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexPos;
}
