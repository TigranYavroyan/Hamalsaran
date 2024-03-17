#include <iostream>
#include <iomanip>
#include <climits>

constexpr int N = 8;

int is_valid(int x, int y) 
{ 
	return (x >= 0 && x < N && y >= 0 && y < N); 
} 

void printSolution(int (*sol)[N]) 
{
	std::cout << "----------------------------------------------" << std::endl;
	for (int x = 0; x < N; x++) { 
		for (int y = 0; y < N; y++) 
			std::cout << " " << std::setw(2) << sol[x][y] << " "; 
		std::cout << std::endl; 
	}
	std::cout << "----------------------------------------------" << std::endl;
} 


int find_moves_backtracking(int x, int y, int movei, int (*sol)[N], int *xMove, int *yMove) 
{
    static long long count = 0;
    ++count;
    if (count == (INT_MAX / 2))
        throw std::abort;

	int k{};
	int next_x{};
	int next_y{};

	if (movei == N * N) 
		return 1; 

	for (k = 0; k < N; k++) { 
		next_x = x + xMove[k]; 
		next_y = y + yMove[k]; 
		if (is_valid(next_x, next_y) && sol[next_x][next_y] == -1) { 
			sol[next_x][next_y] = movei; 
			if (find_moves_backtracking(next_x, next_y, movei + 1, sol, xMove, yMove) == 1) 
				return 1; 
			else
				sol[next_x][next_y] = -1; 
		} 
	} 
	return 0; 
} 

int solve(int current_x = 0, int current_y = 0)
{
    if (!is_valid(current_x, current_y))
        return 0;

	int sol[N][N];
	for (int x = 0; x < N; x++) 
		for (int y = 0; y < N; y++) 
			sol[x][y] = -1; 

	int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
	int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 

	sol[current_x][current_y] = 0; 

	if (find_moves_backtracking(current_x, current_y, 1, sol, xMove, yMove) == 0) { 
		std::cout << "Solution does not exist"; 
		return 0; 
	} 
	else
		printSolution(sol); 
	return 1; 
}

int main()
{
    int x = 0;
    int y = 0;
	solve(x, y);
	return 0; 
} 

