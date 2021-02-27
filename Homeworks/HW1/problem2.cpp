#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct studentData{
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length){
    studentData newStudent;
    newStudent.studentName = studentName;
    newStudent.homework = homework;
    newStudent.recitation = recitation;
    newStudent.quiz = quiz;
    newStudent.exam = exam;
    newStudent.average = (homework + recitation + quiz + exam)/(double)4;
    students[length] = newStudent;
}

char calcLetter(double avg){
    if(avg>90){
        return 'A';
    }
    else if(avg>80 && avg<89.9){
        return 'B';
    }
    else if(avg>70 && avg<79.9){
        return 'C';
    }
    else if(avg>60 && avg<69.9){
        return 'D';
    }
    else if (avg<60){
        return 'F';
    }
    return avg;
}

double upperBound(string arg){
    string grade = arg;
    if(grade == "A"){
        return 100;
    }
    else if(grade == "B"){
        return 89.9;
    }
    else if(grade == "C"){
        return 79.9;
    }
    else if(grade == "D"){
        return 69.9;
    }
    else if (grade == "F"){
        return 59.9;
    }
}

double lowerBound(string arg2){
    string grade = arg2;
    if(grade == "A"){
        return 90;
    }
    else if(grade == "B"){
        return 80;
    }
    else if(grade == "C"){
        return 70;
    }
    else if(grade == "D"){
        return 60;
    }
    else if (grade == "F"){
        return 0;
    }
}

void printList(const studentData students[], int length){
    int i;
    for(i = 0; i < length; i++){
        std::cout << students[i].studentName << " earned " << students[i].average << " which is an " << calcLetter(students[i].average) << std::endl;
    }
}

int main(int argc, char *argv[]){
    studentData student[10];
    int i = 0;
    
    ifstream inFile;
    inFile.open(argv[1]);
    
    string name;
    string quiz;
    string exam;
    string recitation;
    string homework;
    string tempString;
    
    while(getline(inFile, tempString)){
        stringstream string(tempString);
        getline(string, name, ',');
        getline(string, homework, ',');
        getline(string, recitation, ',');
        getline(string, quiz, ',');
        getline(string, exam, ',');
        addStudentData(student, name, stoi(homework), stoi(recitation), stoi(quiz), stoi(exam), i);
        i++;
    }

    ofstream outFile;
    outFile.open(argv[2]);

    printList(student, i);
    string arg = argv[3];
    string arg2 = argv[4];
    
    for(int j = 0; j<10; j++){
        if(student[j].average >= lowerBound(arg) && student[j].average <= upperBound(arg2)){
            outFile << student[j].studentName << "," << student[j].average << "," << calcLetter(student[j].average) << endl;
        }
    }
    inFile.close();
    outFile.close();

}