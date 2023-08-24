#include <iostream>
#include <Windows.h>

using namespace std;

class Game
{

private:
    static const int x = 4;
    static const int y = 4;

    int game_field[x][y];
    const int correct_field[x][y] = {{1, 2, 3, 4},
                                     {5, 6, 7, 8},
                                     {9, 10, 11, 12},
                                     {13, 14, 15}};

    bool check_for_repeate(int a)
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                if (game_field[i][j] == a && a == 0) // if a is 0 we allow to stay
                {
                    return true;
                }
                else if (game_field[i][j] == a)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool find_elem(int a, int &xa, int &ya)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (game_field[i][j] == a)
                {
                    xa = i;
                    ya = j;
                    return 1;
                }
            }
        }
        return 0;
    }

public:
    // Print field
    void print()
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
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

        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {

                do
                {
                    new_value = n + rand() % 15;
                    a = check_for_repeate(new_value);
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
        int a, xa, ya, x0, y0;
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

        bool check_for_move = find_elem(a, xa, ya); // get position of enter number
        if (!check_for_move)
        {
            return false;
        }

        if (((xa - 1) == x0 && ya == y0) || (xa == x0 && ya + 1 == y0) || ((xa + 1) == x0 && ya == y0) || (xa == x0 && (ya - 1) == y0)) // check if numb near 0 on the field
        {
            game_field[x0][y0] = game_field[xa][ya]; // move numbers
            game_field[xa][ya] = 0;
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