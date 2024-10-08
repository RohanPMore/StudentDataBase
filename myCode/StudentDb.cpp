/*
 * StudentDb.cpp
 *
 *  Created on: 26 Jan 2024
 *      Author: ROHAN MORE
 */
#include <iostream>
#include <sstream>
#include "student.h"
#include "string"
#include "StudentDb.h"
#include "enrollment.h"
#include <algorithm>
#include "BlockCourse.h"
#include "WeeklyCourse.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Parser.h"
#include <fstream>
#include <iterator>

StudentDb::StudentDb() {
}

void StudentDb::addNewCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints) {
	Course course(courseKey, title, major, creditPoints);
	// Create a (uniquely owned) resource
	std::unique_ptr<const Course> course_ptr(new Course(course));
	courses[course.getCourseKey()] = std::move(course_ptr);
}

void StudentDb::addNewBlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime) {
	BlockCourse blockCourse { courseKey, title, major, creditPoints,
			Poco::Data::Date(startDate), Poco::Data::Date(endDate),
			Poco::Data::Time(startTime), Poco::Data::Time(endTime) };
	// Create a (uniquely owned) resource
	std::unique_ptr<const Course> blockCourse_ptr(new BlockCourse(blockCourse));
	courses[blockCourse.getCourseKey()] = std::move(blockCourse_ptr);
}

void StudentDb::addNewWeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime) {
	WeeklyCourse weeklyCourse { courseKey, title, major, creditPoints,
			Poco::DateTime::DaysOfWeek(dayOfWeek), Poco::Data::Time(startTime),
			Poco::Data::Time(endTime) };
	// Create a (uniquely owned) resource
	std::unique_ptr<const Course> weeklyCourse_ptr(
			new WeeklyCourse(weeklyCourse));
	courses[weeklyCourse.getCourseKey()] = std::move(weeklyCourse_ptr);

}

void StudentDb::printCourses() const {
	for (auto &itr : courses) {
		itr.second->print();
	}
}

void StudentDb::addNewStudent(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo) {
	Student newStudent(firstName, lastName, Poco::Data::Date(dateOfBirth),
			street, postalCode, cityName, additionalInfo);
	students.insert(
			std::pair<int, Student>(newStudent.getMatrikelNumber(),
					newStudent));
}

void StudentDb::addEnrollment(unsigned int matrikelNumber,
		unsigned int courseKey, std::string semester) {
	bool studentInDb = false;
	bool courseInDb = false;
	studentInDb = isStudentInDb(matrikelNumber);
	courseInDb = isCourseInDb(courseKey);
	//verify if the student is present in database and if the course is present in the db before enrollment
	if (studentInDb == false || courseInDb == false) {
		if (studentInDb == false) {
			std::cout << "Entered matrikel number does not exist in database"
					<< std::endl;
		} else {
			std::cout << "Entered course key does not exist in database"
					<< std::endl;
		}
	}
	//Enroll if student and course is present in the db
	else {
		if (true == hasAlreadyEnrolled(matrikelNumber, courseKey)) {
			std::cout << "Warning : Enrollment for this course already exists"
					<< std::endl;
		} else {
			students.at(matrikelNumber).addEnrollment(semester,
					courses.at(courseKey).get());
		}

	}
}

void StudentDb::printStudent(unsigned int matrikelNumber) {
	students.at(matrikelNumber).print();
}

void StudentDb::searchStudent(const std::string subString) {

	std::size_t subStringFoundInFirstName = 0;
	std::size_t subStringFoundInLastName = 0;
	std::string checkString = subString;
	int foundFlag = 0;
	for (auto studentItr : students) {
		std::string strFirstName = studentItr.second.getFirstName();
		std::string strLastName = studentItr.second.getLastName();
		//converting the first name into lower case
		std::transform(strFirstName.begin(), strFirstName.end(),
				strFirstName.begin(), ::tolower);
		//converting the last name into lower case
		std::transform(strLastName.begin(), strLastName.end(),
				strLastName.begin(), ::tolower);
		//converting the search sub string into lower case
		std::transform(checkString.begin(), checkString.end(),
				checkString.begin(), ::tolower);
		//check if substring is present in either first name or last name and print all student details for matched substring
		subStringFoundInFirstName = strFirstName.find(checkString);
		subStringFoundInLastName = strLastName.find(checkString);
		if ((subStringFoundInFirstName != std::string::npos)
				|| (subStringFoundInLastName != std::string::npos)) {
			foundFlag = 1;
			std::cout << "Matrikel Number : "
					<< studentItr.second.getMatrikelNumber() << std::endl;
			std::cout << "First Name : " << studentItr.second.getFirstName()
					<< std::endl;
			std::cout << "LastName : " << studentItr.second.getLastName()
					<< std::endl;
		}

	}
	//if not match found print on console
	if (foundFlag == 0) {
		std::cout << "No results found for entered string" << std::endl;
	}

}

