bin/programa : src/main.cpp include/Foco.hpp include/EstadoFoco.hpp	
	c++ src/main.cpp -o bin/programa -I include

run : bin/programa
	.bin/programa

bin/memoria : src/memoria.cpp
	c++ src/memoria.cpp -o bin/memoria

runMemoria : bin/memoria
	./bin/memoria

bin/ejemplo : src/ejemplo.cpp
	c++ src/ejemplo.cpp -o bin/ejemplo -lftxui-screen -lftxui-dom -lftxui-component	

runEjemplo : bin/ejemplo
	./bin/ejemplo

bin/animacion : src/animacion.cpp include/*.hpp
	@mkdir -p bin
	g++ -Iinclude -o bin/animacion src/animacion.cpp -lftxui-component -lftxui-dom -lftxui-screen

runanimacion : bin/animacion
	./bin/animacion