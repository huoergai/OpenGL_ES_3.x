#version 320 es
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 aFragColor;

out vec4 vFragColor;

void main() {
    gl_Position = vPosition;
    vFragColor = aFragColor;
}
