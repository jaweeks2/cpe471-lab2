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
	if(argc != 10) {
		cout << "Improper usage: wrong number of arguments" << endl;
		return 0;
	}
	
	unsigned char r, g, b;
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
	tri.v2.x = atoi(argv[6]);
	tri.v2.y = atoi(argv[7]);
	tri.v3.x = atoi(argv[8]);
	tri.v3.y = atoi(argv[9]);
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	// Draw bounding box
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
	for(int y = minY; y <= maxY; ++y) {
		for(int x = minX; x <= maxX; ++x) {
			if (x % 10 < 5)
			{
				r = 255;
				g = 0;
				b = 0;
			}
			else
			{
				r = 0;
				g = 255;
				b = 0;
			}
			image->setPixel(x, y, r, g, b);
		}
	}
	// Draw triangle vertices (as white)
	r = 255;
	g = 255;
	b = 255;
	image->setPixel(tri.v1.x, tri.v1.y, r, g, b);
	image->setPixel(tri.v2.x, tri.v2.y, r, g, b);
	image->setPixel(tri.v3.x, tri.v3.y, r, g, b);
	// Write image to file
	image->writeToFile(filename);
	return 0;
}
