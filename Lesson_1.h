#pragma once


#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <fstream>

struct Person
{
    std::string firstname;
    std::string lastname;
    std::optional<std::string> middle_name;
};

struct PhoneNumber
{
    int code_country;
    int city_code;
    std::string number;
    std::optional<int> add_number;
};

class PhoneBook
{
private:
    std::vector<std::pair<Person, PhoneNumber>> m_data;
public:
    PhoneBook(std::istream& file);
    friend std::ostream& operator<<(std::ostream& out, const PhoneBook& pb);
    void SortByName();
    void SortByPhone();
    std::pair<std::string, std::vector<PhoneNumber>> GetPhoneNumber(const std::string& firstname);
    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn);
};


std::ostream& operator<<(std::ostream& out, const Person& p);
bool operator<(const Person& p1, const Person& p2);
bool operator==(const Person& p1, const Person& p2);

bool operator<(const PhoneNumber& p1, const PhoneNumber& p2);
std::optional<int> get_opt_int(std::string& s);
std::ostream& operator<<(std::ostream& out, const PhoneNumber& p);



std::ostream& operator<<(std::ostream& out, const Person& p)
{
    out << std::setw(15) << p.firstname << std::setw(12) << p.lastname;

    if (p.middle_name.has_value())
    {
        out << std::setw(15) << p.middle_name.value();
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



bool operator<(const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.code_country, p1.city_code, p1.number, p1.add_number) < tie(p2.code_country, p2.city_code, p2.number, p2.add_number);
}

std::optional<int> get_opt_int(std::string& s)
{
    if (s == "")
    {
        return std::nullopt;
    }

    return std::stoi(s);
}

std::ostream& operator<<(std::ostream& out, const PhoneNumber& p)
{
    out << std::setw(5) << '+' << p.code_country << '(' << p.city_code << ')' << p.number;

    if (p.add_number.has_value())
    {
        out << std::setw(5) << p.add_number.value();
    }

    return out;
}



PhoneBook::PhoneBook(std::istream& file)
{
    if (!file)
    {
        std::cout << "Не удаётся открыть файл!" << std::endl;
        exit(1);
    }

    for (std::string line; std::getline(file, line);)
    {
        std::stringstream str(line);
        std::vector<std::string> row_data;

        for (std::string s; getline(str, s, ' ');)
        {
            row_data.push_back(s);
        }

        std::pair<Person, PhoneNumber> entry;

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
                entry.second.city_code = stoi(row_data[i]);
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

std::ostream& operator<<(std::ostream& out, const PhoneBook& pb)
{
    for (const auto& [first, second] : pb.m_data)
    {
        out << first << ' ' << second << std::endl;
    }

    return out;
}

void PhoneBook::SortByName()
{
    sort(m_data.begin(), m_data.end(), [](const std::pair<Person, PhoneNumber>& lhs, const std::pair<Person, PhoneNumber>& rhs)
        {
            return lhs.first < rhs.first;
        });
}

void PhoneBook::SortByPhone()
{
    sort(m_data.begin(), m_data.end(), [](const std::pair<Person, PhoneNumber>& lhs, const std::pair<Person, PhoneNumber>& rhs)
        {
            return lhs.second < rhs.second;
        });
}

std::pair<std::string, std::vector<PhoneNumber>> PhoneBook::GetPhoneNumber(const std::string& firstname)
{
    std::vector<PhoneNumber> phoneNumbers;
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

void PhoneBook::ChangePhoneNumber(const Person& p, const PhoneNumber& pn)
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