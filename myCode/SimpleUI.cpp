/*
 * SimpleUI.cpp
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */

#include "SimpleUI.h"
#include <string>
#include <iostream>
#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>
#include <Poco/DateTime.h>
#include <fstream>

SimpleUI::SimpleUI(StudentDb &db) :
		db { db } {
}

void SimpleUI::run() {
	unsigned int choice;
	while (1) {
		std::cout
				<< "______________________________________Available Commands______________________________________ "
				<< std::endl;
		std::cout << "1. Add New Course" << std::endl;
		std::cout << "2. List Courses" << std::endl;
		std::cout << "3. Add New Student" << std::endl;
		std::cout << "4. Add Enrollment" << std::endl;
		std::cout << "5. Print Student" << std::endl;
		std::cout << "6. Search Student" << std::endl;
		std::cout << "7. Update Student" << std::endl;
		std::cout << "8. Write Database to CSV File" << std::endl;
		std::cout << "9. Read from file (to update database)" << std::endl;
		std::cout << "10. Get student data from server and update in database"
				<< std::endl;
		std::cout << "\nEnter your choice (1-10) : ";
		std::cin >> choice;
		std::cout << std::endl;
		switch (choice) {

		case 1: //Add New Course
		{
			/**Data requried for creating a course :
			 * unsigned int courseKey
			 * std::string title
			 * std::string major
			 * float creditPoints*/

			//Local variables declaration for adding new course
			unsigned int courseKey = 0;
			std::string title = "", major = "";
			float creditPoints;
			unsigned int courseType;

			std::cout
					<< "______________________________________New Course Creation______________________________________"
					<< std::endl;
			std::cout << "Enter course key : ";
			std::cin >> courseKey;
			std::cout << "Enter title of the course : ";
			std::cin.clear();
			fflush(stdin);
			std::getline(std::cin, title);
			std::cout << "Enter the major that course belongs to : ";
			std::cin >> major;
			std::cout << "Enter credit points of the course : ";
			std::cin >> creditPoints;
			std::cout
					<< "Enter the type of the course (0-Simple Course with no schedule) (1-Block Course) (2-Weekly Course) : ";
			std::cin >> courseType;

			if (courseType == 0) {
				db.addNewCourse(courseKey, title, major, creditPoints);
				break;
			}

			else if (courseType == 1) {
				/** Additional data requried for creating a Block course :
				 * 	Poco::Data::Date startDate;
				 * 	Poco::Data::Date endDate;
				 * 	Poco::Data::Time startTime;
				 * 	Poco::Data::Time endTime;*/

				//Local variables declaration for adding new course
				int startDateYear = 0, startDateMonth = 0, startDateDay = 0;
				int endDateYear = 0, endDateMonth = 0, endDateDay = 0;
				int startTimeHour = 0, startTimeMinute = 0, startTimeSecond = 0;
				int endTimeHour = 0, endTimeMinute = 0, endTimeSecond = 0;

				//Start date of the course
				std::cout
						<< "Enter start date of the block course in YYYY MM DD format: ";
				std::cin >> startDateYear >> startDateMonth >> startDateDay;
				//End date of the course
				std::cout
						<< "Enter end date of the block course in YYYY MM DD format: ";
				std::cin >> endDateYear >> endDateMonth >> endDateDay;
				//Start time of the course
				std::cout
						<< "Enter start time of the block course in HH MM SS format: ";
				std::cin >> startTimeHour >> startTimeMinute >> startTimeSecond;
				std::cout
						<< "Enter end time of the block course in HH MM SS format: ";
				std::cin >> endTimeHour >> endTimeMinute >> endTimeSecond;

				db.addNewBlockCourse(courseKey, title, major, creditPoints,
						Poco::Data::Date(startDateYear, startDateMonth,
								startDateDay),
						Poco::Data::Date(endDateYear, endDateMonth, endDateDay),
						Poco::Data::Time(startTimeHour, startTimeMinute,
								startTimeSecond),
						Poco::Data::Time(endTimeHour, endTimeMinute,
								endTimeSecond));
			}

			else if (courseType == 2) {
				/** Additional data required for creating a Weekly course :
				 * 	Poco::DateTime::DaysOfWeek dayOfWeek;
				 * 	Poco::Data::Time startTime;
				 * 	Poco::Data::Time endTime;*/

				//Local variables declaration for adding new course
				int dayOfWeek;
				int startTimeHour = 0, startTimeMinute = 0, startTimeSecond = 0;
				int endTimeHour = 0, endTimeMinute = 0, endTimeSecond = 0;

				//Day of the week the course occurs
				std::cout
						<< "Enter the day of the week the course occurs (0-Sunday, 6-Saturday):";
				std::cin >> dayOfWeek;
				//Start time of the course
				std::cout
						<< "Enter start time of the weekly course in HH MM SS format: ";
				std::cin >> startTimeHour >> startTimeMinute >> startTimeSecond;
				std::cout
						<< "Enter end time of the weekly course in HH MM SS format: ";
				std::cin >> endTimeHour >> endTimeMinute >> endTimeSecond;

				db.addNewWeeklyCourse(courseKey, title, major, creditPoints,
						Poco::DateTime::DaysOfWeek(dayOfWeek),
						Poco::Data::Time(startTimeHour, startTimeMinute,
								startTimeSecond),
						Poco::Data::Time(endTimeHour, endTimeMinute,
								endTimeSecond));
				break;
			}

			break;
		}
		case 2: //List all courses
			std::cout
					<< "______________________________________Courses in DataBase______________________________________"
					<< std::endl;
			db.printCourses();
			break;
		case 3: //Add new student
		{
			std::cout
					<< "______________________________________New Student Creation______________________________________"
					<< std::endl;

			/**Data required for adding a student :
			 * std::string firstName
			 * std::string lastName
			 * Poco::Data::Date dateOfBirth
			 * std::string street
			 * unsigned short postalCode
			 * std::string cityName
			 * std::string additionalInfo*/

			//Local variables declaration for adding new course
			std::string firstName = "", lastName = "";
			int yearOfBirth = 0, monthOfBirth = 0, dayOfBirth = 0;
			std::string street = "", cityName = "", additionalInfo = "";
			unsigned short postalCode = 0;

			std::cout << "::::::::::::PERSONAL DETAILS::::::::::::"
					<< std::endl;
			std::cout << "Enter first Name of the student : ";
			std::cin >> firstName;
			std::cout << "Enter last Name of the student : ";
			std::cin >> lastName;
			std::cout
					<< "Enter dateOfBirth of the student in YYYY MM DD format : ";
			std::cin >> yearOfBirth >> monthOfBirth >> dayOfBirth;

			std::cout << "::::::::::::ADDRESS::::::::::::" << std::endl;
			std::cin.clear();
			fflush(stdin);
			std::cout << "Enter street : ";
			std::getline(std::cin, street);
			std::cout << "Enter postal code : ";
			std::cin >> postalCode;

			std::cin.clear();
			fflush(stdin);
			std::cout << "Enter city name : ";
			std::getline(std::cin, cityName);

			std::cin.clear();
			fflush(stdin);
			std::cout << "Enter additional information : ";
			std::getline(std::cin, additionalInfo);
			db.addNewStudent(firstName, lastName,
					Poco::Data::Date(yearOfBirth, monthOfBirth, dayOfBirth),
					street, postalCode, cityName, additionalInfo);
			break;
		}
		case 4: //Add Enrollment
			/**Data required for adding a student :
			 * unsigned int matrikelNumber
			 * unsigned int courseKey
			 * std::string semester
			 */

			//Local variables declaration for adding new course
		{
			unsigned int matrikelNumber = 0, courseKey = 0;
			std::string semester = "";

			std::cout
					<< "______________________________________Add Enrollment______________________________________"
					<< std::endl;
			std::cout << "Enter student matrikelNumber : ";
			std::cin >> matrikelNumber;
			std::cout << "Enter course key for enrollment : ";
			std::cin >> courseKey;

			std::cin.clear();
			fflush(stdin);
			std::cout << "Enter the semester for enrollment : ";
			std::getline(std::cin, semester);
			db.addEnrollment(matrikelNumber, courseKey, semester);
			break;
		}
		case 5: //Print Student Information
		{/**Data required for adding a student :
		 * unsigned int matrikelNumber
		 */
			unsigned int matrikelNumber = 0;
			std::cout
					<< "______________________________________Student Information______________________________________"
					<< std::endl;
			std::cout << "Enter the matrikel number : ";
			std::cin >> matrikelNumber;
			db.printStudent(matrikelNumber);
			break;
		}
		case 6: //Search Student Information
		{
			/**Data required for searching a student :
			 * std::string subString
			 */

			std::string subString;
			std::cout
					<< "______________________________________Student Search______________________________________"
					<< std::endl;
			std::cout << "Enter a keyword to search for students :"
					<< std::endl;
			std::cin >> subString;
			db.searchStudent(subString);
			break;
		}
		case 7: //Update Student Details
		{
			/**Data required for searching a student :
			 * unsigned int matrikelNumber
			 */
			unsigned int matrikelNumber = 0;
			std::cout << "Enter student matrikelNumber : ";
			std::cin >> matrikelNumber;
			db.updateStudentDetails(matrikelNumber);
			break;
		}
		case 8: //Write data to file
		{
			std::cout
					<< "______________________________________Write to Database______________________________________"
					<< std::endl;

			std::string fileName = "defaultFileName.csv";
			std::cout << "Enter a file name : ";
			std::cin >> fileName;
			fileName = fileName + ".csv";
			std::ofstream outputFile;
			outputFile.open(fileName, std::ios::trunc);
			if (!outputFile) {
				std::cout << "Error in creating file!!!";
			} else {
				db.write(outputFile);
				outputFile.close();
			}
			break;
		}

		case 9: //Read from a file
		{
			std::cout
					<< "______________________________________Update Database from file______________________________________"
					<< std::endl;
			std::string fileName = "defaultFileName.csv";
			std::cout << "Enter a file name : ";
			std::cin >> fileName;
			fileName = fileName + ".csv";
			std::ifstream inputFile;
			inputFile.open(fileName);
			if (!inputFile) {
				std::cout << "Error opening a file!!!!";
			} else {
				db.read(inputFile);
				inputFile.close();

			}
			break;
		}

		case 10: //Get Student details from server and update to database
		{
			int noOfStudents;
			std::cout
					<< "___________________________________Get Student details from server and update to database_________________________________________"
					<< std::endl;
			std::cout
					<< "Enter number of students information required from server :";
			std::cin >> noOfStudents;
			for (int idx = 1; idx <= noOfStudents; idx++) {
				db.getAndUpdateStudentsFromServer();
			}

			break;
		}

		default:
			std::cout
					<< "Selected invalid command, Please select a valid command from the below list"
					<< std::endl;
			break;
		}
	}

}
