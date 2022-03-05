

#include <iostream>
#include <fstream>
#include <numeric>
#include "lesson_7.pb.h"
#include "Students_Group.h"



int main()
{
    FullName fn;
    fn.set_name("John");
    fn.set_surname("Kolpakoff");
    fn.set_patronymic("Leonidovich");

    Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(2);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    SG::StudentsGroup sg;
    sg.add_student(s);
    sg.Save();

    SG::StudentsGroup new_sg;
    new_sg.Open();
    std::cout << new_sg.GetAllInfo(fn) << '\n';
    return 0;
}





