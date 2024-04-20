#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

const size_t size = 4;

void print_vec (const vector<int>& vec);

template <int N, int M>
vector<int> get_sum (int (&matrix)[N][M]);

template <int N, int M>
vector<int> get_prior(int (&matrix)[N][M], vector<int> sum);

template <int N, int M>
vector<int> get_t_j (int (&matrix)[N][M], vector<int> prior);

double get_W (int N, int K, vector<int> sum, vector<int> t_j);


int main () {
	int matrix[][size] = {
		{1, 2, 4, 3},
		{2, 1, 1, 1},
		{4, 3, 3, 4},
		{3, 4, 2 ,2},
	};

	vector<int> sum = get_sum(matrix);
	vector<int> prior = get_prior(matrix, sum);
	vector<int> t_j = get_t_j(matrix, prior);

	print_vec(sum);
	print_vec(prior);
	print_vec(t_j);
	std::cout << get_W(size, size, sum, t_j) << std::endl;
}

template <typename T>
static void __swap (T& op1, T& op2) {
    T tmp = op1;
    op1 = op2;
    op2 = tmp;
}

static void insertion_sort_asc (vector<int>& vec) {
    int i, j;
    for (i = 1; i < vec.size(); ++i) {
        j = i;
        while (vec[j] < vec[j - 1] && j > 0) {
            __swap(vec[j], vec[j - 1]);
            --j;
        }
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
vector<int> get_prior(int (&matrix)[N][M], vector<int> sum) {
	vector<int> prior = sum;
    insertion_sort_asc(sum);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (sum[i] == prior[j]) {
				prior[j] = i + 1;
				break;
			}
		}
	}

	return prior;
}

template <int N, int M>
vector<int> get_t_j (int (&matrix)[N][M], vector<int> prior) {
	vector<int> t_j(N, 0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (matrix[j][i] == prior[j])
				++t_j[i];
		}
	}

	return t_j;
}

double get_W (int N, int K, vector<int> sum, vector<int> t_j) {
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