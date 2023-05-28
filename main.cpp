

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Student {
public:
    // These variables will store the name(s), age(s), and ID of student(s)
    string name;
    int age;
    int studentID;

    // This Constructor initialises the 'name', 'age' and 'studendID' data members for the student class.
    Student(const string& name, int age, int studentID)
            : name(name), age(age), studentID(studentID) {}

    // This will display student information
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Student ID: " << studentID << endl;
    }
};

class UndergraduateStudent : public Student {
public:
    // This variable will basically store the year a student is currently in (e.g., Year 2)
    int year;

    /* This Constructor initialises the 'name', 'age', 'studendID' and 'year' data members by calling the base class
     constructor.
     */
    UndergraduateStudent(const string& name, int age, int year)
            : Student(name, age, studentID), year(year) {}

    // This will display student information
    virtual void display() const override {
        cout << "Name: " << name << ", Age: " << age << ", Year: " << year << ", Student ID: " << studentID << ", Student Type: Undergraduate" << endl;
    }
};

class GraduateStudent : public Student {
public:
    // This variable will store what research a graduate student is currently doing
    string researchTopic;

    /* This Constructor initialises the 'name', 'age', and 'researchTopic' data members by invoking the base class
     constructor.
     */
    GraduateStudent(const string& name, int age, const string& researchTopic)
            : Student(name, age, studentID), researchTopic(researchTopic) {}

    // This will display student information
    virtual void display() const override {
        cout << "Name: " << name << ", Age: " << age << ", Student ID: " << studentID << ", Research Topic: " << researchTopic << ", Student Type: Graduate" << endl;
    }
};

class StudentDatabase {
private:
    vector<Student *> students;

public:
    // This will basically add a student to the database
    void addStudent(Student *student) {
        students.push_back(student);
    }

    // This will display all students currently in the database
    void displayStudents() const {
        cout << "Students in the database:" << endl;
        for (const auto &student: students) {
            student->display();
        }
    }

