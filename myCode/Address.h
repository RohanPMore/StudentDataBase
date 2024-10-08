/*
 * Address.h
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include<string>

class Address {
private:
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;
public:
	/**
	 * Constructor to the class Address
	 * @param street : Input Parameter : Takes string as an input to represent street
	 * @param postal code : Input Parameter : Takes unsigned short as an input to represent postal code
	 * @param city name : Input Parameter : Takes string as an input to represent city name
	 * @param additional Info : Input Parameter : Takes string as an input to represent any other info related to address
	 */
	Address(std::string street, unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	/**
	 * @param None
	 * @return Returns additional information of the student address
	 */
	const std::string& getAdditionalInfo() const;

	/**
	 * @param None
	 * @return Returns city name from the student address
	 */
	const std::string& getCityName() const;

	/**
	 * @param None
	 * @return Returns postal code from the student address
	 */
	unsigned short getPostalCode() const;

	/**
	 * @param None
	 * @return Returns street from the student address
	 */
	const std::string& getStreet() const;
};

#endif /* ADDRESS_H_ */
