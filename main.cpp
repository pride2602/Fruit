#include "Vegetable.h"
#include "Fruit.h"

int main()
{
    IFood* grocery[4];

    grocery[0] = new Apple(50, string("Green"));
    grocery[1] = new Banana(50, 10);
    grocery[2] = new Potato(10, 10);
    grocery[3] = new Tomato(10, string("cherry"));

    bool open = true;
    while (open)
    {
        cout << "Choose product : 1 - Apple, 2 - Banana, 3 - Potato, 4 - Tomato, 0 to quit" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            grocery[0]->Show();
            break;

        case 2:
            grocery[1]->Show();
            break;

        case 3:
            grocery[2]->Show();
            break;

        case 4:
            grocery[3]->Show();
            break;

        case 0:
            open = false;
            break;

        default:
            cout << "Choose product from 1 to 4 or 0 to quit" << endl;
            break;
        }
    }

    delete grocery[0];
    delete grocery[1];
    delete grocery[2];
    delete grocery[3];

    return 0;
}