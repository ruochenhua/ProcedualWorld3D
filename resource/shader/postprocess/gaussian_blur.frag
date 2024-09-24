#version 450 compatibility
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D bright_texture;

uniform bool horizontal;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{

     vec2 tex_offset = 1.0 / textureSize(bright_texture, 0); // gets size of single texel
     vec3 result = texture(bright_texture, TexCoords).rgb * weight[0];
     if(horizontal)
     {
         for(int i = 1; i < 5; ++i)
         {
             vec2 blur_plus_coord = TexCoords + vec2(tex_offset.x * i, 0.0);
             if(blur_plus_coord.x <= 1)
             {
                 result += texture(bright_texture, blur_plus_coord).rgb * weight[i];
             }
             vec2 blur_minus_coord = TexCoords - vec2(tex_offset.x * i, 0.0);
             if(blur_minus_coord.x >= 0)
             {
                 result += texture(bright_texture, blur_minus_coord).rgb * weight[i];
             }
         }
     }
     else
     {
         for(int i = 1; i < 5; ++i)
         {
             vec2 blur_plus_coord = TexCoords + vec2(0.0, tex_offset.y * i);
             if(blur_plus_coord.y <= 1)
             {
                 result += texture(bright_texture, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
             }
             vec2 blur_minus_coord = TexCoords - vec2(0.0, tex_offset.y * i);
             if(blur_minus_coord.y >= 0)
             {
                 result += texture(bright_texture, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
             }
         }
     }
     FragColor = vec4(result, 1.0);
//    FragColor = texture(bright_texture, TexCoords);
}