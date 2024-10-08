/*
 * BlockCourse.h
 *
 *  Created on: 20 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"
#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>

class BlockCourse: public Course {
private:
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
public:
	/**
	 * Constructor to the class BlockCourse
	 * @param courseKey : Input Parameter : Takes an integer as an input to represent course key
	 * @param title : Input Parameter : Takes a string as an input to represent course title
	 * @param major : Input Parameter : Takes a string as an input to represent Major
	 * @param credit points : Input Parameter : Takes float as an input to represent credit points
	 * @param start date : Input Parameter : Represents the start date of the block course
	 * @param end date : Input Parameter : Represents the end date of the block course
	 * @param start time : Input Parameter : Represents the start time of the block course
	 * @param end time : Input Parameter : Represents the end time of the block course
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime);

	/**
	 * This function prints the details of the block course- The course key, title, major, credit points, start/end date and time
	 * @param None
	 */
	void print() const;

	/**
	 * This function writes all the block courses available into a csv file
	 * @param reference to an ofstream
	 */
	void write(std::ostream &out) const;

	/**
	 * This is a destructor to the class BlockCourse
	 */
	~BlockCourse();
};

#endif /* BLOCKCOURSE_H_ */
