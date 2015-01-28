void main(void)
{
    gl_FrontColor = gl_Color;
    gl_PointSize = 20.0;
    gl_Position = ftransform();
}
