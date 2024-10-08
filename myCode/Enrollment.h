/*
 * Enrollment.h
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include "Course.h"
#include <string>

class Enrollment {
private:
	float grade;
	std::string semester;
	const Course *course;

public:
	/**
	 * Constructor to the class Enrollment
	 * @param semester : Input Parameter : Represents the semester of enrollment
	 * @param *course : Input Parameter : Pointer to the Course class object
	 * @param grade : Input Parameter : Represents the grade the student achieved for a particular enrolled course
	 */
	Enrollment(std::string semester, const Course *course, float grade = -1);

	/**
	 * @param None
	 * @returns Returns pointer to an object of class Course
	 */
	const Course* getCourse() const;

	/**
	 * @param None
	 * @returns Returns grade obtained by a student for a particular enrolled course
	 */
	float getGrade() const;

	/**
	 * @param None
	 * @returns Returns semester of enrollment
	 */
	const std::string& getSemester() const;

	/**
	 * @param grade : Input Parameter : Grade obtained by student in a enrolled course
	 * @returns None
	 */
	void setGrade(float grade);

	/**
	 * This function prints the details of the enrollment - Semester, course details and the grade
	 * @param None
	 */
	void print() const;
};

#endif /* ENROLLMENT_H_ */
