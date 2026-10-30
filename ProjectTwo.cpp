/*
 * ProjectTwo.cpp
 * CS 300 Project Two
 * Author: Matt Dickinson
 *
 * This program loads course information from a CSV file into a
 * binary search tree. It allows users to print an alphanumeric
 * course list and search for an individual course.
 *
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Stores the information for one course.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Removes whitespace from the beginning and end of a string.
string trim(const string& text) {
    size_t first = text.find_first_not_of(" \t\r\n");

    if (first == string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

// Returns an uppercase copy of a string.
string toUpper(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char character) {
            return static_cast<char>(toupper(character));
        });

    return text;
}

// Represents one node in the binary search tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(const Course& courseData) {
        course = courseData;
        left = nullptr;
        right = nullptr;
    }
};

// Stores the courses in a binary search tree.
class BinarySearchTree {
private:
    Node* root;

    bool insertNode(Node*& currentNode, const Course& course) {
        if (currentNode == nullptr) {
            currentNode = new Node(course);
            return true;
        }

        if (course.courseNumber < currentNode->course.courseNumber) {
            return insertNode(currentNode->left, course);
        }

        if (course.courseNumber > currentNode->course.courseNumber) {
            return insertNode(currentNode->right, course);
        }

        return false;
    }

    void printInOrder(Node* currentNode) const {
        if (currentNode == nullptr) {
            return;
        }

        printInOrder(currentNode->left);

        cout << currentNode->course.courseNumber << ", "
             << currentNode->course.courseTitle << endl;

        printInOrder(currentNode->right);
    }

    void destroyTree(Node* currentNode) {
        if (currentNode != nullptr) {
            destroyTree(currentNode->left);
            destroyTree(currentNode->right);
            delete currentNode;
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }

    bool insert(const Course& course) {
        return insertNode(root, course);
    }

    const Course* search(const string& courseNumber) const {
        Node* currentNode = root;

        while (currentNode != nullptr) {
            if (courseNumber == currentNode->course.courseNumber) {
                return &currentNode->course;
            }

            if (courseNumber < currentNode->course.courseNumber) {
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }
        }

        return nullptr;
    }

    void printCourseList() const {
        cout << "Here is a sample schedule:" << endl;
        cout << endl;

        printInOrder(root);
    }
// Prints one course and its prerequisites.
void printCourseInformation(const string& requestedCourseNumber) const {
    string courseNumber = toUpper(trim(requestedCourseNumber));
    const Course* selectedCourse = search(courseNumber);

    if (selectedCourse == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << selectedCourse->courseNumber << ", "
         << selectedCourse->courseTitle << endl;

    cout << "Prerequisites: ";

    if (selectedCourse->prerequisites.empty()) {
        cout << "None";
    }
    else {
        for (size_t index = 0;
             index < selectedCourse->prerequisites.size();
             index++) {

            cout << selectedCourse->prerequisites[index];

            if (index < selectedCourse->prerequisites.size() - 1) {
                cout << ", ";
            }
        }
    }

    cout << endl;
}
    void clear() {
        destroyTree(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

// Reads course information from a CSV file.
bool loadCourseFile(const string& fileName, BinarySearchTree& courseTree) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open " << fileName << "." << endl;
        return false;
    }

    vector<Course> parsedCourses;
    string line;

    while (getline(inputFile, line)) {
        if (trim(line).empty()) {
            continue;
        }

        vector<string> fields;
        string field;
        stringstream lineStream(line);

        while (getline(lineStream, field, ',')) {
            fields.push_back(trim(field));
        }

        if (fields.size() < 2 ||
            fields[0].empty() ||
            fields[1].empty()) {
            cout << "Error: Invalid course data: " << line << endl;
            return false;
        }

        Course course;
        course.courseNumber = toUpper(fields[0]);
        course.courseTitle = fields[1];

        // Reject duplicate course numbers.
        for (const Course& existingCourse : parsedCourses) {
            if (existingCourse.courseNumber == course.courseNumber) {
                cout << "Error: Duplicate course number "
                     << course.courseNumber << "." << endl;
                return false;
            }
        }

        // Add every nonempty prerequisite after the title.
        for (size_t index = 2; index < fields.size(); index++) {
            if (!fields[index].empty()) {
                course.prerequisites.push_back(toUpper(fields[index]));
            }
        }

        parsedCourses.push_back(course);
    }

    inputFile.close();

    if (parsedCourses.empty()) {
        cout << "Error: The course file is empty." << endl;
        return false;
    }

    // Confirm that every prerequisite exists in the file.
    for (const Course& course : parsedCourses) {
        for (const string& prerequisite : course.prerequisites) {
            bool prerequisiteFound = false;

            for (const Course& possibleCourse : parsedCourses) {
                if (possibleCourse.courseNumber == prerequisite) {
                    prerequisiteFound = true;
                    break;
                }
            }

            if (!prerequisiteFound) {
                cout << "Error: Prerequisite " << prerequisite
                     << " does not exist in the course file." << endl;
                return false;
            }
        }
    }

    // Replace previously loaded information only after validation succeeds.
    courseTree.clear();

    for (const Course& course : parsedCourses) {
        courseTree.insert(course);
    }

    return true;
}

int main() {
    BinarySearchTree courseTree;
    bool dataLoaded = false;
    bool running = true;

    cout << "Welcome to the course planner." << endl;

    while (running) {
        cout << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        string choiceInput;
        getline(cin, choiceInput);

        int choice;
        char extraCharacter;
        stringstream choiceStream(choiceInput);

        // Reject input that is not one complete integer.
        if (!(choiceStream >> choice) ||
            (choiceStream >> extraCharacter)) {
            cout << choiceInput << " is not a valid option." << endl;
            continue;
        }

        if (choice == 1) {
            string fileName;

            cout << "Enter the name of the course data file: ";
            getline(cin, fileName);

            if (loadCourseFile(fileName, courseTree)) {
                dataLoaded = true;
                cout << "Course data loaded successfully." << endl;
            }
            else {
                dataLoaded = !courseTree.isEmpty();
                cout << "No new course data was loaded." << endl;
            }
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Load course data before printing." << endl;
            }
            else {
                cout << endl;
                courseTree.printCourseList();
            }
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Load course data before searching." << endl;
            }
            else {
                string courseNumber;

                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);

                courseTree.printCourseInformation(courseNumber);
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            running = false;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}