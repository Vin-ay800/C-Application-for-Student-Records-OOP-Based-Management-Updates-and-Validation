#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    int roll_number;
    string name;
    int age;
    string class_level;
    float marks;

public:
    // Function to input student details
    void inputStudent() {
        cout << "Enter Roll Number: ";
        cin >> roll_number;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Class Level: ";
        cin >> class_level;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    // Function to display student details
    void displayStudent() const {
        cout << "Roll Number: " << roll_number << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Class Level: " << class_level << endl;
        cout << "Marks: " << marks << endl;
    }

    // Getter function to retrieve roll number
    int getRollNumber() const {
        return roll_number;
    }

    // Function to write student data to a file
    void writeToFile() const {
        ofstream outFile("students.txt", ios::app);
        if (outFile.is_open()) {
            outFile << roll_number << " " << name << " " << age << " " << class_level << " " << marks << endl;
            outFile.close();
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to read and display all students from the file
    static void readFromFile() {
        ifstream inFile("students.txt");
        if (inFile.is_open()) {
            int roll;
            string name;
            int age;
            string class_level;
            float marks;
            while (inFile >> roll >> ws && getline(inFile, name, ' ') && inFile >> age >> class_level >> marks) {
                cout << "\nRoll Number: " << roll;
                cout << "\nName: " << name;
                cout << "\nAge: " << age;
                cout << "\nClass Level: " << class_level;
                cout << "\nMarks: " << marks << endl;
                cout << "--------------------------" << endl;
            }
            inFile.close();
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to search for a student by roll number
    static void searchByRollNumber(int searchRoll) {
        ifstream inFile("students.txt");
        bool found = false;
        if (inFile.is_open()) {
            int roll;
            string name;
            int age;
            string class_level;
            float marks;
            while (inFile >> roll >> ws && getline(inFile, name, ' ') && inFile >> age >> class_level >> marks) {
                if (roll == searchRoll) {
                    found = true;
                    cout << "\nRoll Number: " << roll;
                    cout << "\nName: " << name;
                    cout << "\nAge: " << age;
                    cout << "\nClass Level: " << class_level;
                    cout << "\nMarks: " << marks << endl;
                    break;
                }
            }
            inFile.close();
            if (!found) {
                cout << "Student not found." << endl;
            }
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to delete a student by roll number
    static void deleteByRollNumber(int deleteRoll) {
        ifstream inFile("students.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        if (inFile.is_open() && tempFile.is_open()) {
            int roll;
            string name;
            int age;
            string class_level;
            float marks;
            while (inFile >> roll >> ws && getline(inFile, name, ' ') && inFile >> age >> class_level >> marks) {
                if (roll == deleteRoll) {
                    found = true;
                    cout << "Deleting student with roll number: " << deleteRoll << endl;
                } else {
                    tempFile << roll << " " << name << " " << age << " " << class_level << " " << marks << endl;
                }
            }
            inFile.close();
            tempFile.close();

            remove("students.txt");
            rename("temp.txt", "students.txt");

            if (!found) {
                cout << "Student not found." << endl;
            }
        } else {
            cout << "Unable to open file." << endl;
        }
    }
};

int main() {
    Student s;
    int choice, roll;

    while (true) {
        cout << "\nMenu:";
        cout << "\n1. Add Student";
        cout << "\n2. View All Students";
        cout << "\n3. Search Student by Roll Number";
        cout << "\n4. Delete Student by Roll Number";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            s.inputStudent();
            s.writeToFile();
            break;
        case 2:
            Student::readFromFile();
            break;
        case 3:
            cout << "Enter roll number to search: ";
            cin >> roll;
            Student::searchByRollNumber(roll);
            break;
        case 4:
            cout << "Enter roll number to delete: ";
            cin >> roll;
            Student::deleteByRollNumber(roll);
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice, please try again.";
        }
    }
    return 0;
}