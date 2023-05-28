# CPP_StudentManagementSystem
Student Database System
The Student Database System is a C++ program that allows users to manage and store information about students in a database. It provides functionality to add students, display the list of students, and update student information.

Note: Username is admin and Password is password. 

Features:
Add a student: Users can add undergraduate or graduate students to the database by providing their name, age, and relevant information based on their student type.
Display students: Users can view the list of students currently stored in the database, including their name, age, student ID, and additional information based on their student type.
Update student information: Users can update the name and age of a specific student by providing their student ID.
Classes
Student: The base class that represents a student. It contains the common attributes of all students, such as name, age, and student ID. It also provides a display() method to output the student's information.

UndergraduateStudent: A derived class from Student that represents an undergraduate student. It adds an additional attribute for the student's current year and overrides the display() method to include the year and student type.

GraduateStudent: A derived class from Student that represents a graduate student. It adds an additional attribute for the student's research topic and overrides the display() method to include the research topic and student type.

StudentDatabase: A class that manages the collection of students. It uses a vector to store pointers to Student objects. It provides methods to add a student to the database, display all students, and update student information.

Usage: There are many options, one of them is listed below.
Add a student:

To add an undergraduate student: Create an UndergraduateStudent object by providing the student's name, age, and year. Then, call the addStudent() method of the StudentDatabase class, passing the UndergraduateStudent object as a parameter.
To add a graduate student: Create a GraduateStudent object by providing the student's name, age, and research topic. Then, call the addStudent() method of the StudentDatabase class, passing the GraduateStudent object as a parameter.
Display students:

Call the displayStudents() method of the StudentDatabase class to show the list of students in the database.
Update student information:

Call the updateStudent() method of the StudentDatabase class, passing the student ID of the student whose information needs to be updated. Follow the prompts to enter the new name and age for the student.
Getting Started
Ensure you have a C++ compiler installed on your system.

Clone the repository and navigate to the project directory.

Compile the source code using the following command:


Copy code
g++ main.cpp -o studentdb
Run the program:


Copy code
./studentdb
Follow the instructions displayed on the console to interact with the Student Database System.
