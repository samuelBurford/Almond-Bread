#version 330 core
out vec4 FragColor;

uniform ivec2 u_resolution;
uniform float u_time;
uniform vec2 u_mousePos = vec2(0.0f,0.0f);
uniform float u_zoom = 1.0f;
uniform int u_maxIter = 2;

vec2 st = gl_FragCoord.xy/u_resolution;

float sens = 0.001;

int rows = 100;
int cols = 100;

float brot(int _maxIter)
{
	vec2 mousePos = vec2(u_mousePos.x , u_mousePos.y );

	st.x = (( st.x - 0.5 ) * u_zoom )  + ( mousePos.x * sens );
	st.y = (( st.y - 0.5 ) * u_zoom )  - ( mousePos.y * sens );

	float iters = 0.0f;
	if(distance(st, vec2(0,0)) <= 2)
	{
		
		vec2 z = vec2(0.0,0.0);

		for(int i; i < _maxIter && distance(z, vec2(0,0)) <= 2; i++)
		{
			z = vec2((z.x*z.x - z.y*z.y) + st.x, (2*z.x*z.y) + st.y);
			iters = i;
		}
	}
	return iters;
}

void main() 
{

	//FragColor = vec4(1.0f,1.0f,0.0f,1.0f);

	
	if (gl_FragCoord.x <= u_resolution.x && gl_FragCoord.y <= u_resolution.y)
	{
		float iters = brot(u_maxIter);
		float r = iters/u_maxIter;

		if (st.x < 0.001 * u_zoom && st.x > -0.001 * u_zoom || st.y < 0.001 * u_zoom && st.y > -0.001 * u_zoom )
		{
			FragColor = vec4(1.0,1.0,0.0,1.0);
		}


		else
		{
			if (iters < u_maxIter/3)
			{
				FragColor = vec4(0, iters/(u_maxIter/3), 1, 1);
			}
			else if (iters < 2*u_maxIter/3)
			{
				FragColor = vec4(iters/(2*u_maxIter/3), 1, 1-iters/(2*u_maxIter/3), 1);
			}
			else
			{
				FragColor = vec4(1, 1-iters/u_maxIter, 0, 1);
			}
		} 
	}
}