#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
using namespace std;

class GlobalUse {

    public :

    void printMenu() {
        cout << "***  File Object Manipulator  ***\n";
        cout << "* 0. QUIT                       *\n";
        cout << "* 1. COPY (Read & Save a file)  *\n";
        cout << "* 2. FILTER (Reduce a file)     *\n";
        cout << "* 3. MERGE (Join two files)     *\n";
        cout << "*********************************\n";
        cout << endl;
        return;
    } // printMenu()

}; // class GlobalUse

class HW2 {

    private : // core functions

    vector<string> sortingByTheCustomizedStandard(vector<string> fileLines) {
        ;
    } // sortingByTheCustomizedStandard()

    string convertToAllDigits(string str) { // "1,680"
        string result = {str[1], str[3], str[4], str[5]};
        return result;
    } // convertToAllDigits()

    bool isContainSpecial(string str) {
        bool result = false;
        for (int i = 0; i < str.length(); i++)
            if (str[i] == '\"' || str[i] == ',') result = true;
        return result;
    } // isContainSpecial()

    bool isAllDigit(string fileName) {
        bool check = false;
        for (int i = 0; i < fileName.length(); i++) {
            if ('0' < fileName[i] && fileName[i] < '9') check = true;
            else check = false;
        } // end for

        return check;
    } // isAllDigit()

    bool isInitialFileExist(string fileName) {
        if (isAllDigit(fileName)) { // ex. fileName = "201"
            fileName = "input" + fileName + ".txt";
        } // end if
        // else if "input204.txt" ...
        // else (totally wrong filename) ...

        ifstream f( fileName.c_str() );
        return f.good();
    } // isFileExist()

    bool isCopyedFileExist(string fileName) {
        if (isAllDigit(fileName)) { // ex. fileName = "201"
            fileName = "copy" + fileName + ".txt";
        } // end if
        // else if "copy204.txt" ...
        // else (totally wrong filename) ...

        ifstream f(fileName.c_str());
        return f.good();
    } // isFileExist()

    void mission1() { // read、copy and save
        GlobalUse PublicUse;
        string fileName = {'\0'}, fileLine = {'\0'};
        
        do {
            cout << "Input 201, 202, ...[0]Quit):" << endl;
            cin >> fileName;
            if (fileName == "0") break; // quit mission1
            else if (! isInitialFileExist(fileName)) cout << "### input" << fileName << ".txt does not exist ! ###\n" << endl;
            else {
                // Read into fileLines
                string openedfileName = "input" + fileName + ".txt"; // ex. "204" -> "input204.txt"
                ifstream openedFile(openedfileName.c_str()); // equal to : ifstream openedFileLine; openedFileLine.open(fileName);
                vector<string> fileLines; // to store fileLine's content
                while ( getline( openedFile, fileLine) ) fileLines.push_back(fileLine); // read from openedFile by line and store into fileLine, then store into fileLines
                openedFile.close();
                for (int i = 0; i < 3; i++) fileLines.erase(fileLines.begin()); // delete line 1 ~ 3
                cout << "Number of records = " << fileLines.size() << endl;

                // copy and store
                string copyedfileName = "copy" + fileName + ".txt"; // ex. "204" -> "copy204.txt"
                ofstream copyedFile(copyedfileName.c_str()); // create and open the new file which to store copyed lines
                for (int i = 0; i < fileLines.size(); i++) copyedFile << fileLines[i] << endl; // copy to the new file
                copyedFile.close();

                break;
            } // end else
        } while(! isInitialFileExist(fileName));

        cout << endl;
        return;
    } // mission1()

