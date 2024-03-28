#include <limits>
#include "helpers.hpp"

int main () {

    // int matrix[13][2] = {
    //     {1, 4},
    //     {2, 4},
    //     {2, 5},
    //     {2, 6},
    //     {3, 6},
    //     {4, 5},
    //     {4, 7},
    //     {5, 8},
    //     {6, 5},
    //     {6, 8},
    //     {7, 8},
    //     {7, 0},
    //     {8, 0},
    // };

    int matrix[25][2] = {
        {1, 6},
        {1, 14},
        {2, 7},
        {3, 8},
        {4, 9},
        {5, 8},
        {6, 13},
        {7, 12},
        {7, 14},
        {8, 11},
        {9, 12},
        {9, 15},
        {10, 9},
        {11, 18},
        {12, 19},
        {13, 20},
        {14, 21},
        {15, 16},
        {15, 17},
        {16, 0},
        {17, 0},
        {18, 0},
        {19, 0},
        {20, 0},
        {21, 0}
    };

    Graph_display graph;
    graph(matrix);
}