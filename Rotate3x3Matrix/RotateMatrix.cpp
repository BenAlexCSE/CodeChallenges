/*
LinkedListClassC++.cpp

Benjamin Alexander

7/17/2024

Assignment: This application rotates a 3x3 matric clockwise or counter clockwise.
This algroithm works for and NxN matric.

Copyright (c) 2024 Benjamin Alexander. All rights reserved.
*/

#include <bits/stdc++.h>
using namespace std;
 
#define N 5
 
// Function to rotate the matrix 90 degree clockwise
void rotate90(int a[N][N], bool right)
{
    // Traverse each cycle
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {

            if(right)
            {
                // Swap elements of each cycle
                // in clockwise direction
                int temp = a[i][j];
                a[i][j] = a[N-j-1][i];
                a[N-j-1][i] = a[N-i-1][N-j-1];
                a[N-i-1][N-j-1] = a[j][N-i-1];
                a[j][N-i-1] = temp;
            }
            else
            {
                int temp = a[N-j-1][i];
                a[N-j-1][i] = a[i][j];
                a[i][j] = a[j][N-i-1];
                a[j][N-i-1] = a[N-i-1][N-j-1];
                a[N-i-1][N-j-1] = temp;
            }
        }
    }
}
 
// Function for print matrix
void printMatrix(int arr[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << arr[i][j] << " ";
        cout << '\n';
    }
}
 
// Driver code
int main()
{
    bool right;
    cout << "0 for left rotation or 1 for right rotation\n";
    while (!(cin >> right)) {
        cout << "0 for left rotation or 1 for right rotation\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    int arr[N][N] = { { 1, 2, 3, 4 , 5},
                      { 6, 7, 8, 9, 10 },
                      { 11, 12, 13, 14, 15 },
                      { 16, 17, 18, 19, 20 },
                      { 21, 22, 23, 24, 25 } };
    rotate90Clockwise(arr, right);
    printMatrix(arr);
    return 0;
}