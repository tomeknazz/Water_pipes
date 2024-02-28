#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

void start_screen();
void clear_screen();
void exit_program();
//bool check_input(const int n, string type);
void city_map_generation();
char get_valid_option(const char* valid_options);
void clear_input_buffer();

template<typename T>
T check_input( T min_val ,T max_val) {
	T input;
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
	start_screen();
	const int choice = check_input<int>(1,2);
	if (choice == 2)
	{
		exit_program();
	}
	else if (choice == 1)
	{
		string* city_map = nullptr;
		cout << "Wprowadz wymiary miasta:" << endl;
		cout << "Szerokosc max. 10 : ";
		int n = check_input<int>(1,31);
		cout << "Wysokosc max. 20 : ";
		int m = check_input<int>(1,31);
		int numer_miasta = 0;

		
	}






}






void city_map_generation()
{

}

void clear_input_buffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
char get_valid_option(const char* valid_options) {
	char choice;
	do {
		cin >> choice;
		cin.ignore(10, '\n');
		if (strchr(valid_options, choice) == nullptr) {
			cout << "Invalid option. Please try again." << endl;
		}
	} while (strchr(valid_options, choice) == nullptr);
	return choice;
}


void exit_program()
{
	cout << "Koniec programu" << endl;
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
	cout << "\033[32m" << "Wybierz opcje:" << "\033[0m" << endl; //Green, Reset
	cout << "1. Rozpocznij program" << endl;
	cout << "2. Wyjscie" << endl;
}

void clear_screen()
{
#ifdef  _WIN32
	system("cls");
#else
	system("clear");
#endif
}
