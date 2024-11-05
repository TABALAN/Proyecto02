#include "pch.h"
#include "Jugador.h"
#include <iostream>
#include <string>
#include "Carta.h"
#include "Planta.h"
#include "Jardin.h"
#include "Hongo.h"
#include "Fungicida.h"
#include "Abono.h"
#include "Juego.h"
using namespace std;
Juego jueguito;

void Jugador::insertarCartaAlFinal(Carta* cartaNueva)
{
	ManoCartas* nuevaCarta = new ManoCartas{ cartaNueva, nullptr, nullptr }; //{Valor, cabeza, final}
	if (cabeza == nullptr)
	{
		cabeza = nuevaCarta;
		final = nuevaCarta;
	}
	else
	{
		final->siguiente = nuevaCarta; //El siguiente es hacia la derecha y anterior izquierda
		nuevaCarta->anterior = final;
		final = nuevaCarta;
	}
	
}

void Jugador::eliminarCartaMano(const Carta& cartaEliminar)
{
	if (cabeza == nullptr)
	{
		cout << "El jugador no tiene ninguna carta..." << endl;
		return;
	}

	ManoCartas* cartaRecorrida = cabeza;

	while (cartaRecorrida != nullptr && cartaRecorrida->cartaJugador != &cartaEliminar)
	{
		cartaRecorrida = cartaRecorrida->siguiente;
	}
	if (cartaRecorrida == nullptr)
	{
		cout << "Carta no encontrada en la mano..." << endl;
		return;
	}

	if (cartaRecorrida == cabeza) //En caso de que la carta sea la primera de la mano
	{
		cabeza = cartaRecorrida->siguiente;
		if (cabeza != nullptr)
		{
			cabeza->anterior = nullptr;
		}
		else
		{
			final = nullptr;
		}
	}
	else if (cartaRecorrida == final) //En el caso de que la carta sea la ultima de la mano
	{
		final = cartaRecorrida->anterior;
		if (final != nullptr)
		{
			final->siguiente = nullptr;
		}
		else
		{
			cabeza = nullptr;
		}
	}
	else
	{
		cartaRecorrida->anterior->siguiente = cartaRecorrida->siguiente;
		cartaRecorrida->siguiente->anterior = cartaRecorrida->anterior;
	}

	cartaRecorrida->siguiente = nullptr;
	cartaRecorrida->anterior  = nullptr;
}

void Jugador::eliminarPrimeraCarta() //En realidad se refiere al último
{
	if (cabeza == nullptr)
	{
		cout << "El jugador no tiene ninguna carta..." << endl;
		return;
	}

	ManoCartas* cartaRecorrida = final;

	if (cartaRecorrida == final)
	{
		final = cartaRecorrida->anterior;
		if (final != nullptr)
		{
			final->siguiente = nullptr;
		}
		else
		{
			cabeza = nullptr;
		}
	}
}

void Jugador::imprimirMano()
{
	int indiceCarta = 1;
	if (cabeza == nullptr && final == nullptr)
	{
		cout << "El jugador no tiene ninguna carta en mano..." << endl;
	}
	ManoCartas* cartaRecorrida = cabeza;
	while (cartaRecorrida != nullptr)
	{
		cout << "Carta " << indiceCarta << ": " << endl; //Será importante para que el usuario valide cual quiere jugar
		cartaRecorrida->cartaJugador->mostrarInformacion();
		cartaRecorrida = cartaRecorrida->siguiente;
		indiceCarta++;
	}
}

void Jugador::informacionJugador()
{
	cout << "Nombre del jugador " << getNumeroJugador() << " es: " << getNombreJugador() << endl;
	cout << endl;
}

Carta* Jugador::cartaJugar()
{
	int numeroCarta;
	cout << "Turno de " << getNombreJugador() << endl;
	cout << "Mano de cartas: " << endl;
	cout << endl;
	imprimirMano();
	cout << "Ingrese el numero de carta que quiere jugar (ingrese '5' si quiere pasar turno): ";

	do
	{
		cin >> numeroCarta;
		if (numeroCarta < 1 || numeroCarta > 5)
		{
			cout << "Numero de carta no valido, intente de nuevo..." << endl;
			cout << "Numero: ";
		}
	} while (numeroCarta < 1 || numeroCarta > 5);

	cout << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << endl;

	if (numeroCarta == 5)
	{
		return nullptr;
	}

	cout << "La carta elegida es: " << endl;
	Carta* cartaJugada = buscarCarta(numeroCarta);
	cout << endl;
	cartaJugada->mostrarInformacion();

	return cartaJugada;
	cout << endl;
}

Carta* Jugador::buscarCarta(int numeroCarta) const
{
	if (numeroCarta == 0)
	{
		return cabeza->cartaJugador;
	}
	else
	{
		ManoCartas* cartaRecorrida = cabeza;
		for (int i = 1; i < numeroCarta; i++)
		{
			cartaRecorrida = cartaRecorrida->siguiente; ///Verificar funcionamiento
		}
		return cartaRecorrida->cartaJugador;
	}
}

void Jugador::imprimirJardin()
{
	informacionJugador();
	jardin.imprimirJardin();
}
