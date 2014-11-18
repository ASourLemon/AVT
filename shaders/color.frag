#version 330

uniform sampler2D texmap;

in Data {
	vec4 texCoord;
} DataIn;

out vec4 outputF;
uniform bool selected;

void main()
{
	vec4 col=selected?vec4(1,0,0,1):vec4(1);
	outputF = texture(texmap, DataIn.texCoord.st)*col;
	if (outputF.a < 0.5 || outputF.a == 0.0 || outputF.rgb == vec3(0.0f)) {
		discard;
	}
		
} 
