/*
 * WeeklyCourse.cpp
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#include "WeeklyCourse.h"
#include<iostream>

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course { courseKey, title, major, creditPoints }, dayOfWeek { dayOfWeek }, startTime(
				startTime), endTime(endTime)
{
}

void WeeklyCourse::print() const {
	std::cout << "Course Key:" << courseKey << ", ";
	std::cout << "Title:" << title << ", ";
	std::cout << "Major:" << majorById.at(major) << ", ";
	std::cout << "Credit Points:" << creditPoints << ", ";
	std::cout << "Day of the Week:" << dayOfWeek << ", ";
	std::cout << "Start Time:" << startTime.hour() << ":" << startTime.minute()
			<< ":" << startTime.second() << ", ";
	std::cout << "End Time:" << endTime.hour() << ":" << endTime.minute() << ":"
			<< endTime.second();
	std::cout << std::endl;
	std::cout << std::endl;
}

void WeeklyCourse::write(std::ostream &out) const {
	out << "W" << ";";
	Course::write(out);
	out << dayOfWeek << ";" << startTime.hour() << ":" << startTime.minute()
			<< ":" << startTime.second() << ";" << endTime.hour() << ":"
			<< endTime.minute() << ":" << endTime.second();
}

WeeklyCourse::~WeeklyCourse() {
}

