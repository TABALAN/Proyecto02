#include "pch.h"
#include "Jardin.h"
#include "Planta.h"
#include <iostream>

using namespace std;

bool Jardin::agregarPlantaJardin(const Planta& plantaNueva)
{
	contarPlantasJardin(); 

	if (getContadorPlantas() == 0)
	{
		setSumarContadorPlantas(1);
		if (cabeza == nullptr)
		{
			plantasJardin* nuevaPlanta = new plantasJardin(plantaNueva);
			cabeza = ultimo = nuevaPlanta;
		}
		cout << "Planta agregada con exito..." << endl;
		cout << endl;
		return seAgregoPlanta();
	}
	else if (getContadorPlantas() > 0 && getContadorPlantas() < 6)
	{
		setSumarContadorPlantas(1);
		plantasJardin* nuevaPlanta = new plantasJardin(plantaNueva);
		ultimo->siguiente = nuevaPlanta; //El siguiente es hacia la derecha y anterior izquierda
		nuevaPlanta->anterior = ultimo;
		ultimo = nuevaPlanta;
		cout << "Planta agregada con exito..." << endl;
		cout << endl;
		return seAgregoPlanta();
	}
	else if (getContadorPlantas() == 5)
	{
		cout << "Espacio insuficiente para colocar una planta..." << endl;
		cout << endl;
		return false;
	}
	return false;
}

void Jardin::imprimirJardin()
{
	int numeroPlanta = 1;
	if (!estaVacio())
	{
		eliminarPlantaNoValida(); //Eliminar una planta antes de imprimir

		plantasJardin* plantaRecorrida = cabeza;
		cout << "Jardin: " << endl;
		cout << endl;
		while (plantaRecorrida != nullptr)
		{
			if (plantaRecorrida->planta != nullptr)
			{
				cout << "Numero de planta: " << numeroPlanta << endl;
				plantaRecorrida->planta->mostrarInformacion();
				numeroPlanta++;
			}
			else
			{
				cout << "Planta no valida..." << endl;
			}
			plantaRecorrida = plantaRecorrida->siguiente;
			cout << endl;
		}
	}
	else
	{
		cout << "Aun no hay plantas agregadas al jardin..." << endl;
		cout << endl;
	}
}

Planta* Jardin::jugarSobrePlantaJardinHongo(int numeroPlanta)
{
	int indice = numeroPlanta - 1;

	if (indice < 0 || indice >= contadorPlantas) // Verificar que el índice sea válido
	{
		cout << "Número de planta fuera de rango." << endl;
		return nullptr;
	}

	if (indice == 0)
	{
		return cabeza->planta;
	}
	else
	{
		plantasJardin* plantaRecorrida = cabeza;
		for (int i = 0; i < indice; i++)
		{
			plantaRecorrida = plantaRecorrida->siguiente;
		}
		return plantaRecorrida->planta;
	}
}

void Jardin::eliminarPlantaNoValida()
{
	if (estaVacio())
	{
		return;
	}

	plantasJardin* plantaRecorrida = cabeza;
	while (plantaRecorrida != nullptr)
	{
		plantasJardin* siguientePlanta = plantaRecorrida->siguiente;

		if (plantaRecorrida->planta->getEliminado() == true)
		{
			if (plantaRecorrida == cabeza)
			{
				cabeza = plantaRecorrida->siguiente;
				if (cabeza != nullptr)
				{
					cabeza->anterior = nullptr;
				}
				else
				{
					ultimo = nullptr;
				}
			}
			else if (plantaRecorrida == ultimo)
			{
				ultimo = plantaRecorrida->anterior;
				if (ultimo != nullptr)
				{
					ultimo->siguiente = nullptr;
				}
				else
				{
					cabeza = nullptr;
				}
			}
			else
			{
				plantaRecorrida->anterior->siguiente = plantaRecorrida->siguiente;
				plantaRecorrida->siguiente->anterior = plantaRecorrida->anterior;
			}
			delete plantaRecorrida;
		}
		plantaRecorrida = siguientePlanta; //Se continúa al siguiente nodo si no se encontró un caso de planta nula
	}
}

