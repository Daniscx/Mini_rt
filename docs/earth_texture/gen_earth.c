
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <include/minirt.h>

#define WIDTH 512
#define HEIGHT 256

/* Simple noise function */
double noise(double x, double y, double z)
{
	int xi = (int)floor(x) & 255;
	int yi = (int)floor(y) & 255;
	int zi = (int)floor(z) & 255;
	return fmod((sin(xi * 12.9898 + yi * 78.233 + zi * 37.719) * 43758.5453), 1.0);
}

/* Smooth noise with interpolation */
double smooth_noise(double x, double y, double z)
{
	double fx = x - floor(x);
	double fy = y - floor(y);
	double fz = z - floor(z);
	int x0 = (int)floor(x);
	int y0 = (int)floor(y);
	int z0 = (int)floor(z);

	double n000 = noise(x0, y0, z0);
	double n100 = noise(x0 + 1, y0, z0);
	double n010 = noise(x0, y0 + 1, z0);
	double n110 = noise(x0 + 1, y0 + 1, z0);
	double n001 = noise(x0, y0, z0 + 1);
	double n101 = noise(x0 + 1, y0, z0 + 1);
	double n011 = noise(x0, y0 + 1, z0 + 1);
	double n111 = noise(x0 + 1, y0 + 1, z0 + 1);

	double nx00 = n000 * (1 - fx) + n100 * fx;
	double nx10 = n010 * (1 - fx) + n110 * fx;
	double nx01 = n001 * (1 - fx) + n101 * fx;
	double nx11 = n011 * (1 - fx) + n111 * fx;

	double nxy0 = nx00 * (1 - fy) + nx10 * fy;
	double nxy1 = nx01 * (1 - fy) + nx11 * fy;

	return nxy0 * (1 - fz) + nxy1 * fz;
}

/* Fractal Brownian motion for terrain */
double fbm(double x, double y, double z, int octaves)
{
	double value = 0;
	double amplitude = 0.5;
	double frequency = 1;
	for (int i = 0; i < octaves; i++)
	{
		value += amplitude * fabs(smooth_noise(x * frequency, y * frequency, z * frequency));
		amplitude *= 0.5;
		frequency *= 2;
	}
	return value;
}

int main(void)
{
	FILE *earth = fopen("earth.ppm", "wb");
	FILE *bump = fopen("earth_bump.ppm", "wb");

	if (!earth || !bump)
	{
		printf("Error creating files\n");
		return 1;
	}

	fprintf(earth, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
	fprintf(bump, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			/* Convert to spherical coordinates */
			double u = (double)x / WIDTH;
			double v = (double)y / HEIGHT;
			double phi = u * 2.0 * M_PI;
			double theta = v * M_PI;

			/* 3D coordinates on sphere */
			double sx = sin(theta) * cos(phi);
			double sy = cos(theta);
			double sz = sin(theta) * sin(phi);

			/* Generate terrain noise */
			double terrain = fbm(sx * 2, sy * 2, sz * 2, 6);

			/* Land/water threshold */
			double threshold = 0.35;
			int is_land = terrain > threshold;

			/* Latitude-based ice caps */
			double lat = fabs(v - 0.5) * 2.0;
			int is_ice = lat > 0.85;

			/* Colors */
			unsigned char r, g, b;
			unsigned char br, bg, bb;

			if (is_ice)
			{
				/* Ice caps - white */
				r = 240; g = 245; b = 250;
				br = bg = bb = 200;
			}
			else if (is_land)
			{
				/* Land - green/brown gradient based on altitude */
				double alt = (terrain - threshold) / (1.0 - threshold);
				if (lat > 0.6)
				{
					/* Tundra */
					r = 139; g = 137; b = 112;
				}
				else if (alt > 0.5)
				{
					/* Mountains - brown/gray */
					r = 139; g = 119; b = 101;
				}
				else if (lat < 0.3)
				{
					/* Tropical forest - dark green */
					r = 34; g = 139; b = 34;
				}
				else
				{
					/* Temperate - lighter green */
					r = 60; g = 179; b = 60;
				}
				br = bg = bb = (unsigned char)(terrain * 255);
			}
			else
			{
				/* Ocean - blue gradient based on depth */
				double depth = threshold - terrain;
				r = (unsigned char)(10 + depth * 30);
				g = (unsigned char)(40 + depth * 50);
				b = (unsigned char)(120 + depth * 80);
				br = bg = bb = (unsigned char)(50 + terrain * 100);
			}

			/* Add some noise variation */
			double var = smooth_noise(sx * 20, sy * 20, sz * 20) * 20 - 10;
			r = (unsigned char)fmax(0, fmin(255, r + var));
			g = (unsigned char)fmax(0, fmin(255, g + var));
			b = (unsigned char)fmax(0, fmin(255, b + var));

			fputc(r, earth);
			fputc(g, earth);
			fputc(b, earth);

			fputc(br, bump);
			fputc(bg, bump);
			fputc(bb, bump);
		}
	}

	fclose(earth);
	fclose(bump);
	printf("Generated earth.ppm and earth_bump.ppm (%dx%d)\n", WIDTH, HEIGHT);
	return 0;
}
