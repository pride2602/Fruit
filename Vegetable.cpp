#include "Vegetable.h"

Vegetable::Vegetable(int salt) : _salt(salt)
{
}

void Vegetable::Show() { cout << "Basic Vegetable salt: " << _salt << endl; }

Potato::Potato(int salt, int starch) : Vegetable(salt), _starch(starch)
{
}

void Potato::Show()
{
    cout << " Potato, starch: " << _starch << " salt per 100g: " << _salt << endl;
}

Tomato::Tomato(int salt, string shape) : Vegetable(salt), _shape(shape)
{
}

void Tomato::Show()
{
    cout << " Tomato, form: " << _shape << " salt per 100g: " << _salt << endl;
}
