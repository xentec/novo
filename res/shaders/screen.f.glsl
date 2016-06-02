#version 330 core

in VS_FS {
	vec2 tex;
} fsIn;

out vec4 outColor;

uniform sampler2D fb;
uniform int effectFlag;

vec4 invert(in sampler2D fb, in vec2 tex)
{
	return vec4(1.0) -  texture(fb, tex);
}

vec4 greyscale(in sampler2D fb, in vec2 tex)
{
	vec4 frag = texture(fb, tex);
	float avg = 0.2126 * frag.r + 0.7152 * frag.g + 0.0722 * frag.b;
	return vec4(avg, avg, avg, 1.0);
}


vec4 blur_box(in sampler2D fb, in vec2 tex, in int samplesN, in float sizeH, in float sizeV)
{
	vec4 sum = vec4(0.0);
	float samples = pow((samplesN+1) * 2.0, 2.0);
	for (int x = -samplesN; x <= samplesN; x++)
		for (int y = -samplesN; y <= samplesN; y++)
			sum += texture(fb, vec2(tex.x + x * sizeH, tex.y + y * sizeV)) / samples;
	return sum;
}

vec4 sobel(in sampler2D fb, in vec2 tex)
{
	vec4 s1 = texture(fb, tex - 1.0 / 300.0 - 1.0 / 200.0);
	vec4 s2 = texture(fb, tex + 1.0 / 300.0 - 1.0 / 200.0);
	vec4 s3 = texture(fb, tex - 1.0 / 300.0 + 1.0 / 200.0);
	vec4 s4 = texture(fb, tex + 1.0 / 300.0 + 1.0 / 200.0);
	vec4 sx = 4.0 * ((s4 + s3) - (s2 + s1));
	vec4 sy = 4.0 * ((s2 + s4) - (s1 + s3));
	return sx * sx + sy * sy;
}

void main() {
	switch(effectFlag)
	{
	case 1:
		outColor = invert(fb, fsIn.tex);
		break;
	case 2:
		outColor = greyscale(fb, fsIn.tex);
		break;
	case 3:
		outColor = blur_box(fb, fsIn.tex, 4, 1.0/300.0, 1.0/200.0);
		break;
	case 4:
		outColor = sobel(fb, fsIn.tex);
		break;
	case 5:
		if(fsIn.tex.x < 0.25)
			outColor = invert(fb, fsIn.tex);
		else if(fsIn.tex.x > 0.25 && fsIn.tex.x < 0.50)
			outColor = sobel(fb, fsIn.tex);
		else if(fsIn.tex.x > 0.50 && fsIn.tex.x < 0.75)
			outColor = blur_box(fb, fsIn.tex, 4, 1.0/300.0, 1.0/200.0);
		else if(fsIn.tex.x > 0.75)
			outColor = greyscale(fb, fsIn.tex);
		break;
	default:
		outColor = texture(fb, fsIn.tex);
	}
}
