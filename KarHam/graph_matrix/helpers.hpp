#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <vector>
#include "matrix.h"
#include <cmath>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class Graph_display {
public:
   Graph_display ();
    ~Graph_display();
public:
    template <int N>
    void operator() (int (&matrix)[N][2]);
    void operator() ();
    template <int N, int M>
    void operator() (int (&matrix)[N][2], int (&distances)[M]);
private:
    vector<int> _the_road; // իտերացիոն հաշվարկների մեթոդով կարճագույն ճանապարհը գտնելու համար
    vector<int> t1; // մուտքային տարրեր
    vector<int> t2; // միջանկյալ տարրեր
    vector<int> t3; // ելքային տարրեր
    vector<int> t4; // յուրաքանչյուր մատրիցի զրոյական սյուների թիվը
    vector<int> t5; // զուտ 2 միջանկյալ տարրերի միջև կապերի քանակ
    vector<int> t6; // ելքային տարրերի միջև կապերի թիվ
    int t7{}; // ձևավորվող տարրերի թիվ
    vector<double> Kmo_all_values; // ամեն մատրիցի միջանկյալ տարրերի օգտագործման գործակից
    double Km{}; // միջանկյալ տարրերի գործակից
    double Knk{}; // ներքին կապերի գործակից
    double Kmo_average{}; // միջանկյալ տարրերի օգտագործման միջին գործակից
    double Kkrk{}; // ելքային տարրերի 
    int unit_connections_size{}; // միավոր կապերի քանակ
    int top_size{}; // գագաթների քանակ
private:
//--------------------------------------for finding the road----------------------------------------------
//---------------------------------------for dynamic matrix-----------------------------------------------
    void _find_t2 (int find, int **matrix, int N);
    void _find_t3 (int **matrix, int N);
    void _find_t1_t2_t3 (int **matrix, int N);
    Matrix _creating_A (int **matrix, int N);
    // for finding t5 (both static and dynamic matrixes)
    bool _is_t2 (int num);
    // for finding t6 (both static and dynamic matrixes)
    bool _is_t3 (int num);
    void _find_t5 (int **matrix, int N);
    void _find_t6 (int **matrix, int N);
//-------------------------------------------for static matrix-----------------------------------------------------
    template <int N>
    void _find_t2 (int find, int (&matrix)[N][2]);
    template <int N>
    void _find_t3 (int (&matrix)[N][2]);
    template <int N>
    void _find_t1_t2_t3 (int (&matrix)[N][2]);
    template <int N>
    void _find_t5 (int (&matrix)[N][2]);
    template <int N>
    void _find_t6 (int (&matrix)[N][2]);
    template <int N>
    Matrix _creating_A (int (&matrix)[N][2]);
    // for both static and dynamic matrixes
    void _find_t4 (const Matrix& m);
    void _print_elements () const;
    void _print_t4 ();
    void _print_t7 (int count);
    bool _major_diagonal_zero_check (const Matrix& m) const;
    int **_create_direct_flow_matrix_by_input (int row) const;
    void _console_output (const Matrix& m, int count);
    void print_coefficient ();
    void print_is_rational ();
    void _display (const Matrix& m1);
};

Graph_display::Graph_display () = default;
Graph_display::~Graph_display() = default;

template <int N>
void Graph_display::operator() (int (&matrix)[N][2]) {
    unit_connections_size = N;
    Matrix m1 = _creating_A(matrix);
    top_size = m1.get_row();
    _display(m1);
}

void Graph_display::operator() () {
    int row = 0;
    std::cout << "Input the direct-flow matrixs row: ";
    std::cin >> row;
    if (row <= 0 || row > 100)
        throw std::out_of_range("Input the corrent row (0 < row < 100)");

    unit_connections_size = row;
    int **matrix = _create_direct_flow_matrix_by_input(row);

    Matrix m1 = _creating_A(matrix, row);
    top_size = m1.get_row();

    delete[] matrix;
    matrix = nullptr;
    
    _display(m1);
}
//----------------------------------------for finding the road---------------------------------------------
static int __min(std::vector<double> vec) {
    int min_i = 0;
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[min_i] > vec[i])
            min_i = i;
    }
    return min_i;
}

template <int N>
static int find_Dij_index (int (&matrix)[N][2], int from, int to) {
    for (int i = 0; i < N; ++i) {
        if (from == matrix[i][0] && to == matrix[i][1])
            return i;
    }
    return -1;
}

template <int N>
static int find_index (int (&matrix)[N][2], int start, int find) {
    while (start < N) {
        if (find == matrix[start][1])
            return start;
        ++start;
    }
    return -1;
}

template <int N, int M>
void Graph_display::operator() (int (&matrix)[N][2], int (&distances)[M]) {
    unordered_map<int, int> the_Us;
    vector<int> nodes;
    int max = matrix[0][0]; // create separate function
    for (int i = 1; i < N; ++i) {
        if (max < matrix[i][1])
            max = matrix[i][1];
    }
    int index = 0;
    double min = 0;
    for (int i = 1; i <= max; ++i) {
        index = find_index (matrix, index, i);
        if (index == -1) {
            the_Us.insert({i, 0});
            index = 0;
        }
        else {
            vector<double> U;
            while (index != -1) {
                U.push_back(the_Us[matrix[index][0]] + distances[find_Dij_index(matrix, matrix[index][0], matrix[index][1])]);
                index = find_index (matrix, index + 1, i);
            }
            min = __min(U);
            the_Us.insert({i, U[min]});
            index = 0;
        }
    }
    std::cout.put('\n');
    for (const auto& pair : the_Us) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}
