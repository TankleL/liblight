uniform sampler2D sampler;
varying vec2 vTexCoord;

void main()
{
	vec4 tex_pixel = texture2D(sampler, vTexCoord);
	gl_FragColor = vec4(tex_pixel.r, tex_pixel.g, tex_pixel.b, 1.0);
}