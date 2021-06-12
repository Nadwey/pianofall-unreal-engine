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