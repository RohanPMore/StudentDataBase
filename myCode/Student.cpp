/*
 * Student.cpp
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#include "Student.h"
#include <sstream>
#include<iterator>
#include<algorithm>
#include<iostream>

unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo) :
		firstName(firstName), lastName(lastName), dateOfBirth(
				dateOfBirth), address { street, postalCode, cityName,
				additionalInfo } {

	matrikelNumber = nextMatrikelNumber++;
}

const Address Student::getAddress() const {
	return address;
}

const std::string Student::getFirstName() const {
	return firstName;
}

const std::string Student::getLastName() const {
	return lastName;
}

unsigned int Student::getMatrikelNumber() const {
	return matrikelNumber;
}

const Poco::Data::Date Student::getDateOfBirth() const {
	return dateOfBirth;
}

void Student::setAddress(const Address &address) {
	this->address = address;
}

void Student::setFirstName(std::string firstName) {
	this->firstName = firstName;
}

void Student::setLastName(std::string lastName) {
	this->lastName = lastName;
}

void Student::setDateOfBirth(Poco::Data::Date dateOfBirth) {
	this->dateOfBirth = dateOfBirth;
}

void Student::addEnrollment(std::string semester, const Course *course) {
	Enrollment courseEnrollment(semester, course);
	enrollments.push_back(courseEnrollment);
}

std::vector<Enrollment> Student::getEnrollments() const {
	return enrollments;
}

void Student::updateEnrollment(unsigned int courseKey, float grade) {
	for (auto &enrollmentItr : enrollments) {
		if (enrollmentItr.getCourse()->getCourseKey() == courseKey) {
			enrollmentItr.setGrade(grade);
		}
	}
}

void Student::deleteEnrollment(unsigned int courseKey) {
	int index = 0;
	for (auto &enrollmentItr : enrollments) {

		if (enrollmentItr.getCourse()->getCourseKey() == courseKey) {
			enrollments.erase(enrollments.begin() + index);
		}
		index++;
	}
}

void Student::resetMartrikelNumber() {
	nextMatrikelNumber = 100000;
}

void Student::print() const {
	std::cout << "::::::::::::Student Details::::::::::::" << std::endl;
	std::cout << "MatrikelNumber:" << matrikelNumber << ", ";
	std::cout << "First Name:" << firstName << ", ";
	std::cout << "Last Name:" << lastName << ", ";
	std::cout << "Date of Birth:" << dateOfBirth.year() << "-"
			<< dateOfBirth.month() << "-" << dateOfBirth.day() << ", ";
	std::cout << "Street :" << address.getStreet() << ", ";
	std::cout << "Postal Code:" << address.getPostalCode() << ",";
	std::cout << "City Name:" << address.getCityName() << ",";
	std::cout << "Additional Information:" << address.getAdditionalInfo()
			<< std::endl;
	std::cout << std::endl;
	std::cout << "::::::::::::Enrollment Details::::::::::::" << std::endl;
	std::cout << "________________________________________________________"
			<< std::endl;
	for (auto enrollmentItr : enrollments) {
		enrollmentItr.print();
		std::cout << "________________________________________________________"
				<< std::endl;
	}

	std::cout << std::endl;
}

void Student::write(std::ostream &out) const {
	out << matrikelNumber << ";" << firstName << ";" << lastName << ";"
			<< dateOfBirth.day() << "." << dateOfBirth.month() << "."
			<< dateOfBirth.year() << ";" << address.getStreet() << ";"
			<< address.getPostalCode() << ";" << address.getCityName() << ";"
			<< address.getAdditionalInfo();
}

void Student::writeEnrollment(std::ostream &out) const {
	for (auto enrollmentItr : enrollments) {
		out << matrikelNumber << ";"
				<< enrollmentItr.getCourse()->getCourseKey() << ";"
				<< enrollmentItr.getSemester() << ";"
				<< enrollmentItr.getGrade();
		out << "\n";
	}
}
