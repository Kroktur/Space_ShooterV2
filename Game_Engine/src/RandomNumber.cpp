#include "RandomNumber.h"
/*****************************************************************//**
 * \file   RandomNumber.cpp
 * \brief  Implementation of RandomNumber.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
RandomNumber::RandomNumber() :m_gen(m_rd())
{}

RandomNumber& UseRandomNumber()
{
	static RandomNumber rd;
	return rd;
}


