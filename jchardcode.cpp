#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include<cstring>

using namespace std;

void nextStep (string MBTI){

    string acceptedLine;
    ifstream file("jcalg hardcode.txt");   
    string line;
    string nextStepString;
    string returnLine;
    bool infinite = true;

    while(infinite){

        if(MBTI.length() < 17) {
            while(getline(file, line)) {
                if(line.find(MBTI, 0) != string::npos && line.find(MBTI, 0) < 2){
                    returnLine = line;
                    cout << line << endl;
                    break;
                }
            }
            if(returnLine=="") {
                cout << "MBTI type does not exist. Please try again" << endl;
                getline(cin, nextStepString);
                nextStep(nextStepString);
            }
            else {
                nextStep(returnLine);
            }
        }   
    

        if(MBTI.length() > 17){
            cout << "Enter your next chart" << endl;
            getline(cin, nextStepString);
            if(nextStepString == "display current chart") {
                cout << MBTI << endl;
                nextStep(MBTI);
            }
        
            if(MBTI.find(nextStepString, 0)!=string::npos){
                while(getline(file, line)) {
                    if(line.find(nextStepString, 0) != string::npos && line.find(nextStepString, 0) < 2){
                        cout << line << endl;
                        MBTI = line;
                        break;
                    }
                }
                nextStep(MBTI);
            }
            else {
                cout << "Choice is not within the current chart. Please select from the current chart" << endl;
                nextStep(MBTI);
            }    
        }

        if(MBTI=="Quit"){
            infinite = false;
        }
    }
}

int main () {

    string signMBTI;
    string withinChart;
    string fullLine;

    cout << "Input MBTI and astrological sign. MBTI type than astrological sign." << endl;
    getline(cin, signMBTI);
    nextStep(signMBTI);


    return 0;
}