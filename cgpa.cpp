#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Base class: Student
class Student {
protected:
    string name;
    int rollNo;
    int numSubjects;

public:
    Student(string n, int r, int ns) {
        name = n;
        rollNo = r;
        numSubjects = ns;
    }

    void displayStudentInfo() {
        cout << "\nStudent Name: " << name;
        cout << "\nRoll No: " << rollNo;
        cout << "\nNumber of Subjects: " << numSubjects << endl;
    }
};

// Derived class: Marks
class Marks : public Student {
protected:
    float marks[10];
    float credits[10];

public:
    Marks(string n, int r, int ns) : Student(n, r, ns) {}

    void inputMarks() {
        cout << "\nEnter marks and credits for each subject:\n";
        for (int i = 0; i < numSubjects; i++) {
            cout << "Subject " << i + 1 << " marks (out of 100): ";
            cin >> marks[i];
            cout << "Credit hours: ";
            cin >> credits[i];
        }
    }
};

// Derived class: Result
class Result : public Marks {
private:
    float cgpa;

public:
    Result(string n, int r, int ns) : Marks(n, r, ns) {
        cgpa = 0.0;
    }

    void displayStudentInfo() {
        cout << "\n---------- STUDENT DETAILS ----------";
        Student::displayStudentInfo();
        cout << "-------------------------------------\n";
    }

    void calculateCGPA() {
        float totalCredits = 0, totalGradePoints = 0;

        for (int i = 0; i < numSubjects; i++) {
            float gradePoint;

            if (marks[i] >= 90)
                gradePoint = 10;
            else if (marks[i] >= 80)
                gradePoint = 9;
            else if (marks[i] >= 70)
                gradePoint = 8;
            else if (marks[i] >= 60)
                gradePoint = 7;
            else if (marks[i] >= 50)
                gradePoint = 6;
            else if (marks[i] >= 40)
                gradePoint = 5;
            else
                gradePoint = 0;

            totalGradePoints += gradePoint * credits[i];
            totalCredits += credits[i];
        }

        if (totalCredits != 0)
            cgpa = totalGradePoints / totalCredits;
        else
            cgpa = 0;
    }

    void displayResult() {
        cout << "\n---------- RESULT SUMMARY ----------";
        for (int i = 0; i < numSubjects; i++) {
            cout << "\nSubject " << i + 1
                 << " - Marks: " << marks[i]
                 << ", Credits: " << credits[i];
        }
        cout << "\n------------------------------------";
        cout << "\nYour CGPA is: " << cgpa;
        cout << "\nEquivalent Percentage: " << cgpa * 9.5 << "%";
        cout << "\n------------------------------------\n";
    }
};

// Main function
int main() {
    string name;
    int rollNo, subjects;

    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter roll number: ";
    while (!(cin >> rollNo)) {
        cout << "? Invalid input! Please enter a numeric roll number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer after roll number

    // ? Safe input for number of subjects
    while (true) {
        cout << "Enter number of subjects: ";
        if (cin >> subjects && subjects > 0 && subjects <= 10) {
            break;
        } else {
            cout << "d Please enter a valid number between 1 and 10.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Result student(name, rollNo, subjects);

    student.displayStudentInfo();
    student.inputMarks();
    student.calculateCGPA();
    student.displayResult();

    return 0;
}

