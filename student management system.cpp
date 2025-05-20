#include <iostream>
#include <fstream>
using namespace std;


string trim(string str) {
    int start = 0;
    while (start < str.length() && (str[start] == ' ' || str[start] == '\t'))
        start++;
    int end = str.length() - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t'))
        end--;
    return (start > end) ? "" : str.substr(start, end - start + 1);
}

class Student{
protected:
    string Name, RollNo;
    float CGPA;

public:
    void input() {
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, Name);
        cout << "Enter Roll No: ";
        getline(cin, RollNo);
        cout << "Enter CGPA: ";
        cin >> CGPA;
    }

    void display() {
        cout << Name << " : " << RollNo<< " : " << CGPA<<endl;
    }

    string getName() { return Name; }
    string getRollNo() { return RollNo; }
    float getCGPA() { return CGPA; }
    void setCGPA(float newCGPA) { CGPA = newCGPA; }
};

// Manager class
class StudentManager {
private:
    string filename = "Student.txt";

public:
    void addStudent() {
        Student s;
        s.input();

        ofstream outFile(filename, ios::app);
        outFile << s.getName() << " : " << s.getRollNo() << " : " << s.getCGPA() << endl;
        outFile.close();

        cout << "Student added successfully!" << endl;
    }

    void searchStudent() {
        string name;
        cin.ignore();
        cout << "Enter student name to search: ";
        getline(cin, name);

        ifstream inFile(filename);
        string line;

        while (getline(inFile, line)) {
            if (line.find(name) != string::npos) {
                cout << "Name | RollNo | CGPA" << endl;
                cout << line << endl;
                inFile.close();
                return;
            }
        }

        cout << "Student not found!" << endl;
        inFile.close();
    }

    void updateStudent() {
        string rollNo;
        cin.ignore();
        cout << "Enter Roll No of student to update: ";
        getline(cin, rollNo);

        ifstream inFile(filename);
        ofstream tempFile("Student_Temp.txt");

        string name, rno;
        float cgpa;
        string line;

        while (getline(inFile, line)) {
            // Read using string stream for simplicity
            size_t pos1 = line.find(" : ");
            size_t pos2 = line.rfind(" : ");

            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
                tempFile << line << endl; // invalid format, keep as-is
                continue;
            }

            name = trim(line.substr(0, pos1));
            rno = trim(line.substr(pos1 + 3, pos2 - pos1 - 3));
            string cgpaStr = trim(line.substr(pos2 + 3));

            if (rno == rollNo) {
                cout << "Enter new CGPA: ";
                cin >> cgpa;
                tempFile << name << " : " << rno << " : " << cgpa << endl;
                cout << "CGPA updated for: " << rno << endl;
            } else {
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();
        remove(filename.c_str());
        rename("Student_Temp.txt", filename.c_str());
    }
};

int main() {
    StudentManager sm;
    int choice;

    while (true) {
        cout << "\nWelcome To Student Management System" << endl;
        cout << "" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sm.addStudent(); break;
            case 2: sm.searchStudent(); break;
            case 3: sm.updateStudent(); break;
            case 4: cout << "Good Luck!" << endl; return 0;
            default: cout << "Invalid Choice!" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
 