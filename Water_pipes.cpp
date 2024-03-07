#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;
sd
struct node
{
	int x;
	int y;
	node* left;
	node* right;
	bool visited;
};

void start_screen();
void clear_screen();
void exit_program(char** map, int height);
void city_map_generation(int n, int m, char** map);
void clear_input_buffer();
void create_empty_map(char**& map, int width, int height);
void start_program(char** map);
void print_map(char** map, int width, int height);
void fill_nodes(node* nodes, int n, int m);
void dfs(node* current);
void street(char** map, int map_height, int map_width, int direction, int costam); // 1 - right, 0 - left, 2 - down, 3 - up


int check_input(int min_val, int max_val) {
	int input{};
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

int main()
{
	srand(time(nullptr));
	char** map = nullptr;
	start_screen();
	const int choice = check_input(1, 2);
	if (choice == 2)
	{
		exit_program(map, 0);
	}
	else if (choice == 1)
	{
		start_program(map);
	}
}

void start_program(char** map)
{
	clear_screen();
	cout << "Please enter map dimensions :" << endl;
	cout << "Width : ";
	const int col = check_input(2, 100);
	cout << "Height : ";
	const int row = check_input(2, 100);
	auto nodes = new node[col * row];
	const int width = (col * 6);
	const int height = (row * 4);
	create_empty_map(map, width, height);
	city_map_generation(col, row, map);
	fill_nodes(nodes, row, col);
	dfs(&nodes[0]);
	print_map(map, width, height);

	for (int i = 0; i < (col * row);i++)
	{
		cout << nodes[i].x << ',' << nodes[i].y <<  endl;
	}
}

void create_empty_map(char**& map, const int width, const int height)
{
	map = new char* [height];
	for (int i = 0; i < height; i++)
	{
		map[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = ' ';
		}
	}
}

void city_map_generation(const int n, const int m, char** map)
{
	const int max_width = (n * 6 - 6);
	const int max_height = (m * 4 - 4);
	int city_number = 0;
	for (int map_height = 0; map_height < m * 4; map_height++)
	{
		for (int map_width = 0; map_width < n * 6; map_width++)
		{
			if ((map_height % 4 == 0) && (map_width % 6 == 0))
			{
				map[map_height][map_width] = static_cast<char>(65 + city_number);
				city_number = ++city_number % 26;
			}

			if ((map_height % 4 == 0) && map_width < max_width && ((map_width % 6 == 0)))
			{
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

			if ((map_width % 6 == 0) && (map_height % 4 == 0) && (map_height < max_height))
			{
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
			else if ((map_height % 4 != 0 && map_width % 6 != 0) || map_height > max_height || map_width > max_width)
			{
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

void street(char** map, const int map_height, const int map_width, const int direction, const int costam)
{
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

void fill_nodes(node* nodes, const int n, const int m) {
	char city_number = 0;
	int z = 0;
	for (int i = 0; i < n * m; i++) 
	{
		for (int j = 0; j < n * m; j++)
		{
			
				nodes[i].x = i % n;
				nodes[i].y = i / n;
				nodes[i].left = (i - 1 >= 0 && (i % n != 0)) ? &nodes[i - 1] : nullptr;
				nodes[i].right = (i + 1 < n * m && ((i + 1) % n != 0)) ? &nodes[i + 1] : nullptr;
				nodes[i].visited = false;
			
		}
		city_number++;
	}
}

void dfs(node* current) {
	if (current == nullptr || current->visited)
		return;

	// Mark the current node as visited
	current->visited = true;
	std::cout << "(" << current->x << ", " << current->y << ") ";

	// Recursively visit adjacent nodes
	if (current->left != nullptr && !current->left->visited)
		dfs(current->left);
	if (current->right != nullptr && !current->right->visited)
		dfs(current->right);
}

void connect_cities(char** map, int width, int height, node* nodes)
{

}

void print_map(char** map, const int width, const int height)
{
	clear_screen();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void clear_input_buffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void exit_program(char** map, const int height)
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}

	delete[] map;
	cout << "End of program" << endl;
	exit(0);
}

void start_screen()
{
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

void clear_screen()
{
#ifdef  _WIN32
	system("cls");
#else
	system("clear");
#endif
}