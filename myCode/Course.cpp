/*
 * Course.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#include "Course.h"
#include<iostream>
#include <algorithm>
#include <iterator>

Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints) :title(title),creditPoints(creditPoints)
{
	this->courseKey = courseKey;
	this->major = 'U';

	for (auto majorByIdMapItr : majorById)
	{
		if (majorByIdMapItr.second == major)
		{
			this->major = majorByIdMapItr.first;
		}
	}
}

unsigned int Course::getCourseKey() const {
	return courseKey;
}

float Course::getCreditPoints() const {
	return creditPoints;
}

std::string Course::getMajor() const {
	return majorById.at(major);
}

const std::string Course::getTitle() const {
	return title;
}

void Course::print() const {
	std::cout << "Course Key:" << courseKey << ", ";
	std::cout << "Title:" << title << ", ";
	std::cout << "Major:" << major << ", ";
	std::cout << "Credit Points:" << creditPoints;
	std::cout << std::endl;
	std::cout << std::endl;
}

void Course::write(std::ostream &out) const {
	out << courseKey << ";" << title << ";" << majorById.at(major) << ";"
			<< creditPoints << ";";
}

Course::~Course() {
}
