#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void start_screen();
void clear_screen();
void exit_program(char** map, int height);
void city_map_generation(int n, int m, char** map);
void clear_input_buffer();
void create_empty_map(char**& map, int width, int height);
void start_program(char** map);
void print_map(char** map, int width, int height);
void street(char** map, int map_height, int map_width, int direction, int costam); // 1 - right, 0 - left, 2 - down, 3 - up
void dfs(int x, int y, char** map, int cols, int rows, bool* visited, int last_x, int last_y);
bool check_if_left(int x, int y, char** map);
bool check_if_right(int x, int y, char** map, int max_width);
bool check_if_up(int x, int y, char** map);
bool check_if_down(int x, int y, char** map, int max_height);
void supply_network_screen();
int check_input(int min_val, int max_val);


int main() {
	srand(time(nullptr));
	char** map = nullptr;
	start_screen();
	const int choice = check_input(1, 2);
	if (choice == 2) {
		exit_program(map, 0);
	}
	else if (choice == 1) {
		start_program(map);
	}
}

void start_program(char** map) {
	clear_screen();
	cout << "Please enter map dimensions :" << endl;
	cout << "Width : ";
	const int col = check_input(2, 100);
	cout << "Height : ";
	const int row = check_input(2, 100);
	const int width = (col * 6);
	const int height = (row * 4);
	int enter;
	int counting_cities;
	create_empty_map(map, width, height);
	const auto visited = new bool[col * row] { false };
	do {
		counting_cities = 0;
		create_empty_map(map, width, height);
		city_map_generation(col, row, map);
		print_map(map, width, height);

		dfs(0, 0, map, col, row, visited, -1, -1);
		for (int i = 0; i < col * row; i++) {
			if (visited[i] == 1)
				counting_cities++;
		}
		if (counting_cities != col * row) 
			clear_screen();
		
	} while (counting_cities != col * row);
	supply_network_screen();
	cin >> enter;
	if (enter == 1) {
		clear_screen();
		print_map(map, width, height);
	}
	delete[] visited;
	exit_program(map,height);
}

void create_empty_map(char**& map, const int width, const int height) {
	map = new char* [height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
		for (int j = 0; j < width; j++) 
			map[i][j] = ' ';
	}
}

void city_map_generation(const int n, const int m, char** map) {
	const int max_width = (n * 6 - 6);
	const int max_height = (m * 4 - 4);
	int city_number = 0;
	for (int map_height = 0; map_height < m * 4; map_height++) {
		for (int map_width = 0; map_width < n * 6; map_width++) {
			if ((map_height % 4 == 0) && (map_width % 6 == 0)) {
				map[map_height][map_width] = static_cast<char>(65 + city_number);
				city_number = ++city_number % 26;
			}

			if ((map_height % 4 == 0) && map_width < max_width && ((map_width % 6 == 0))) {
				if (rand() % 9 < 8) {
					street(map, map_height, map_width, 1, 1);
				}
				else {
					street(map, map_height, map_width, 1, 0);
				}

				if ((rand() % 9 < 8) && map_width != 0) {
					street(map, map_height, map_width, 0, 1);
				}
				else if (map_width != 0) {
					street(map, map_height, map_width, 0, 0);
				}
			}

			if ((map_width % 6 == 0) && (map_height % 4 == 0) && (map_height < max_height)) {
				if (rand() % 9 < 8) {
					street(map, map_height, map_width, 2, 1);
				}
				else {
					street(map, map_height, map_width, 2, 0);
				}

				if ((rand() % 9 < 8) && map_height != 0) {
					street(map, map_height, map_width, 3, 1);
				}
				else if (map_height != 0) {
					street(map, map_height, map_width, 3, 0);
				}
			}
			else if ((map_height % 4 != 0 && map_width % 6 != 0) || map_height > max_height || map_width > max_width) {
				map[map_height][map_width] = ' ';
			}
		}
	}

	for (int map_height = 0; map_height < m * 4; map_height++) {
		for (int map_width = 0; map_width < n * 6; map_width++) {
			if ((map_height % 4 == 0) && (map_width % 6 == 0) && map_width != max_width && map_height != max_height && map[map_height + 1][map_width] == ' ' && map[map_height][map_width + 1] == ' ') {
				if (rand() % 9 < 5) {
					street(map, map_height, map_width, 2, 1);
				}
				else {
					street(map, map_height, map_width, 1, 1);
				}
			}
			else if ((map_height % 4 == 0) && (map_width % 6 == 0) && map_width != 0 && map_height != 0 && map[map_height][map_width - 1] == ' ' && map[map_height - 1][map_width] == ' ') {
				if (rand() % 9 < 5) {
					street(map, map_height, map_width, 3, 1);
				}
				else {
					street(map, map_height, map_width, 0, 1);
				}
			}
		}
	}
}

