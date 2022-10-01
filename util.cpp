#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <cstring>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    rawWords = convToLower(rawWords);
    std::set <string> wordCollection;
    int rawSize = rawWords.length();
    int start=0;
    int finish=0;
    while(finish < rawSize)
    {
        for(int i=0; i<rawSize; i++)
        {
            char curr = rawWords[i];
            if(isalpha(curr))
            {
                finish++;
                if(finish==rawSize && finish-start>=2)
                {
                    string finalString = rawWords.substr(start, finish-start);
                    wordCollection.insert(finalString);
                }
            }
            else if(!isalpha(curr))
            {
                if(finish-start>=2)
                {
                    string currString = rawWords.substr(start, finish-start);
                    wordCollection.insert(currString);
                }
                start = finish + 1;
                finish = start;
            }
        }
    }

    return wordCollection;

}

/*int main()
{
    std::string basicABC = "Men's";
    std::set<string> parsedString = parseStringToWords(basicABC);
    for(std::set<string>::iterator it=parsedString.begin(); it!=parsedString.end(); ++it)
    {
        cout<< *it <<endl;
    }
    std::string basicABC = "hey what's go'ing on co'ol beans";
    std::set<string> parsedString = parseStringToWords(basicABC);
    for(std::set<string>::iterator it=parsedString.begin(); it!=parsedString.end(); ++it)
    {
        cout<< *it <<endl;
    }

    std::set<string> setOne;
    setOne.insert("ee109");
    setOne.insert("math226");
    setOne.insert("arlt100");
    setOne.insert("csci104");

    std::set<string> setTwo;
    setTwo.insert("ee109");
    setTwo.insert("writ140");
    setTwo.insert("csci170");
    setTwo.insert("csci104");


    std::set<string> unionSet = setUnion(setOne, setTwo);
    for(std::set<string>::iterator it=unionSet.begin(); it!=unionSet.end(); ++it)
    {
        cout<< *it <<endl;
    }

    std::set<string> intersectionSet = setIntersection(setOne, setTwo);
    for(std::set<string>::iterator it=intersectionSet.begin(); it!=intersectionSet.end(); ++it)
    {
        cout<< *it <<endl;
    }

    
}*/



/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
