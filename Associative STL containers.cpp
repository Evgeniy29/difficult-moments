#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <unordered_map>

using namespace std;

template<typename iter>

void printWords(iter it, iter end)
{
    unordered_set<std::string> countWords(it, end);
    copy(countWords.begin(), countWords.end(), ostream_iterator<std::string>(cout, ", "));
}

int main()
{
    vector<string> v{ "one", "two", "three", "six", "one", "six", "five", "two", "two", "one", "seven", "nine" };
    cout << "output vector:" << "\n";
    printWords(v.begin(), v.end());

    list<string> l(v.begin(), v.end());
    cout << "\noutput list:" << "\n";
    printWords(l.begin(), l.end());

    deque<std::string> d(v.begin(), v.end());
    cout << "\noutput deque:" << "\n";
    printWords(d.begin(), d.end());
    cout << "\n";

    //----------------------------------------
       
    unordered_map<int, string> sentences;
    string punctuation_marks;
    size_t gap = 0;
    string temp;
    getline(cin, punctuation_marks);

    while ((gap = punctuation_marks.find(".")) != string::npos)
    {
        temp = punctuation_marks.substr(0, gap);
        punctuation_marks.erase(0, gap + 1 );
        sentences.insert({ temp.length(), temp });
    }

    for_each(sentences.begin(), sentences.end(),[](pair<int, string> item) 
        {
            cout << item.first << " " << item.second << "\n";
        }
    );
      
}



