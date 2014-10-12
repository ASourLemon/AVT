#version 330

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

layout (std140) uniform Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

layout (std140) uniform Lights {
	vec3 l_dir;	   // camera space
};

in vec4 position;	// local space
in vec3 normal;		// local space

// the data to be sent to the fragment shader
out Data {
	vec4 color;
} DataOut;


void main () {
	// transform normal to camera space and normalize it
	vec3 n = normalize(m_normal * normal);

	// compute the intensity as the dot product
	// the max prevents negative intensity values
	float intensity = max(dot(n, l_dir), 0.0);

	// Compute the color
	DataOut.color = intensity * diffuse;

	// transform the vertex coordinates
	gl_Position = m_pvm * position;	
}