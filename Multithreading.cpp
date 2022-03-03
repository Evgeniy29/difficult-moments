#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include "Timer.h"

using namespace std;

mutex m;

class pcout
{
private:
    lock_guard<mutex> lg;
public:
    pcout() : lg(lock_guard<mutex>(m))
    {
    }

    template<typename T>
    pcout& operator<<(const T& data)
    {
        cout << data;
        return *this;
    }

};

void doSomething(int number)
{
    pcout() << "start thread " << number << '\n';
    pcout() << "stop thread " << number << '\n';
}
//----------------------
bool prime(size_t num)
{
    size_t limit = num / 2;

    if (num > 2)
    {
        for (size_t i = 2; i <= limit; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
    }

    return true;
}

//---------------


void generate_things(vector<int>& v)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 1000);

    lock_guard lg(m);

    generate(v.begin(), v.end(), [&]()
        {
            return dis(gen);
        });
}

void pop_things(vector<int>& v)
{
    this_thread::sleep_for(500ms);

    lock_guard lg(m);

    cout << *max_element(v.begin(), v.end()) << '\n';
}

int main()
{
   
    //1--------------------------
    thread th1(doSomething, 1);
    thread th2(doSomething, 2);
    thread th3(doSomething, 3);
    th1.join();
    th2.join();
    th3.join();

    //2----------------------------
    
    size_t max_value = 50000;
    size_t count_threads = 30;
    vector<size_t> answers;
    mutex m;

    Timer timer("with threads");

    for (size_t i = 0; i < max_value;)
    {
        vector<thread> v;

        for (size_t j = i + count_threads; i <= j; ++i)
        {
            v.push_back(thread([=, &m, &answers]()
                {
                    if (prime(i))
                    {
                        lock_guard lg(m);
                        answers.push_back(i);
                    }
                }));
        }

        for (auto& t : v)
        {
            t.join();
        }
    }

            /*for (const auto& a : answers)
            {
                cout << "the number " << a << " is simple" << '\n';
            }*/

    timer.print();

    answers.clear();
    answers.shrink_to_fit();

    timer.start("without threads");

    for (size_t i = 0; i < max_value; ++i)
    {
        if (prime(i))
        {
            answers.push_back(i);
        }
    }
   /* for (const auto& a : answers)
    {
        cout << "the number " << a << " is simple" << '\n';
    }*/
    timer.print();

    //3-----------------

    vector<int> v(100);
    size_t count = 20;

    while (count--)
    {
        thread owner([&]()
            {
                generate_things(v);
            });
        thread robber([&]()
            {
                pop_things(v);
            });

        owner.join();
        robber.join();
    }

}