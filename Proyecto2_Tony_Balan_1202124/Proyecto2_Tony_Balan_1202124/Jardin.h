#pragma once
#include <iostream>
#include <string>
#include "Carta.h"
#include "Planta.h"
using namespace std;

class Jugador;

class Jardin
{
	struct plantasJardin
	{
		Planta* planta;
		plantasJardin* siguiente;
		plantasJardin* anterior;
		plantasJardin(const Planta& planta) : planta(new Planta(planta)), siguiente(nullptr), anterior(nullptr) {}
	};
private:
	plantasJardin* cabeza;
	plantasJardin* ultimo;
	int contadorPlantas;
	int contadorPlantasGanadoras;

public:
	Jardin() : cabeza(nullptr), ultimo(nullptr), contadorPlantas(0), contadorPlantasGanadoras(0) {};

	bool agregarPlantaJardin(const Planta& plantaNueva);
	Planta* jugarSobrePlantaJardinHongo(int numeroPlanta);
	bool estaVacio() { return cabeza == nullptr; }
	void imprimirJardin();
	int getContadorPlantas() { return contadorPlantas; }
	void setSumarContadorPlantas(int n) { contadorPlantas = contadorPlantas + n; }
	void setReiniciarContadorPlantas() { contadorPlantas = 0; }
	bool seAgregoPlanta() { return true; }
	void eliminarPlantaNoValida();
	void contarPlantasJardin();
	Planta* ObtenerPlantaTrasplantar(int numeroPlanta);
	void desconectarPlanta(Planta* plantaQuitar);

	//Victoria
	bool comprobarVictoria();
	bool plantaRoja();
	bool plantaAzul();
	bool plantaAmarilla();
	void sumarPlantasGanadoras() { contadorPlantasGanadoras++; }
	void reiniciarConteoPlantasGanadoras() { contadorPlantasGanadoras = 0; }
	int getContadorPlantasGanadoras() { return contadorPlantasGanadoras; }
};