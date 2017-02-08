#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"
#include "Triangle.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int main(int argc, char **argv)
{
	if(argc != 19) 
	{
		cout << "Improper usage: wrong number of arguments" << endl;
		return 0;
	}
	
	unsigned char r, g, b;
	double alpha, beta, gamma, denom;
	int minX, minY, maxX, maxY;
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);
	// Triangle vertices
	Triangle tri;
	tri.v1.x = atoi(argv[4]);
	tri.v1.y = atoi(argv[5]);
	tri.v1.r = atoi(argv[6]);
	tri.v1.g = atoi(argv[7]);
	tri.v1.b = atoi(argv[8]);
	tri.v2.x = atoi(argv[9]);
	tri.v2.y = atoi(argv[10]);
	tri.v2.r = atoi(argv[11]);
	tri.v2.g = atoi(argv[12]);
	tri.v2.b = atoi(argv[13]);
	tri.v3.x = atoi(argv[14]);
	tri.v3.y = atoi(argv[15]);
	tri.v3.r = atoi(argv[16]);
	tri.v3.g = atoi(argv[17]);
	tri.v3.b = atoi(argv[18]);
	
	/*
	// Output vertices as ordered pairs to terminal - for testing
	cout << "v1: (" << tri.v1.x << ", " << tri.v1.y << ")" << endl;
	cout << "v2: (" << tri.v2.x << ", " << tri.v2.y << ")" << endl;
	cout << "v3: (" << tri.v3.x << ", " << tri.v3.y << ")" << endl;
	*/
	
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	
	// Compute bounding box
	minX = tri.v1.x, maxX = tri.v1.x;
	minY = tri.v1.y, maxY = tri.v1.y;
	if (minX - tri.v2.x > 0)
	{
		minX = tri.v2.x;
	}
	if (maxX - tri.v2.x < 0)
	{
		maxX = tri.v2.x;
	}
	if (minY - tri.v2.y > 0)
	{
		minY = tri.v2.y;
	}
	if (maxY - tri.v2.y < 0)
	{
		maxY = tri.v2.y;
	}
	if (minX - tri.v3.x > 0)
	{
		minX = tri.v3.x;
	}
	if (maxX - tri.v3.x < 0)
	{
		maxX = tri.v3.x;
	}
	if (minY - tri.v3.y > 0)
	{
		minY = tri.v3.y;
	}
	if (maxY - tri.v3.y < 0)
	{
		maxY = tri.v3.y;
	}
	
	// Draw triangle
	for(int y = minY; y <= maxY; ++y) 
	{
		for(int x = minX; x <= maxX; ++x) 
		{
			// Calculate alpha, beta, gamma
			denom = (double)(tri.v2.y - tri.v3.y) * (double)(tri.v1.x - tri.v3.x);
			denom += (double)(tri.v3.x - tri.v2.x) * (double)(tri.v1.y - tri.v3.y);
			
			alpha = (double)(tri.v2.y - tri.v3.y) * (double)(x - tri.v3.x);
			alpha += (double)(tri.v3.x - tri.v2.x) * (double)(y - tri.v3.y);
			alpha = alpha / denom;
			
			beta = (double)(tri.v3.y - tri.v1.y) * (double)(x - tri.v3.x);
			beta += (double)(tri.v1.x - tri.v3.x) * (double)(y - tri.v3.y);
			beta = beta / denom;
			
			gamma = (1 - alpha) - beta;
			
			// Draw pixel if in triangle
			if ( (alpha >= 0.0) && (alpha <= 1.0) && (beta >= 0.0) 
				&& (beta <= 1.0) && (gamma >= 0.0) && (gamma <= 1.0) )
			{
				r = (int)(alpha*tri.v1.r + beta*tri.v2.r + gamma*tri.v3.r);
				g = (int)(alpha*tri.v1.g + beta*tri.v2.g + gamma*tri.v3.g);
				b = (int)(alpha*tri.v1.b + beta*tri.v2.b + gamma*tri.v3.b);
				image->setPixel(x, y, r, g, b);
			}
		}
	}
	
	/*
	// Draw triangle vertices - for testing
	image->setPixel(tri.v1.x, tri.v1.y, tri.v1.r, tri.v1.g, tri.v1.b);
	image->setPixel(tri.v2.x, tri.v2.y, tri.v2.r, tri.v2.g, tri.v2.b);
	image->setPixel(tri.v3.x, tri.v3.y, tri.v3.r, tri.v3.g, tri.v3.b);
	*/
	
	// Write image to file
	image->writeToFile(filename);
	return 0;
}