void StudentDb::updateStudentDetails(unsigned int matrikelNumber) {

	int updateOption = -1;

	if (isStudentInDb(matrikelNumber) == false) {
		std::cout << "Entered Matrikel number not found" << std::endl;
	}

	else {
		do {
			std::cout
					<< "______________________________________Choose Field to be updated______________________________________ "
					<< std::endl;

			std::string firstName;
			std::string lastName;
			Poco::Data::Date dateOfBirth;

			std::cout << "1. Update first name" << std::endl;
			std::cout << "2. Update last name" << std::endl;
			std::cout << "3. Update date of birth" << std::endl;
			std::cout << "4. Update address" << std::endl;
			std::cout << "5. Update enrollment" << std::endl;
			std::cout << "0. Terminate Student Details Update" << std::endl;

			std::cout << "Select an option 0-5 : ";
			std::cin >> updateOption;

			switch (updateOption) {
			case 1: //Update first name
			{
				std::string firstName;
				std::cout << "Enter first Name : ";
				std::cin >> firstName;
				students.at(matrikelNumber).setFirstName(firstName);
				break;
			}
			case 2: //Update last name
			{
				std::string lastName;
				std::cout << "Enter last Name : ";
				std::cin >> lastName;
				students.at(matrikelNumber).setLastName(lastName);
				break;
			}
			case 3: //Update date of birth
			{
				int yearOfBirth = 0, monthOfBirth = 0, dayOfBirth = 0;
				std::cout << "Enter date of Birth in format YYYY MM DD : ";
				std::cin >> yearOfBirth >> monthOfBirth >> dayOfBirth;
				students.at(matrikelNumber).setDateOfBirth(
						Poco::Data::Date(yearOfBirth, monthOfBirth,
								dayOfBirth));
				break;
			}
			case 4: //Update address
			{
				std::string street = "", cityName = "", additionalInfo = "";
				unsigned short postalCode = 0;

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

				Address address(street, postalCode, cityName, additionalInfo);
				students.at(matrikelNumber).setAddress(address);
				break;
			}
			case 5: //Update Enrollment
			{
				int choice = 0; //Delete Enrollment or Update enrollment
				std::cout
						<< "Enter 1-To delete enrollment or 2-To add grade or 0-To exit enrollment update: ";
				std::cin >> choice;

				if (choice == 1) {
					unsigned int courseKey;
					std::cout
							<< "Enter the course key to delete the enrollment : ";
					std::cin >> courseKey;
					if (hasAlreadyEnrolled(matrikelNumber, courseKey)
							== false) {
						std::cout << "Enrollment not present for this course"
								<< std::endl;
					} else {
						students.at(matrikelNumber).deleteEnrollment(courseKey);
					}
					break;
				}

				else if (choice == 2) //add grade
						{
					unsigned int courseKey;
					std::cout
							<< "Enter the enrolled course key to update grade : ";
					std::cin >> courseKey;

					float courseGrade;
					std::cout << "Enter the grade : ";
					std::cin >> courseGrade;

					if (hasAlreadyEnrolled(matrikelNumber, courseKey)
							== false) {
						std::cout << "Enrollment not present for this course"
								<< std::endl;
					} else {
						students.at(matrikelNumber).updateEnrollment(courseKey,
								courseGrade);
					}
					break;
				} else if (choice == 0) {
					//do nothing
				}
				break;
			}
			case 0:
			default: //do nothing
				break;
			}
			students.at(matrikelNumber).print();
		} while (updateOption != 0);
	}
}

bool StudentDb::isStudentInDb(unsigned int matrikelNumber) {
	for (auto studentItr : students) {
		if (studentItr.first == matrikelNumber) {
			return true;
		}
	}
	return false;
}

bool StudentDb::isCourseInDb(unsigned int courseKey) {
	for (auto &courseItr : courses) {
		if (courseItr.first == courseKey) {
			return true;
		}
	}
	return false;
}

bool StudentDb::hasAlreadyEnrolled(unsigned int matrikelNumber,
		unsigned int coursekey) {

	for (auto enrolledCoursesItr : students.at(matrikelNumber).getEnrollments()) {
		if (enrolledCoursesItr.getCourse()->getCourseKey() == coursekey) {
			return true;
		}
	}
	return false;
}

void StudentDb::write(std::ostream &out) const {
	int numberOfElements = 0;
	out << courses.size() << "\n";
	for (auto &courseItr : courses) {
		courseItr.second->write(out);
		out << "\n";
	}
	out << students.size() << "\n";
	for (auto studentItr : students) {
		studentItr.second.write(out);
		out << "\n";
	}
	for (auto studentItr : students) {
		numberOfElements = numberOfElements
				+ studentItr.second.getEnrollments().size();
	}
	out << numberOfElements << "\n";
	for (auto studentItr : students) {
		studentItr.second.writeEnrollment(out);
	}
}

