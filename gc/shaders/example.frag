// Shader-ul de fragment / Fragment shader 
#version 120

varying vec4 ex_Color;

void main(void)
{
    gl_FragColor = ex_Color;
}