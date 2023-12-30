#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

int getNumNeighbours(int **grid, int N, int j, int k) {
  if (j >= N || k >= N || j < 0 || k < 0)
    return 0;

  int a = (j + 1 < N) ? grid[j + 1][k] : 0;                    // down
  int b = (j + 1 < N && k + 1 < N) ? grid[j + 1][k + 1] : 0;   // bottom right
  int c = (k + 1 < N) ? grid[j][k + 1] : 0;                    // right
  int d = (k - 1 >= 0) ? grid[j][k - 1] : 0;                   // : 0 left
  int e = (j - 1 >= 0 && k - 1 >= 0) ? grid[j - 1][k - 1] : 0; // top left
  int f = (j - 1 >= 0) ? grid[j - 1][k] : 0;                   // up
  int g = (j - 1 >= 0 && k + 1 < N) ? grid[j - 1][k + 1] : 0;  // top right
  int h = (j + 1 < N && k - 1 >= 0) ? grid[j + 1][k - 1] : 0;  // bottom left

  return a + b + c + d + e + f + g + h;
}

void displayGrid(int **grid, int N) {
  system("cls");

  for (int i = 0; i < N + 2; i++)
    cout << "🔶 ";
  cout << endl;

  for (int j = 0; j < N; j++) {
    cout << "🔶 ";
    for (int k = 0; k < N; k++) {
      //   cout << grid[j][k];
      if (grid[j][k] == 1)
        cout << "🔹 ";
      else
        cout << "🔲 ";
    }

    cout << "🔶 " << endl;
  }

  for (int i = 0; i < N + 2; i++)
    cout << "🔶 ";
}

int main() {
  // constants
  const int N = 10; // for NxN grid
  const int steps = 100;
  const int dt = 2000; // milliseconds

  srand(time(0));
  SetConsoleOutputCP(CP_UTF8); // for emojis

  // initializing grid with random values
  int **grid = new int *[N];
  for (int i = 0; i < N; i++) {
    grid[i] = new int[N];
    for (int j = 0; j < N; j++) {
      int val = rand() % 10;
      grid[i][j] = val <= 2;
    }
  }

  for (int i = 0; i < steps; i++) {
    Sleep(dt);

    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        int cell = grid[j][k];
        int neighbours = getNumNeighbours(grid, N, j, k);
        if (cell == 1) { // alive
          if (neighbours < 2) {
            grid[j][k] = 0; // died (by underpopulation)
          } else if (neighbours > 3) {
            grid[j][k] = 0; // died (by overpopulation)
          }                 /*else {
                            // doesn't die
                          }*/
        } else {
          if (neighbours == 3) {
            grid[j][k] = 1; // alive (by reproduction)
          }
        }
      }
    }

    displayGrid(grid, N);
  }

  // delete
  for (int i = 0; i < N; i++)
    delete[] grid[i];
  delete[] grid;
}