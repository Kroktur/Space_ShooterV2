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



Vec2::Vec2(sf::Vector2f Amin_, sf::Vector2f Amax) : Pmin(Amin_), Pmax(Amax) {}

sf::Vector2f RandomSpanw::getPosition(Vec2 zone)
{
	auto x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x, zone.Pmax.x);
	auto y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y, zone.Pmax.y);
	return sf::Vector2f(x, y);

}

sf::Vector2f RandomSpanw::getPosition(Vec2 zone, Vec2 RestrictedArea)
{
	auto x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x, zone.Pmax.x);
	auto y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y, zone.Pmax.y);
	sf::Vector2f result = sf::Vector2f(x, y);
	while (result.x > RestrictedArea.Pmin.x && result.x < RestrictedArea.Pmax.x && result.y > RestrictedArea.Pmin.y && result.y < RestrictedArea.Pmax.y)
	{
		result.x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x, zone.Pmax.x);
		result.y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y, zone.Pmax.y);
	}
	return result;

}

sf::Vector2f RandomSpanw::getPosition(Vec2 zone, SpanwPosition position)
{
	auto x = 0;
	auto y = 0;
	sf::Vector2f result = sf::Vector2f(x, y);

	switch (position)
	{
	case SpanwPosition::Left:
		{
		result.x = zone.Pmin.x;
		result.y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y, zone.Pmax.y);
		}
		break;
	case SpanwPosition::Right:
		{
		result.x = zone.Pmax.x;
			result.y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y, zone.Pmax.y);
		}
		break;
	case SpanwPosition::Up:
		{

		result.y = zone.Pmin.y;
		result.x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x, zone.Pmax.x);
		}
		break;
	case SpanwPosition::Down:
		{
		result.x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x, zone.Pmax.x);
		result.y = zone.Pmax.y;
		}
		break;
	}
	return  result;
}
