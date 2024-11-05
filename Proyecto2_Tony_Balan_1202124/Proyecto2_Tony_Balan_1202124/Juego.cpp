#include "pch.h"
#include "Juego.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //para shffle
#include <random> //para random_device y mt19937
#include "Carta.h"
#include "Planta.h"
#include "Hongo.h"
#include "Fungicida.h"
#include "Abono.h"
#include "Jugador.h"
#include "Jardin.h"
#include "Truco.h"
using namespace std;

void Juego::creacionDelPool()
{
	//Crear y agregar las plantas rojas al vector
	int cantidadPlantasRojas = 4;
	for (int i = 0; i < cantidadPlantasRojas; i++)
	{
		pozoCartas.push_back(new Planta("planta", "rojo", false, false, 0, 0, false));
	}

	//Crear y agregar las plantas azules al vector
	int cantidadPlantasAzules = 4;
	for (int i = 0; i < cantidadPlantasAzules; i++)
	{
		pozoCartas.push_back(new Planta("planta", "azul", false, false, 0, 0, false));
	}

	//Crear y agregar las plantas amarillas al vector
	int cantidadPlantasAmarillas = 4;
	for (int i = 0; i < cantidadPlantasAmarillas; i++)
	{
		pozoCartas.push_back(new Planta("planta", "amarillo", false, false, 0, 0, false));
	}
	 //Crear hongos de grado 1
	int cantidadDeHongosGrado1 = 10;
	for (int i = 0; i < cantidadDeHongosGrado1; i++)
	{
		pozoCartas.push_back(new Hongo("hongo", "s/c", 1, false));
	}
	//Crear hongos de grado 2
	int cantidadDeHongosGrado2 = 5;
	for (int i = 0; i < cantidadDeHongosGrado2; i++)
	{
		pozoCartas.push_back(new Hongo("hongo", "s/c", 2, false));
	}
	//Crear hongos de grado fatal
	int cantidadDeHongosGradoFatal = 3;
	for (int i = 0; i < cantidadDeHongosGradoFatal; i++)
	{
		pozoCartas.push_back(new Hongo("hongo", "s/c", 0, true));
	}
	//Crear fungicida rojo
	int cantidadFungicidasRojos = 3;
	for (int i = 0; i < cantidadFungicidasRojos; i++)
	{
		pozoCartas.push_back(new Fungicida("fungicida", "rojo"));
	}
	//Crear fungicida azul
	int cantidadFungicidasAzul = 3;
	for (int i = 0; i < cantidadFungicidasAzul; i++)
	{
		pozoCartas.push_back(new Fungicida("fungicida", "azul"));
	}
	//Crear fungicida amarillo
	int cantidadFungicidasAmarillo = 3;
	for (int i = 0; i < cantidadFungicidasAmarillo; i++)
	{
		pozoCartas.push_back(new Fungicida("fungicida", "amarillo"));
	}
	//Crear abono de color rojo
	int cantidadAbonosRojo = 4;
	for (int i = 0; i < cantidadAbonosRojo; i++)
	{
		pozoCartas.push_back(new Abono("abono", "rojo"));
	}
	//Crear abono de color azul
	int cantidadAbonosAzul = 4;
	for (int i = 0; i < cantidadAbonosAzul; i++)
	{
		pozoCartas.push_back(new Abono("abono", "azul"));
	}
	//Crear abono de color amarillo
	int cantidadAbonosAmarillo = 4;
	for (int i = 0; i < cantidadAbonosAmarillo; i++)
	{
		pozoCartas.push_back(new Abono("abono", "amarillo"));
	}
	//Crear truco - intercambio de jardin
	int cantidadIntercambios = 3;
	for (int i = 0; i < cantidadIntercambios; i++)
	{
		pozoCartas.push_back(new Truco("Truco", "n/t", "Intercambio"));
	}
	//Crear truco - trasplantar
	int cantidadTrasplantar = 6;
	for (int i = 0; i < cantidadTrasplantar; i++)
	{
		pozoCartas.push_back(new Truco("Truco", "n/t", "Trasplantar"));
	}
	//Realizar mezcla de cartas antes de imprimir
	random_device mezcla;
	mt19937 g(mezcla());
	shuffle(pozoCartas.begin(), pozoCartas.end(), g);
}