//---------------------------------------for dynamic matrix-----------------------------------------------
void Graph_display::_find_t2 (int find, int **matrix, int N) {
    bool flag = false;
    for (int i = 0; i < N; ++i) {
        if (find == matrix[i][1]) {
            flag = true;
            break;
        }
    }
    if (flag) {
        for (int i = 0; i < N; ++i) {
            if (find == matrix[i][0] && matrix[i][1] != 0) {
                t2.push_back(find);
                break;
            }
        }
    }
}

void Graph_display::_find_t3 (int **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        if (matrix[i][1] == 0)
            t3.push_back(matrix[i][0]);
    }
}

void Graph_display::_find_t1_t2_t3 (int **matrix, int N) {
    int check = 0;
    bool flag = true;
    for (int i = 0; i < N; ++i) {
        flag = true;
        if (check != matrix[i][0]) {
            check = matrix[i][0];
            for (int j = 0; j < N; ++j) {
                if (check == matrix[j][1]) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                t1.push_back(check);
            else {
                _find_t2(check, matrix, N);
            }
        }
    }
    _find_t3(matrix, N);
}

Matrix Graph_display::_creating_A (int **matrix, int N) {
    _find_t1_t2_t3(matrix, N);
    _find_t5(matrix, N);
    _find_t6(matrix, N);
    int max = matrix[0][0];
    for (int i = 1; i < N; ++i) {
        if (max < matrix[i][1])
            max = matrix[i][1];
    }
    Matrix goal(max, max);
    for (int i = 0; i < N; ++i) {
        goal(matrix[i][0] - 1, matrix[i][1] - 1) = 1;
    }
    
    return goal;
}


// for finding t5 (both static and dynamic matrixes)
bool Graph_display::_is_t2 (int num) { 
    for (int i : t2) {
        if (i == num)
            return true;
    }
    return false;
}

// for finding t6 (both static and dynamic matrixes)
bool Graph_display::_is_t3 (int num) {
    for (int i : t3) {
        if (i == num)
            return true;
    }
    return false;
}

void Graph_display::_find_t5 (int **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        if (_is_t2(matrix[i][0])) {
            if (_is_t2(matrix[i][1])) {
                t5.push_back(matrix[i][0]);
            }
        }
        else if (_is_t3(matrix[i][0])) {
            if (_is_t3(matrix[i][1])) {
                t6.push_back(matrix[i][0]);
            }
        }
    }
}

void Graph_display::_find_t6 (int **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        if (_is_t3(matrix[i][0])) {
            if (_is_t3(matrix[i][1])) {
                t6.push_back(matrix[i][0]);
            }
        }
    }
}

//-------------------------------------------for static matrix-----------------------------------------------------
template <int N>
void Graph_display::_find_t2 (int find, int (&matrix)[N][2]) {
    bool flag = false;
    for (int i = 0; i < N; ++i) {
        if (find == matrix[i][1]) {
            flag = true;
            break;
        }
    }
    if (flag) {
        for (int i = 0; i < N; ++i) {
            if (find == matrix[i][0] && matrix[i][1] != 0) {
                t2.push_back(find);
                break;
            }
        }
    }
}

template <int N>
void Graph_display::_find_t3 (int (&matrix)[N][2]) {
    for (int i = 0; i < N; ++i) {
        if (matrix[i][1] == 0)
            t3.push_back(matrix[i][0]);
    }
}

