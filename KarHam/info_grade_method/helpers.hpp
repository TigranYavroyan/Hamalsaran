#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;

void print_vec (const vector<int>& vec);

template <int N, int M>
vector<int> get_sum (int (&matrix)[N][M]);

template <int N, int M>
vector<int> get_prior(int (&matrix)[N][M], vector<int> sum, bool ascending = true);

template <int N, int M>
vector<int> get_t_j (int (&matrix)[N][M], vector<int>& prior);

double get_W (int N, int K, vector<int>& sum, vector<int>& t_j);

template <int N, int M>
void print_result (int (&matrix)[N][M], vector<int>& sum, vector<int>& prior, vector<int>& t_j);



template <typename T>
static void __swap (T& op1, T& op2) {
    T tmp = op1;
    op1 = op2;
    op2 = tmp;
}

template <typename T>
bool comparator (T& op1, T& op2, bool greater) {
    return (greater) ? op1 > op2 : op1 < op2;
}

static void insertion_sort(vector<int>& vec, bool asceding = true) {
    int i, j;
    for (i = 1; i < vec.size(); ++i) {
        int key = vec[i];
        j = i - 1;
        while (j >= 0 && comparator(key, vec[j], !asceding)) {
           vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

template <int N, int M>
vector<int> get_sum (int (&matrix)[N][M]) {
	vector<int> sum(N, 0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			sum[i] += matrix[i][j];
		}
	}
	return sum;
}

template <int N, int M>
vector<int> get_prior(int (&matrix)[N][M], vector<int> sum, bool ascending) {
	vector<int> prior = sum;
    vector<int> res = prior;
    insertion_sort(sum, ascending);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (sum[i] == prior[j]) {
				res[j] = i + 1;
				break;
			}
		}
	}

	return res;
}

template <int N, int M>
vector<int> get_t_j_for_pair (int (&matrix)[N][M], vector<int>& prior) {
	vector<int> t_j(N, 0);
    vector<vector<int>> matrix_copy;
    for (int i = 0; i < 4; ++i) {
        vector<int> row_vector;
        for (int j = 0; j < 4; ++j) {
            row_vector.push_back(matrix[i][j]);
        }
        matrix_copy.push_back(row_vector);
    }

	for (int i = 0; i < N; ++i) {
        vector<int> col_vector;
        for (int k = 0; k < N; ++k) {
            col_vector.push_back(matrix_copy[k][i]);
        }
        col_vector = get_prior(matrix, col_vector, false);
		for (int j = 0; j < M; ++j) {
			if (col_vector[j] == prior[j])
				++t_j[i];
		}
	}

	return t_j;
}

template <int N, int M>
vector<int> get_t_j (int (&matrix)[N][M], vector<int>& prior) {
	vector<int> t_j(N, 0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (matrix[j][i] == prior[j])
				++t_j[i];
		}
	}

	return t_j;
}

double get_W (int N, int K, vector<int>& sum, vector<int>& t_j) {
	double T = 0;
	double S = 0;
	double a = (N * (K + 1)) / 2;

	for (int i = 0; i < sum.size(); ++i) {
		S += pow((sum[i] - a), 2);
	}
	for (int i = 0; i < t_j.size(); ++i) {
		T += pow(t_j[i], 3) - t_j[i];
	}

	return (12 * S) / (pow(N, 2) * (pow(K, 3) - K) - (N * T));
}

void print_vec (const vector<int>& vec) {
	for (int i : vec) {
		std::cout << i << ' ';
	}
	std::cout << std::endl;
}

template <int N, int M>
void print_result (int (&matrix)[N][M], vector<int>& sum, vector<int>& prior, vector<int>& t_j) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cout << matrix[i][j] << std::setw(4);
		}
		std::cout << std::setw(8) << sum[i] << std::setw(4) << prior[i];
		std::cout.put('\n');
	}
	std::cout.put('\n');
	for (int i = 0; i < t_j.size(); ++i) {
		std::cout << t_j[i] << std::setw(4);
	}

	std::cout << "\n\n";
	double W = get_W(N, M, sum, t_j);
	std::cout << "W = " << W << std::endl; // համաձայնեցվածության աստիճան

	if (W >= 0.86) std::cout << "Փորձագետների կարծիքները համաձայնեցված են" << std::endl;
	else std::cout << "Փորձագետների կարծիքները համաձայնեցված չեն" << std::endl;
}

#endif // HELPERS_H