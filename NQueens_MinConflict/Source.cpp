#include<iostream>
#include<chrono>
#include<ctime>
using namespace std;

class Queens 
{
private:
	int n;
	int queens[30000] = { 0 };
	int queens_in_row[30000] = { 0 };
	int d1[2 * 30000 - 1] = { 0 };
	int d2[2 * 30000 - 1] = { 0 };
public:
	Queens(int a);
	void placeQueensRandomly();
	void placeQueensSmart();
	void clear();
	void print();
	int getRowFromMinConfRows(int col);
	int getPointConflicts(int row, int col);
	int getQueenFromMaxConflQueens();
	void solve();
	bool isSolved();
};

int main()
{
	srand(time(NULL));
	int n;
	cin >> n;
	Queens q(n);
	int answers[1000] = { 0 };
	using namespace std::chrono;
	auto start = std::chrono::high_resolution_clock::now();
	q.placeQueensSmart();
	q.solve();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	double time_elapsed = double(duration.count()) / 1000000;
	cout << endl << "Time elapsed in seconds: " << time_elapsed << endl;
	if (n < 28)q.print();
	cin >> n;

}

Queens::Queens(int a)
{
	n = a;
}

void Queens::placeQueensRandomly()
{
	for (int col = 0; col < n; col++)
	{
		queens[col] = rand() % n;
		queens_in_row[queens[col]]++;
		d1[col + queens[col]]++;
		d2[(n - 1) - (queens[col] - col)]++;
	}
}

void Queens::placeQueensSmart()
{
	for (int col = 0; col < n; col++)
	{
		queens[col] = getRowFromMinConfRows(col);
		queens_in_row[queens[col]]++;
		d1[col + queens[col]]++;
		d2[(n - 1) - (queens[col] - col)]++;
	}
}

void Queens::clear()
{
	for (int i = 0; i < 2*n - 1; i++)
	{
		d1[i] = 0;
		d2[i] = 0;
		if (i < n)
		{
			queens[i] = 0;
			queens_in_row[i] = 0;
		}
	}
}

void Queens::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (queens[j] == i) cout << " Q ";
			else cout << " . ";
		}
		cout << endl;
	}
}

int Queens::getRowFromMinConfRows(int col)
{
	int min_confl_row_so_far = n + 1;
	int current_row_conflicts = n + 1;
	int arr_min_cofl_rows[30000];
	int number_equal_min_confl_rows = 0;
	for (size_t row = 0; row < n; row++)
	{
		current_row_conflicts = getPointConflicts(row, col);
		if (current_row_conflicts < min_confl_row_so_far)
		{
			number_equal_min_confl_rows = 0;
			min_confl_row_so_far = current_row_conflicts;
			arr_min_cofl_rows[number_equal_min_confl_rows] = row;
		}
		else if (current_row_conflicts == min_confl_row_so_far)
		{
			number_equal_min_confl_rows++;
			arr_min_cofl_rows[number_equal_min_confl_rows] = row;
		}
	}
	return arr_min_cofl_rows[rand() % (number_equal_min_confl_rows + 1)];
}

int Queens::getPointConflicts(int row, int col)
{
	int queen_on_point_confl = 0;
	int other_queens_confl = queens_in_row[row] + d1[row + col] + d2[(n - 1) - (row - col)];
	if (row == queens[col] && (other_queens_confl >=3)) queen_on_point_confl = 3;
	return  other_queens_confl - queen_on_point_confl;
}

int Queens::getQueenFromMaxConflQueens()
{
	int arr_max_conf_queens[30000];
	int max_confl_so_far = -1;
	int number_equal_max_confl_queens = 0;
	int current_queens_confl = -1;
	for (size_t col = 0; col < n; col++)
	{
		current_queens_confl = getPointConflicts(queens[col], col);
		if (current_queens_confl > max_confl_so_far)
		{
			max_confl_so_far = current_queens_confl;
			number_equal_max_confl_queens = 0;
			arr_max_conf_queens[number_equal_max_confl_queens] = col;
		}
		else if (current_queens_confl == max_confl_so_far)
		{
			number_equal_max_confl_queens++;
			arr_max_conf_queens[number_equal_max_confl_queens] = col;
		}
	}
	return arr_max_conf_queens[rand() % (number_equal_max_confl_queens + 1)];
}

void Queens::solve()
{
	int queen_to_be_moved;
	int old_row;
	int new_row;
	int number_of_steps = 0;
	while (true)
	{
		if (isSolved())return;
		number_of_steps++;		
		queen_to_be_moved = getQueenFromMaxConflQueens();
		old_row = queens[queen_to_be_moved];
		new_row = getRowFromMinConfRows(queen_to_be_moved);
		if (old_row != new_row)
		{
			queens_in_row[old_row]--;
			d1[old_row + queen_to_be_moved]--;
			d2[(n - 1) - (old_row - queen_to_be_moved)]--;
			queens_in_row[new_row]++;
			d1[new_row + queen_to_be_moved]++;
			d2[(n - 1) - (new_row - queen_to_be_moved)]++;
			queens[queen_to_be_moved] = new_row;
		}
		if (number_of_steps >= n * 2)
		{
			this->clear();
			this->placeQueensSmart();
		}
	}
}

bool Queens::isSolved()
{
	int conflicts = 0;
	for (size_t col = 0; col < n; col++)
	{
		conflicts = getPointConflicts(queens[col], col);
		if (conflicts != 0) return false;
	}
	return true;
}