void StudentDb::read(std::istream &in) {

	//deleting all elements in the database
	courses.clear();
	students.clear();
	Student::resetMartrikelNumber();

	int numberOfCourses = 0;
	int numberOfStudents = 0;
	int numberOfEnrollments = 0;
	std::string tempString = "";

	//Determine number of courses available
	std::getline(in, tempString);
	numberOfCourses = std::stoi(tempString);
	tempString = "";

	for (int idx = 0; idx < numberOfCourses; idx++) {
		//initialising all the local variables
		int courseKey = 0, creditPoints = 0.0, dayOfWeek = 0, startDateYear = 0,
				startDateMonth = 0, startDateDay = 0, endDateYear = 0,
				endDateMonth = 0, endDateDay = 0, startTimeHour = 0,
				startTimeMinute = 0, startTimeSecond = 0, endTimeHour = 0,
				endTimeMinute = 0, endTimeSecond = 0;
		std::string courseTitle = "", major = "";

		//If the line starts with 'B' then the information of blocked course is retrieved stored in local variables and a new blocked course is created
		std::getline(in, tempString, ';');
		if (tempString == "B") {
			tempString = "";
			std::getline(in, tempString, ';');
			courseKey = std::stoi(tempString);
			tempString = "";

			std::getline(in, courseTitle, ';');

			std::getline(in, major, ';');

			std::getline(in, tempString, ';');
			creditPoints = std::stof(tempString);
			tempString = "";

			std::getline(in, tempString, '.');
			startDateDay = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, '.');
			startDateMonth = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ';');
			startDateYear = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, '.');
			endDateDay = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, '.');
			endDateMonth = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ';');
			endDateYear = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			startTimeHour = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			startTimeMinute = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ';');
			startTimeSecond = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			endTimeHour = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			endTimeMinute = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString);
			endTimeSecond = std::stoi(tempString);
			tempString = "";

			addNewBlockCourse(courseKey, courseTitle, major, creditPoints,
					Poco::Data::Date(startDateYear, startDateMonth,
							startDateDay),
					Poco::Data::Date(endDateYear, endDateMonth, endDateDay),
					Poco::Data::Time(startTimeHour, startTimeMinute,
							startTimeSecond),
					Poco::Data::Time(endTimeHour, endTimeMinute,
							endTimeSecond));
		}

		//If the line starts with 'W' then the information of blocked course is retrieved stored in local variables and a new blocked course is created
		else if (tempString == "W") {
			tempString = "";
			std::getline(in, tempString, ';');
			courseKey = std::stoi(tempString);
			tempString = "";

			std::getline(in, courseTitle, ';');

			std::getline(in, major, ';');

			std::getline(in, tempString, ';');
			creditPoints = std::stof(tempString);
			tempString = "";

			std::getline(in, tempString, ';');
			dayOfWeek = stoi(tempString);

			std::getline(in, tempString, ':');
			startTimeHour = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			startTimeMinute = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ';');
			startTimeSecond = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			endTimeHour = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString, ':');
			endTimeMinute = std::stoi(tempString);
			tempString = "";

			std::getline(in, tempString);
			endTimeSecond = std::stoi(tempString);
			tempString = "";

			addNewWeeklyCourse(courseKey, courseTitle, major, creditPoints,
					Poco::DateTime::DaysOfWeek(dayOfWeek),
					Poco::Data::Time(startTimeHour, startTimeMinute,
							startTimeSecond),
					Poco::Data::Time(endTimeHour, endTimeMinute,
							endTimeSecond));
		}

	}

	//Determine number of students data available
	std::getline(in, tempString);
	numberOfStudents = std::stoi(tempString);
	tempString = "";

	//Retrieve student details and create a new student(the matriculation number is set back to default value)
	for (int idx = 0; idx < numberOfStudents; idx++) {

		std::string firstName = "";
		std::string lastName = "";
		int yearOfBirth = 0;
		int monthOfBirth = 0;
		int dayOfBirth = 0;
		std::string street = "";
		unsigned short postalCode = 0;
		std::string cityName = "";
		std::string additionalInfo = "";

		std::getline(in, tempString, ';');
		tempString = "";

		std::getline(in, firstName, ';');
		std::getline(in, lastName, ';');

		std::getline(in, tempString, '.');
		dayOfBirth = std::stoi(tempString);
		tempString = "";

		std::getline(in, tempString, '.');
		monthOfBirth = std::stoi(tempString);
		tempString = "";

		std::getline(in, tempString, ';');
		yearOfBirth = std::stoi(tempString);
		tempString = "";

		std::getline(in, street, ';');

		std::getline(in, tempString, ';');
		postalCode = (unsigned short) (std::stoi(tempString));
		tempString = "";

		std::getline(in, cityName, ';');
		std::getline(in, additionalInfo);

		addNewStudent(firstName, lastName,
				Poco::Data::Date(yearOfBirth, monthOfBirth, dayOfBirth), street,
				postalCode, cityName, additionalInfo);
	}

	//determining number of enrollments available in the file
	std::getline(in, tempString);
	numberOfEnrollments = std::stoi(tempString);
	tempString = "";

	//Retrieve information related to enrollment and assigning the enrollemnts to the previoslu created students
	for (int idx = 0; idx < numberOfEnrollments; idx++) {

		int matrikelNumber = 0;
		int courseKey = 0;
		std::string semester = "";
		float grade = 0;

		std::getline(in, tempString, ';');
		matrikelNumber = std::stoi(tempString);
		tempString = "";

		std::getline(in, tempString, ';');
		courseKey = std::stoi(tempString);
		tempString = "";

		std::getline(in, semester, ';');

		std::getline(in, tempString);
		grade = std::stof(tempString);
		tempString = "";

		addEnrollment(matrikelNumber, courseKey, semester);
		students.at(matrikelNumber).updateEnrollment(courseKey, grade);

	}

}