void Juego::imprimirPozoCartas()
{
	int contador = 0;
	for (Carta* carta : pozoCartas)
	{
		carta->mostrarInformacion();
		contador++;
	}
	cout << "Hay: " << contador << " en total." << endl;
}

void Juego::repartirCartas(vector<Carta*>& pozoCartas, Jugador* jugador)
{
	for (int i = 0; i < 4; i++) //El ciclo es cuatro veces para darle específicamente 4 cartas
	{
		if (!pozoCartas.empty()) //Si no está vacía
		{
			Carta* cartaDar = pozoCartas.front(); //Toma la primer carta
			pozoCartas.erase(pozoCartas.begin()); //De una vez elimina la carta del pozo
			jugador->insertarCartaAlFinal(cartaDar); //El jugador recibe la carta
		}
		else
		{
			cout << "No hay cartas suficientes en el pozo de cartas..." << endl;
			break; 
		}
	}
}

Carta* Juego::devolverCarta(vector<Carta*>& pozoCartas)
{
	if (!pozoCartas.empty()) //Si no está vacía
	{
		Carta* cartaDar = pozoCartas.front(); //Toma la primer carta
		pozoCartas.erase(pozoCartas.begin()); //De una vez elimina la carta del pozo
		return cartaDar;
	}
	else
	{
		cout << "No hay cartas suficientes en el pozo de cartas..." << endl;
		return nullptr;
	}
}

void Juego::ingresarCantidadJugadores(int numeroJugadores)
{
	string nombreJugador;
	int numeroJugador = 0; ///Este podría ayudar a llevar un control de cómo imprimir la mano de un jugador

	for (int i = 0; i < numeroJugadores; i++)
	{
		numeroJugador++;
		setNumeroJugadoresPartida(1);
		cout << "Ingrese el nombre del jugador " << numeroJugador << ": " << endl;
		getline(cin, nombreJugador);
		Jugador* nuevoJugador = new Jugador(nombreJugador, numeroJugador);
		agregarNuevoJugador(nuevoJugador);
		nuevoJugador->setNumeroJugador(numeroJugador);
		repartirCartas(getPozoCartas(), nuevoJugador);
		cout << endl;
	}
	cout << "Jugadores ingresados con exito...." << endl;
	cout << endl;
}

void Juego::agregarNuevoJugador(Jugador* jugadorNuevo)
{
	jugadoresEnJuego* nuevoJugador = new jugadoresEnJuego{ jugadorNuevo, nullptr, nullptr };

	if (cabeza == nullptr)
	{
		cabeza = nuevoJugador;
		ultimo = nuevoJugador;
	}
	else
	{
		nuevoJugador->siguiente = cabeza; //El siguiente es hacia la derecha y anterior izquierda
		cabeza->anterior = nuevoJugador;
		cabeza = nuevoJugador;
	}
}

void Juego::imprimirManodelJugador(int identificador)
{
	jugadoresEnJuego* jugadorRecorrido = cabeza;

	while (jugadorRecorrido != nullptr)
	{
		if (jugadorRecorrido->jugadorActual->getIdentificadorDelJugador() == identificador) //En el caso sea diferente al primero
		{
			cout << "Mano de cartas de " << jugadorRecorrido->jugadorActual->getNombreJugador() << ": " << endl;
			cout << endl;
			jugadorRecorrido->jugadorActual->imprimirMano();
			cout << endl;
			return;
		}
		else
		{
			jugadorRecorrido = jugadorRecorrido->siguiente;
		}
	}
}

void Juego::imprimirJugadoresPartida()
{
	jugadoresEnJuego* jugadorRecorrido = ultimo;

	if (!estaVacia())
	{
		while (jugadorRecorrido != nullptr)
		{
			cout << endl;
			jugadorRecorrido->jugadorActual->informacionJugador();
			jugadorRecorrido = jugadorRecorrido->anterior;
		}
	}
	else
	{
		cout << "La lista de jugadores esta vacia..." << endl;
	}
	
	cout << endl;
}

