#include <vector>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "lesson_1.h"




class TestBook : public testing::Test
{
protected:
    PhoneBook* book;

    void SetUp() override
    {
        std::stringstream src_stream;
        src_stream << "Ivanov Daniil Maksimovich 7 366 7508887  \n"
                   << "Aleksandrov Georgii  493 7637 6114861  \n"
                   << "Aleksandrov Andrey Mikhailovich 7 247 1377660 5542 \n"
                   << "Markelov;Dmitrii Vadimovich 19 7576 5734416 2 \n";

        book = new PhoneBook(src_stream);
    }

    void TearDown() override
    {
        delete book;
    }
};

TEST_F(TestBook, GetPhoneNumber_notFound)
{
    std::string lastname = "Egorov";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "not found");
}

TEST_F(TestBook, GetPhoneNumber_foundOne)
{
    std::string lastname = "Ivanov";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "");
}

TEST_F(TestBook, GetPhoneNumber_foundMore)
{
    std::string lastname = "Aleksandrov";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "found more than 1");
}

TEST_F(TestBook, GetPhoneNumber_empty)
{
    std::string lastname = "";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "not found");
}

TEST_F(TestBook, ChangePhoneNumber)
{
    std::string lastname = "Ivanov";

    ASSERT_EQ(std::get<0>(book->GetPhoneNumber(lastname)).empty(), true);

    PhoneNumber answer = std::get<1>(book->GetPhoneNumber(lastname))[0];
    EXPECT_EQ(answer.number, "7508887");

    book->ChangePhoneNumber(Person{ "Ivanov", "Daniil", "Maksimovich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });

    answer = std::get<1>(book->GetPhoneNumber(lastname))[0];
    EXPECT_EQ(answer.code_country, 7);
    EXPECT_EQ(answer.city_code, 123);
    EXPECT_EQ(answer.number, "15344458");
    EXPECT_EQ(answer.add_number, std::nullopt);
}




int main(int argc, const char** argv)
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}