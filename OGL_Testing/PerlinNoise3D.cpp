#include "PerlinNoise3D.h"

PerlinNoise3D::PerlinNoise3D(int noiseseed, int depth)///size is a power
{
	seed = noiseseed;
	size = pow(2, depth);

	std::vector < std::vector < std::vector<float>>> Noise = std::vector< std::vector< std::vector<float> > > (size, std::vector< std::vector< float > >(size, std::vector< float >(size, 0)));
	Result = std::vector< std::vector< std::vector<float> > >(size, std::vector< std::vector< float > >(size, std::vector< float >(size, 0)));

	srand(seed);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				Noise[i][j][k] = ((float)(rand() % 1000) / 1000);
			}
		}
	}
	
	float depthmultiplier = 1;
	float maxvalue = 0;
	for (int d = 0; d < depth; d++)//O(d)
	{
		depthmultiplier /= 1.2;
		int numberofpoints = pow(2, d);
		int step = size / numberofpoints;
		maxvalue += depthmultiplier;

		for (int i = 0; i < size; i++)//O(2^d)
		{
			int disti = i % step;
			float firstmultiplieri = 1-((float)(disti)/step);
			float secondmultiplieri = 1 - firstmultiplieri;
			int firsti = i - disti;
			int secondi = (i - disti +step)%size;
			for (int j = 0; j < size; j++)//O(2^d)
			{
				int distj = j % step;
				float firstmultiplierj = 1 - ((float)(distj) / step);
				float secondmultiplierj = 1 - firstmultiplierj;
				int firstj = j - distj;
				int secondj = (j - distj + step) % size;
				for (int k = 0; k < size; k++)//O(2^d)
				{
					int distk = k % step;
					float firstmultiplierk = 1 - ((float)(distk) / step);
					float secondmultiplierk = 1 - firstmultiplierk;
					int firstk = k - distk;
					int secondk = (k - distk + step) % size;
					Result[i][j][k] += (depthmultiplier) * 
						(Noise[firsti][firstj][firstk] * firstmultiplieri * firstmultiplierj * firstmultiplierk +
						Noise[firsti][firstj][secondk] * firstmultiplieri * firstmultiplierj * secondmultiplierk +
						Noise[firsti][secondj][firstk] * firstmultiplieri * secondmultiplierj * firstmultiplierk +
						Noise[firsti][secondj][secondk] * firstmultiplieri * secondmultiplierj * secondmultiplierk +
						Noise[secondi][firstj][firstk] * secondmultiplieri * firstmultiplierj * firstmultiplierk +
						Noise[secondi][firstj][secondk] * secondmultiplieri * firstmultiplierj * secondmultiplierk +
						Noise[secondi][secondj][firstk] * secondmultiplieri * secondmultiplierj * firstmultiplierk +
						Noise[secondi][secondj][secondk] * secondmultiplieri * secondmultiplierj * secondmultiplierk);
				}
			}
		}
	}
	for (int i = 0; i < size; i++)for (int j = 0; j < size; j++)for (int k = 0; k < size; k++)Result[i][j][k] /= maxvalue;
	Noise.~vector();
}
float PerlinNoise3D::Calculate(float x, float y, float z)
{
	///inputs are -1 to 1
	/// 0 <= x,y,z <= 1
	x = (x+4) / 2;
	x *= size;
	int firsti = (int)x%size;
	int secondi = (firsti + 1) % size;
	float disti = x- (int)x;
	float firstmultiplieri = 1 - disti;
	float secondmultiplieri = disti;
	y = (y+4) / 2;
	y *= size;
	int firstj = (int)y % size;
	int secondj = (firstj + 1) % size;
	float distj = y - (int)y;
	float firstmultiplierj = 1 - distj;
	float secondmultiplierj = distj;
	z = (z + 4) / 2;
	z *= size;
	int firstk = (int)z % size;
	int secondk = (firstk + 1) % size;
	float distk = z - (int)z;
	float firstmultiplierk = 1 - distk;
	float secondmultiplierk = distk;

	


	return (Result[firsti][firstj][firstk] * firstmultiplieri * firstmultiplierj * firstmultiplierk +
			Result[firsti][firstj][secondk] * firstmultiplieri * firstmultiplierj * secondmultiplierk +
			Result[firsti][secondj][firstk] * firstmultiplieri * secondmultiplierj * firstmultiplierk +
			Result[firsti][secondj][secondk] * firstmultiplieri * secondmultiplierj * secondmultiplierk +
			Result[secondi][firstj][firstk] * secondmultiplieri * firstmultiplierj * firstmultiplierk +
			Result[secondi][firstj][secondk] * secondmultiplieri * firstmultiplierj * secondmultiplierk +
			Result[secondi][secondj][firstk] * secondmultiplieri * secondmultiplierj * firstmultiplierk +
			Result[secondi][secondj][secondk] * secondmultiplieri * secondmultiplierj * secondmultiplierk);
}
PerlinNoise3D::~PerlinNoise3D()
{
	Result.~vector();
}