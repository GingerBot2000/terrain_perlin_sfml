#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;

vec2 easing(vec2 t)
{
    // 6x^5 - 15x^4 + 10x^3
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float perlin_val(vec2 p)
{
    vec2 p_floor = floor(p); // * bottom left corner in lattice of point
    vec2 p_fract = fract(p);

    // * Four corners in 2D of a tile
    float a = rand(p_floor);                    // * bl
    float b = rand(p_floor + vec2(1.0, 0.0));   // * br
    float c = rand(p_floor + vec2(0.0, 1.0));   // * tl
    float d = rand(p_floor + vec2(1.0, 1.0));   // * tr

    // * easing function
    vec2 u = easing(p_fract);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main() {
    vec2 pos = gl_FragCoord.xy / resolution;

    vec2 v = pos * 5.0+ time*.5;
    float n = perlin_val(v);

    gl_FragColor = vec4(n, n, n, 1.0);

}
