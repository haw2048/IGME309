#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Complimentary = false;

out vec4 Fragment;

void main()
{
	vec3 change = Color;
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		{
			change = SolidColor;
		}
	
	if(Complimentary == true)
		{
			change = vec3(1.0f, 1.0f, 1.0f) - change;
		}
		
	Fragment = vec4(change,1);

	return;

}