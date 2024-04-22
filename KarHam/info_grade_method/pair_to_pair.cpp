#include <iostream>
#include <vector>
#include "helpers.hpp"

using std::vector;

void print_pair_indexes (int start, int end) {
    if (start >= end)
        throw std::invalid_argument("start must be less than end");

    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j <= end; ++j) {
            std::cout << "|" << i << ", " << j << "|" << "  ";
        }
    }
    std::cout.put('\n');
}

template <int N, int M>
void pair_to_pair(int (&matrix)[N][M]) {
    int sum[N][M]; // գումարային մատրից
    vector<int> sum_Qij; // գումար Qij
    vector<int> prior; // 
    vector<int> t_j; //

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            sum[i][j] = 0;
        }
    }

    print_pair_indexes(1, N);

    for (int k = 0; k < M; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                int a, b;
                if (matrix[i][k] < matrix[j][k]) {
                    sum[i][k] += 1;
                    a = 1;
                    b = 0;
                }
                else {
                    sum[j][k] += 1;
                    a = 0;
                    b = 1;
                }
                std::cout << ' ' << a << ' ' << b << "    ";
            }
        }
        std::cout.put('\n');
    }
    std::cout.put('\n');
    sum_Qij = get_sum(sum);
    prior = get_prior(matrix, sum_Qij, false); // նոր դասակարգում
	t_j = get_t_j_for_pair(sum, prior); // նոր դասակարգվածի հետ համընկումները
    print_result (sum, sum_Qij, prior, t_j);
}

int main() {
    int matrix[][4] = {
		{1, 2, 4, 3},
		{2, 1, 1, 1},
		{4, 3, 3, 4},
		{3, 4, 2 ,2},
	};

    pair_to_pair(matrix);

    return 0;
}
