#version 330

uniform sampler2D gSampler;

in vec2 TexCoord0;



void main()

{
	gl_FragColor = texture2D(gSampler, TexCoord0.st);
}
