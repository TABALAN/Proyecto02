#pragma once
#include <iostream>
#include <string>
#include "Planta.h"
#include "Carta.h"
using namespace std;
class Abono: public Carta
{
public:
	Abono(string tipo, string color) : Carta(tipo, color) {}

	void eliminarAbono(Abono* cartaAbono);

	bool aplicarAbono(Planta* plantaObjetivo, Abono* abonoAplicado);

	void mostrarInformacion() override;

	string getColorAbono() { return color; }

	bool abonoAplicadoExitosamente() { return true; }
};