    // This will update the information of a student
    void updateStudent(int studentID) {
        for (auto& student : students) {
            if (student->studentID == studentID) {
                cout << "Enter new name for the student: ";
                cin.ignore(); // Ignore the newline character from previous input
                getline(cin, student->name);

                int age;

                while (true) {
                    cout << "Enter new age for the student: ";
                    if (!(cin >> age)) {
                        cout << "Invalid age. Please enter a numeric value." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    // This will validate the age of a student
                    if (age < 15 || age > 150) {
                        cout << "Invalid age. Please enter an age between 15 and 150." << endl;
                        continue;
                    }

                    /* This is to check if there are any trailing characters after the numeric input and to make sure
                        that age is not a non-numerical value such as 22A
                    */
                    char c;
                    if (cin.get(c) && c != '\n') {
                        cout << "Invalid input. Please enter a numeric value." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    break; // If the age is valid then the loop will be exited.
                }


                if (auto undergrad = dynamic_cast<UndergraduateStudent*>(student)) {
                    cout << "Enter new year for the undergraduate student: ";

                    int year;
                    while (!(cin >> year) || year < 1 || year > 4) {
                        if (cin.fail()) {
                            cout << "Invalid input. Please enter a numerical value." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            cout << "Invalid input. Year must be an integer between 1 and 4." << endl;
                        }

                        cout << "Enter new year for the undergraduate student: ";
                    }

                    undergrad->year = year;
                }

                else if (auto grad = dynamic_cast<GraduateStudent*>(student)) {
                    cout << "Enter new research topic for the graduate student: ";
                    cin >> grad->researchTopic;
                }

                cout << "Student information updated successfully." << endl;
                return;
            }
        }
        cout << "Student ID not found in the database." << endl;
    }


    // This will delete a student from the database
    void deleteStudent(int studentID) {
        while (true) {
            auto it = std::find_if(students.begin(), students.end(), [studentID](const Student *student) {
                return student->studentID == studentID;
            });

            if (it != students.end()) {
                delete *it;
                students.erase(it);
                cout << "Student deleted successfully." << endl;
                break;  // Exit the loop when the student is deleted
            } else {
                cout << "Student ID not found in the database." << endl;
                cout << "Enter the correct student ID to delete: ";
                cin >> studentID;
                if (cin.fail()) {
                    cout << "Invalid input. Student ID must be an integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
        }
    }
};

// This will be our authentication system logic
bool authenticateUser(const string& username, const string& password) {

    return (username == "admin" && password == "password");
}

// This is the menu that has all the choices
void displayMenu() {
    cout << "------------------------" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display Students" << endl;
    cout << "3. Update Student" << endl;
    cout << "4. Delete Student" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    string username, password;
    bool authenticated = false;

    cout << "Student Database System" << endl;
    cout << "------------------------" << endl;

    while (!authenticated) {
        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if (authenticateUser(username, password)) {
            authenticated = true;
        } else {
            cout << "Wrong username or password. Please try again." << endl;
        }
    }

    StudentDatabase database;
    char choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case '1': {
                // This is the Add student logic
                string name;
                int age;
                int year;
                string researchTopic;
                char studentType;
                int studentID;

                cout << "Enter student type (U for Undergraduate, G for Graduate): ";
                cin >> studentType;

                cout << "Enter student name: ";
                cin.ignore(); // Ignores the newline character from previous input
                getline(cin, name);

                while (true) {
                    cout << "Enter student age: ";
                    if (!(cin >> age)) {
                        cout << "Invalid age. Please enter a numeric value." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    // This will validate the age of a student.
                    if (age < 15 || age > 150) {
                        cout << "Invalid age. Please enter an age between 15 and 150." << endl;
                        continue;
                    }

                    /* This is to check if there are any trailing characters after the numeric input and to make sure
                     * that age is not a non-numerical value such as 22A
                     */
                    char c;
                    if (cin.get(c) && c != '\n') {
                        cout << "Invalid input. Please enter a numeric value." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    break; // If the age is valid then the loop will be exited
                }

                while (true) {
                    cout << "Enter Student ID (8 digits): ";
                    if (!(cin >> studentID)) {
                        cout << "Invalid input. Student ID must be a numeric value." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    /* This is to validate the student ID and it is using 8-digits like the university's database
                     * system
                    */
                    if (to_string(studentID).length() != 8) {
                        cout << "Invalid student ID. Please enter an 8-digit ID." << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    break; // If the Student ID is valid, the loop will be exited
                }

                if (studentType == 'U') {
                    while (true) {
                        cout << "Enter student year (1, 2, 3, or 4): ";
                        if (!(cin >> year)) {
                            cout << "Invalid input. Year must be an integer." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        if (year < 1 || year > 4) {
                            cout << "Invalid year. Please enter a value between 1 and 4." << endl;
                            continue;
                        }

                        break; // If the year is valid, the loop will be exited
                    }

                    auto undergraduateStudent = new UndergraduateStudent(name, age, year);

                    // This will assign the student ID to undergraduate student
                    undergraduateStudent->studentID = studentID;

                    //This will add the undergraduate student to the database
                    database.addStudent(undergraduateStudent);
                    cout << "Added Undergraduate Student: " << name << endl;
                }
                else if (studentType == 'G') {
                    cout << "Enter Student Research Topic: ";
                    cin >> researchTopic;


                    if (researchTopic.empty()) {
                        cout << "Invalid input. Research topic cannot be empty." << endl;
                        break;
                    }

                    auto graduateStudent = new GraduateStudent(name, age, researchTopic);
                    graduateStudent->studentID = studentID;  // This will assign the student ID to graduate student

                    //This will add the graduate student to the database
                    database.addStudent(graduateStudent);
                    cout << "Added graduate student: " << name << endl;
                    cout << "Student added successfully." << endl;

                    break;
                }
                else {
                    cout << "Invalid student type. Please try again." << endl;
                }
                break; // If student type is valid, the loop will be exited
            }
            case '2': {
                // Display students logic
                database.displayStudents();
                break;
            }
            case '3': {
                // Update student logic
                int studentID;
                cout << "Enter the student ID to update: ";

                while (true) {
                    cin >> studentID;

                    // This will validate the student ID to make sure it is 8-digits
                    if (to_string(studentID).length() != 8) {
                        cout << "Invalid student ID. Please enter an 8-digit ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    break;
                }

                database.updateStudent(studentID);
                break;
            }
            case '4': {
                // Delete student logic
                int studentID;

                cout << "Enter the student ID to delete: ";
                cin >> studentID;

                if (cin.fail()) {
                    cout << "Invalid input. Student ID must be an integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                database.deleteStudent(studentID);
                break;
            }
            case '5': {
                cout << "Exiting program." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice != '5');


    return 0;
}
