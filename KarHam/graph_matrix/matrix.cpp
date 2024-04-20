#include "matrix.h"

Matrix::Matrix () : m_row{3}, m_col{m_row} {
    _get_area();

    int count = 1;
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            m_matrix[i][j] = count;
            ++count;
        }
    }
}

Matrix::Matrix (int row, int col) : m_row{row}, m_col{col} {
    _get_area();
    set_zero();
}

Matrix::Matrix (const Matrix& other) : m_row{other.m_row}, m_col{other.m_col} {
    _get_area();

    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            m_matrix[i][j] = other.m_matrix[i][j];
        }
    }
}

Matrix::~Matrix () noexcept {
    erase();
}

void Matrix::set_zero () {
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            m_matrix[i][j] = 0;
        }
    }
}

void Matrix::set_random (int row, int col) {
    srand(time(0));
    if (row != m_row || col != m_col) {
        erase();
        m_row = row;
        m_col = col;
        _get_area();
    }
    _set_random();
}

void Matrix::set_by_input () {
    if (!empty())
        erase();
    std::cout << "Input the rows and cols: ";
    std::cin >> m_row >> m_col;
    _get_area();

    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            std::cout << "Input the matrix[" << i << "][" << j << "] element: ";
            std::cin >> m_matrix[i][j];
        }
    }
}

int Matrix::get_row () const {
    return m_row;
}

int Matrix::get_col () const {
    return m_col;
}

// the old display function
// void Matrix::display () const {
//     if (empty())
//         std::cout << "Matrix is empty";
//     for (int i = 0; i < m_row; ++i) {
//         for (int j = 0; j < m_col; ++j) {
//             std::cout << std::setw(4) << m_matrix[i][j];
//         }
//         std::cout << std::endl;
//     }
//     std::cout << std::endl;
// }

void Matrix::display() const {

    int maxRowIndexDigits = 2/*std::to_string(m_row - 1).length()*/;
    int maxColIndexDigits = std::to_string(m_col - 1).length();

    std::cout << "      ";
    for (int j = 0; j < m_col; ++j) {
        std::cout << std::setw(maxColIndexDigits + 1) << j + 1;
    }
    std::cout << '\n' << std::endl;
    for (int i = 0; i < m_row; ++i) {
        std::cout << std::setw(maxRowIndexDigits + 2) << i + 1 << " |";
        for (int j = 0; j < m_col; ++j) {
            std::cout << std::setw(maxColIndexDigits + 1) << m_matrix[i][j];
        }
        std::cout.put('\n');
    }
    std::cout << std::endl;
}

bool Matrix::empty () const {
    return !m_matrix;
}

bool Matrix::all_is_zero () const {
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            if (m_matrix[i][j] != 0)
                return 0;
        }
    }
    return 1;
}

void Matrix::erase () noexcept {
    m_row = 0;
    m_col = 0;
    for (int i = 0; i < m_row; ++i) {
        delete m_matrix[i];
    }
    delete m_matrix;
    m_matrix = nullptr;
}

Matrix Matrix::operator+ (const Matrix& rhs) {
    if (m_row != rhs.m_row || m_col != rhs.m_col)
        throw std::invalid_argument("The cols and rows aren't equal");
    Matrix other(*this);
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            other.m_matrix[i][j] += rhs.m_matrix[i][j];
        }
    }
    return other;
}

const Matrix& Matrix::operator= (const Matrix& rhs) {
    if (this == &rhs)
        return *this;
    if (rhs.m_row != m_row || rhs.m_col != m_col) {
        erase();
        m_row = rhs.m_row;
        m_col = rhs.m_col;
        _get_area();
    }
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            m_matrix[i][j] = rhs.m_matrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator* (const Matrix& rhs) {
    if (m_col != rhs.m_row) // ստուգում ենք առաջին մատրիցի սյուների և երկրորդ մատրիցի տողերի համապատասխանությունը
        throw std::invalid_argument("the cols must be equal to rows");

    Matrix matrix;
    matrix.set_random(m_row, rhs.m_col);
    matrix.set_zero();
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < rhs.m_col; ++j) {
            for (int k = 0; k < m_col; ++k) { // օգտագործում ենք մատրիցների արտադրյալի բանաձևը
                matrix.m_matrix[i][j] += (m_matrix[i][k] * rhs.m_matrix[k][j]);
            }
        }
    }
    return matrix;
}

void Matrix::operator+= (const Matrix& rhs) {
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            m_matrix[i][j] += rhs.m_matrix[i][j];
        }
    }
}

const int& Matrix::operator() (int i, int j) const {
    return m_matrix[i][j];
}

int& Matrix::operator() (int i, int j) {
    return const_cast<int&>(static_cast<const Matrix&>(*this)(i, j));
}

void Matrix::_set_random () {
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            m_matrix[i][j] = rand () % 6;
        }
    }
}

void Matrix::_get_area () {
    m_matrix = new int*[m_row];
    for (int i = 0; i < m_row; ++i) {
        m_matrix[i] = new int[m_col];
    }
}

