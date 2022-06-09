### Why is the bottom left side of our triangle black? 

The rgba values in OpenGL usually takes values from 0-1, where numbers below 0 is converted to 0.
Since our fragment shader now takes the color value from the position of our vertices, 
and we have negative values for the bottom left, it converted the negative values to 0, resulting in a black color.

```
GLfloat vertices[] =
	{
		-0.5f, -0.5, 0.0f, // bottom left
		0.5f, -0.5, 0.0f, // bottom right
		0.0f, 0.5, 0.0f, // top
	};
```
