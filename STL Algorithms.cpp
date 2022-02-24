

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <random>
#include <algorithm>

using namespace std;

template<template<typename, typename> class TContainer, typename TItem, typename TIterator, typename T>
void generator(TContainer<TItem, TIterator>& c, const T& range_start, const T& range_end)
{
    random_device rd;
    mt19937 mersenne(rd());
    uniform_real_distribution<double> urd(range_start, range_end);
    generate(c.begin(), c.end(), [&]()
        {
            return urd(mersenne);
        });
}

template<template<typename, typename> class TContainer, typename TItem, typename TIterator>
void print(const TContainer<TItem, TIterator>& c)
{
    copy(c.begin(), c.end(), ostream_iterator<TItem> { cout, "  " });
    cout << endl;
}

template<template<typename, typename> class TContainer, typename TItem, typename TIterator>
void insert_sorted(TContainer<TItem, TIterator>& c, const TItem& i)
{
    typename TContainer<TItem, TIterator>::iterator it = find_if(c.begin(), c.end(), [&](const TItem& current)
    {
            return current >= i;
    });
    c.insert(it, i);
  
}
int main()
{
    /*1*/
    const unsigned int size = 10;
    int new_int_value = 5;
    double new_double_value = 2.5;
    string new_string_value = "john";

    vector<int> v(size);

    generator(v, 0,20);
    sort(v.begin(), v.end());
    print(v);                             
    insert_sorted(v, new_int_value);
    print(v);                             
    

    list<double> v2(size);

    generator(v2, -10.0,20.0);
    v2.sort();
    print(v2);                             
    insert_sorted(v2, new_double_value);
    print(v2);   

    vector<string> v3(size);

    generator(v3, 'a', 'z');
    sort(v3.begin(), v3.end());
    print(v3);
    insert_sorted(v3, new_string_value);
    print(v3);
    cout << '\n';

    //-----------------2----------------------


    vector<double> v4(100);

    double error = 0;
    generator(v4, -100.0, 100.0);
    cout << "Analog signal  " << '\n';
    print(v4);   
    cout << '\n';
    cout << "Digital signal " << '\n';
    copy(v4.begin(), v4.end(), ostream_iterator<int> { cout, "  " });     

    for_each(v4.begin(), v4.end(), [&](const double& i)
        {
            error += pow(i - static_cast<int>(i), 2);
        });
    cout << '\n';
    cout << '\n' << " Error between  analog and digital signal = " << error << '\n';

}


