#version 330 core

uniform float width;
uniform float height;
uniform float u_time;

in vec3 ourColor;

void main() {
  vec2 u_resolution = vec2(width, height);

  gl_FragColor = vec4(ourColor, 1.0f);
  // Normalize pixel coordinates (from 0 to 1)
  //vec2 uv = gl_FragCoord.xy/u_resolution.xy;
  //
  //// Center the coordinate system
  //uv = uv * 2.0 - 1.0;
  //
  //// Calculate angle for rotation
  //float angle = atan(uv.y, uv.x);
  //
  //// Calculate distance from center
  //float radius = length(uv);
  //
  //// Create spinning effect
  //float spin = angle + u_time;
  //
  //// Create rainbow effect using HSV to RGB conversion
  //vec3 col;
  //float hue = spin / (3.14159 * 2.0) + u_time * 0.5;
  //
  //// HSV to RGB conversion
  //float h = mod(hue, 1.0) * 6.0;
  //float f = mod(h, 1.0);
  //float p = 0.0;
  //float q = 1.0 - f;
  //float t = f;
  //
  //if(h < 1.0) col = vec3(1.0, t, p);
  //else if(h < 2.0) col = vec3(q, 1.0, p);
  //else if(h < 3.0) col = vec3(p, 1.0, t);
  //else if(h < 4.0) col = vec3(p, q, 1.0);
  //else if(h < 5.0) col = vec3(t, p, 1.0);
  //else col = vec3(1.0, p, q);
  //
  //// Add fade out at edges
  //col *= smoothstep(1.0, 0.8, radius);
  
  // Output final color

  
}
