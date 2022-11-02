#version 320 es
layout(location = 0) in float vPosition;
layout(location = 1) in float vSensorValue;

void main() {
    gl_Position = vec4(vPosition, vSensorValue/9.81, 0, 1);
}