template <int N>
void Graph_display::_find_t1_t2_t3 (int (&matrix)[N][2]) {
    int check = 0;
    bool flag = true;
    for (int i = 0; i < N; ++i) {
        flag = true;
        if (check != matrix[i][0]) {
            check = matrix[i][0];
            for (int j = 0; j < N; ++j) {
                if (check == matrix[j][1]) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                t1.push_back(check);
            else {
                _find_t2(check, matrix);
            }
        }
    }
    _find_t3(matrix);
}

template <int N>
void Graph_display::_find_t5 (int (&matrix)[N][2]) {
    for (int i = 0; i < N; ++i) {
        if (_is_t2(matrix[i][0])) {
            if (_is_t2(matrix[i][1])) {
                t5.push_back(matrix[i][0]);
            }
        }
    }
}

template <int N>
void Graph_display::_find_t6 (int (&matrix)[N][2]) {
    for (int i = 0; i < N; ++i) {
        if (_is_t3(matrix[i][0])) {
            if (_is_t3(matrix[i][1])) {
                t6.push_back(matrix[i][0]);
            }
        }
    }
}

template <int N>
Matrix Graph_display::_creating_A (int (&matrix)[N][2]) {
    _find_t1_t2_t3(matrix);
    _find_t5(matrix);
    _find_t6(matrix);
    int max = matrix[0][0];
    for (int i = 1; i < N; ++i) {
        if (max < matrix[i][1])
            max = matrix[i][1];
    }
    Matrix goal(max, max);
    for (int i = 0; i < N; ++i) {
        goal(matrix[i][0] - 1, matrix[i][1] - 1) = 1;
    }
    
    return goal;
}

// for both static and dynamic matrixes
void Graph_display::_find_t4 (const Matrix& m) {
    bool flag = true;
    int i = 0;
    int j = 0;
    while (i < m.get_row()) {
        while (j < m.get_col()) {
            if (m(j, i) != 0) {
                flag = false;
                break;
            }
            ++j;
        }
        if (flag)
            t4.push_back(i + 1);
        ++i;
        j = 0;
        flag = true;
    }
}

void Graph_display::_print_elements () const {
    std::cout << "t1 = " << t1.size() << "-> { ";
    for (int i : t1) {
        std::cout << i << ' ';
    }
    std::cout << '}' << std::endl;
    std::cout << "t2 = " << t2.size() << "-> { ";
    for (int i : t2) {
        std::cout << i << ' ';
    }
    std::cout << '}' << std::endl;
    std::cout << "t3 = " << t3.size() << "-> { ";
    for (int i : t3) {
        std::cout << i << ' ';
    }
    std::cout << '}' << std::endl;
    std::cout << "t5 = " << t5.size() << "-> { ";
    for (int i : t5) {
        std::cout << i << ' ';
    }
    std::cout << '}' << std::endl;
    std::cout << "t6 = " << t6.size() << "-> { ";
    for (int i : t6) {
        std::cout << i << ' ';
    }
    std::cout << '}' << std::endl;
}

void Graph_display::_print_t4 () {
    std::cout << "t4 = " << t4.size() << "-> { ";
    for (int i : t4) {
        std::cout << i << ' ';
    }
    std::cout << '}' << std::endl;
    t4.clear();
}

void Graph_display::_print_t7 (int count) {
    t7 = t4.size() - count;
    std::cout << "t7 = " << t7 << std::endl;
}

bool Graph_display::_major_diagonal_zero_check (const Matrix& m) const {
    for (int i = 0; i < m.get_row(); ++i) {
        if (m(i, i) != 0)
            return true;
    }
    return false;
}

int** Graph_display::_create_direct_flow_matrix_by_input (int row) const {
    int **matrix = nullptr;

    matrix = new int*[row];
    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[2];
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << "matrix[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }

    return matrix;
}

void Graph_display::_console_output (const Matrix& m, int count) {
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << "\n A^" << count << std::endl;
    m.display();
    _find_t4(m);
    _print_t7(count);
    double Kmo = static_cast<double>(t7) / static_cast<double>(t4.size());
    Kmo_all_values.push_back(Kmo);
    _print_t4();
    std::cout << "Kmo = " << Kmo << '\n';
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
}

void Graph_display::print_coefficient () {

    double size = Kmo_all_values.size();
    for (int i = 0; i < size; ++i) {
        Kmo_average += Kmo_all_values[i];
    }

    Kmo_average /= size;
    Km = static_cast<double>(t2.size()) / static_cast<double>(top_size);
    Knk = static_cast<double>(t5.size()) / static_cast<double>(unit_connections_size);
    Kkrk = 2 * static_cast<double>(t6.size()) / (static_cast<double>(t3.size()) * (static_cast<double>(t3.size()) - 1));
    std::cout << "Km = " << Km << '\n';
    std::cout << "Knk = " << Knk << '\n';
    std::cout << "Kmo_average = " << Kmo_average << std::endl;
    std::cout << "Kkrk = " << Kkrk << std::endl;
}

void Graph_display::print_is_rational () {
    double epsilion = fabs(Km - Kmo_average);
    std::cout << "Epsiliion is: " << epsilion << "\n\n";
    if (epsilion >= 0.01 && epsilion <= 0.1)
        std::cout << "The graph is rational" << std::endl;
    else
        std::cout << "The graph is not raional" << std::endl;
}

void Graph_display::_display (const Matrix& m1) {
    char check{};
    short count{1};
    Matrix m2 = m1;
    Matrix m3;
    Matrix delta = m1;
    system("clear");
    _console_output(m1, count++);

    do {
        if (m3.all_is_zero())
            break;
        m3 = m2 * m1;
        delta += m3;

        _console_output(m3, count);


        if (_major_diagonal_zero_check(m3))
            throw std::invalid_argument("There is a circuit in matrix (check the diagonal)");

        ++count;
        if (count <= m1.get_row() && check != 'd') {
            std::cout << "Do you want to get A^" << count << " (if you want to get all, type (d))(y, n)? ";
            std::cin >> check;
        }
        m2 = m3;
    } while (check != 'n' && count <= m1.get_row());
    if (check != 'n') {
        std::cout << "\nDelta matrix: " << std::endl;
        delta.display();
        _find_t4(delta);
        _print_elements();
        _print_t4();
        print_coefficient();
        print_is_rational();
    }
}

#endif // HELPERS_HPP