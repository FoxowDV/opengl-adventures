#version 330 core

precision mediump float;

in vec3 position;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main()
{
	
	if (u_mouse.x >  u_resolution.x/2) {
		gl_FragColor = vec4(0.5, 0.0, 0.0, 1.0);

	} else {
		//gl_FragColor = vec4(sin(u_time)/2.0 + 0.5, 0.0, 0.0, 1.0);
		gl_FragColor = vec4(0.1, 0.1, 1.0, 1.0);
	}

}

