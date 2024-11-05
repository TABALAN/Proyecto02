#include "pch.h"
#include "Hongo.h"
#include <string>
#include "Carta.h"
#include "Planta.h"
using namespace std;

void Hongo::mostrarInformacion()
{
	cout << "Carta tipo: " << tipo << endl;
	if (esFatal())
	{
		cout << "Fatalidad: " << (esFatal() ? "Si" : "No") << endl;
	}
	else
	{
		cout << "Grado infeccion: " << gradoLetal << endl;
	}
	cout << endl;
}

bool Hongo::aplicarHongo(Planta* plantaAtacar, Hongo* hongoAtacante)
{
	if(plantaAtacar->getContadorFungicidas() < 2 && hongoAtacante->getGradoHongo() == 2)
	{
		int totalHongosAplicables = 0;

		plantaAtacar->setAgregarHongos(totalHongosAplicables, plantaAtacar, hongoAtacante); //Caso en el que la planta tenga 1 fungicida, pero hongo grado 2
		return seAplicoHongo();
	}
	else if (plantaAtacar->getContadorFungicidas() > 0 && plantaAtacar->esInmune() == false ) //Si la planta tiene fungicidas
	{
		int totalHongosAplicables = plantaAtacar->setAgregarHongosSiFungicidas(plantaAtacar, hongoAtacante);

		plantaAtacar->setAgregarHongos(totalHongosAplicables, plantaAtacar, hongoAtacante); //agregar y validar en el método si se puede eliminar
		return seAplicoHongo();
	}
	else if (plantaAtacar->esInmune() == true && hongoAtacante->esFatal() == false) //caso planta inmune
	{
		cout << "No se puede eliminar la planta porque esta inmunizada..." << endl;
		eliminarHongo(hongoAtacante); //De todas formas se elimina el hongo PREGUNTAR
		return false;
		cout << endl;
	}
	else if (plantaAtacar->esInmune() == true && hongoAtacante->esFatal() == true)
	{
		int totalHongosAplicables = 0;
		plantaAtacar->setAgregarHongos(totalHongosAplicables, plantaAtacar, hongoAtacante);
		return seAplicoHongo();
	}
	else if (plantaAtacar->getContadorFungicidas() == 0)
	{
		int totalHongosAplicables = hongoAtacante->getGradoHongo();
		plantaAtacar->setAgregarHongos(totalHongosAplicables, plantaAtacar, hongoAtacante);
		return seAplicoHongo();
	}

}

void Hongo::eliminarHongo(Hongo* hongoAtacante)
{
	delete hongoAtacante;
	hongoAtacante = nullptr;
}

bool Hongo::esFatal()
{
	return letalidad;
}
