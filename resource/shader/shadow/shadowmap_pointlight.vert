#version 450 compatibility

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 in_pos;

// Values that stay constant for the whole mesh.
uniform mat4 model;

void main(){
	gl_Position =  model * vec4(in_pos, 1);
}

