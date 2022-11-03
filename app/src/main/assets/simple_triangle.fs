#version 320 es
precision mediump float;
in vec4 vFragColor;
out vec4 glFragColor;

void main() {
    glFragColor = vFragColor;
}