void street(char** map, const int map_height, const int map_width, const int direction, const int costam) {
	if (direction == 1) {
		for (int i = 1; i < 6; i++) {
			if (costam == 1)
				map[map_height][map_width + i] = '-';
			else {
				map[map_height][map_width + i] = ' ';
			}
		}
	}
	else if (direction == 0) {
		for (int i = 1; i < 6; i++) {
			if (costam == 1)
				map[map_height][map_width - i] = '-';
			else {
				map[map_height][map_width - i] = ' ';
			}
		}
	}
	else if (direction == 2) {
		for (int i = 1; i < 4; i++) {
			if (costam == 1)
				map[map_height + i][map_width] = '|';
			else {
				map[map_height + i][map_width] = ' ';
			}
		}
	}
	else if (direction == 3) {
		for (int i = 1; i < 4; i++) {
			if (costam == 1)
				map[map_height - i][map_width] = '|';
			else {
				map[map_height - i][map_width] = ' ';
			}
		}
	}
}

void dfs(const int x, const int y, char** map, const int cols, const int rows, bool* visited, const int last_x, const int last_y) {
	const int max_width = (cols * 6 - 6);
	const int max_height = (rows * 4 - 4);
	visited[x + y * cols] = true;
	bool moved = false;

	if (check_if_left(x, y, map) and !visited[x - 1 + y * cols]) {
		for (int i = 0; i < 5; i++)
			map[y * 4][x * 6 - i - 1] = '=';
		dfs(x - 1, y, map, cols, rows, visited, x, y);
		moved = true;
	}
	if (check_if_down(x, y, map, max_height) and !visited[x + (y + 1) * cols]) {
		for (int i = 0; i < 3; i++)
			map[y * 4 + i + 1][x * 6] = static_cast<char>(186);
		dfs(x, y + 1, map, cols, rows, visited, x, y);
		moved = true;
	}
	if (check_if_right(x, y, map, max_width) and !visited[x + 1 + y * cols]) {
		for (int i = 0; i < 5; i++) 
			map[y * 4][x * 6 + i + 1] = '=';
		dfs(x + 1, y, map, cols, rows, visited, x, y);
		moved = true;
	}
	if (check_if_up(x, y, map) and !visited[x + (y - 1) * cols]) {
		for (int i = 0; i < 3; i++)
			map[y * 4 - i - 1][x * 6] = static_cast<char>(186);
		dfs(x, y - 1, map, cols, rows, visited, x, y);
		moved = true;
	}
	if (!moved && last_x != -1 && last_y != -1) {
		dfs(last_x, last_y, map, cols, rows, visited, -1, -1);
	}
}

bool check_if_left(const int x, const int y, char** map) {
	if (x != 0 and x * 6 - 1 > 0) {
		if (map[y * 4][x * 6 - 1] == '-')
			return true;
	}
	return false;
}

