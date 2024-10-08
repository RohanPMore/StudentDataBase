/*
 * Address.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#include "Address.h"

Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo) :
		street(street), cityName(cityName), additionalInfo(additionalInfo)
{
	this->postalCode = postalCode;
}

const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

const std::string& Address::getCityName() const
{
	return cityName;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

const std::string& Address::getStreet() const
{
	return street;
}
