#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>

using namespace std;

const int N = 16; // Size of the Sudoku grid (16x16)
vector<vector<int>> grid(N, vector<int>(N, 0)); // The Sudoku grid

// Use bitmasks to track which numbers are used in each row, column, and subgrid
array<int, N> rowUsed = {0};
array<int, N> colUsed = {0};  // i had to use bit to make it fater it was litrelly like the only way
array<int, N> boxUsed = {0};

vector<int> emptyCells; // Vector to store the positions of empty cells

// Precompute the subgrid indices for all cells to avoid redundant calculations
array<array<int, N>, N> boxIndex;

// Function to initialize the precomputed subgrid indices
void initializeBoxIndex() {
    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            boxIndex[row][col] = (row / 4) * 4 + (col / 4); // Calculate subgrid index for each cell
        }
    }
}

// Function to check if placing a number is safe (i.e., doesn't violate Sudoku rules) using bitwise operations
bool isSafe(int row, int col, int num)
{
    int bit = 1 << num; // Create a bitmask for the number `num` (e.g., 1 -> 2^1, 2 -> 2^2, etc.)
    // Check if the bit for `num` is set in any of the bitmasks for the row, column, or subgrid
    return !(rowUsed[row] & bit) && !(colUsed[col] & bit) && !(boxUsed[boxIndex[row][col]] & bit);
}

// Function to place a number in the grid and update tracking arrays using bitwise operations
void setNumber(int row, int col, int num)
{
    grid[row][col] = num;
    int bit = 1 << num; // Create a bitmask for the number `num`
    rowUsed[row] |= bit; // Set the corresponding bit in the row's bitmask
    colUsed[col] |= bit; // Set the corresponding bit in the column's bitmask
    boxUsed[boxIndex[row][col]] |= bit; // Set the corresponding bit in the subgrid's bitmask
}

// Function to remove a number from the grid and update tracking arrays using bitwise operations
void unsetNumber(int row, int col, int num)
{
    grid[row][col] = 0;
    int bit = 1 << num; // Create a bitmask for the number `num`
    rowUsed[row] &= ~bit; // Clear the corresponding bit in the row's bitmask
    colUsed[col] &= ~bit; // Clear the corresponding bit in the column's bitmask
    boxUsed[boxIndex[row][col]] &= ~bit; // Clear the corresponding bit in the subgrid's bitmask


}

// Function to count the possible numbers that can be placed in a given cell
int countPossibleNumbers(int row, int col)
{
    int count = 0;
    // Combine the row, column, and subgrid bitmasks to find out which numbers are already used
    int used = rowUsed[row] | colUsed[col] | boxUsed[boxIndex[row][col]];
    for (int num = 1; num <= N; ++num)
    {
        // Check if the bit for `num` is not set (i.e., the number is not used)
        if (!(used & (1 << num)))
        {
            count++;
        }
    }
    return count;
}


// Function to get all possible numbers for a given cell
vector<int> getPossibleNumbers(int row, int col)
{
    vector<int> possible;
    // Combine the row, column, and subgrid bitmasks to find out which numbers are already used
    int used = rowUsed[row] | colUsed[col] | boxUsed[boxIndex[row][col]];
    for (int num = 1; num <= N; ++num)
    {
        // Check if the bit for `num` is not set (i.e., the number is not used)
        if (!(used & (1 << num)))
        {
            possible.push_back(num);
        }
    }
    return possible;
}



bool solve() {
    if (emptyCells.empty()) return true; // If no empty cells remain, the Sudoku is solved

    int minOptions = N + 1; // Minimum possible numbers that can be placed in a cell
    int bestIndex = -1; // Index of the cell with the least number of options

    // Find the empty cell with the least number of possible options
    for (int i = 0; i < emptyCells.size(); ++i)
    {
        int cell = emptyCells[i];
        int row = cell / N, col = cell % N;
        int options = countPossibleNumbers(row, col);

        if (options == 0) return false; // No valid options for this cell; trigger backtracking
        if (options < minOptions)
        {
            minOptions = options;
            bestIndex = i;
            if (options == 1) break; // Early exit if there's only one option
        }
    }

    // Retrieve the cell coordinates with the least number of options
    int cell = emptyCells[bestIndex];
    int row = cell / N, col = cell % N;

    // Get the list of all possible numbers for the current cell
    vector<int> possibleNumbers = getPossibleNumbers(row, col);

    // Swap the current cell to the end of the emptyCells vector for backtracking
    swap(emptyCells[bestIndex], emptyCells.back());
    emptyCells.pop_back();

    // Try each possible number
    for (int num : possibleNumbers)
    {
        setNumber(row, col, num); // Place the number in the grid

        if (solve()) return true; // If the recursive call solves the Sudoku, return true

        // Backtrack: Undo the previous move
        unsetNumber(row, col, num);
    }

    // Restore the cell back to emptyCells for further backtracking
    emptyCells.push_back(cell);
    swap(emptyCells[bestIndex], emptyCells.back());

    return false; // No valid solution found, trigger backtracking
}



// Function to convert hex character input to decimal number
int hexToDecimal(char ch)
{
    return (ch >= '1' && ch <= '9') ? ch - '0' : (ch >= 'A' && ch <= 'G') ? 10 + (ch - 'A') : 0;
}



// Function to convert decimal number to hex character for output
char decimalToHex(int num)
{
    return (num >= 1 && num <= 9) ? '0' + num : (num >= 10 && num <= 16) ? 'A' + (num - 10) : '0';
}



int main() {
    // Initialize precomputed box indices
    initializeBoxIndex();

    // Read the input grid and initialize the solver
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            char input;
            cin >> input;
            int num = hexToDecimal(input);
            if (num != 0) {
                setNumber(row, col, num); // Place number in grid if not empty
            } else {
                emptyCells.push_back(row * N + col); // Store empty cell position
            }
        }
    }

    if (solve()) {
        // Print the grid
        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                cout << decimalToHex(grid[row][col]);
                if (col < N - 1) cout << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No Solution" << endl;
    }
    return 0;
}
