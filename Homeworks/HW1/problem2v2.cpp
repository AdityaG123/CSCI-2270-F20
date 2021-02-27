#include <iostream>
#include <fstream>
#include <string>
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

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length);

char calcLetter(double avg);

int main(int argc, char* argv[]){
    if(argc >= 5){
        char *infile_name = argv[1];
        char *outfile_name = argv[2];
        char lowBound = argv[3][0];
        char upBound = argv[4][0];
        
        ifstream fin(infile_name); 
        
        if(!fin.is_open()){
            cout<<"Unable to open file: "<<infile_name<<endl;
            return 1;
        }
        ofstream fout(outfile_name); 
        string line;
        string name, temp;
        int homework, quiz, recitation, exam;
        studentData students[10];
        int length = 0; 
        while((!fin.eof()) && (length < 10)){
            getline(fin,line); // read a line of data
            stringstream ss(line);
            getline(ss,name,',');
            getline(ss,temp,',');
            stringstream homeworkData;
            homeworkData << temp;
            homeworkData >> homework;
            
            getline(ss,temp,',');
            stringstream recitationData;
            recitationData << temp;
            recitationData >> recitation;
            
            getline(ss,temp,',');
            stringstream quizData;
            quizData << temp;
            quizData >> quiz;
            
            getline(ss,temp,',');
            stringstream examData;
            examData << temp;
            examData >> exam;
            
            addStudentData(students, name, homework, recitation, quiz, exam, length);
            length++; // increment the length
        }
        fin.close(); // close the input file
        printList(students, length);
        char grade;
        for(int i=0;i<length;i++){
            grade = calcLetter(students[i].average);
            if(grade >= lowBound && grade <= upBound){
                fout<<students[i].studentName<<", "<<students[i].average<<", "<<grade<<endl;

            }
        }
        fout.close(); // close the output file
    }
    else{
        cout<<"USAGE: <input_file> <output_file> <lower_bound> <upper_bound>"<<endl;
    } // command line arguments < 5
return 0;
}

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length){
    students[length].studentName = studentName;
    students[length].homework = homework;
    students[length].recitation = recitation;
    students[length].quiz = quiz;
    students[length].exam = exam;
    students[length].average = ((homework+recitation+exam+quiz))/(double)4;
}

char calcLetter(double avg){
    if(avg >= 90)
    {
        return 'A';
    }
    else if(avg >= 80){
        return 'B';
    }
    else if(avg >= 70){
        return 'C';
    }
    else if(avg >= 60){
        return 'D';
    }
    else{
        return 'F';
    }
}

void printList(const studentData students[], int length){
    for(int i=0;i<length-1;i++){
        cout<<students[i].studentName<<" earned "<<students[i].average<<" which is an "<<calcLetter(students[i].average)<<endl;
    }
}