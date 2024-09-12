uniform sampler2D texture; // Input texture
uniform vec2 lightPos;    // Position of the light source
uniform float lightRadius;  // Radius of the light
uniform vec4 lightColor; // Color of the light
uniform vec4 ambientColor; // Ambient color

void main()
{
    // Get the position of the current pixel
    vec2 pos = gl_TexCoord[0].xy;

    // Calculate the distance from the light source to the current pixel
    float dist = distance(pos, lightPos);

    // Calculate the attenuation factor
    float attenuation = clamp(1.0 - (dist / lightRadius), 0.0, 1.0);

    // Sample the texture and apply the attenuation factor
    vec4 texColor = texture2D(texture, pos);
    vec4 finalColor = texColor * (ambientColor + attenuation * lightColor);

    // Output the final color
    gl_FragColor = finalColor;
}