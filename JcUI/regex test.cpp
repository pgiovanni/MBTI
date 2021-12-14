#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

int main() {
std::string returnLine;
std::vector<std::string> MBTIbroken;
std::string MBTIstring;
std::regex r(" *(\\w+ \\w+)"); // entire match will be 2 numbers
std::smatch m;
std::string line;
std::cout << "input MBTI type" << std::endl;
getline(std::cin, MBTIstring);

  std::ifstream file("jcalg hardcode.txt");

    if(MBTIstring.length() < 17) {

        while(getline(file, line)) {
         if(line.find(MBTIstring, 0) != std::string::npos && line.find(MBTIstring, 0) < 2) {
           returnLine = line;
           break;
         }
       }
    }

  auto flag = std::regex_constants::match_continuous;
  while(std::regex_search(returnLine, m, r, flag)) {
    MBTIbroken.push_back(m[1]);
    returnLine = m.suffix().str();
  }



  int i = 0;
  std::cout << "Vector Contents:" << std::endl;
  for(auto s : MBTIbroken) {
    std::cout << (++i) << ") " << s << std::endl;
  }
}