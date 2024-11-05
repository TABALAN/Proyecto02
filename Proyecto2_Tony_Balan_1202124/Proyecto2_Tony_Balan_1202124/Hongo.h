#pragma once
#include <iostream>
#include <string>
#include "Carta.h"

class Planta; //Declaración anticipada

class Hongo : public Carta
{
protected:
	int gradoLetal;
	bool letalidad = false;

public:
	Hongo(string tipoCarta, string color, int grado, bool fatal) :Carta(tipoCarta, color), gradoLetal(grado), letalidad(fatal) {}

	void mostrarInformacion() override;

	bool aplicarHongo(Planta* plantaAtacar, Hongo* hongoAtacante);

	void eliminarHongo(Hongo* hongoAtacante);

	int getGradoHongo() { return gradoLetal; }

	bool getLetalidad() { return letalidad; }

	bool esFatal();

	bool seAplicoHongo() { return true; }
};

