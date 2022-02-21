#include <iostream>
#include <list>
#include <iomanip>
#include <random>
#include <math.h>

using namespace std;

void print_list(list<float>& l)
{
    cout << "( ";
    for (list<float>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
    {
        cout << *iter << (next(iter, 1) == l.end() ? " " : " | ");
    }
    cout << ')' << endl;
}

void push_back_list(list<float>& l)
{
    float sum = 0;

    for (const float& value : l)
    {
        sum += value;
    }

    l.push_back(sum / l.size());
}

//_____________________________________________________________

class Matrix
{
private:
    const size_t matrix_size;
    const size_t matrix_capacity;
    double* array;
    double matrix_determinant{ 0.0 };

    Matrix get_modified_matrix(Matrix& arr, const size_t item);
    double calculate_determinant(Matrix& arr);
public:
    Matrix(const int size);
    void fill_random();                 
    void print_matrix() const;               
    size_t size() const;               
    double determinant() const;        

    //3
    class Iterator
    {
    private:
        double* current;
    public:
        Iterator(double* pointer);
        double& operator[](size_t i);
        Iterator& operator ++();
        bool operator !=(const Iterator& iterator);
        double& operator *();
    };

    Iterator operator[](size_t i);
    Iterator begin();
    Iterator end();

    ~Matrix();
};

//--------------------------------------------------------------


Matrix::Matrix(const int size) : matrix_size(size), matrix_capacity(size* size)
{
    array = new double[matrix_capacity];
}

Matrix::Iterator::Iterator(double* pointer) : current(pointer)
{

}

double& Matrix::Iterator::operator[](size_t i)
{
    return *(current + i);
}

Matrix::Iterator Matrix::operator[](size_t i)
{
    return Iterator(array + i * matrix_size);
}

Matrix::Iterator& Matrix::Iterator::operator ++()
{
    ++current;
    return *this;
}

bool Matrix::Iterator::operator !=(const Iterator& iterator)
{
    return current != iterator.current;
}

double& Matrix::Iterator::operator *()
{
    return *current;
}

Matrix::Iterator Matrix::begin()
{
    return Iterator(array);
}

Matrix::Iterator Matrix::end()
{
    return Iterator(array + matrix_capacity);
}

Matrix Matrix::get_modified_matrix(Matrix& arr, const size_t item)
{
    Matrix new_array(arr.size() - 1);
    size_t current_row = 0;

    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (item == i)
        {
            current_row = i;
            continue;
        }

        for (size_t j = 0; j < new_array.size(); ++j)
        {
            new_array[current_row][j] = arr[i][j + 1];
        }

        ++current_row;
    }

    return new_array;
}

double Matrix::calculate_determinant(Matrix& arr)
{
    double determinant = 0;

    if (arr.size() == 1)
    {
        determinant = arr[0][0];
    }
    else if (arr.size() == 2)
    {
        determinant = arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
    }
    else
    {
        int sign = 1;

        for (size_t i = 0; i < arr.size(); ++i)
        {
            Matrix newArray = get_modified_matrix(arr, i);
            determinant += sign * arr[i][0] * calculate_determinant(newArray);
            sign = -sign;
        }
    }

    return determinant;
}

void Matrix::fill_random()
{
    random_device rd;
    mt19937 mersenne(rd());                                   
    uniform_real_distribution<double> urd(-10.0, 10.0);       

    for (size_t i = 0; i < matrix_capacity; ++i)
    {
        *(array + i) = round(urd(mersenne) * 10) / 10;
    }

    matrix_determinant = calculate_determinant((*this));
}

void Matrix::print_matrix() const
{
    cout << '[';

    for (size_t i = 0; i < matrix_capacity;)
    {
        cout << setw(5) << *(array + i++);

        if (!(i % matrix_size))
        {
            cout << " ]" << endl;

            if (i < matrix_capacity)
            {
                cout << '[';
            }
        }
        else
        {
            cout << ',';
        }
    }
}

size_t Matrix::size() const
{
    return matrix_size;
}

double Matrix::determinant() const
{
    return matrix_determinant;
}

Matrix::~Matrix()
{
    delete[] array;
}

//-----------------------------------------------------------


int main()
{
    //1

    list<float> l{ 1.00, 2.00, 3.00, 4.00 };
    push_back_list(l);
    print_list(l);
    cout << "\n";
    
    //2\

    size_t i = 2;
     cout << "Matrix " << i << 'x' << i << ':' << "\n";
    Matrix m(i);
    m.fill_random();
    m.print_matrix();
    cout << "Matrix determinant: "  << m.determinant() << "\n\n";

    //3

    m.fill_random();
    m.print_matrix();
    for (const double& i : m)
    {
        cout  <<" " << i;
    }
    cout << "\n";
    
}