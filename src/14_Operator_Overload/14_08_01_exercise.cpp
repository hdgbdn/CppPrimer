#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// 14.38
class WordCount{
public:
    void operator()(const string& input){
        stringstream ss(input);
        string s;
        while(ss >> s){
            size_t sz = s.size();
            ++lengthCount[sz];
        }
    }
    void Print(){
        for(auto m: lengthCount){
            cout << "length is " << m.first << " count is " << m.second << endl;
        }
    }
private:
    map<size_t, size_t> lengthCount;
};

// 14.38
class WordCountRange{
public:
    WordCountRange(): low(), high(), baseline() {}
    void operator()(const string& input, size_t sz){
        baseline = sz;
        stringstream ss(input);
        string s;
        while(ss >> s){
            if(s.size() > baseline) high++;
            else low++;
        }
    }
    void Print(){
        cout << "base line is " << baseline << " > baseline count is " << high << " <= baseline count is " << low << endl;
    }
private:
    size_t low;
    size_t high;
    size_t baseline;
};

// 14.40
void biggise(vector<string> &words, vector<string>::size_type sz){

}

int main()
{
    string s = "Input stream class to operate on strings.Objects of this class use a string buffer that contains a sequence of characters. This sequence of characters can be accessed directly as a basic_string object, using member str.The characters in the sequence can be extracted from the stream using any operation allowed on input streams.Apart from the internal string buffer, objects of these classes keep a set of internal fields inherited from ios_base, basic_ios and basic_istream:";
    
    // 14.38
    WordCount wc;
    wc(s);
    wc.Print();

    // 14.39
    WordCountRange wcr;
    wcr(s, 9);
    wcr.Print();

    // 14.40


    // 14.41
    // lambda is like a syntactic sugar, can save a lot time for defining class or functions

    return 0;
}