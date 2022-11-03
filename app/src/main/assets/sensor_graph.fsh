#version 320 es
precision mediump float;

layout(location = 2) uniform vec4 uFragColor;
out vec4 glFragColor;

void main() {
    glFragColor = uFragColor;
}
