#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Carta.h"
#include <sstream>
#include "Planta.h"
#include "Hongo.h"
#include "Fungicida.h"
#include "Abono.h"
#include "Jugador.h"
#include "Jardin.h"
using namespace std;

class Juego
{
	struct jugadoresEnJuego
	{
		Jugador* jugadorActual;
		jugadoresEnJuego* siguiente;
		jugadoresEnJuego* anterior;
	};

private:
	vector <Carta*> pozoCartas;
	jugadoresEnJuego* cabeza = nullptr;
	jugadoresEnJuego* ultimo = nullptr;
	int numeroJugadoresPartida = 0; 

public:
	void creacionDelPool();
	void imprimirPozoCartas();
	void repartirCartas(vector <Carta*> &pozoCartas, Jugador* jugador);
	vector<Carta*>& getPozoCartas() { return pozoCartas; }
	void ingresarCantidadJugadores(int numeroJugadores); //Acá funcionará el get del número de jugadores
	void imprimirJugadoresPartida();
	void agregarNuevoJugador(Jugador* jugadorNuevo);
	void imprimirManodelJugador(int identificador);
	bool estaVacia() { return cabeza == nullptr; }
	Jugador* turnoJugador(int NumeroJugador);
	void mostrarJardines(int NumeroJugadorActual, int numeroJugadores);
	void mostrarJardinJugador(int jugadorMostrar);
	int getNumeroJugadoresPartida() { return numeroJugadoresPartida; }
	Carta* devolverCarta(vector<Carta*>& pozoCartas);
	void setNumeroJugadoresPartida(int n) { numeroJugadoresPartida = numeroJugadoresPartida + n; }
	void insertarNuevaCartaAlJugador(int numeroJugador, Carta* nuevaCarta);
	Jugador* jugadorObjetivoIntercambio(int numeroJugador);

	//Metodos para el hongo
	Jardin& getJardinJugador(int numeroJugador);
};

