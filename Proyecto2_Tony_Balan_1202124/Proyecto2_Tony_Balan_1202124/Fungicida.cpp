#include "pch.h"
#include "Fungicida.h"
#include "Planta.h"
#include <string>
using namespace std;

bool Fungicida::aplicarFungicida(Planta* plantaProteger, Fungicida* fungicidaAplicado) //Recibir una planta y un fungicida para eliminar
{
	//Caso de hongo agregado
	if (plantaProteger->getColorPlanta() == fungicidaAplicado->getColorCarta() && plantaProteger->getContadorFungicidas() == 2) //Si está inmunizada
	{
		cout << "No es posible aplicar el fungicida a esta carta porque esta inmunizada..." << endl;
		cout << endl;
		plantaProteger->mostrarInformacion();
		return false;
	}
	else if (plantaProteger->getColorPlanta() == fungicidaAplicado->getColorCarta() && plantaProteger->getContadorFungicidas() < 2 && plantaProteger->getContadorHongos() == 0) //Si tiene un fungicida o menos
	{
		plantaProteger->setContadorFungicida(1); //Sumar un fungicida al contador de la planta
		if (plantaProteger->getContadorFungicidas() == 2)
		{
			plantaProteger->setDarInmunidad();
		}
		eliminarFungicida(fungicidaAplicado);
		return seAplicoFungicida();
	}
	else if (plantaProteger->getContadorHongos() == 1 && plantaProteger->getColorCarta() == fungicidaAplicado->getColorCarta())
	{
		plantaProteger->setRestarHongos(1);
		eliminarFungicida(fungicidaAplicado);
		cout << "Se ha eliminado un hongo de la planta. " << endl; //Es necesario imprimir información desde el main si se quiere ver cambios
		return seAplicoFungicida();
	}
	else
	{
		cout << "No es posible aplicar el fungicida a esta planta porque es de otro color..." << endl;
		cout << endl;
		plantaProteger->mostrarInformacion();
		return false;
	}
}

void Fungicida::eliminarFungicida(Fungicida* cartaFungicida)
{
	delete cartaFungicida;
	cartaFungicida = nullptr;
}

void Fungicida::mostrarInformacion()
{
	cout << "Carta tipo: " << tipo << endl;
	cout << "Color del fungicida: " << color << endl;
	cout << endl;
}