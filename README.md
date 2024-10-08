# StudentDB Project 
## Overview 
The StudentDB project is a student database management system designed for a course exercise. It allows users to manage students, courses, and enrollments, while ensuring data persistence using a custom CSV-like format. The project is built using C++ with emphasis on immutability, object-oriented design, and separation of concerns (MVC pattern). It utilizes the Poco and Boost libraries for various functionalities such as handling dates and networking. 

## Features 
1. Course Management:  
Add new courses. 
List all courses. 
2. Student Management:  
Add new students with their corresponding address.  
Search students by name.  
Update student details, including enrollments and grades. 
3. Enrollment Management: 
Add student enrollments for courses. 
Update or remove enrollments. 
4. Data Persistence:  
Save database content to a file using a CSV-like format.  
Load the data back from the file.  
5. External Data Fetching:  
Fetch sample student data from an external server using a Boost iostream for networking.  
Automatically generate and add students to the database using JSON format.  

## Class Structure  
Key Classes  
SimpleUI: Handles the user interface and command processing.  
StudentDb: Manages students, courses, and enrollments.  
Student: Represents a student, including address and enrollments.  
Course: Represents a course, including course details and its unique major.  
Enrollment: Handles student enrollments, storing grades and semester information.  

## Class Diagram  
The class diagram shows the relationships between various entities in the system such as Student, Course, Enrollment, and Address. Each class is designed with immutability in mind, meaning objects cannot be directly modified after creation unless absolutely necessary.

## Key Concepts  
1. Immutability: Most of the classes are designed to be immutable. For instance, updating an Address creates a new object rather than modifying the existing one.

2. Major Optimization: The Course class uses an internal optimization by storing major as a char, but exposes it as a std::string using the getMajor() method. This reduces memory usage while keeping the API user-friendly. 

3. Matrikel Number: New students are assigned a unique matrikel number, automatically generated based on the nextMatrikelNumber static member. 

4. MVC Pattern:  
The StudentDb class represents the Model. 
The SimpleUI class provides both the View and Controller, handling user input and output while interacting with the StudentDb. 

## Commands (User Interface) 
1. Add new Course: 
Prompts for course details and adds a new course to the database. 
2. List Courses: 
Lists all available courses with relevant details. 
3. Add new Student: 
Prompts for student and address details, and creates a new student in the database. 
4. Add Enrollment:  
Queries for a matrikel number, course ID, and semester, then adds a new enrollment to the student’s record. 
5. Print Student: 
Queries for a matrikel number and prints the student's information, including enrollments and grades. 
6. Search Student:  
Searches for students by substring match in their first or last name and prints their matrikel number, last name, and first name. 
7. Update Student: 
Allows modification of student details. Users can update student properties or manage their enrollments (add/remove enrollments or update grades). 
8. Persist Data (Read/Write): 
Save the current database content to a file or load it from a file. 
9. Generate Test Data:  
Connects to a server to fetch and generate random student data using the Boost JSON library.  

## Data Persistence Format 
Data is stored in a custom format that is derived from CSV. It first writes the number of data sets for each entity (Courses, Students, and Enrollments), followed by the actual data separated by semicolons (;).


## External Libraries:  
Poco: Used for handling dates and times in classes such as BlockCourse and WeeklyCourse.   
Boost: Used for networking and JSON parsing to fetch external student data. 