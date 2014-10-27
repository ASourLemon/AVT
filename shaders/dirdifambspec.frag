#version 330

uniform sampler2D texmap;

in Data {
	vec4 color;
	vec2 tex_coord;
} DataIn;

out vec4 colorOut;

void main() {
    vec4 texel = texture(texmap, DataIn.tex_coord);  // texel from lighwood.tga
	colorOut = DataIn.color*texel;
}