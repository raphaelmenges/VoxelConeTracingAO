#version 330

/*
* Fragmentshader to pass out geometry into the GBuffer.
* We pass out diffuse color, position and normal.
*/

//!< in-variables
in vec3 passWorldPosition;
in vec2 passUVCoord;
in vec3 passWorldNormal;
in vec3 passWorldTangent;

//!< uniforms
uniform vec4 color;
uniform float blendColor;
uniform sampler2D tex;

//!< out-
layout(location = 0) out vec4 fragPosition;
layout(location = 1) out vec4 fragColor;
layout(location = 2) out vec4 fragNormal;
layout(location = 3) out vec4 fragTangent;

void main()
{
    vec4 color = texture(tex,passUVCoord).rgba;

    if(color.a < 0.1)
    {
        discard;
    }
	
    fragColor = vec4(color.rgb, 1);
    fragPosition = vec4(passWorldPosition,1);
    fragNormal =  normalize(vec4(passWorldNormal,0));
    fragTangent =  normalize(vec4(passWorldTangent,0));
}