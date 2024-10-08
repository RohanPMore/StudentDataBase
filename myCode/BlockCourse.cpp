/*
 * BlockCourse.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#include "BlockCourse.h"
#include <iostream>

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course { courseKey, title, major, creditPoints }, startDate(startDate), endDate(
				endDate),startTime(startTime), endTime(endTime)
{
}

void BlockCourse::print() const {
	std::cout << "Course Key:" << courseKey << ", ";
	std::cout << "Title:" << title << ", ";
	std::cout << "Major:" << majorById.at(major) << ", ";
	std::cout << "Credit Points:" << creditPoints << ", ";
	std::cout << "Start Date:" << startDate.year() << "-" << startDate.month()
			<< "-" << startDate.day() << ", ";
	std::cout << "End Date:" << endDate.year() << "-" << endDate.month() << "-"
			<< endDate.day() << ", ";
	std::cout << "Start Time:" << startTime.hour() << ":" << startTime.minute()
			<< ":" << startTime.second() << ", ";
	std::cout << "End Time:" << endTime.hour() << ":" << endTime.minute() << ":"
			<< endTime.second();
	std::cout << std::endl;
	std::cout << std::endl;
}

void BlockCourse::write(std::ostream &out) const {
	out << "B" << ";";
	Course::write(out);
	out << startDate.day() << "." << startDate.month() << "."
			<< startDate.year() << ";" << endDate.day() << "."
			<< endDate.month() << "." << endDate.year() << ";"
			<< startTime.hour() << ":" << startTime.minute() << ":"
			<< startTime.second() << ";" << endTime.hour() << ":"
			<< endTime.minute() << ":" << endTime.second();
}

BlockCourse::~BlockCourse() {
}
