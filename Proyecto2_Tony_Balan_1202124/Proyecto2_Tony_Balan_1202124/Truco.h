#pragma once
#include <iostream>
#include <string>
#include "Carta.h"
#include "Jardin.h"
#include "Jugador.h"
using namespace std;

class Truco : public Carta
{
protected:
	string subTipoCarta;
public:
	Truco(string tipoCarta, string color, string subtipo) : Carta(tipoCarta, color), subTipoCarta(subtipo) {}

	void mostrarInformacion() override;

	bool cambioDeJardin(Jardin& jardinJugadorActual,Jardin& jardinJugadorObjetivo, Jugador& jugadorActual, Jugador& jugadorObjetivo); //Intercambiar en la lista

	bool trasplantarPlanta(Planta* plantaObtenida, Jardin& jardinActual);

	string getSubtTipoCarta() { return subTipoCarta; }
};

