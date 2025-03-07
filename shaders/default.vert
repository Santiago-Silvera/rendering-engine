#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;


out vec2 texCoord;
out vec3 Normal;
out vec3 currPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main() {
    currPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = camMatrix * model * vec4(currPos, 1.0f);
    texCoord = aTex;
    Normal = aNormal;
}
