#include <iostream>
#include <Windows.h>

using namespace std;

class Game
{
public:
    // Print field
    void print()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << game_field[i][j] << "\t";
            }
            cout << "\n\n";
        }
    }

    void generate_field()
    {
        int new_value = 0, n = 0;
        bool a = false;

        srand(time(0));

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {

                do
                {
                    new_value = n + rand() % 15;
                    a = check_for_repeate(game_field, new_value);
                } while (!a);

                if (new_value == 0) // we need only one 0 so, next generations starts with 1
                {
                    n = 1;
                }

                game_field[i][j] = new_value;
            }
        }
    }

    bool logic()
    {
        int a, x, y, x0, y0;
        cout << "Enter number for switch\n";
        cin >> a;
        if (a <= 0 || a > 15)
        {
            return false;
        }

        bool check_for_zero = find_elem(0, x0, y0); // get 0 postion
        if (!check_for_zero)
        {
            return false;
        }

        bool check_for_move = find_elem(a, x, y); // get position of enter number
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
                if (game_field[i][j] != correct_field[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

private:
    int game_field[4][4];
    const int correct_field[4][4] = {{1, 2, 3, 4},
                                     {5, 6, 7, 8},
                                     {9, 10, 11, 12},
                                     {13, 14, 15}};

    bool check_for_repeate(int (&x)[4][4], int a)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (x[i][j] == a && a == 0) // if a is 0 we allow to stay
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
    bool find_elem(int a, int &x, int &y)
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
};

int main(int argc, char *argv[])
{
    Game new_game;
    new_game.generate_field();

    new_game.print();

    bool a = false;

    do
    {
        a = new_game.logic();
        system("cls");
        new_game.print();

    } while (!a);

    cout << "You win! Congrats!";
    system("pause");

    return 0;
}