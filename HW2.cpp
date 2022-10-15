// 11020107、11020140
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
        cout << "* 4. MERGE (Join M files)       *\n";
        cout << "*********************************\n";
        cout << endl;
        return;
    } // printMenu()

}; // class GlobalUse

class HW2 {

    /*************************sub functions and variables*************************/

    private :

    // for mission 1 ~ 3

    bool isFileExist(string fileName, int missionNum) {
        if (isAllDigit(fileName)) { // ex. fileName = "201"
            if (missionNum == 1) fileName = "input" + fileName + ".txt";
            else if (missionNum == 2 || missionNum == 3 || missionNum == 4) fileName = "copy" + fileName + ".txt";
        } // end if
        // else if "input204.txt" ...
        // else (totally wrong filename) ...

        ifstream ifFileExist( fileName.c_str() );
        return ifFileExist.good();
    } // isFileExist()

    // for mission 2

    bool isAllDigit(string fileName) {
        bool check = false;
        for (int i = 0; i < fileName.length(); i++) {
            if ('0' < fileName[i] && fileName[i] < '9') check = true;
            else check = false;
        } // end for

        return check;
    } // isAllDigit()

    bool isContainSpecial(string str) {
        bool result = false;
        for (int i = 0; i < str.length(); i++)
            if (str[i] == '\"' || str[i] == ',') result = true;
        return result;
    } // isContainSpecial()

    string convertToAllNumberDigits(string str) { // "1,680"
        string result = {str[1], str[3], str[4], str[5]};
        return result;
    } // convertToAllDigits()

    // for mission 3

    vector<string> file1Data, file2Data;

    vector<int> SchoolAndDepartment(string str) { // store the school number and the department number into vector and return
        vector<int> toReturn;
        string tempStr = "";
        char ch = '\0';
        int i = 0;
        for (i = 0; str[i] != '\t'; i++) tempStr = tempStr + str[i]; // read in school number(digit)
        toReturn.push_back(stoi(tempStr)); // string to int, store school number into toReturn(int)
        for (i++; str[i] != '\t'; i++) ch = str[i]; // read garbage
        tempStr = "";
        for (i++; str[i] != '\t'; i++) tempStr = tempStr + str[i]; // read in department number
        toReturn.push_back(stoi(tempStr)); // string to int, store department number into toReturn(int)
        return toReturn;
    } // SchoolAndDepartment()

    // exist error
    void sortingByCustomizedRules(string file1line, string file2line, vector<int> fileNums1, vector<int> fileNums2, vector<string>::iterator &index) {
        if (index > file1Data.end()) {
            cout << "DEBUG" << endl;
            exit(0);
        } // end if

        if (find(file1Data.begin(), file1Data.end(), file2line) == file1Data.end()) file1Data.push_back(file2line); // if file2line doesn't exist in file1Data
        else if (fileNums2[0] < fileNums1[0]) file1Data.insert(index, file2line); // school2 number < school1 number, insert before the now index
        else if (fileNums1[0] == fileNums2[0]) { // same school
            if (fileNums2[1] < fileNums1[1]) file1Data.insert(index, file2line); // department2 number < department1 number, insert before the now index
            else {
                index++;
                file1Data.insert(index, file2line); // no matter same or bigger, just insert after the now index
            } // end else
        } // end else if
        else {
            // debug
            // cout << *(index) << endl;
            for (int a = 0; a < 10; a++) cout << file1Data[a] << endl;
            exit(0);

            // update every variables' data about file1 line[i] to file1 line[i+1]
            index++;
            fileNums1 = SchoolAndDepartment(*(index)); // file1 line[i+1]'s two numbers
            sortingByCustomizedRules(*(index), file2line, fileNums1, fileNums2, index); // compare file2line's numbers with file1 line[i+1]'s numbers
        } // end else
        return;
    } // sortingByCustomizedRules()

    /*************************mission 1 ~ 3*************************/

