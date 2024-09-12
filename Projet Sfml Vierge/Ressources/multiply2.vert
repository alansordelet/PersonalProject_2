attribute vec2 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
uniform mat3 u_transform;

void main()
{
    gl_Position = vec4(u_transform * vec3(a_position, 1.0), 1.0);
    v_texcoord = a_texcoord;
}