void StudentDb::getAndUpdateStudentsFromServer() {

	//Connecting to server mnl.de port 4242
	Poco::Net::SocketAddress sa("mnl.de", 4242);

	//Creating a socket - communication end point
	Poco::Net::StreamSocket socket(sa);

	//Creating a socket stream to send and receive data
	Poco::Net::SocketStream sStream(socket);

	//Sending 'generate' command to generate student data
	sStream << "generate\n";
	sStream.flush();

	//creating a file to update the data recieved from server into json file
	std::string fileName = "dataFromServer.json";
	std::ofstream tempOutputFile;
	std::string line;
	tempOutputFile.open("temp.json", std::ios::trunc);

	//Copying the stream into a temporary output file
	Poco::StreamCopier::copyStream(sStream, tempOutputFile);

	tempOutputFile.close();
	sStream << "quit\n";
	sStream.flush();

	//Removing additional unnecessary lines in the file
	std::ifstream tempinputFile("temp.json", std::ios::in);
	std::ofstream outputFile;
	outputFile.open(fileName, std::ios::trunc);

	while (getline(tempinputFile, line)) {
		if (line[0] == '{') {
			if (!line.empty()) {
				outputFile << line;
			}
		}
	}

	std::remove("temp.json");
	outputFile.close();

	//Reading the file into a string
	std::ifstream inputFile(fileName, std::ios::in);
	std::string dataFromServer((std::istreambuf_iterator<char>(inputFile)),
			(std::istreambuf_iterator<char>()));


	Poco::JSON::Object::Ptr pObject;
	Poco::JSON::Object::Ptr nampePObject;
	Poco::JSON::Object::Ptr dateOfBirthPObject;
	Poco::JSON::Object::Ptr addressPObject;
	Poco::Dynamic::Var temp_value;


	std::string firstName = "", lastName = "", street = "", cityName = "",
			additionalInfo = "";
	int yearOfBirth = 0, monthOfBirth = 0, dayOfBirth = 0;
	int postalCode = 0;

	//Parsing the json string, retrieving data and creating a new student
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(dataFromServer);
	pObject = result.extract<Poco::JSON::Object::Ptr>();

	temp_value = pObject->get("name");
	nampePObject = temp_value.extract<Poco::JSON::Object::Ptr>();
	firstName = nampePObject->getValue<std::string>("firstName");
	lastName = nampePObject->getValue<std::string>("lastName");

	temp_value = pObject->get("dateOfBirth");
	dateOfBirthPObject = temp_value.extract<Poco::JSON::Object::Ptr>();
	yearOfBirth = dateOfBirthPObject->get("year");
	//yearOfBirth = yearOfBirth+1970;
	monthOfBirth = dateOfBirthPObject->get("month");
	dayOfBirth = dateOfBirthPObject->get("date");

	temp_value = pObject->get("location");
	addressPObject = temp_value.extract<Poco::JSON::Object::Ptr>();
	street = addressPObject->getValue<std::string>("street");
	postalCode = (int) addressPObject->get("postCode");
	cityName = addressPObject->getValue<std::string>("city");
	additionalInfo = addressPObject->getValue<std::string>("state");

	addNewStudent(firstName, lastName,
			Poco::Data::Date(yearOfBirth, monthOfBirth, dayOfBirth), street,
			postalCode, cityName, additionalInfo);

}

