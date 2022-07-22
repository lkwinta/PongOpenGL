#version 330 core

uniform vec3 bgcolor;

out vec4 outColor;

void main(){
    outColor = vec4(bgcolor, 1.0);
}