//9x9 sudoku solver

#include <iostream>
#include <math.h>
using namespace std;

void print(int board[][9], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isValid(int board[][9], int row, int col, int num, int n){

    for(int x=0; x<n; x++){
        //row check
        if(board[row][x] == num){
            return false;
        }

        //col check
        if(board[x][col] == num){
            return false;
        }
    }

    //sub matrix check
    int rn = sqrt(n);
    int sr = row - row%rn; //starting index of row in submatrix
    int sc = col - col%rn; //starting index of col in submatrix

    for(int x=sr; x<sr+rn; x++){
        for(int y=sc; y<sc+rn; y++){
            if(board[x][y] == num){
                return false;
            }
        }
    }

    return true;

}


//i and j = starting point of board, n = size
bool sudokuSolver(int board[][9], int row, int col, int n){

    //Base Case
    if(row==n){
        print(board, n);
        return true;
    }
    
    //if we are not inside the board
    if(col==n){
        return sudokuSolver(board, row+1, 0, n);  //row+1 = next row, 0= 1st col
    }

    //if cell is alredy filled --> just move ahead
    if(board[row][col] != 0){
        return sudokuSolver(board, row, col+1, n);   //col+1 indicates next column
    }

    //we try to fill the cell with an appropriate number
    for(int num=1; num<=9; num++){
        //check is num can be filled
        if(isValid(board, row, col, num, n)){
            board[row][col] = num;
            bool subAns = sudokuSolver(board, row, col+1, n);

            if(subAns){
                return true;
            }
            //Backtracking --> undo the changes
            board[row][col] = 0;
        }
    }

    return false;  //not able to fill any no. between 1-9.

}

int main(){
    
    int n = 9;
    int board[9][9] = {
        {0, 0, 7, 1, 0, 0, 0, 6, 0},
        {1, 0, 5, 2, 0, 8, 0, 0, 0},
        {6, 0, 0, 0, 0, 7, 1, 2, 0},
        {3, 1, 2, 4, 0, 5, 0, 0, 8},
        {0, 0, 6, 0, 9, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 1},
        {0, 0, 1, 0, 0, 4, 9, 8, 6},
        {8, 0, 3, 9, 0, 6, 0, 0, 0},
        {0, 6, 0, 0, 8, 2, 7, 0, 3}
    };

    cout << "solved sudoku: " << endl;
    sudokuSolver(board, 0, 0, n);

    return 0;
}