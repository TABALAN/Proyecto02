#include "pch.h"
#include "Planta.h"
#include <string>
#include "Hongo.h"
using namespace std;

//Planta("planta", "rojo", false (abono), false (inmunidad), 0 (fungicidas), 0 (hongos), false (tiene hongo letal)
void Planta::mostrarInformacion()
{
	cout << "Carta tipo: " << tipo << endl;
	cout << "Color de la planta: " << color << endl;
	cout << "Abono: " << (tieneAbono() ? "Si" : "No") << endl;
	cout << "Inmunidad: " << (esInmune() ? "Si" : "No") << endl;
	cout << "Fungicidad aplicados: " << contadorFungicidas << endl;
	cout << "Hongos sobre la planta: " << hongosPuestos << endl;
	cout << "Hongo letal: " << (tieneLetal() ? "Si" : "No") << endl;
	cout << endl;
}

bool Planta::tieneAbono()
{
	return abono;
}

bool Planta::esInmune()
{
	return inmunidad;
}

bool Planta::tieneLetal()
{
	return infeccionLetal;
}

void Planta::eliminarPlantaHongo(Planta* plantaEliminar, Hongo* hongoAplicado)
{
	//Eliminar planta si tiene dos hongos acumulados y si no es inmune
	if (plantaEliminar->getContadorHongos() == 2 && plantaEliminar->getContadorFungicidas() == 0 && plantaEliminar->esInmune() == false)
	{
		//delete plantaEliminar;
		plantaEliminar = nullptr;
		haSidoEliminado();
		 
		cout << "Planta eliminada..." << endl;
		hongoAplicado->eliminarHongo(hongoAplicado);
		cout << endl;
	}
	else if (hongoAplicado->esFatal() == true && hongoAplicado->getGradoHongo() == 0) //Eliminar planta si el hongo aplicado es fatal
	{
		//delete plantaEliminar;
		plantaEliminar = nullptr;
		haSidoEliminado();

		cout << "Planta eliminada por hongo fatal..." << endl;
		hongoAplicado->eliminarHongo(hongoAplicado);
		cout << endl;
	}
	else if (hongoAplicado->getGradoHongo() == 2  && plantaEliminar->esInmune() == false) //Eliminar planta si no es inmune
	{
		//delete plantaEliminar;
		plantaEliminar = nullptr;
		haSidoEliminado();

		cout << "Planta eliminada por hongo grado 2..." << endl;
		hongoAplicado->eliminarHongo(hongoAplicado);
		cout << endl;
	}
	else
	{
		cout << "Hongo aplicado exitosamente..." << endl;
		cout << endl;
	}
}

void Planta::setAgregarHongos(int n, Planta* plantaHongos, Hongo* hongoAplicado) //Recibir como parametros el número aplicado de hongos y la planta a la que se aplicó para validar eliminación
{

	hongosPuestos = hongosPuestos + n; //Agrega el hongo
	eliminarPlantaHongo(plantaHongos, hongoAplicado);
}

int Planta::setAgregarHongosSiFungicidas(Planta* plantaHongos, Hongo* hongoAplicado)
{
	int nuevoNumeroFungicidas;
	nuevoNumeroFungicidas = plantaHongos->getContadorFungicidas() - hongoAplicado->getGradoHongo();

	if (nuevoNumeroFungicidas < 0)//Retornar un entero para suamar al contador de hongos
	{
		plantaHongos->setReiniciarContadorFungicidas();
		nuevoNumeroFungicidas = nuevoNumeroFungicidas * -1; //Este caso solo controla una posible excepción, pero según el flujo del juego no es aplicable
		return nuevoNumeroFungicidas;
	}
	else if (nuevoNumeroFungicidas == 0)
	{
		plantaHongos->setReiniciarContadorFungicidas();
		return nuevoNumeroFungicidas;
	}
	else if (nuevoNumeroFungicidas > 0)
	{
		plantaHongos->setActualizarContadorFungicidas(nuevoNumeroFungicidas);
		return 0;
	}
}