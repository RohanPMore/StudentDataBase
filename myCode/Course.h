/*
 * Course.h
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef COURSE_H_
#define COURSE_H_

#include<string>
#include<map>

class Course {
protected:
	std::map<unsigned char, std::string> majorById { { 'A', "Automation" }, {
			'C', "Communication" }, { 'E', "Embedded" }, { 'P', "Power" }, {
			'U', "Unknown" } };
	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;
public:
	/**
	 * Constructor to the class Course
	 * @param courseKey : Input Parameter : Takes an integer as an input to represent course key
	 * @param title : Input Parameter : Takes a string as an input to represent course title
	 * @param major : Input Parameter : Takes a string as an input to represent Major
	 * @param credit points : Input Parameter : Takes float as an input to represent credit points
	 */
	Course(unsigned int courseKey, std::string title, std::string major,
			float creditPoints);

	/**
	 * @param None
	 * @returns Returns course key
	 */
	unsigned int getCourseKey() const;

	/**
	 * @param None
	 * @returns Returns credit points of a course
	 */
	float getCreditPoints() const;

	/**
	 * @param None
	 * @returns Returns major that the course belongs to
	 */
	std::string getMajor() const;

	/**
	 * @param None
	 * @returns Returns title of the course
	 */
	const std::string getTitle() const;

	/**
	 * This function prints the details of the course- The course key, title, major, credit points
	 * @param None
	 */
	virtual void print() const;

	/**
	 * This function writes all the courses available into a csv file
	 * @param reference to an ofstream
	 */
	virtual void write(std::ostream &out) const;

	/**
	 * This is a destructor to the class Course
	 */
	virtual ~Course();
};

#endif /* COURSE_H_ */