    void mission1() { // read、copy and save
        string fileName = "", fileLine = "";
        do {
            cout << "Input 201, 202, ...[0]Quit): " << endl;
            cin >> fileName;
            if (fileName == "0") break; // quit mission1
            else if (! isFileExist(fileName, 1)) cout << "### input" << fileName << ".txt does not exist ! ###\n" << endl;
            else {
                // Read into fileLines
                string openedfileName = "input" + fileName + ".txt"; // ex. "204" -> "input204.txt"
                ifstream openedFile(openedfileName.c_str()); // equal to : ifstream openedFileLine; openedFileLine.open(fileName);
                vector<string> fileLines; // to store fileLine's content
                while (getline(openedFile, fileLine)) fileLines.push_back(fileLine); // read from openedFile by line and store into fileLine, then store into fileLines
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
        } while(! isFileExist(fileName, 1));

        cout << endl;
        return;
    } // mission1()

    void mission2() {
        int students = 0, graduates = 0;
        string fileName = "", fileLine = "";
        do {
            cout << "Input 201, 202, ...[0]Quit): " << endl;
            cin >> fileName;
            if (fileName == "0") break; // quit mission2
            else if (! isFileExist(fileName, 2)) cout << "### copy" << fileName << ".txt does not exist ! ###\n" << endl;
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
                    fileLine = "";
                    splitedLine.erase(splitedLine.begin(), splitedLine.end());

                    // checking
                    stringstream ss(*i);
                    for (int j = 0; getline(ss, fileLine, '\t'); j++) splitedLine.push_back(fileLine); // store the line's content splited by '\t'
                    for (auto k = splitedLine.begin(); k != splitedLine.end(); k++) { // find two numbers
                        count++;
                        if (isContainSpecial(*k)) *k = convertToAllNumberDigits(*k); // ex. change "1,680" to 1680
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
                overwritedFile.open(openedfileName.c_str(), ofstream::out | ofstream::trunc); // clear the previous content
                for (auto k = fileLines.begin(); k != fileLines.end(); ++k) overwritedFile << *k << endl; // write in the new content
                overwritedFile.close();
                cout << "Number of records = " << fileLines.size() << endl;
                
            } // end else
        } while(! isFileExist(fileName, 2));

        cout << endl;
        return;
    } // mission2()

    void mission3() {
        string fileName1 = "", fileName2 = "";
        do {
            // fileName1
            cout << "Input 201, 202, ...[0]Quit): ";
            cin >> fileName1;
            if (fileName1 == "0") break; // quit mission3
            else if (! isFileExist(fileName1, 3)) {
                cout << "### copy" << fileName1 << ".txt does not exist ! ###\n" << endl;
                continue;
            } // end else if

            // fileName2
            cout << "Input 201, 202, ...[0]Quit): ";
            cin >> fileName2;
            if (fileName2 == "0") break; // quit mission3
            else if (! isFileExist(fileName2, 3)) {
                cout << "### copy" << fileName2 << ".txt does not exist ! ###\n" << endl;
                continue;
            } // end else if

            // both exist
            if (isFileExist(fileName1, 3) && isFileExist(fileName2, 3)) {
                // naming
                string outputFileName = "output" + fileName1 + "_" + fileName2 + ".txt"; // ex. output204_205.txt
                fileName1 = "copy" + fileName1 + ".txt";
                fileName2 = "copy" + fileName2 + ".txt";
                ifstream file1(fileName1.c_str());
                ifstream file2(fileName2.c_str());

                // store files' content into vector
                string tempStr = "";
                while (getline(file1, tempStr)) file1Data.push_back(tempStr);
                file1.close();
                tempStr = ""; // reset so as to reuse
                while (getline(file2, tempStr)) file2Data.push_back(tempStr);
                file2.close();

                // merging
                /*
                file1Data will be inserted in file2Data's lines, so file1Data is changeable;
                file2Data is the content to insert in file1Data, so file2Data is unchangeable.
                The final result will be file1Data(inserted with all file2Data's content).
                */
                vector<int> fileNums1, fileNums2; // seperately store school number and department number of file1 and file2
                vector<string>::iterator index = find(file1Data.begin(), file1Data.end(), file1Data[0]); // the first line's index of file1
                for (int i = 0; i < file2Data.size(); i++) {
                    fileNums1 = SchoolAndDepartment(file1Data[0]); // initially set the first line's two numbers of file1Data, then the line's may index + 1 recursively
                    fileNums2 = SchoolAndDepartment(file2Data[i]); // the line[i]'s two number of file2Data
                    sortingByCustomizedRules(file1Data[0], file2Data[i], fileNums1, fileNums2, index);
                } // end for

                vector<string> temp = file1Data;

                // debug
                // for (int i = 0; i < temp.size(); i++) cout << temp[i] << endl;
                // exit(0);

                // store in the new file
                ofstream combined_file(outputFileName.c_str());
                int lines = 0;
                for (lines = 0; lines < temp.size(); lines++) combined_file << temp[lines] << endl;
                cout << "Number of records = " << lines << endl;
                combined_file.close();

                break;
            } // end for
        } while(! isFileExist(fileName1, 3) || ! isFileExist(fileName2, 3));

        cout << endl;
        return;
    } // mission3()

    void mission4() {
        int fileNums = 0;
        string fileName1 = "", fileNameM = "", tempStr = "";
        vector<vector<string>> files;
        do {
            // fileName1, the very first file
            cout << "Input 201, 202, ...[0]Quit): ";
            cin >> fileName1;
            if (fileName1 == "0") break; // quit mission3
            else if (! isFileExist(fileName1, 4)) {
                cout << "### copy" << fileName1 << ".txt does not exist ! ###\n" << endl;
                continue;
            } // end else if

            do {
                // fileNameM, the following files
                cout << "Input the number of files to be merged: ";
                cin >> fileNums;
                if (fileNums < 0) continue; // negative
                else if (fileNums == 0) {
                    cout << "File(s) that wil be merged can't be zero !\nPlease input a correct number." << endl;
                    continue;
                } // end else if
                else {
                    int count = 0;
                    int x = 0;
                    vector<string> tempV; // to store fileM's lines
                    do {
                        cout << "do-while run " << x << " times." << endl; // debug
                        // cout << "count is " << count << endl; // debug
                        cout << "Input 201, 202, ...[0]Quit): ";
                        cin >> fileNameM;
                        if (fileNameM == "0") break; // quit mission4
                        else if (! isFileExist(fileNameM, 4)) {
                            cout << "### copy" << fileNameM << ".txt does not exist ! ###\n" << endl;
                            continue;
                        } // end else if
                        else {
                            // store fileM's lines into vector tempV
                            fileNameM = "copy" + fileNameM + ".txt";
                            ifstream fileM(fileNameM.c_str());
                            if (count == 0 && fileM.good()) cout << "file1 good" << endl; // debug
                            if (count == 1 && fileM.good()) cout << "file2 good" << endl; // debug
                            while (getline(fileM, tempStr)) tempV.push_back(tempStr);
                            fileM.close();
                            // store all fileM's data into vector files
                            files.push_back(tempV);
                            if (count == 1) cout << files[1][tempV.size() - 1] << endl; // debug
                            // reset
                            tempV.clear();
                            fileNameM = "";
                            tempStr = "";
                            count++;
                        } // end else
                        x++;
                    } while (count <= fileNums);
                } // end else

                // merge files
                exit(0);
            } while(fileNums < 0);

            break;
        } while(! isFileExist(fileName1, 4) || ! isFileExist(fileNameM, 4));
    } // mission4()

    /*************************callers*************************/

    public :

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

    void callMission4() {
        mission4();
        return;
    } // callMission4()

}; // class HW2

int main() {
    int missionNum = -1;
    char ch = '\0';
    GlobalUse PublicUse;
    HW2 chooseMission;
    
    do {
        PublicUse.printMenu();
        cout << "Input a choice(0, 1, 2, 3, 4): ";
        cin >> missionNum;
        if (missionNum < 0 || 4 < missionNum) {
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
            case 4:
                chooseMission.callMission4();
                break;
            default:
                break;
        } // end switch
    } while (missionNum != 0);
    
    system("pause");
    return 0;
} // main()