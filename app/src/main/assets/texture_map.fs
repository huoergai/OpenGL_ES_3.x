#version 320 es
precision mediump float;

in vec2 vTexCoord;
layout(location = 0) out vec4 outColor;
uniform sampler2D sTextureMap;

void main() {
    outColor = texture(sTextureMap, vTexCoord);
}