void Jardin::contarPlantasJardin()
{
	setReiniciarContadorPlantas();

	if (estaVacio())
	{
		return;
	}

	plantasJardin* plantaRecorrida = cabeza;

	while (plantaRecorrida != nullptr)
	{
		if (plantaRecorrida->planta->getEliminado() == false)
		{
			setSumarContadorPlantas(1);
		}
		plantaRecorrida = plantaRecorrida->siguiente;
	}
}

Planta* Jardin::ObtenerPlantaTrasplantar(int numeroPlanta)
{
	int indice = numeroPlanta - 1;

	if (indice < 0 || indice >= contadorPlantas) // Verificar que el índice sea válido
	{
		cout << "Número de planta fuera de rango." << endl;
		return nullptr;
	}

	if (indice == 0)
	{
		return cabeza->planta;
	}
	else
	{
		plantasJardin* plantaRecorrida = cabeza;
		for (int i = 0; i < indice; i++)
		{
			plantaRecorrida = plantaRecorrida->siguiente;
		}
		return plantaRecorrida->planta;
	}
}

bool Jardin::plantaRoja()
{
	plantasJardin* plantaRecorrida = cabeza;

	while (plantaRecorrida != nullptr)
	{
		if (plantaRecorrida->planta->tieneAbono() == true && plantaRecorrida->planta->getColorPlanta() == "rojo")
		{
			return true;
		}
		plantaRecorrida = plantaRecorrida->siguiente;
	}
	return false;
}

bool Jardin::plantaAzul()
{
	plantasJardin* plantaRecorrida = cabeza;

	while (plantaRecorrida != nullptr)
	{
		if (plantaRecorrida->planta->tieneAbono() == true && plantaRecorrida->planta->getColorPlanta() == "azul")
		{
			return true;
		}
		plantaRecorrida = plantaRecorrida->siguiente;
	}
	return false;
}

bool Jardin::plantaAmarilla()
{
	plantasJardin* plantaRecorrida = cabeza;

	while (plantaRecorrida != nullptr)
	{
		if (plantaRecorrida->planta->tieneAbono() == true && plantaRecorrida->planta->getColorPlanta() == "amarillo")
		{
			return true;
		}
		plantaRecorrida = plantaRecorrida->siguiente;
	}
	return false;
}

bool Jardin::comprobarVictoria()
{
	if (plantaRoja() == true)
	{
		sumarPlantasGanadoras();
	}

	if (plantaAzul() == true)
	{
		sumarPlantasGanadoras();
	}

	if (plantaAmarilla() == true)
	{
		sumarPlantasGanadoras();
	}

	if (getContadorPlantasGanadoras() == 3)
	{	
		return true;
	}

	reiniciarConteoPlantasGanadoras();
	return false;
}

void Jardin::desconectarPlanta(Planta* desconectarPlanta)
{
	if (estaVacio())
	{
		return;
	}

	plantasJardin* plantaRecorrida = cabeza;

	while (plantaRecorrida != nullptr)
	{
		if (plantaRecorrida->planta == desconectarPlanta)
		{
			if (plantaRecorrida == cabeza)
			{
				cabeza = plantaRecorrida->siguiente;
				if (cabeza != nullptr)
				{
					cabeza->anterior = nullptr;
				}
				else
				{
					ultimo = nullptr;
				}
			}
			else if (plantaRecorrida == ultimo)
			{
				ultimo = plantaRecorrida->anterior;
				if (ultimo != nullptr)
				{
					ultimo->siguiente = nullptr;
				}
				else
				{
					cabeza = nullptr;
				}
			}
			else
			{
				plantaRecorrida->anterior->siguiente = plantaRecorrida->siguiente;
				plantaRecorrida->siguiente->anterior = plantaRecorrida->anterior;
			}
		}
		plantaRecorrida = plantaRecorrida->siguiente;
	}
}