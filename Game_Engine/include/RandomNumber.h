#pragma once
/*****************************************************************//**
 * \file   RandomNumber.h
 * \brief  contain the class RandomNumber
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include <random>
#include <SFML/System/Vector2.hpp>
/**
 * @brief class RandomNumber
 */
class RandomNumber
{
public:
	/**
	 * @brief Default Constructor
	 */
	RandomNumber();
	/**
	 * @brief Default Destructor
	 */
	~RandomNumber() = default;

	/**
	 * @brief Get A random number over a given range
	 * @tparam type 
	 * @param type min 
	 * @param type max 
	 * @return type
	 */
	template<typename type = int>
    type getRandomNumber(type min, type max)
    {
        std::uniform_int_distribution<type> dis(min, max);
        return dis(m_gen);
    }
private:
    std::random_device m_rd;
    std::mt19937 m_gen;
};

/**
 * @brief Singleton for RandomNumber
 * @return RandomNumber& 
 */
RandomNumber& UseRandomNumber();

struct Vec2
{
	Vec2(sf::Vector2f Amin_, sf::Vector2f Amax);
	sf::Vector2f Pmin;
	sf::Vector2f Pmax;
};


enum class SpanwPosition
{
	Left
	, Up
	, Down
	,Right
};

class RandomSpanw
{
public:
	static sf::Vector2f getPosition(Vec2 zone, const sf::Vector2f& size);
	static sf::Vector2f getPosition(Vec2 zone, Vec2 RestrictedArea , const sf::Vector2f& size);
	static sf::Vector2f getPosition(Vec2 zone, SpanwPosition position , const sf::Vector2f& size);
};

