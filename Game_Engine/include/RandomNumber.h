#pragma once
/*****************************************************************//**
 * \file   RandomNumber.h
 * \brief  contain the class RandomNumber
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include <random>
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
