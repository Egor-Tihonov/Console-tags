#include <iostream>
#include <Windows.h>

using namespace std;

bool check_for_repeate(int (&)[4][4], int a);
void generate_field(int (&)[4][4]);
bool logic(int (&)[4][4], int (&)[4][4]);
bool find_elem_get_position(int (&)[4][4], int a, int &x, int &y);
void print(int (&)[4][4]);

int main(int argc, char *argv[])
{
    int correct_field[4][4] = {{1, 2, 3, 4},
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15}};
    int game_field[4][4];
    generate_field(game_field);

    print(game_field);

    bool a = false;

    do
    {
        a = logic(game_field, correct_field);
        system("cls");
        print(game_field);

    } while (!a);
    cout << "You win! Congrats!";
}

void print(int (&field)[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << field[i][j] << "\t";
        }
        cout << "\n\n";
    }
}

bool logic(int (&game_field)[4][4], int (&correct_field)[4][4])
{
    int a, x, y, x0, y0;
    cout << "Enter number for switch\n";
    cin >> a;
    if (a <= 0 || a > 15)
    {
        return false;
    }

    bool check_for_zero = find_elem_get_position(game_field, 0, x0, y0); // get 0 postion
    if (!check_for_zero)
    {
        return false;
    }

    bool check_for_move = find_elem_get_position(game_field, a, x, y); // get position of enter number
    if (!check_for_move)
    {
        return false;
    }

    if (((x - 1) == x0 && y == y0) || (x == x0 && y + 1 == y0) || ((x + 1) == x0 && y == y0) || (x == x0 && (y - 1) == y0)) // check if numb near 0 on the field
    {
        game_field[x0][y0] = game_field[x][y]; // move numbers
        game_field[x][y] = 0;
    }
    else
    {
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (game_field[i][j] == correct_field[i][j])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool find_elem_get_position(int (&game_field)[4][4], int a, int &x, int &y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (game_field[i][j] == a)
            {
                x = i;
                y = j;
                return 1;
            }
        }
    }
    return 0;
}

void generate_field(int (&new_game_field)[4][4])
{
    int new_value = 0, n = 0;
    bool a = false;

    srand(time(0));

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            // if (i == 2 && j == 1)
            // {
            //     new_game_field[i][j] = 0;
            //     continue;
            // }

            do
            {
                new_value = n + rand() % 15;
                a = check_for_repeate(new_game_field, new_value);
            } while (!a);

            if (new_value == 0)
            {
                n = 1;
            }

            new_game_field[i][j] = new_value;
        }
    }
}

bool check_for_repeate(int (&x)[4][4], int a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (x[i][j] == a && a == 0)
            {
                return true;
            }
            else if (x[i][j] == a)
            {
                return false;
            }
        }
    }
    return true;
}