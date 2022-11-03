#ifndef PERLINNOISE3D_H
#define PERLINNOISE3D_H

#include <random>
#include <vector>

class PerlinNoise3D
{
public:
	std::vector < std::vector < std::vector<float>>> Result;
	int seed;
	int size;
	PerlinNoise3D(int seed,int depth);
	float Calculate(float x, float y, float z);
	~PerlinNoise3D();
};

#endif