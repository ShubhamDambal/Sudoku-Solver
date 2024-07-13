document.addEventListener("DOMContentLoaded", function () {

    var arr = [];

    // Function to initialize the array arr
    function initializeArray() {
        for (var i = 0; i < 9; i++) {
            arr[i] = [];
            for (var j = 0; j < 9; j++) {
                arr[i][j] = document.getElementById(i * 9 + j);
            }
        }
    }

    var board = [];

    // Function to fill the Sudoku board
    function FillBoard(board) {
        for (var i = 0; i < 9; i++) {
            for (var j = 0; j < 9; j++) {
                if (board[i][j] != 0) {
                    arr[i][j].innerText = board[i][j];
                } else {
                    arr[i][j].innerText = '';
                }
            }
        }
    }

    // Function to check if a number can be placed at a position
    function isValid(board, row, col, num, n) {
        for (let x = 0; x < n; x++) {
            if (board[row][x] == num || board[x][col] == num) {
                return false;
            }
        }

        let rn = Math.sqrt(n);
        let sr = row - row % rn;
        let sc = col - col % rn;

        for (let x = sr; x < sr + rn; x++) {
            for (let y = sc; y < sc + rn; y++) {
                if (board[x][y] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    // Function to solve Sudoku recursively
    function SudokuSolver(board, row, col, n) {
        if (row == n) {
            FillBoard(board);
            return true;
        }

        if (col == n) {
            return SudokuSolver(board, row + 1, 0, n);
        }

        if (board[row][col] != 0) {
            return SudokuSolver(board, row, col + 1, n);
        }

        for (let num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num, n)) {
                board[row][col] = num;
                let subAns = SudokuSolver(board, row, col + 1, n);

                if (subAns) {
                    return true;
                }
                board[row][col] = 0;
            }
        }

        return false;
    }

    // Function to get a Sudoku puzzle from the server
    function getPuzzle() {
        var xhrRequest = new XMLHttpRequest();
        xhrRequest.onload = function () {
            var response = JSON.parse(xhrRequest.response);
            console.log(response);
            board = response.board;
            FillBoard(board);
        };
        xhrRequest.open('GET', 'https://sugoku.onrender.com/board?difficulty=easy');
        xhrRequest.send();
    }

    // Event listener for GetPuzzle button
    document.getElementById('GetPuzzle').addEventListener('click', function () {
        getPuzzle();
    });

    // Event listener for SolvePuzzle button
    document.getElementById('SolvePuzzle').addEventListener('click', function () {
        SudokuSolver(board, 0, 0, 9);
    });

    // Initialize array and get a puzzle when the page loads
    initializeArray();
});
