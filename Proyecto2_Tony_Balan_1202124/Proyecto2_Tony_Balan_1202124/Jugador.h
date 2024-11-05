#pragma once
#include <iostream>
#include <string>
#include "Carta.h"
#include "Jardin.h"
using namespace std;

class Jardin;

class Jugador
{
	struct ManoCartas
	{
		Carta* cartaJugador;
		ManoCartas* anterior;
		ManoCartas* siguiente;
	};
private:
	string Nombre;
	int numeroJugador;
	ManoCartas* cabeza = nullptr;
	ManoCartas* final = nullptr;
	Jardin jardin;
public:
	Jugador(string nombreJugador, int num) : Nombre(nombreJugador), numeroJugador(num) {}

	void insertarCartaAlFinal(Carta* cartaNueva);
	void eliminarCartaMano(const Carta& cartaEliminar);
	void imprimirMano();
	int getIdentificadorDelJugador() { return numeroJugador; }
	string getNombreJugador() { return Nombre; }
	int getNumeroJugador() { return numeroJugador; }
	void setJardinJugador(Jardin& jardinNuevo) { jardin = jardinNuevo; }
	void informacionJugador();
	Carta* cartaJugar(); 
	Carta* buscarCarta(int numeroCarta) const;
	Jardin& getJardin() { return jardin; }
	void imprimirJardin();
	void setNumeroJugador(int numeroAsignar) { numeroJugador = numeroAsignar; }
	void eliminarPrimeraCarta(); //si no puede jugar nada
};