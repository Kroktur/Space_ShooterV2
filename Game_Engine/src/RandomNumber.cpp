#include "RandomNumber.h"
#include <cmath>

#include <ctime>

RandomNumber::RandomNumber() :m_gen(m_rd())
{}

RandomNumber& UseRandomNumber()
{
	static RandomNumber rd;
	return rd;
}


