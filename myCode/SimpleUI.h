/*
 * SimpleUI.h
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"
#include <memory>

class SimpleUI {
private:
	StudentDb &db;
public:
	/**
	 * Contructor to the class StudentDb
	 * @param StudentDb object as reference : Input Parameter
	 */
	SimpleUI(StudentDb &db);

	/**
	 * This function provides commands to the user to create, add and update elements of student data base
	 * 	1. Add New Course
	 * 	2. List Courses
	 * 	3. Add New Student
	 * 	4. Add Enrollment
	 * 	5. Print Student
	 * 	6. Search Student
	 * 	7. Update Student
	 * 	8. Write Database to CSV File
	 * 	9. Read from file (to update database)
	 * 	10. Get student data from server and update in database
	 */
	void run();
};

#endif /* SIMPLEUI_H_ */
