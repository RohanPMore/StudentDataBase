/*
 * WeeklyCourse.h
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>

class WeeklyCourse: public Course {
private:
	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
public:
	/**
	 * Constructor to the class WeeklyCourse
	 * @param courseKey : Input Parameter : Takes an integer as an input to represent course key
	 * @param title : Input Parameter : Takes a string as an input to represent course title
	 * @param major : Input Parameter : Takes a string as an input to represent Major
	 * @param credit points : Input Parameter : Takes float as an input to represent credit points
	 * @param dayOfWeek: Input Parameter : Represents the day on which the weekly course occurs
	 * @param start time : Input Parameter : Represents the start time of the block course
	 * @param end time : Input Parameter : Represents the end time of the block course
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

	/**
	 * This function prints the details of the block course- The course key, title, major, credit points, start/end time and day of the week the course occurs
	 * @param None
	 */
	void print() const;

	/**
	 * This function writes all the weekly courses available into a csv file
	 * @param reference to an ofstream
	 */
	void write(std::ostream &out) const;

	/**
	 * This is a destructor to the class WeeklyCourse
	 */
	~WeeklyCourse();

};

#endif /* WEEKLYCOURSE_H_ */
