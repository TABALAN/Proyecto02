#pragma once
#include <iostream>
#include <string>
#include "Carta.h"
#include "planta.h"
class Fungicida : public Carta
{
public:

	Fungicida(string tipoCarta, string color) : Carta(tipoCarta, color) {}

	void eliminarFungicida(Fungicida* cartaFungicida);

	bool aplicarFungicida(Planta* plantaProteger, Fungicida* fungicidaAplicado);

	void mostrarInformacion() override;

	bool seAplicoFungicida() { return true; }

};