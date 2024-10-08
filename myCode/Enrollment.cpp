/*
 * Enrollment.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#include "Enrollment.h"
#include <iostream>

Enrollment::Enrollment(std::string semester, const Course *course, float grade) :
		grade { grade }, semester(semester), course { course }
{
}

const Course* Enrollment::getCourse() const
{
	return course;
}

float Enrollment::getGrade() const
{
	return grade;
}

const std::string& Enrollment::getSemester() const
{
	return semester;
}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

void Enrollment::print() const
{
	std::cout << "Course Name :" << course->getTitle() << std::endl;
	std::cout << "Course Major :" << course->getMajor() << std::endl;
	std::cout << "Course Points :" << course->getCreditPoints() << std::endl;
	std::cout << "Course Key :" << course->getCourseKey() << std::endl;
	std::cout << "Semester :" << semester << std::endl;
	std::cout << "Grade :" << grade << std::endl;

}

