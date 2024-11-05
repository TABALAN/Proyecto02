#pragma once
#include <iostream>
#include <string>
using namespace std;

class Carta
{
protected:
	string tipo;
	string color;

public:
	Carta(string tipoCarta, string Color): tipo(tipoCarta), color(Color) {};
	virtual ~Carta() = default;

	//Método virtual
	virtual void mostrarInformacion() {};

	string getColorCarta() { return color; }
};