Jugador* Juego::turnoJugador(int numeroJugador)
{
	jugadoresEnJuego* jugadorRecorrido = cabeza;
	while (jugadorRecorrido != nullptr)
	{
		if (jugadorRecorrido->jugadorActual->getNumeroJugador() == numeroJugador)
		{
			return jugadorRecorrido->jugadorActual;
		}
		else
		{
			jugadorRecorrido = jugadorRecorrido->siguiente;
		}
	}

	if (jugadorRecorrido == nullptr)
	{
		cout << "Jugador no encontrado..." << endl;
		return nullptr;
	}
}

Jugador* Juego::jugadorObjetivoIntercambio(int numeroJugador)
{
	jugadoresEnJuego* jugadorRecorrido = cabeza;
	while (jugadorRecorrido != nullptr)
	{
		if (jugadorRecorrido->jugadorActual->getNumeroJugador() == numeroJugador)
		{
			return jugadorRecorrido->jugadorActual;
		}
		else
		{
			jugadorRecorrido = jugadorRecorrido->siguiente;
		}
	}

	if (jugadorRecorrido == nullptr)
	{
		cout << "Jugador no encontrado..." << endl;
		return nullptr;
	}
}

void Juego::mostrarJardinJugador(int jugadorMostrar)
{
	jugadoresEnJuego* jugadorRecorrido = cabeza;

	while (jugadorRecorrido != nullptr)
	{
		if (jugadorRecorrido->jugadorActual->getNumeroJugador() == jugadorMostrar)
		{
			jugadorRecorrido->jugadorActual->imprimirJardin();
			return;
		}
		
		jugadorRecorrido = jugadorRecorrido->siguiente;
	}
}

void Juego::mostrarJardines(int numeroJugadorActual, int numeroJugadores) //Este parámetro debería obtenerse con el get de cada jugador
{
	if (numeroJugadores == 4)
	{
		if (numeroJugadorActual == 1)
		{
			mostrarJardinJugador(2);
			mostrarJardinJugador(3);
			mostrarJardinJugador(4);
		}
		else if (numeroJugadorActual == 2)
		{
			mostrarJardinJugador(1);
			mostrarJardinJugador(3);
			mostrarJardinJugador(4);
		}
		else if (numeroJugadorActual == 3)
		{
			mostrarJardinJugador(1);
			mostrarJardinJugador(2);
			mostrarJardinJugador(4);
		}
		else if (numeroJugadorActual == 4)
		{
			mostrarJardinJugador(1);
			mostrarJardinJugador(2);
			mostrarJardinJugador(3);
		}
	}
	else if (numeroJugadores == 3)
	{
		if (numeroJugadorActual == 1)
		{
			mostrarJardinJugador(2);
			mostrarJardinJugador(3);
		}
		else if (numeroJugadorActual == 2)
		{
			mostrarJardinJugador(1);
			mostrarJardinJugador(3);
		}
		else if (numeroJugadorActual == 3)
		{
			mostrarJardinJugador(1);
			mostrarJardinJugador(2);
		}
	}
	else if (numeroJugadores == 2)
	{
		if (numeroJugadorActual == 1)
		{
			mostrarJardinJugador(2);
		}
		else if (numeroJugadorActual == 2)
		{
			mostrarJardinJugador(1);
		}
	}
	else
	{
		cout << "Algo no esta bien..." << endl;
		cout << endl;
	}
}

Jardin& Juego::getJardinJugador(int numeroJugador)
{
	jugadoresEnJuego* jugadorRecorrido = cabeza;

	while (jugadorRecorrido != nullptr)
	{
		if (jugadorRecorrido->jugadorActual->getNumeroJugador() == numeroJugador)
		{
			return jugadorRecorrido->jugadorActual->getJardin();
		}
		
		jugadorRecorrido = jugadorRecorrido->siguiente;
	}

	throw runtime_error("Jugador no encontrado...");
}

void Juego::insertarNuevaCartaAlJugador(int numeroJugador, Carta* nuevaCarta)
{
	jugadoresEnJuego* jugadorRecorrido = cabeza;
	while (jugadorRecorrido != nullptr)
	{
		if (jugadorRecorrido->jugadorActual->getNumeroJugador() == numeroJugador)
		{
			jugadorRecorrido->jugadorActual->insertarCartaAlFinal(nuevaCarta);
			return;
		}
		else
		{
			jugadorRecorrido = jugadorRecorrido->siguiente;
		}
	}

	if (jugadorRecorrido == nullptr)
	{
		cout << "Jugador no encontrado..." << endl;
		return;
	}
}