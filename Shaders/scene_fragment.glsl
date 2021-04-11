#version 330 core

const float PI = 3.1415926535897932384626433832795;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 light_direction;
uniform sampler2D textureSampler ;
uniform vec3 object_color;


const float shading_ambient_strength    = 0.2;
const float shading_diffuse_strength    = 1.0f;
const float shading_specular_strength   = 0.8;

uniform float light_cutoff_outer;
uniform float light_cutoff_inner;
uniform float light_near_plane;
uniform float light_far_plane;

uniform vec3 ambient = vec3(0.0f);
uniform vec3 diffuse = vec3(0.0f);
uniform vec3 specular = vec3(0.0f);
uniform int issphere =0 ;
uniform vec3 view_position;
uniform int testtext ; 
uniform int shadow_or_not ;

uniform sampler2D depth_map_texture;
in vec2 UV ;
in vec3 fragcol ;
in vec3 fragment_position;
in vec4 fragment_position_light_space;
in vec3 fragment_normal;

in vec4 gl_FragCoord;

out vec4 result;

vec3 ambient_color(vec3 light_color_arg) {
    return shading_ambient_strength * light_color_arg;
}

vec3 diffuse_color(vec3 light_color_arg, vec3 light_position_arg) {
    vec3 light_direction = normalize(light_position_arg - fragment_position);
    return shading_diffuse_strength * light_color_arg * max(dot(normalize(fragment_normal), light_direction), 0.0f);
}

vec3 specular_color(vec3 light_color_arg, vec3 light_position_arg) {
    vec3 light_direction = normalize(light_position_arg - fragment_position);
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_light_direction = reflect(-light_direction, normalize(fragment_normal));
    return shading_specular_strength * light_color_arg * pow(max(dot(reflect_light_direction, view_direction), 0.0f),32);
}


float shadow_scalar() {
    // this function returns 1.0 when the surface receives light, and 0.0 when it is in a shadow
    // perform perspective divide
    vec3 ndc = fragment_position_light_space.xyz / fragment_position_light_space.w;
    // transform to [0,1] range
    ndc = ndc * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragment_position_light_space as coords)
    float closest_depth = texture(depth_map_texture, ndc.xy).r;
    // get depth of current fragment from light's perspective
    float current_depth = ndc.z;
    // check whether current frag pos is in shadow
    float bias = 0.0005;  // bias applied in depth map: see shadow_vertex.glsl
    return ((current_depth - bias) < closest_depth) ? 1.0 : 0.0;
}


void main()
{
    vec4 textureColor = texture(textureSampler,UV) ;
   
     float scalar ;
if (shadow_or_not==0){
     scalar = shadow_scalar() ; }else {scalar=shadow_scalar() ;}
 vec3   ambient1 =ambient_color(light_color);
   vec3   diffuse1 = scalar * diffuse_color(light_color, light_position);
   vec3   specular1 = scalar * specular_color(light_color, light_position);
 vec4 color ;
 float wvalue; 
 if (issphere==0){ wvalue=1.0 ;} else {wvalue=0.2; }
 if (testtext==0)
    {
     color =  vec4( vec3(specular1 + diffuse1 + ambient1),wvalue) * textureColor ;   result = color ;   }
 else {    color = vec4(vec3(specular1 + diffuse1 + ambient1) * fragcol,wvalue) ;  result = color ; }
     
  
 
} 

