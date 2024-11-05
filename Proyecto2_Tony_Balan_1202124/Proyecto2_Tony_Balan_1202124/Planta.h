#pragma once
#include <iostream>
#include <string>
#include "Carta.h"
using namespace std;

class Hongo;

class Planta : public Carta
{
protected:
	bool abono = false;
	bool inmunidad = false;
	int contadorFungicidas = 0;
	int hongosPuestos;
	bool infeccionLetal;
	bool eliminado = false;
public:
	Planta(string tipo, string color, bool abon, bool inmuni, int cantidadFungi, int hongosAplicados, bool tieneLetal) : Carta(tipo, color), abono(abon), inmunidad(inmuni), contadorFungicidas(cantidadFungi), hongosPuestos(hongosAplicados), infeccionLetal(tieneLetal)  {}
	//Planta("planta", "rojo", false (abono), false (inmunidad), 0 (fungicidas), 0 (hongos), false (tiene hongo letal)
	void mostrarInformacion() override;

	bool tieneAbono();

	bool esInmune();

	bool tieneLetal(); //verificar si tiene hongo letal
	 
	int getContadorHongos() { return hongosPuestos; }

	void eliminarPlantaHongo(Planta* plantaEliminar, Hongo* hongoAplicado);

	void setAgregarHongos(int n, Planta* plantaHongos, Hongo* hongoAplicado);

	int setAgregarHongosSiFungicidas(Planta* plantaHongos, Hongo* hongoAplicado);

	void setContadorFungicida(int n) { contadorFungicidas = contadorFungicidas + n; }

	void setDarInmunidad() { inmunidad = true; }

	void setRestarHongos(int n) { hongosPuestos = hongosPuestos - n; }

	void setActualizarContadorFungicidas(int n) { contadorFungicidas = n; }

	int getContadorFungicidas() { return contadorFungicidas; }

	void setReiniciarContadorFungicidas() { contadorFungicidas = 0; }
	
	string getColorPlanta() { return color; } //Recordar de validar el texto todo en minúscula

	void setDarAbonoPlanta() { abono = true; }

	void haSidoEliminado() { eliminado = true; }

	bool getEliminado() { return eliminado; }

};

