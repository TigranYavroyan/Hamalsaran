#include <iostream> 
#include <vector> 
#include <iomanip> 
#include <climits> 
#include <ctime> 
 
constexpr int N = 8; 
using std::vector; 
 
int zapas1[N][N] = { 
    {2, 3, 4, 4, 4, 4, 3, 2}, 
    {3, 4, 6, 6, 6, 6, 4, 3}, 
    {4, 6, 8, 8, 8, 8, 6, 4}, 
    {4, 6, 8, 8, 8, 8, 6, 4}, 
    {4, 6, 8, 8, 8, 8, 6, 4}, 
    {4, 6, 8, 8, 8, 8, 6, 4}, 
    {3, 4, 6, 6, 6, 6, 4, 3}, 
    {2, 3, 4, 4, 4, 4, 3, 2} 
}; 
 
int zapas2[N][N]{ 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1}, 
    {-1, -1, -1, -1, -1, -1, -1, -1} 
}; 
 
struct Position { 
    int start_x{}; 
    int start_y{}; 
    int x{}; 
    int y{}; 
} knight; 
 
int xMove[8] = { 2, 1, -1, -2, -2, -1, 1,  2 }; 
int yMove[8] = { 1, 2,  2,  1, -1, -2,-2, -1 }; 
 
bool is_valid(int x, int y) 
{ 
    return (x >= 0 && x < N&& y >= 0 && y < N); 
} 
 
void printSolution(int(*sol)[N]) 
{ 
    std::cout << "----------------------------------------------" << std::endl; 
    for (int x = 0; x < N; x++) { 
        for (int y = 0; y < N; y++) 
            std::cout << " " << std::setw(2) << sol[x][y] << " "; 
        std::cout << std::endl; 
    } 
    std::cout << "----------------------------------------------" << std::endl; 
} 
 
void sub_the_access_matrix(int x, int y, int(*access_matrix)[8]) { 
    int next_x{}; 
    int next_y{}; 
    for (int i = 0; i < 8; ++i) { 
        next_x = x + xMove[i]; 
        next_y = y + yMove[i]; 
        if (is_valid(next_x, next_y)) 
            --access_matrix[next_x][next_y]; 
    } 
} 
 
void optimal_move(int x, int y, Position& pos, int(*sol)[8], int(*access_matrix)[8], int& movei) { 
    vector<int> valid_x; 
    vector<int> valid_y; 
    bool flag = false; 
    for (int i = 0, current_x = 0, current_y = 0; i < 8; ++i) { 
        current_x = x + xMove[i]; 
        current_y = y + yMove[i]; 
        if (is_valid(current_x, current_y) && sol[current_x][current_y] == -1) { 
            flag = true; 
            valid_x.push_back(current_x); 
            valid_y.push_back(current_y); 
        } 
    }
    if (flag) { 
        pos.x = valid_x[0]; 
        pos.y = valid_y[0]; 
    } 
    else { 
        pos.x = knight.start_x; 
        pos.y = knight.start_y; 
        movei = 0; 
        for (int i = 0; i < N; ++i) { 
            for (int j = 0; j < N; ++j) { 
                sol[i][j] = zapas2[i][j]; 
                access_matrix[i][j] = zapas1[i][j]; 
            } 
        } 
        return; 
    } 
    for (int i = 1; i < valid_x.size(); ++i) { 
        if (access_matrix[valid_x[i]][valid_y[i]] < access_matrix[pos.x][pos.y]) { 
            pos.x = valid_x[i]; 
            pos.y = valid_y[i]; 
        } 
        else if (access_matrix[valid_x[i]][valid_y[i]] == access_matrix[pos.x][pos.y]) { 
            srand(time(0)); 
            switch (rand() % 2) { 
                case 0: { 
                    pos.x = valid_x[i]; 
                    pos.y = valid_y[i]; 
                    break; 
                } 
            } 
        } 
    } 
} 
 
int find_moves_varnsdorf(int(*sol)[N], int(*access_matrix)[8]) 
{ 
    static long long count = 0; 
    ++count; 
    if (count == (INT_MAX / 2)) 
        throw std::abort; 
 
    int movei{ 1 }; 
    Position pos; 
 
    while (movei != N * N) { 
        sub_the_access_matrix(knight.x, knight.y, access_matrix); 
        optimal_move(knight.x, knight.y, pos, sol, access_matrix, movei); 
        knight.x = pos.x; 
        knight.y = pos.y; 
        ++movei; 
        sol[knight.x][knight.y] = movei; 
    } 
    return 1; 
} 
 
int solve(int current_x = 0, int current_y = 0) 
{ 
    if (!is_valid(current_x, current_y)) 
        return 0; 
    int sol[N][N]; 
    for (int x = 0; x < N; x++) 
        for (int y = 0; y < N; y++) 
            sol[x][y] = -1; 
 
    int access_matrix[N][N] = { 
        {2, 3, 4, 4, 4, 4, 3, 2}, 
        {3, 4, 6, 6, 6, 6, 4, 3}, 
        {4, 6, 8, 8, 8, 8, 6, 4}, 
        {4, 6, 8, 8, 8, 8, 6, 4}, 
        {4, 6, 8, 8, 8, 8, 6, 4}, 
        {4, 6, 8, 8, 8, 8, 6, 4}, 
        {3, 4, 6, 6, 6, 6, 4, 3}, 
        {2, 3, 4, 4, 4, 4, 3, 2} 
    }; 
 
    sol[current_x][current_y] = 1; 
    knight.x = current_x; 
    knight.y = current_y; 
    knight.start_x = current_x; 
    knight.start_y = current_y; 
 
    if (find_moves_varnsdorf(sol, access_matrix) == 0) { 
        std::cout << "Solution does not exist"; 
        return 0; 
    } 
    else 
        printSolution(sol); 
    return 1; 
} 
 
int main() 
{ 
    for (int i = 0; i < 8; ++i) { 
       for (int j = 0; j < 8; ++j) {
           solve(i, j); 
       } 
    }
    return 0; 
}