//Phone_Book
#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Person
{
    string firstname;
    string lastname;
    optional<string> middle_name;
};

ostream& operator<<(ostream& out, const Person& p)
{
    out << setw(15) << p.firstname << setw(15) << p.lastname;

    if (p.middle_name.has_value())
    {
        out << setw(15) << p.middle_name.value();
    }
   
    return out;
}

bool operator<(const Person& p1, const Person& p2)
{
    return tie(p1.firstname, p1.lastname, p1.middle_name) < tie(p2.firstname, p2.lastname, p2.middle_name);
}

bool operator==(const Person& p1, const Person& p2)
{
    return tie(p1.firstname, p1.lastname, p1.middle_name) == tie(p2.firstname, p2.lastname, p2.middle_name);
}

struct PhoneNumber
{
    int code_country;
    int code_city;
    string number;
    optional<int> add_number;
};
optional<int> get_opt_int(string& s)
{
    if (s == "-")
    {
        return nullopt;
    }
    return stoi(s);
}
bool operator<(const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.code_country, p1.code_city, p1.number, p1.add_number) < tie(p2.code_country, p2.code_city, p2.number, p2.add_number);
}

ostream& operator<<(ostream& out, const PhoneNumber& p)
{
    out << setw(5) << '+' << p.code_country << '(' << p.code_city << ')'  << p.number ;

    if (p.add_number.has_value())
    {
        out << setw(5) << p.add_number.value();
    }
    
    return out;
}

class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> m_data;
public:
    PhoneBook(ifstream& file)
    {
        if (!file)
        {
            cout << "Не удаётся открыть файл!" << endl;
            exit(-1);
        }

        for (string line; getline(file, line);)
        {
            stringstream str(line);
            vector<string> row_data;

            for (string s; getline(str, s, ' ');)
            {
                row_data.push_back(s);
            }

            pair<Person, PhoneNumber> entry;

            for (size_t i = 0; i < row_data.size(); ++i)
            {
                switch (i)
                {
                case 0:
                    entry.first.firstname = row_data[i];
                    break;
                case 1:
                    entry.first.lastname = row_data[i];
                    break;
                case 2:
                    entry.first.middle_name = row_data[i];
                    break;
                case 3:
                    entry.second.code_country = stoi(row_data[i]);
                    break;
                case 4:
                    entry.second.code_city = stoi(row_data[i]);
                    break;
                case 5:
                    entry.second.number = row_data[i];
                    break;
                case 6:
                    entry.second.add_number = get_opt_int(row_data[i]);
                    break;
                }
            }

            m_data.push_back(entry);
        }
    }

    friend ostream& operator<<(ostream& out, const PhoneBook& pb)
    {
        for (const auto& [first, second] : pb.m_data)
        {
            out << first << ' ' << second << endl;
        }

        return out;
    }

    void SortByName()
    {
        sort(m_data.begin(), m_data.end(), [](const pair<Person, PhoneNumber>& lhs, const pair<Person, PhoneNumber>& rhs)
            {
                return lhs.first < rhs.first;
            });
    }

    void SortByPhone()
    {
        sort(m_data.begin(), m_data.end(), [](const pair<Person, PhoneNumber>& lhs, const pair<Person, PhoneNumber>& rhs)
            {
                return lhs.second < rhs.second;
            });
    }

    pair<string, vector<PhoneNumber>> GetPhoneNumber(const string& firstname)
    {
        vector<PhoneNumber> phoneNumbers;
        int count = 0;

        for_each(m_data.begin(), m_data.end(), [&](const auto& entry)
            {
                if (entry.first.firstname == firstname)
                {
                    phoneNumbers.push_back(entry.second);
                    ++count;
                }
            });

        switch (count)
        {
        case 0:
            return { "not found", phoneNumbers };
        case 1:
            return { "", phoneNumbers };
        default:
            return { "found more than 1", phoneNumbers };
        }
    }

    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn)
    {
        auto entry = find_if(m_data.begin(), m_data.end(), [&](const auto& entry)
            {
                return entry.first == p;
            });

        if (entry != m_data.end())
        {
            entry->second = pn;
        }
    }
};

int main()
{
    ifstream file("C:\\PhoneBook.txt");
    PhoneBook book(file);
    cout << book;

    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого     человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname)
    {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
        {
            for (size_t i = 0; i < get<1>(answer).size(); ++i)
            {
                cout << get<1>(answer)[i];
            }
        }
        else
        {
            cout << get<0>(answer);
        }
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;

    return 0;
}
