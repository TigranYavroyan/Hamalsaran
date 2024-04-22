#include "helpers.hpp"

using std::vector;

int main () {
	int matrix[][4] = {
		{1, 2, 4, 3},
		{2, 1, 1, 1},
		{4, 3, 3, 4},
		{3, 4, 2 ,2},
	};

	vector<int> sum = get_sum(matrix); // խմբակային գնահատում
	vector<int> prior = get_prior(matrix, sum); // նոր դասակարգում
	vector<int> t_j = get_t_j(matrix, prior); // նոր դասակարգվածի հետ համընկումները

	print_result(matrix, sum, prior, t_j);
}
