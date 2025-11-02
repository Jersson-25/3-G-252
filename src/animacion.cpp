#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <Dibujo.hpp>
#include <GestorDibujos.hpp>

using namespace ftxui;

int main()
{
    // Crear la ventana (manteniendo el tamaño original)
    auto screen = Screen::Create(
        Dimension::Fixed(80),
        Dimension::Fixed(24));

    // Arte ASCII anterior: Barco Grande
    const std::vector<std::u32string> barco1 = {
        U" v  ~.    v            ",
        U" v          /|          ",
        U"            / |        v  ",
        U"  v        /__|__         ",
        U"       \\--------/         ",
        U"~~~~~~~~~~~~~~~~~~~`~~~~~~'~~~~~~~~~~~~~~~~~~~~"
    };

    // Arte ASCII: Ballena (antes velero_pequeno)
    const std::vector<std::u32string> ballena = {
        U" .                  ",
        U" :                  ",
        U" ___:____   |\"/\\/\"|  ",
        U" ,'       `.   \\ /   ",
        U" | O        \\___/ |   ",
        U"~^~^~^~^~^~^~^~^~^~^~^~^~"
    };

    // Arte ASCII: Peces/Boyas
    const std::vector<std::u32string> peces = {
        U" o "
    };

    GestorDibujos gestor;
    
    // ## Barcos Grandes: Color Negro
    gestor.Agregar(Dibujo(2, 1, barco1, ftxui::Color::Black));     // Barco 1 (índice 0)
    gestor.Agregar(Dibujo(10, 5, barco1, ftxui::Color::Black));  // Barco 2 (índice 1)
    gestor.Agregar(Dibujo(-10, 10, barco1, ftxui::Color::Black));    // Barco 3 (índice 2)
    gestor.Agregar(Dibujo(30, 1, barco1, ftxui::Color::Black));    // Barco 4 (índice 3)
    gestor.Agregar(Dibujo(-5, 18, barco1, ftxui::Color::Black));    // Barco 5 (índice 4)

    // ## Peces/Boyas: Color Azul (Movimiento Derecha a Izquierda)
    gestor.Agregar(Dibujo(70, 15, peces, ftxui::Color::Blue));    // Peces/Boyas 1 (índice 5)
    gestor.Agregar(Dibujo(15, 17, peces, ftxui::Color::Blue));    // Peces/Boyas 2 (índice 6)
    gestor.Agregar(Dibujo(55, 12, peces, ftxui::Color::Blue));   // Peces/Boyas 3 (índice 7)
    gestor.Agregar(Dibujo(35, 20, peces, ftxui::Color::Blue));    // Peces/Boyas 4 (índice 8)
    gestor.Agregar(Dibujo(5, 7, peces, ftxui::Color::Blue));     // Peces/Boyas 5 (índice 9)

    // ## Ballenas Azules (MÁXIMA SEPARACIÓN): Color Azul
    gestor.Agregar(Dibujo(20, 16, ballena, ftxui::Color::Blue)); // Ballena 1 (índice 10)
    gestor.Agregar(Dibujo(45, 18, ballena, ftxui::Color::Blue)); // Ballena 2 (índice 11)
    gestor.Agregar(Dibujo(70, 20, ballena, ftxui::Color::Blue)); // Ballena 3 (índice 12)

    int frames = 120;
    for (int frame = 0; frame < frames; ++frame)
    {
        // Limpia la pantalla
        screen.Clear();

        // --- Barcos Grandes: Movimiento Izquierda a Derecha ---
        gestor.dibujos[0].x = 2 + (frame % 15);
        gestor.dibujos[1].x = 10 + (frame % 10);
        gestor.dibujos[2].x = -10 + (frame % 20);
        gestor.dibujos[3].x = 30 + (frame % 12);
        
        // Barco 5 (índice 4): SOLO MOVIMIENTO HORIZONTAL
        gestor.dibujos[4].x = -5 + (frame % 18);
        // Se ELIMINÓ la línea: gestor.dibujos[4].y = 18 + (frame % 3);

        // Animación del Pez/Boya 1 (índice 5) - Mantiene Derecha a Izquierda
        gestor.dibujos[5].x = 70 - (frame % 25); 
        
        // Animación de las Ballenas Azules (índices 10 a 12) - Mantiene Derecha a Izquierda
        gestor.dibujos[10].x = 20 - (frame % 5);
        gestor.dibujos[11].x = 45 - (frame % 8);
        gestor.dibujos[12].x = 70 - (frame % 10);

        gestor.DibujarTodos(screen);

        // Imprime la pantalla y resetea el cursor
        std::cout << screen.ToString();
        std::cout << screen.ResetPosition();
        std::cout << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
    return 0;
}