    void mission2() {
        int students = 0, graduates = 0;
        string fileName = {'\0'}, fileLine = {'\0'};
        do {
            cout << "Input 201, 202, ...[0]Quit):" << endl;
            cin >> fileName;
            if (fileName == "0") break; // quit mission2
            else if (! isCopyedFileExist(fileName)) cout << "### copy" << fileName << ".txt does not exist ! ###\n" << endl;
            else {
                // read how many students and graduates
                do {
                    cout << "Input the lower bound on the number of students: ";
                    cin >> students;
                } while (students < 0);

                do {
                    cout << "Input the lower bound on the number of graduates: ";
                    cin >> graduates;
                } while(graduates < 0);

                // read into fileLines
                string openedfileName = "copy" + fileName + ".txt"; // ex. "204" -> "copy204.txt"
                ifstream openedFile(openedfileName.c_str()); // equal to : ifstream openedFileLine; openedFileLine.open(fileName);
                vector<string> fileLines; // to store fileLine's content
                while (getline(openedFile, fileLine)) fileLines.push_back(fileLine); // read from openedFile by line and store into fileLine, then store into fileLines
                openedFile.close();

                // filtering
                bool deleted = false;
                int tempStudents = 0, tempGraduates = 0, count = 0;
                vector<string> splitedLine; // to store the splited line's content
                for (auto i = fileLines.begin(); i != fileLines.end(); i++) { // all lines
                    // reset so as to reuse
                    tempStudents = 0;
                    tempGraduates = 0;
                    count = 0;
                    fileLine = {'\0'};
                    splitedLine.erase(splitedLine.begin(), splitedLine.end());

                    // checking
                    stringstream ss(*i);
                    for (int j = 0; getline(ss, fileLine, '\t'); j++) splitedLine.push_back(fileLine); // store the line's content splited by '\t'
                    for (auto k = splitedLine.begin(); k != splitedLine.end(); k++) { // find two numbers
                        count++;
                        if (isContainSpecial(*k)) *k = convertToAllDigits(*k); // ex. change "1,680" to 1680
                        if (count == 7) tempStudents = stoi(*k); // students number
                        if (count == 9) tempGraduates = stoi(*k); // graduates number
                    } // end for

                    // comparing
                    vector<string>::iterator index = std::find(fileLines.begin(), fileLines.end(), *i);
                    if (tempStudents < students || tempGraduates < graduates) {
                        deleted = true;
                        fileLines.erase(index); // remove
                    } // end if

                    if (deleted) i--;
                    deleted = false;
                } // end for

                cout << "Number of records = " << fileLines.size() << endl;
                exit(0); // debug

                // overwriting
                ofstream overwritedFile;
                overwritedFile.open(openedfileName.c_str(), ofstream::out | ofstream::trunc); // clear
                for (auto k = fileLines.begin(); k != fileLines.end(); ++k) overwritedFile << *k << endl; // write in the new content
                overwritedFile.close();
                cout << "Number of records = " << fileLines.size() << endl;
                
            } // end else
        } while(! isCopyedFileExist(fileName));

        cout << endl;
        return;
    } // mission2()

    void mission3() {
        string fileName1 = {'\0'}, fileName2 = {'\0'};
        do {
            // fileName1
            cout << "Input 201, 202, ...[0]Quit):" << endl;
            cin >> fileName1;
            if (fileName1 == "0") break; // quit mission3
            else if (! isCopyedFileExist(fileName1)) {
                cout << "### copy" << fileName1 << ".txt does not exist ! ###\n" << endl;
                continue;
            } // end else if

            // fileName2
            cout << "Input 201, 202, ...[0]Quit):" << endl;
            cin >> fileName2;
            if (fileName2 == "0") break; // quit mission3
            else if (! isCopyedFileExist(fileName2)) {
                cout << "### copy" << fileName2 << ".txt does not exist ! ###\n" << endl;
                continue;
            } // end else if

            // both exist
            if (isCopyedFileExist(fileName1) && isCopyedFileExist(fileName2)) {
                string outputFileName = "output" + fileName1 + "_" + fileName2 + ".txt"; // ex. output204_205.txt
                fileName1 = "copy" + fileName1 + ".txt";
                fileName2 = "copy" + fileName2 + ".txt";
                ifstream file1(fileName1.c_str());
                ifstream file2(fileName2.c_str());
                ofstream combined_file(outputFileName.c_str());
                combined_file << file1.rdbuf() << file2.rdbuf();
                file1.close();
                file2.close();

                // read merged file's lines
                int lines = 0;
                string temp = {'\0'};
                ifstream mergedFile(outputFileName.c_str()); // mergedFile("\"" + outputFileName + "\"", ios::in); // only to read the file // "output204_205.txt"
                while (getline(mergedFile, temp)) lines++; // count line number
                cout << "Number of records = " << lines << endl;
                // sort
                vector<string> fileLines;
                string fileLine = {'\0'};
                while (getline(mergedFile, fileLine)) fileLines.push_back(fileLine);
                fileLines = sortingByTheCustomizedStandard(fileLines);
                mergedFile.close();

                break;
            } // end for
        } while(! isCopyedFileExist(fileName1) || ! isCopyedFileExist(fileName2));

        cout << endl;
        return;
    } // mission3()

    public : // caller

    void callMission1() {
        mission1();
        return;
    } // callMission1()

    void callMission2() {
        mission2();
        return;
    } // callMission2()

    void callMission3() {
        mission3();
        return;
    } // callMission3()

}; // class HW2

int main() {
    int missionNum = -1;
    char ch = '\0';
    GlobalUse PublicUse;
    HW2 chooseMission;
    
    do {
        PublicUse.printMenu();
        cout << "Input a choice(0, 1, 2, 3):";
        cin >> missionNum;
        if (missionNum < 0 || 3 < missionNum) {
            cout << "Command does not exist !\n" << endl;
            continue;
        } // end if

        switch (missionNum) {
            case 0:
                break;
            case 1:
                chooseMission.callMission1();
                break;
            case 2:
                chooseMission.callMission2();
                break;
            case 3:
                chooseMission.callMission3();
                break;
            default:
                break;
        } // end switch
    } while (missionNum != 0);
    
    system("pause");
    return 0;
} // main()