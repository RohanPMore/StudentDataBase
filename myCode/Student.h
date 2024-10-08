/*
 * Student.h
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include<string>
#include<vector>
#include<Poco/Data/Date.h>
#include"Enrollment.h"
#include"Address.h"

class Student {
private:
	static unsigned int nextMatrikelNumber;
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName;
	Poco::Data::Date dateOfBirth;
	std::vector<Enrollment> enrollments;
	Address address;

public:
	/**
	 * Constructor to the class Student
	 * @param firstName : Input Parameter
	 * @param lastName : Input Parameter
	 * @param dateofBirth : Input Parameter
	 * @param street : Input Parameter
	 * @param postalCode : Input Parameter
	 * @param cityName : Input Parameter
	 * @param additionalInformation : Input Parameter
	 */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::string street,
			unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	/**
	 * @param None
	 * @returns Returns object of class Address containing - street,postalCode,cityName and additionalInformation
	 */
	const Address getAddress() const;

	/**
	 * This function assigns new Address object to the student object
	 * @param reference of an object of class Address
	 * @returns None
	 */
	void setAddress(const Address &address);

	/**
	 * @param None
	 * @returns Returns date of birth of the student
	 */
	const Poco::Data::Date getDateOfBirth() const;

	/**
	 * This function is used to update date of birth of the student object
	 * @param dateOfBirth : Input Parameter
	 * @returns None
	 */
	void setDateOfBirth(Poco::Data::Date dateOfBirth);

	/**
	 * This function retrieves all the courses that the student object has enrolled in
	 * @param None
	 * @returns Returns all the courses the student object has enrolled in.
	 */
	std::vector<Enrollment> getEnrollments() const;

	/**
	 * This function deletes a previously made enrollment
	 * @param courseKey : Input Parameter
	 * @returns None
	 */
	void deleteEnrollment(unsigned int courseKey);

	/**
	 * This function updates previously created enrollment. Updates grade acheieved.
	 * @param courseKey : Input Parameter
	 * @param grade : Input Parameter
	 * @returns None
	 */
	void updateEnrollment(unsigned int courseKey, float grade);

	/**
	 * This function adds an enrollment
	 * @param semester : Input Parameter
	 * @param *course : Input Parameter : Pointer to an object of class Course
	 * @returns None
	 */
	void addEnrollment(std::string semester, const Course *course);

	/**
	 * @param None
	 * @returns Returns first name of the student object
	 */
	const std::string getFirstName() const;

	/**
	 * This function is used to update the first name of the student
	 * @param firstName : Input Parameter
	 * @returns None
	 */
	void setFirstName(std::string firstName);

	/**
	 * @param None
	 * @returns Returns last name of the student object
	 */
	const std::string getLastName() const;

	/**
	 * This function is used to update the last name of the student
	 * @param lastName : Input Parameter
	 * @returns None
	 */
	void setLastName(std::string lastName);

	/**
	 * @param None
	 * @returns Returns matrikelNumber of the student
	 */
	unsigned int getMatrikelNumber() const;

	/**
	 * This function writes all the details of the student into a csv file
	 * @param reference to an ofstream
	 */
	void write(std::ostream &out) const;

	/**
	 * This function writes all the details of the enrollment of a particular student into a csv file
	 * @param reference to an ofstream
	 */
	void writeEnrollment(std::ostream &out) const;

	/**
	 * This function is used to reset the matrikel number to initial value while reading the data from the csv file
	 * @param None
	 * @returns None
	 */
	static void resetMartrikelNumber();

	/**
	 * This function prints the details of the student- Name, DateOfBirth, Address
	 * @param None
	 */
	void print() const;
};

#endif /* STUDENT_H_ */
