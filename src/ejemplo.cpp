#include <iostream>
using namespace std;
#include <string>
#include <thread>
#include <chrono>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
using namespace ftxui;


string nave =
string("       ___        \n")+
string("   ___/   \\___   \n")+
string("  /   '---'   \\  \n")+
string("  '--_______--'   \n")+
string("       / \\       \n")+
string("      /   \\      \n")+
string("     / \\O/ \\     \n")+
string("    /   |   \\      \n")+
string("   /   /\\    \\      \n");

int main()
{
    auto pantalla = Screen::Create(
        Dimension::Full(),
        Dimension::Fixed(10));
    int x = 4;
    int y = 0;

    while (true)
    {
        x++;
        
        stringstream ss(nave);
        string linea;
        int noLinea = 0;
        while (getline(ss, linea))
        {
            int columna = 0;
            for (auto &&letra : linea)
            {
                auto &pixel = pantalla.PixelAt(x + columna, y + noLinea);
                pixel.character = letra;
                columna++;
            }
            noLinea++;
        }
        pantalla.Print();
        pantalla.Clear();
        this_thread::sleep_for(chrono::microseconds(500000));
        cout << pantalla.ResetPosition();
    }
    return 0;
}