/*
 * StudentDb.h
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include <map>
#include "Student.h"
#include "Course.h"
#include<memory>

class StudentDb {
private:
	std::map<unsigned int, Student> students;
	std::map<unsigned int, std::unique_ptr<const Course>> courses;

	//Helper Functions
	bool isStudentInDb(unsigned int matrikelNumber);
	bool isCourseInDb(unsigned int courseKey);
	bool hasAlreadyEnrolled(unsigned int matrikelNumber,
			unsigned int coursekey);

public:
	/**
	 * Constructor to the class StudentDb
	 * @param None
	 */
	StudentDb();

	/**
	 * This function is used to add a new course to the data base
	 * @param courseKey : Input Parameter
	 * @param title : Input Parameter
	 * @param major : Input Parameter
	 * @param creditPoints : Input Parameter
	 * @return None
	 */
	void addNewCourse(unsigned int courseKey, std::string title,
			std::string major, float creditPoints);

	/**
	 * This function is used to add a new blocked course
	 * @param courseKey : Input Parameter
	 * @param title : Input Parameter
	 * @param major : Input Parameter
	 * @param startDate : Input Parameter
	 * @param endDate : Input Parameter
	 * @param startTime : Input Parameter
	 * @param endTime : Input Parameter
	 * @return None
	 */
	void addNewBlockCourse(unsigned int courseKey, std::string title,
			std::string major, float creditPoints, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime);

	/**
	 * This function is used to add a new weekly course
	 * @param courseKey : Input Parameter
	 * @param title : Input Parameter
	 * @param major : Input Parameter
	 * @param DayOfWeek : Input Parameter
	 * @param startTime : Input Parameter
	 * @param endTime : Input Parameter
	 * @return None
	 */
	void addNewWeeklyCourse(unsigned int courseKey, std::string title,
			std::string major, float creditPoints,
			Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime,
			Poco::Data::Time endTime);

	/**
	 * This function is used to print all courses available in the database
	 * @return None
	 */
	void printCourses() const;

	/**
	 * This function is used to add a new student to the database
	 * @param firstName : Input Parameter
	 * @param lastName : Input Parameter
	 * @param dateOfBirth : Input Parameter
	 * @param street : Input Parameter
	 * @param postalCode : Input Parameter
	 * @param cityName : Input Parameter
	 * @param additionalInfo : Input Parameter
	 * @return None
	 */
	void addNewStudent(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::string street,
			unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	/**
	 * This function is used to add a new enrollment to a student
	 * @param matrikelNumber : Input Parameter
	 * @param courseKey : Input Parameter
	 * @param semester : Input Parameter
	 * @return None
	 */
	void addEnrollment(unsigned int matrikelNumber, unsigned int courseKey,
			std::string semester);

	/**
	 * This function prints  details of all students available in the database
	 * @param matrikelNumber : Input Parameter
	 * @return None
	 */
	void printStudent(unsigned int matrikelNumber);

	/**
	 * This function prints all the students with having an user inputted substring
	 * @param subString : Input Parameter
	 * @return None
	 */
	void searchStudent(const std::string subString);

	/**
	 * This function is used to update student details
	 * 1. Update first name
	 * 2. Update last name
	 * 3. Update date of birth
	 * 4. Update address
	 * 5. Update enrollment
	 * @param matrikelNumber : InputParameter
	 * @return None
	 */
	void updateStudentDetails(unsigned int matrikelNumber);

	/**
	 * This function writes all the course, all students and their entrollment into a csv file in semicolon seperated format
	 * @param reference to an ofstream
	 * @return None
	 */
	void write(std::ostream &out) const;

	/**
	 * This function reads csv file (semicolon seperated values) for courses, students and enrollments and updates the database
	 * @param reference to an ifstream
	 * @return None
	 */
	void read(std::istream &in);

	/**
	 * This function connects to server "mnl.de" and fetches student details and adds it to the database
	 * @param None
	 * @return None
	 */
	void getAndUpdateStudentsFromServer();

};

#endif /* STUDENTDB_H_ */
