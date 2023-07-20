#pragma once

#include <string>
#include <sstream>

std::string ZeroPadNumber(int num, int length)
{
	std::stringstream ss;
	ss << num;
	std::string ret;
	ss >> ret;
	int str_length = ret.length();
	for (int i = 0; i < length - str_length; i++)
		ret = "0" + ret;
	return ret;
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

struct RGB {
	double r;
	double g;
	double b;
};

RGB rgb(double ratio)
{
	//we want to normalize ratio so that it fits in to 6 regions
	//where each region is 256 units long
	int normalized = int(ratio * 256 * 6);

	//find the distance to the start of the closest region
	int x = normalized % 256;

	int red = 0, grn = 0, blu = 0;
	switch (normalized / 256)
	{
	case 0: red = 255;      grn = x;        blu = 0;       break;//red
	case 1: red = 255 - x;  grn = 255;      blu = 0;       break;//yellow
	case 2: red = 0;        grn = 255;      blu = x;       break;//green
	case 3: red = 0;        grn = 255 - x;  blu = 255;     break;//cyan
	case 4: red = x;        grn = 0;        blu = 255;     break;//blue
	case 5: red = 255;      grn = 0;        blu = 255 - x; break;//magenta
	}

	RGB color;
	color.r = red;
	color.g = grn;
	color.b = blu;

	return color;
}

RGB RandomColor()
{
	RGB color;
	color.r = FMath::RandRange(0, 255);
	color.g = FMath::RandRange(0, 255);
	color.b = FMath::RandRange(0, 255);

	return color;
}
