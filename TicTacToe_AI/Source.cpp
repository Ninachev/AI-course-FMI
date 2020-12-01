#include<iostream>
#include<algorithm>
#include<ctime>
#include<chrono>
using namespace std;

void print(char board[][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
int evaluate(char board[][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			if (board[i][0] == 'O')return -10;
			else if (board[i][0] == 'X')return +10;
		}
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			if (board[0][i] == 'O')return -10;
			else if (board[0][i] == 'X')return +10;
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		if (board[0][0] == 'O')return -10;
		else if (board[0][0] == 'X')return +10;
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		if (board[0][2] == 'O')return -10;
		else if (board[0][2] == 'X')return +10;
	}
	return 0;
}
bool areMovesLeft(char board[][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board[i][j] == '-')return true;
		}
	}
	return false;
}

int minimax(char board[][3], int depth,int alpha, int beta, bool isMaximazing)
{
	int score = evaluate(board);
	if (score ==  10)
	{
		return score - depth;
	}
	else if (score == -10)
	{
		return score + depth;
	}
	if (!areMovesLeft(board))return 0;
	if (isMaximazing)
	{
		int bestScore = -1000;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (board[i][j] == '-')
				{
					board[i][j] = 'X';
					score = minimax(board, depth + 1, alpha, beta, false);
					board[i][j] = '-';
					bestScore = max(score, bestScore);
					alpha = max(alpha, bestScore);
					if (beta <= alpha)break;
					
				}
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 1000;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (board[i][j] == '-')
				{
					board[i][j] = 'O';
					score = minimax(board, depth + 1, alpha, beta, true);
					board[i][j] = '-';
					bestScore = min(score, bestScore);
					beta = min(bestScore, beta);
					if (beta <= alpha)break;
				}
			}
		}
		return bestScore;
	}
}

void fillBoard(char board[][3])
{
	int row = -1;
	int col = -1;
	int bestVal = -1000;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board[i][j] == '-')
			{
				board[i][j] = 'X';
				int moveVal = minimax(board, 0, -1000, 1000, false);
				board[i][j] = '-';

				if (moveVal > bestVal)
				{
					row = i;
					col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	board[row][col] = 'X';
}
int main()
{
	cout << "Who should go first? (0 : computer |  1: player )" << endl;
	int row = 0, col = 0, n;
	cin >> n;
	srand((unsigned)time(0));
	using namespace std::chrono;
	char board[3][3] = { '-','-','-',
						 '-','-','-',
						 '-','-','-',};
	if (n == 0) 
	{
		auto start = std::chrono::high_resolution_clock::now();
		fillBoard(board);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		double time_elapsed = double(duration.count());
		print(board);
		cout << endl << "Time elapsed in microseconds: " << time_elapsed << endl;
	}
	while (areMovesLeft(board))
	{
		cin >> row >> col;
		if (board[row - 1][col - 1] == '-')board[row - 1][col - 1] = 'O';
		else continue;
		auto start = std::chrono::high_resolution_clock::now();
		fillBoard(board);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		double time_elapsed = double(duration.count());
		print(board);
		cout << endl << "Time elapsed in microseconds: " << time_elapsed << endl;
	}
	cin >> n;
}