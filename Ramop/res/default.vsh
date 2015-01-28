void main(void)
{
    gl_FrontColor = gl_Color;
    gl_PointSize = 1.0;
    gl_Position = ftransform();
}
