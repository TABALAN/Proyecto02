#include "pch.h"
#include "Truco.h"
#include <string>
#include "Jardin.h"
#include "Jugador.h"
using namespace std;

void Truco::mostrarInformacion()
{
	if (subTipoCarta == "Trasplantar")
	{
		cout << "Carta tipo: " << tipo << endl;
		cout << "Habilidad: " << subTipoCarta << endl;
		cout << endl;
	}
	else if(subTipoCarta == "Intercambio")
	{
		cout << "Carta tipo: " << tipo << endl;
		cout << "Habilidad: " << subTipoCarta << endl;
		cout << endl;
	}
}

bool Truco::cambioDeJardin(Jardin& jardinJugadorActual, Jardin& jardinJugadorObjetivo, Jugador& jugadorActual, Jugador& jugadorObjetivo)
{
		Jardin jardinActual = jardinJugadorActual;
		Jardin jardinJugadorNuevo = jardinJugadorObjetivo;

		//Asignar jardines
		jugadorActual.setJardinJugador(jardinJugadorNuevo);
		jugadorObjetivo.setJardinJugador(jardinActual);
		return true;
}

bool Truco::trasplantarPlanta(Planta* plantaObtenida, Jardin& jardinActual)
{
	if (plantaObtenida != nullptr && jardinActual.getContadorPlantas() < 6)
	{
		jardinActual.agregarPlantaJardin(*plantaObtenida);
		return true;
	}
	else
	{
		cout << "No hay espacio suficiciente en el jardin para trasplantar..." << endl;
		cout << endl;
		return false;
	}
}