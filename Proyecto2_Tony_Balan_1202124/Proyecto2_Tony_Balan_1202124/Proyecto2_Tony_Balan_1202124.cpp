#include "pch.h"
#include "Planta.h"
#include "Carta.h"
#include "Fungicida.h"
#include "Hongo.h"
#include "Abono.h"
#include "Juego.h"
#include "Jugador.h"
#include "Truco.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    Juego juego;
	int numeroJugadoresPartida = 0;

	cout << endl;
	cout << "Hola!!, bienvenido al juego de cartas 'Plantas y Hongos'!!" << endl;
	cout << "Para iniciar, por favor indique el numero de jugadores que ingresaran a la partida (2 - 4 jugadores): ";
	do
	{
		cin >> numeroJugadoresPartida;
		if (numeroJugadoresPartida > 4 || numeroJugadoresPartida < 2)
		{
			cout << endl;
			cout << "Solo pueden haber de 2 a 4 jugadores por partida..." << endl;
			cout << "Ingrese nuevamente el numero de jugadores a jugar: ";
		}
	} while (numeroJugadoresPartida > 4 || numeroJugadoresPartida < 2);

	cout << endl;
	cin.ignore();

	cout << "---------------------------------------------------------------------------------------------------" << endl;
	juego.creacionDelPool(); //Crear el pool de cartas y barajearlo
	cout << endl;

	cout << "El pozo de cartas ha sido generado: " << endl;
	cout << endl;

	juego.imprimirPozoCartas();
	cout << endl;

	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	juego.ingresarCantidadJugadores(numeroJugadoresPartida);

	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "Cartas repartidas. Pozo de cartas actualizado..." << endl;
	cout << endl;
	juego.imprimirPozoCartas();
	cout << endl;
	cout << "Inicia la partida.... BUENA SUERTE A TODOS!!" << endl;
	cout << endl;

	bool fin = false;
	int turnoJugador = 1;
	int contadorNoPudoJugar = 0;
	do
	{
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		cout << endl;
		cout << "Jardin/es del/los jugador/es: " << endl;
		cout << endl;
		juego.mostrarJardines(turnoJugador, juego.getNumeroJugadoresPartida());
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		cout << endl;
		Jugador* jugadorTurno = juego.turnoJugador(turnoJugador); //Obtener al jugador con el turno actual
		Jardin& jardinJugadorTurno = jugadorTurno->getJardin(); //Obtener su jardín para efectuar cambios
		cout << endl;
		jardinJugadorTurno.imprimirJardin(); //Imprimir
		cout << endl;
		
		Carta* cartaJugada = jugadorTurno->cartaJugar();

		if (cartaJugada != nullptr) //Obtener la carta que jugará
		{

			if (const Planta* const plantaJugada = dynamic_cast<Planta*>(cartaJugada)) //Este método sirve para convertir puntero a un puntero de clase derivada (herencia)
			{
				cout << "---------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "Jardin actual: " << endl;
				cout << endl;
				jugadorTurno->imprimirJardin();

				if (jardinJugadorTurno.agregarPlantaJardin(*plantaJugada))
				{

					jugadorTurno->eliminarCartaMano(*plantaJugada); ///Eliminar carta de la mano

					Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

					if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
					{
						juego.insertarNuevaCartaAlJugador(turnoJugador, cartaNueva);
					}

					turnoJugador++; //Dar turno al siguiente jugador
					cout << "---------------------------------------------------------------------------------------------------" << endl;
					cout << endl;
					cout << "Jardin actualizado exitosamente... " << endl;
					cout << endl;
					jardinJugadorTurno.imprimirJardin();
				}
			}
			else if (Hongo* hongoPerron = dynamic_cast<Hongo*>(cartaJugada))
			{
				int numeroPlanta;
				int numeroJugadorAtacar = 0;

				cout << "---------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "Jardines de los otros jugadores: " << endl;
				cout << endl;

				juego.mostrarJardines(jugadorTurno->getNumeroJugador(), juego.getNumeroJugadoresPartida()); //Mostrar los jardines de los demás

				cout << "Ingrese el numero de jugador al que quiere atacar: ";

				if (juego.getNumeroJugadoresPartida() == 2)
				{
					if (jugadorTurno->getNumeroJugador() == 1)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar != 2)
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar != 2);
					}
					else if (jugadorTurno->getNumeroJugador() == 2)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar != 1)
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar != 1);
					}
				}
				else if (juego.getNumeroJugadoresPartida() == 3)
				{
					if (jugadorTurno->getNumeroJugador() == 1)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida());
					}
					else if (jugadorTurno->getNumeroJugador() == 2)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
					}
					else if (jugadorTurno->getNumeroJugador() == 3)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
					}
				}
				else if (juego.getNumeroJugadoresPartida() == 4)
				{
					if (jugadorTurno->getNumeroJugador() == 1)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida());
					}
					else if (jugadorTurno->getNumeroJugador() == 2)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
					}
					else if (jugadorTurno->getNumeroJugador() == 3)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
					}
					else if (jugadorTurno->getNumeroJugador() == 4)
					{
						do
						{
							cin >> numeroJugadorAtacar;
							if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
							{
								cout << endl;
								cout << "Numero de jugador invalido... intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
					}
				}
				else { cout << "Algo no esta bien..."; }

				cout << endl;
				cout << "---------------------------------------- Jardin objetivo ------------------------------------------" << endl;
				cout << endl;
				Jardin& jardinObjetivo = juego.getJardinJugador(numeroJugadorAtacar);

				if (!jardinObjetivo.estaVacio())
				{
					jardinObjetivo.imprimirJardin();

					cout << "Ingrese el numero de planta que quiere jugar: ";
					do
					{
						cin >> numeroPlanta;
						if (numeroPlanta < 1 || numeroPlanta > jardinObjetivo.getContadorPlantas())
						{
							cout << "Numero de planta no valido, intente de nuevo..." << endl;
							cout << "Numero: ";
						}
					} while (numeroPlanta < 1 || numeroPlanta > jardinObjetivo.getContadorPlantas());

					if (hongoPerron->aplicarHongo(jardinObjetivo.jugarSobrePlantaJardinHongo(numeroPlanta), hongoPerron) == true)
					{
						jardinObjetivo.eliminarPlantaNoValida();

						jugadorTurno->eliminarCartaMano(*hongoPerron); ///Eliminar carta de la mano

						Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

						if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
						{
							juego.insertarNuevaCartaAlJugador(turnoJugador, cartaNueva);
						}

						turnoJugador++; //Dar turno al siguiente jugador
					}
				}
				else
				{
					cout << endl;
					cout << "---------------------------------------------------------------------------------------------------" << endl;
					cout << endl;
					cout << "El jardin elegido esta vacio...." << endl;
					cout << endl;
				}
			}
			else if (Fungicida* fungicida = dynamic_cast<Fungicida*>(cartaJugada))
			{
				int numeroPlanta;
				cout << "---------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "Jardin actual: " << endl;
				cout << endl;

				if (!jardinJugadorTurno.estaVacio())
				{
					jardinJugadorTurno.imprimirJardin();
					cout << "---------------------------------------------------------------------------------------------------" << endl;
					cout << endl;
					cout << "Ingrese el numero de planta que quiere aplicar fungicida: ";
					do
					{
						cin >> numeroPlanta;
						if (numeroPlanta < 1 && numeroPlanta > jardinJugadorTurno.getContadorPlantas())
						{
							cout << "Numero de planta no valido, intente de nuevo..." << endl;
							cout << "Numero: ";
						}
					} while (numeroPlanta < 1 && numeroPlanta > jardinJugadorTurno.getContadorPlantas());

					if (fungicida->aplicarFungicida(jardinJugadorTurno.jugarSobrePlantaJardinHongo(numeroPlanta), fungicida) == true)
					{
						jugadorTurno->eliminarCartaMano(*fungicida); ///Eliminar carta de la mano

						Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

						if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
						{
							juego.insertarNuevaCartaAlJugador(turnoJugador, cartaNueva);
						}

						turnoJugador++; //Dar turno al siguiente jugador
					}
				}
				else
				{
					cout << "---------------------------------------------------------------------------------------------------" << endl;
					cout << endl;
					cout << "No hay plantas disponibles en el jardin actual... (esta vacio)" << endl;
					cout << endl;
					jardinJugadorTurno.imprimirJardin();
				}
			}
			else if (Abono* abonito = dynamic_cast<Abono*>(cartaJugada))
			{
				int numeroPlanta;
				cout << "---------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "Jardin actual: " << endl;
				cout << endl;

				if (!jardinJugadorTurno.estaVacio())
				{
					jardinJugadorTurno.imprimirJardin();

					cout << "Ingrese el numero de planta que quiere aplicar abono: ";
					do
					{
						cin >> numeroPlanta;
						if (numeroPlanta < 1 && numeroPlanta > jardinJugadorTurno.getContadorPlantas())
						{
							cout << endl;
							cout << "Numero de planta no valido, intente de nuevo..." << endl;
							cout << "Numero: ";
						}
					} while (numeroPlanta < 1 && numeroPlanta > jardinJugadorTurno.getContadorPlantas());

					if (abonito->aplicarAbono(jardinJugadorTurno.jugarSobrePlantaJardinHongo(numeroPlanta), abonito) == true)
					{
						jugadorTurno->eliminarCartaMano(*abonito);

						Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

						if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
						{
							juego.insertarNuevaCartaAlJugador(turnoJugador, cartaNueva);
						}

						turnoJugador++; //Dar turno al siguiente jugador
					}
				}
				else
				{
					cout << "---------------------------------------------------------------------------------------------------" << endl;
					cout << endl;
					cout << "No hay plantas disponibles en el jardin actual... (esta vacio)" << endl;
					cout << endl;
					jardinJugadorTurno.imprimirJardin();
				}
			}
			else if (Truco* truquitoPerron = dynamic_cast<Truco*>(cartaJugada))
			{
				int numeroPlanta;
				int numeroJugadorAtacar = 0;

				cout << "---------------------------------------------------------------------------------------------------" << endl;
				cout << endl;
				cout << "Jardines de los otros jugadores: " << endl;
				cout << endl;

				juego.mostrarJardines(jugadorTurno->getNumeroJugador(), juego.getNumeroJugadoresPartida()); //Mostrar los jardines de los demás

				if (truquitoPerron->getSubtTipoCarta() == "Intercambio")
				{
					cout << "Ingrese el numero de jugador con el que quiere intercambiar jardin: ";

					if (juego.getNumeroJugadoresPartida() == 2)
					{
						if (jugadorTurno->getNumeroJugador() == 1)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar != 2)
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar != 2);
						}
						else if (jugadorTurno->getNumeroJugador() == 2)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar != 1)
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar != 1);
						}
					}
					else if (juego.getNumeroJugadoresPartida() == 3)
					{
						if (jugadorTurno->getNumeroJugador() == 1)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida());
						}
						else if (jugadorTurno->getNumeroJugador() == 2)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
						else if (jugadorTurno->getNumeroJugador() == 3)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
					}
					else if (juego.getNumeroJugadoresPartida() == 4)
					{
						if (jugadorTurno->getNumeroJugador() == 1)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida());
						}
						else if (jugadorTurno->getNumeroJugador() == 2)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
						else if (jugadorTurno->getNumeroJugador() == 3)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
						else if (jugadorTurno->getNumeroJugador() == 4)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
					}
					else { cout << "Algo no esta bien..."; }

					cout << endl;
					Jardin& jardinObjetivo = juego.getJardinJugador(numeroJugadorAtacar);
					Jugador* jugadorObjetivo = juego.jugadorObjetivoIntercambio(numeroJugadorAtacar);

					if (truquitoPerron->cambioDeJardin(jardinJugadorTurno, jardinObjetivo, *jugadorTurno, *jugadorObjetivo) == true)
					{

						jugadorTurno->eliminarCartaMano(*truquitoPerron); ///Eliminar carta de la mano
						Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

						if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
						{
							juego.insertarNuevaCartaAlJugador(turnoJugador, cartaNueva);
						}

						turnoJugador++; //Dar turno al siguiente jugador
					}
					else { cout << "Cambio no hecho..."; }
				}
				else if (truquitoPerron->getSubtTipoCarta() == "Trasplantar")
				{
					cout << "Ingrese el numero de jugador del que quiere obtener una planta: ";

					if (juego.getNumeroJugadoresPartida() == 2)
					{
						if (jugadorTurno->getNumeroJugador() == 1)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar != 2)
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar != 2);
						}
						else if (jugadorTurno->getNumeroJugador() == 2)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar != 1)
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar != 1);
						}
					}
					else if (juego.getNumeroJugadoresPartida() == 3)
					{
						if (jugadorTurno->getNumeroJugador() == 1)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida());
						}
						else if (jugadorTurno->getNumeroJugador() == 2)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
						else if (jugadorTurno->getNumeroJugador() == 3)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
					}
					else if (juego.getNumeroJugadoresPartida() == 4)
					{
						if (jugadorTurno->getNumeroJugador() == 1)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 2 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida());
						}
						else if (jugadorTurno->getNumeroJugador() == 2)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
						else if (jugadorTurno->getNumeroJugador() == 3)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
						else if (jugadorTurno->getNumeroJugador() == 4)
						{
							do
							{
								cin >> numeroJugadorAtacar;
								if (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador())
								{
									cout << endl;
									cout << "Numero de jugador invalido... intente de nuevo..." << endl;
									cout << "Numero: ";
								}
							} while (numeroJugadorAtacar < 1 || numeroJugadorAtacar > juego.getNumeroJugadoresPartida() || numeroJugadorAtacar == jugadorTurno->getNumeroJugador());
						}
					}
					else { cout << "Algo no esta bien..."; }
					cout << endl;
					Jardin& jardinObjetivo = juego.getJardinJugador(numeroJugadorAtacar);
					cout << endl;
					if (!jardinObjetivo.estaVacio())
					{
						cout << "---------------------------------------- Jardin objetivo ------------------------------------------" << endl;
						cout << endl;
						jardinObjetivo.imprimirJardin();

						cout << "Ingrese el numero de planta que quiere jugar: ";
						do
						{
							cin >> numeroPlanta;
							if (numeroPlanta < 1 || numeroPlanta > jardinObjetivo.getContadorPlantas())
							{
								cout << "Numero de planta no valido, intente de nuevo..." << endl;
								cout << "Numero: ";
							}
						} while (numeroPlanta < 1 || numeroPlanta > jardinObjetivo.getContadorPlantas());

						Planta* plantaRequerida = jardinObjetivo.ObtenerPlantaTrasplantar(numeroPlanta);
						if (plantaRequerida != nullptr)
						{
							jardinObjetivo.desconectarPlanta(plantaRequerida);
						}

						if (truquitoPerron->trasplantarPlanta(plantaRequerida, jardinJugadorTurno) == true)
						{
							jugadorTurno->eliminarCartaMano(*truquitoPerron); ///Eliminar carta de la mano

							Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

							if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
							{
								juego.insertarNuevaCartaAlJugador(turnoJugador, cartaNueva);
							}

							turnoJugador++; //Dar turno al siguiente jugador
						}
					}
					else
					{
						cout << endl;
						cout << "El jardin elegido esta vacio...." << endl;
						cout << endl;
					}
				}
			}

			contadorNoPudoJugar = 0;
		}
		else
		{
			cout << "Pasando Turno..." << endl;
			turnoJugador++;
			contadorNoPudoJugar++;
		}

		if (contadorNoPudoJugar == 2)
		{
			cout << endl;
			cout << "Ningun jugador ha podido jugar ninguna carta en una vuelta, asi que usted recibira una nueva carta..." << endl;
			cout << endl;

			jugadorTurno->eliminarPrimeraCarta();

			Carta* cartaNueva = juego.devolverCarta(juego.getPozoCartas()); //Dar otra carta

			if (cartaNueva != nullptr) //Validar que se obtenga una carta válida del pozo
			{
				juego.insertarNuevaCartaAlJugador(jugadorTurno->getNumeroJugador(), cartaNueva);
			}

			turnoJugador++; //Dar turno al siguiente jugador
			contadorNoPudoJugar = 0;
		}

		if (jardinJugadorTurno.comprobarVictoria())
		{
			cout << endl;
			cout << "----------------------------------------------------------------------------------------" << endl;
			cout << endl;
			cout << "FELICITACIONES!!! El/la jugador/a " << jugadorTurno->getNombreJugador() << " ha ganado...." << endl;
			cout << endl;
			jardinJugadorTurno.imprimirJardin();
			fin = true;
		}

		if (turnoJugador > juego.getNumeroJugadoresPartida())
		{
			turnoJugador = 1;
		}

	} while (fin == false);
}