bool check_if_right(const int x, const int y, char** map, const int max_width) {
	if (x * 6 + 1 <= max_width) {
		if (map[y * 4][x * 6 + 1] == '-') 
			return true;
	}
	return false;
}

bool check_if_up(const int x, const int y, char** map) {
	if (y != 0 and y * 4 - 1 > 0) {
		if (map[y * 4 - 1][x * 6] == '|') 
			return true;
	}
	return false;
}

bool check_if_down(const int x, const int y, char** map, const int max_height) {
	if (y * 4 - 1 <= max_height) {
		if (map[y * 4 + 1][x * 6] == '|') {
			return true;
		}
	}
	return false;
}

void supply_network_screen() {
	cout << "---------------------------------------------------------------------------------------------------- " << endl;
	cout << "All cities are connected at least with one road. To connect cities with water supply network, press 1 " << endl;
	cout << "---------------------------------------------------------------------------------------------------- " << endl;
}

void print_map(char** map, const int width, const int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (static_cast<int>(map[i][j]) >= 65 && static_cast<int>(map[i][j]) <= 90)
			{
				cout << "\033[92m" << map[i][j] << "\033[0m"; // Red, Reset
			}
			else if (map[i][j] == '-' || map[i][j] == '|')
			{
				cout << "\033[37m" << map[i][j] << "\033[0m"; // Green, Reset
			}
			else if (map[i][j] == '=') {
				cout << "\033[36m" << map[i][j] << "\033[0m"; // Cyan, Reset
			}
			else if (map[i][j] == char(186)) {
				cout << "\033[36m" << map[i][j] << "\033[0m"; // Blue, Reset
			}
			else if (map[i][j] == ' ') {
				cout << "\033[37m" << map[i][j] << "\033[0m"; // White, Reset
			}
			else
			{
				cout << map[i][j];
			}



		}
		cout << endl;
	}
}

void clear_input_buffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int check_input(const int min_val, const int max_val) {
	int input;
	bool is_valid_input = false;
	do {
		if (!(cin >> input)) {
			cout << "Invalid input. Please try again." << endl;
			clear_input_buffer();
		}
		else if (input < min_val || input > max_val) {
			cout << "Input out of range. Please enter a value between "
				<< min_val << " and " << max_val << endl;
		}
		else {
			is_valid_input = true;
		}
	} while (!is_valid_input);
	clear_input_buffer(); // Clear input buffer for next input
	return input;
}

void exit_program(char** map, const int height) {
	for (int i = 0; i < height; i++)
		delete[] map[i];
	delete[] map;
	cout << "End of program" << endl;
	exit(0);
}

void start_screen() {
	cout << "\033[31m" << " _    _       _           ______ _                 " << endl; // Red
	cout << "\033[33m" << "| |  | |     | |          | ___ (_)                " << endl; // Yellow
	cout << "\033[32m" << "| |  | | __ _| |_ ___ _ __| |_/ /_ _ __   ___  ___ " << endl; // Green
	cout << "\033[34m" << "| |\\/| |/ _` | __/ _ \\ '__|  __/| | '_ \\ / _ \\/ __|" << endl; // Blue
	cout << "\033[35m" << "\\  /\\  / (_| | ||  __/ |  | |   | | |_) |  __/\\__ \\" << endl; // Magenta
	cout << "\033[36m" << " \\/  \\/ \\__,_|\\__\\___|_|  \\_|   |_| .__/ \\___||___/" << endl; // Cyan
	cout << "\033[31m" << "Tomasz Nazar     197613    ACiR3  | |              " << endl; // Red
	cout << "\033[33m" << "Lukasz Orluk     197641    ACiR3  |_|              " << endl << endl; // Yellow
	cout << "\033[32m" << "Choose option :" << "\033[0m" << endl; //Green, Reset
	cout << "1. Run program" << endl;
	cout << "2. Exit" << endl;
}

void clear_screen() {
#ifdef  _WIN32
	system("cls");
#else
	system("clear");
#endif
}
