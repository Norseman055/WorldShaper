#version 150

in vec4 interpColor;
in vec3 interpNormal;

varying vec2 surfaceUV;

uniform vec4 cameraPos;
uniform vec4 specularColor;
uniform float shininess;
uniform sampler2D tex;

out vec4 fragmentColor;

void main(void)
{
	vec4 lightColor = vec4(1, 1, 1, 1);
	vec3 lightPos = vec3(4.0f, -1.0f, -3.0f);
	vec4 ambient = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	vec4 color = texture(tex, surfaceUV.xy) * interpColor * lightColor;

	// ambient light is simple; just multiple standard light color by ambient vec3
	vec4 final_color = ambient * color;

	// now to determine if we should display diffuse and specular.
	// similar to the unitNormal we found in program_1 and 2, we normalize the vec3 from the interpolated pixel position to the light position
	// then we normalize the interpolated pixel position and check the dot product to see if the pixel in question faces the light for diffuse shading
	vec3 L = normalize(interpNormal - lightPos);
	vec3 N = normalize(interpNormal);

	if (dot(N, L) > 0.0) 
	{
		// if it IS facing the light source, apply the diffuse shader to the pixel first
		vec4 diffuse = clamp(dot(interpNormal, L), 0, 1) * color;
		final_color += diffuse;

		// then find the pixels where the reflection from the lightPos to the eye (0, 0, -1) have a dot product greater than 0
		// these pixels should be colored based on the specular color and shininess of the specular effect, in this case white and 50
		// apply the specular vec4 to the final_color i'm using to track everything
		vec3 E = normalize(vec3(cameraPos));
		vec3 R = reflect(-L, N);
		vec4 specular = pow(max(dot(R, E), 0.0), shininess) * specularColor;
		final_color += specular;
	}

	// the fragment color should equal the sum of all the light effects applied to the base
	fragmentColor = final_color;
}
