# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess;


vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolorIn, const in vec3 normal, const in vec3 halfvec) {
	float nDotL = dot(normal, direction);
	vec4 lambert = diffuse * lightcolorIn * max(nDotL, 0.0);

	float nDotH = dot(normal, halfvec);
	vec4 phong = specular * lightcolorIn * pow (max(nDotH, 0.0), shininess);

	return lambert + phong;
}

void main (void) 
{       
    if (enablelighting) {
		const vec3 eyePosition = vec3(0, 0, 0);

		vec4 myPosition4 = modelview * myvertex;  // Position was not transformed in vertex shader, so we do it here.
		vec3 myPosition3 = myPosition4.xyz / myPosition4.w;

		vec3 eyeDirection = normalize(eyePosition - myPosition3);

		vec3 normal = normalize(mat3(transpose(inverse(modelview))) * mynormal);  // Normal was not transformed in vertex shader, so we do it here

		vec4 finalcolor = ambient;

		vec4 lightPosition4;
		vec3 lightPosition3;
		vec3 lightDirection;
		vec3 halfAngleVector;

		for (int i = 0; i < numused; i++) {
			if (abs(lightposn[i].w) > 0.00001) // Point light, w != 0, with small tolerance for float error.
			{
				lightPosition4 = lightposn[i];
				lightPosition3 = lightPosition4.xyz / lightPosition4.w; 
				lightDirection = normalize(lightPosition3 - myPosition3); 
			}
			else // Directional light
			{
				lightPosition4 = lightposn[i];
				lightDirection = normalize(lightPosition4.xyz);
			}
			halfAngleVector = normalize(lightDirection + eyeDirection);
			finalcolor += ComputeLight(lightDirection, lightcolor[i], normal, halfAngleVector);
		}

        fragColor = finalcolor; 
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}