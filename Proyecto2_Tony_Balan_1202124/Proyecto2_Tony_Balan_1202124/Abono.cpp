#include "pch.h"
#include "Abono.h"
#include "Planta.h"
#include <iostream>
#include <string>
using namespace std;

void Abono::mostrarInformacion()
{
	cout << "Carta de tipo: " << tipo << endl;
	cout << "Color del abono: " << color << endl;
	cout << endl;
}

bool Abono::aplicarAbono(Planta* plantaObjetivo, Abono* abonoAplicado)
{
	if (plantaObjetivo->getColorCarta() != abonoAplicado->getColorAbono())
	{
		cout << "No se puede aplicar el abono sobre la planta debido a que son de diferente color" << endl;
		return false;
	}
	else if (plantaObjetivo->tieneAbono() == true && plantaObjetivo->getColorPlanta() == abonoAplicado->getColorAbono())
	{
		cout << "La planta seleccionada ya tiene abono." << endl;
		return false;
	}
	else if (plantaObjetivo->getColorPlanta() == abonoAplicado->getColorAbono() && plantaObjetivo->tieneAbono() == false)
	{
		plantaObjetivo->setDarAbonoPlanta();
		eliminarAbono(abonoAplicado); //Se llama a sí mismo para eliminarse
		cout << "Abono aplicado correctamente..." << endl;
		return abonoAplicadoExitosamente();
	}
}

void Abono::eliminarAbono(Abono* abonoEliminar)
{
	delete abonoEliminar;
	abonoEliminar = nullptr;
}