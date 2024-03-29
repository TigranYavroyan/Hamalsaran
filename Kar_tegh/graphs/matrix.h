#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <ctime>
#include <iomanip>

class Matrix {
	// proxy for operator[]
	class my_array {
		int *m_arr;
	public:
		my_array (int *arr);
		int operator[] (int i) const;
		int& operator[] (int i);
	};
public:
    Matrix ();
    Matrix (int row, int col);
    Matrix (const Matrix& other);
    ~Matrix () noexcept;
public:
    void set_zero ();
    void set_random (int row, int col);
    void set_by_input ();
    void display () const;
    void erase () noexcept;
    int get_row () const;
    int get_col () const;
    bool empty () const;
    bool all_is_zero () const;
public:
    Matrix operator+ (const Matrix& rhs);
    const Matrix& operator= (const Matrix& rhs);
    Matrix operator* (const Matrix& rhs);
    void operator+= (const Matrix& rhs);
	const my_array operator[] (int i) const;
	my_array operator[] (int i);
private:
    int **m_matrix{nullptr};
    int m_row{};
    int m_col{};
    void _set_random ();
    void _get_area ();
};

#endif // MATRIX_H
