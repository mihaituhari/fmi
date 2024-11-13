// Shader-ul de varfuri / Vertex shader
#version 120

attribute vec4 in_Position;
attribute vec4 in_Color;

varying vec4 ex_Color;

void main()
{
    gl_Position = in_Position;
    ex_Color = in_Color;
}
