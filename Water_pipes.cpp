#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <ctime>
using namespace std;

void start_screen();
void clear_screen();
void exit_program();
//bool check_input(const int n, string type);
void city_map_generation(char numer_miasta, int n, int m, char map[][100]);
char get_valid_option(const char* valid_options);
void clear_input_buffer();

template<typename T>
T check_input(T min_val, T max_val) {
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
    const int choice = check_input<int>(1, 2);
    if (choice == 2)
    {
        exit_program();
    }
    else if (choice == 1)
    {
        string* city_map = nullptr;
        cout << "Wprowadz wymiary miasta:" << endl;
        cout << "Szerokosc max. 15 : ";
        int n = check_input<int>(2, 10);
        cout << "Wysokosc max. 15 : ";
        int m = check_input<int>(2, 10);

        char numer_miasta = 'a';
        char map[100][100];
        city_map_generation(numer_miasta, n, m, map);
    }


}

void city_map_generation(char numer_miasta, int n, int m, char map[][100])
{
    srand(time(NULL));
    int max_width = (n * 5 - 5);
    int max_height = (m * 5 - 5);
    for (int map_height = 0; map_height < m * 5; map_height++)
    {
        for (int map_width = 0; map_width < n * 5; map_width++)
        {
            if ((map_height % 5 == 0) && (map_width % 5 == 0))
            {
                map[map_height][map_width] = numer_miasta;
                numer_miasta++;
            }

            if ((map_height % 5 == 0) && map_width < max_width && ((map_width % 5 == 0)))
            {
                if (rand() % 9 < 8) {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height][map_width + i] = '-';
                    }
                }
                else
                {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height][map_width + i] = ' ';
                    }
                }

                if ((rand() % 9 < 8) && map_width != 0) {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height][map_width - i] = '-';
                    }
                }
                else if (map_width != 0)
                {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height][map_width - i] = ' ';
                    }
                }
            }

            if ((map_width % 5 == 0) && (map_height % 5 == 0) && (map_height < max_height))
            {
                if (rand() % 9 < 8) {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height + i][map_width] = '|';
                    }
                }
                else
                {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height + i][map_width] = ' ';
                    }
                }

                if ((rand() % 9 < 8) && map_height != 0) {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height - i][map_width] = '|';
                    }
                }
                else if (map_height != 0)
                {
                    for (int i = 1;i < 5;i++)
                    {
                        map[map_height - i][map_width] = ' ';
                    }
                }
            }
            else if ((map_height % 5 != 0 && map_width % 5 != 0) || map_height > max_height || map_width > max_width)
            {
                map[map_height][map_width] = ' ';
            }
        }
    }

    for (int map_height = 0; map_height < m * 5; map_height++)
    {
        for (int map_width = 0; map_width < n * 5; map_width++)
        {
            if ((map_height == 0 || map_height % 5 == 0) && (map_width == 0 || map_width % 5 == 0))
            {
                if (map[map_height + 1][map_width] == ' ' && map_height != max_height && map[map_height][map_width + 1] == ' ' && map_width != max_width)
                {
                    if (rand() % 9 < 5)
                    {
                        for (int i = 1;i < 5;i++)
                        {
                            map[map_height - i][map_width] = '|';
                        }
                    }
                    else
                    {
                        for (int i = 1;i < 5;i++)
                        {
                            map[map_height][map_width + i] = '-';
                        }
                    }
                }
                else if (map[map_height][map_width - 1] == ' ' && map_width != 0 && map[map_height - 1][map_width] == ' ' && map_height != 0)
                {
                    if (rand() % 9 < 5)
                    {
                        for (int i = 1;i < 5;i++)
                        {
                            map[map_height + i][map_width] = '|';
                        }
                    }
                    else
                    {
                        for (int i = 1;i < 5;i++)
                        {
                            map[map_height][map_width - i] = '-';
                        }
                    }

                }
            }
        }
    }




    for (int i = 0; i < m * 5; i++) {
        for (int j = 0; j < n * 5; j++) {
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