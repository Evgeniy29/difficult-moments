#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Timer.h"

using namespace std;


void Swap(int* a, int* b)
{
    Timer timer("Swap program execution time");
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    timer.print();
}

void SortPointers(vector<int*> & v)
{
    Timer timer("SortPointers program execution time");
    sort(v.begin(), v.end(), [](const auto& v1, const auto& v2)
            {
                return *v1 < *v2;
            }
       
        );
    timer.print();
}

const string_view vowels { "аеёиоуыэюяАЕЁИОУЫЭЮЯ" };

void metod_1(const string_view  &s)
{
    Timer timer("Metod_1  count_if and find");
    size_t count = count_if(s.begin(), s.end(), [&](const auto& c)
        {
            return vowels.find(c) != string::npos;
        });
    cout  << count<<" vowels   -     " ;
    timer.print();
}

void metod_2(const string_view& s)
{
    Timer timer("Metod_2  count_if and for ");
    size_t count = count_if(s.begin(), s.end(), [&](const auto& c)
        {
            for(int i=0;i<vowels.size();i++)
            {
                if (vowels[i] == c)
                    return true;
            }
            return false;
        });
    cout << count << " vowels   -     ";
    timer.print();
}

void metod_3(const string_view& s)
{
    Timer timer("Metod_3  for and find     ");
    size_t count = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                if (vowels.find(s[i]) != string::npos)
                {
                    count++;
                }
                    
            }
    cout << count << " vowels   -     ";
    timer.print();
}

void metod_4(const string_view& s)
{
    Timer timer("Metod_4  for and find     ");
    size_t count = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        for (size_t j=0; j< vowels.size();j++)
        {
            if (s[i] == vowels[j])
            count++;
        }

    }
    cout << count << " vowels   -     ";
    timer.print();
}

int main()
{
    //1
    int x = 0;
    int y = 1;
    Swap(&x,&y);
    cout << x << " " << y<<endl;
    cout << endl;
    cout << "------------------------------------------------" << endl;
    
    //2
    int L = 10;
    vector<int*> v;
    for (int i = 0; i < L; ++i)
    {
        int* a = new int;
        *a = rand() %100 ;
        v.push_back(a);
    }
    cout << "Random vector:";
    for (int i = 0; i < L; ++i)
    {
        cout << *v[i] << ' ';
    }

    cout << endl<<endl;

    SortPointers(v);
    cout << "Sort vector:" ;
    for (int i = 0; i < L; ++i)
    {
        
        cout  << *v[i] << ' ';
    }
    cout << endl;
    cout <<"-------------------------------------------------------" << endl;
    //3

    ifstream file("C:\\War and peace.txt");
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0);
    string s(size, ' ');
    file.read(&s[0], size);

    metod_1(s);
    metod_2(s);
    metod_3(s);
    metod_4(s);
}

