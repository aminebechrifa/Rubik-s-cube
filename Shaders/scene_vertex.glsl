#version 330 core

uniform vec3 view_position;

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 couleur;
layout (location = 2) in vec2 vecuv;
layout (location = 3) in vec3 normals;


uniform vec3 couleur;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 light_proj_view_matrix;

out vec2 UV ;
out vec3 fragment_normal;
out vec3 fragment_position;
out vec4 fragment_position_light_space;
out vec3 fragcol ;
void main()
{   UV=vecuv ;
    fragcol=couleur ;
    fragment_normal = mat3(model_matrix) * normals;
    fragment_position = vec3(model_matrix * vec4(position, 1.0));
    fragment_position_light_space = light_proj_view_matrix * vec4(fragment_position, 1.0);
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}
