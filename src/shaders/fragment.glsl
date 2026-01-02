#version 330 core

out vec4 frag_color;

void main()
{
	if (gl_FragCoord.x > 400 && gl_FragCoord.x < 401)
		frag_color = vec4(1.0,0,0,0);
	else
		frag_color = vec4(0,1.0,0,0);
}
