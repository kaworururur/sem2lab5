#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>

class Student {
public:
    std::string name;
    std::string group;
    int id;
    double grades[4];

    Student() {};

    Student(std::string n, std::string g, int i, double g1, double g2, double g3, double g4) : name(n), group(g), id(i) {
        grades[0] = g1;
        grades[1] = g2;
        grades[2] = g3;
        grades[3] = g4;
    }
    //кентик
    friend std::ostream& operator<<(std::ostream& out, const Student& student) {
        out << "Name: " << student.name << "\nGroup: " << student.group << "\nID: " << student.id << "\nGrades: ";
        for (double grade : student.grades) {
            out << grade << " ";
        }
        out << "\n";
        return out;
    }

    double getAverageGrade() const {
        double sum = 0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / 4.0;
    }

    struct Hash {
        size_t operator()(const Student& student) const {
            return std::hash<std::string>()(student.name);
        }
    };

    bool operator==(const Student& other) const {
        return name == other.name;
    }

    bool operator<(const Student& other) const {
        return getAverageGrade() < other.getAverageGrade();
    }
};

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::vector<Student> students;
    std::list<Student> studentsList;
    std::unordered_set<Student, Student::Hash> studentsUnorderedSet;
    std::set<Student> studentsSet;

    std::string name, group;
    int id;
    double g1, g2, g3, g4;

    while (input >> name >> group >> id >> g1 >> g2 >> g3 >> g4) {
        Student student(name, group, id, g1, g2, g3, g4);
        students.push_back(student);
        studentsList.push_back(student);
        studentsSet.insert(student);
        studentsUnorderedSet.insert(student);
    }

    output << "Original Vector:\n";
    for (const Student& student : students) {
        output << student;
    }

    output << "\nOriginal List:\n";
    for (const Student& student : studentsList) {
        output << student;
    }

    output << "\nOriginal Set:\n";
    for (const Student& student : studentsSet) {
        output << student;
    }

    output << "\nOriginal Unordered Set:\n";
    for (const Student& student : studentsUnorderedSet) {
        output << student;
    }

    std::vector<Student> copiedStudents(students.size());
    std::copy(students.begin(), students.end(), copiedStudents.begin());

    std::sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
        return s1.getAverageGrade() < s2.getAverageGrade();
        });

    output << "\nSorted Vector:\n";
    for (const Student& student : students) {
        output << student;
    }

    output << "\nCopied Vector:\n";
    for (const Student& student : copiedStudents) {
        output << student;
    }

    return 0;
}