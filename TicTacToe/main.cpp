//main.cpp

// Importamos
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <locale.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int valores[3][3];

enum options {
	menu, play, playPC, exitRun
};

string	rawInput;
string	message;
int		currentPlayer, turn;

bool activeGame = false;
bool showMessage = false;

void cleanValores()
{
	for (int ii = 0; ii < 3; ii++)
	{
		for (int jj = 0; jj < 3; jj++)
		{
			valores[ii][jj] = 3*(ii)+(jj+1);
		}
	}
}

void drawTitle()
{
	cout << "==========================================" << endl;
	cout << "============= Juego del gato =============" << endl;
	cout << "==========================================" << endl;
}

string getItem(int _ii, int _jj)
{
	if (valores[_ii][_jj] == -1)
	{
		return "X";
	}
	else if (valores[_ii][_jj] == -2)
	{
		return "O";
	}
	else
	{
		return to_string(valores[_ii][_jj]);
	}
}

void drawBoard()
{
	for (int ii = 0; ii < 3; ii++)
	{
		cout << "\t\t" + getItem(ii, 0) + "|" + getItem(ii, 1) + "|" + getItem(ii, 2) << endl;
		
		if (ii < 2)
		{
			cout << "\t\t" << "-" << "+" << "-" << "+" << "-" << endl;
		}
	}
}

bool allNumber()
{
	for (int ii = 0; ii < rawInput.length(); ++ii)
	{
		if (!std::isdigit(rawInput[ii]))
		{
			return false;
		}
	}

	return true;
}

bool allAlpha()
{
	for (int ii = 0; ii < rawInput.length(); ++ii)
	{
		if (std::isdigit(rawInput[ii]))
		{
			return false;
		}
	}

	return true;
}

bool validateLength()
{
	return (rawInput.length() == 1);
}

// Valida que la posición no haya sido reemplazada por haber sido usada antes-
bool validatePlay()
{
	for (int ii = 0; ii < 3; ii++)
	{
		for (int jj = 0; jj < 3; jj++)
		{
			if (stoi(rawInput) == valores[ii][jj])
			{
				return true;
			}
		}
	}
	
	return false;
}

// Método que valida todos los casos.
bool validateRawInput(options _option)
{
	string onlyABC = "Solo se permite las opciones a, b, c.";
	string onlyNums = "Solo se permiten números válidos (del 1 al 9) no jugados.";

	if (rawInput.empty())
	{
		cout << "El valor no puede ser vacío.";
	}
	cout << "";

	// validamos el input según el estado en donde nos encontramos
	switch (_option)
	{
		case options::menu:
			if (!allAlpha() || (rawInput != "a" && rawInput != "b" && rawInput != "c"))
			{
				cout << onlyABC;
				return false;
			}
			break;

		case options::play:
		case options::playPC:
			if (!allNumber())
			{
				cout << onlyNums;
				return false;
			}
			
			if (!validateLength())
			{
				cout << onlyNums;
				return false;
			}

			if (!validatePlay())
			{
				cout << onlyNums;
				return false;
			}
			break;
	}

	return true;
}

// Valida todas las posibles opciones.
int validateWinConditions()
{
	// Validación de líneas
	if (valores[0][0] == valores[0][1] && valores[0][1] == valores[0][2])
	{
		return valores[0][0];
	}

	if (valores[1][0] == valores[1][1] && valores[1][1] == valores[1][2])
	{
		return valores[1][0];
	}

	if (valores[2][0] == valores[2][1] && valores[2][1] == valores[2][2])
	{
		return valores[2][0];
	}

	// Validación de columnas
	if (valores[0][0] == valores[1][0] && valores[1][0] == valores[2][0])
	{
		return valores[0][0];
	}

	if (valores[0][1] == valores[1][1] && valores[1][1] == valores[2][1])
	{
		return valores[0][1];
	}

	if (valores[0][2] == valores[1][2] && valores[1][2] == valores[2][2])
	{
		return valores[0][2];
	}

	// Validación de diagonales
	if (valores[0][0] == valores[1][1] && valores[1][1] == valores[2][2])
	{
		return valores[0][0];
	}

	if (valores[2][0] == valores[1][1] && valores[1][1] == valores[0][2])
	{
		return valores[2][0];
	}

	if (turn == 9)
	{
		return 999;
	}

	return 0;
}

// Método que llama a otros métodos para simplificar el proceso
void drawScreen()
{
	system("cls");
	drawTitle();
	cout << endl;
	drawBoard();
	cout << endl;
	if (showMessage)
	{
		cout << message << endl;
	}
	if (activeGame)
	{
		cout << "Turno del jugador " + to_string(currentPlayer)<<endl;
	}
}

// Método simple para cambiar de jugador
int switchPlayer(int _currentPlayer)
{
	if (_currentPlayer == 1)
	{
		cout << "Turno del jugador DOS: " << "endl";
		return 2;
	}
	else
	{
		cout << "Turno del jugador UNO: " << "endl";
		return 1;
	}
}

// Este método revisa el input y el usuario y cambia el valor del array
void changeValueOnBoard(int _currentPlayer)
{
	int cell = stoi(rawInput);

	// Usamos -1 para el jugador 1, -2 para jugador 2
	switch (cell)
	{
		case 1:
			valores[0][0] = (-1)*(_currentPlayer);
			break;
		case 2:
			valores[0][1] = (-1) * (_currentPlayer);
			break;
		case 3:
			valores[0][2] = (-1) * (_currentPlayer);
			break;
		case 4:
			valores[1][0] = (-1) * (_currentPlayer);
			break;
		case 5:
			valores[1][1] = (-1) * (_currentPlayer);
			break;
		case 6:
			valores[1][2] = (-1) * (_currentPlayer);
			break;
		case 7:
			valores[2][0] = (-1) * (_currentPlayer);
			break;
		case 8:
			valores[2][1] = (-1) * (_currentPlayer);
			break;
		case 9:
			valores[2][2] = (-1) * (_currentPlayer);
			break;
	}
}

void getPCMoveToRawInput()
{
	srand(time(0));

	// num aleatorio entre 0 y 8, agrega 1.
	int randomNum = rand() % 9;

	// como regla general, es útil empezar en cinco si el turno es 2 para
	// forzar un empate, pero hagamos eso solo parte de las veces para
	// ser menos deterministas.
	if (turn == 2 && randomNum > 5)
	{
		rawInput = to_string(5);		
	}
	else
	{
		rawInput = to_string(randomNum + 1);
	}

	while (!validatePlay())
	{
		randomNum = rand() % 9;

		rawInput = to_string(randomNum + 1);
	}

	message = "PC ha elegido la posición " + rawInput;
	this_thread::sleep_for(chrono::milliseconds(1000));
}

int main()
{
	setlocale(LC_ALL, "es_MX");

	bool activeRun = true;
	
	// inicializamos algunas cosas
	cleanValores();

	options currentOption = options::menu;
	int		playerWon;
	string	playerString;

	// un while para que la ejecución no salga
	while (activeRun)
	{
		drawScreen();
		
		cout << endl;
		cout << "= Opciones disponibles =" << endl;
		cout << "a. Humano (X) vs Humano (O)." << endl;
		cout << "b. Humano (X) vs CPU (O)" << endl;
		cout << "c. Salir" << endl;
		
		// mientrás estamos en el menú permite elegir opción
		while (currentOption == options::menu)
		{
			cout << endl << "Elegir opcion: ";
			cin >> rawInput;

			if (validateRawInput(currentOption))
			{
				if (rawInput == "a")
				{
					currentOption = options::play;
					activeGame = true;
					turn = 1;
				}
				else if (rawInput == "b")
				{
					currentOption = options::playPC;
					activeGame = true;
					turn = 1;
				}
				else if (rawInput == "c")
				{
					cout << "Saliendo del programa.";
					currentOption = options::exitRun;
					activeRun = false;
				}
			}
		}
		
		// al jugar, vamos a permitir al usuario elegir una celda
		while (currentOption == options::play || currentOption == options::playPC)
		{
			while (activeGame)
			{
				if (turn == 1)
				{
					currentPlayer	= 1;
					playerWon		= 0;
					cleanValores();
				}
				
				drawScreen();
				cout << endl;
				if (currentOption == options::playPC && currentPlayer == 2)
				{
					cout << "Esperando a la PC" << endl;
				}
				else
				{
					cout << "Introduzca una celda válida" << endl;
				}
				
				if (currentOption == options::play || (currentOption == options::playPC && currentPlayer == 1))
				{
					cin >> rawInput;
				}
				else
				{
					showMessage = true;
					getPCMoveToRawInput();
				}

				// validamos el input y mostramos todo de nuevo
				if (validateRawInput(currentOption))
				{
					changeValueOnBoard(currentPlayer);

					playerWon = validateWinConditions();

					if (playerWon == -1 || playerWon == -2)
					{
						if (playerWon == -1)
						{
							playerString = "UNO";
						}
						else if (playerWon == -2)
						{
							playerString = "DOS";
						}
						drawScreen();

						cout << "¡Jugador " + playerString + " ganó! Presiona <<Intro>> para regresar al menú principal.";
						cin >> rawInput;
						
						rawInput = "";
						activeGame = false;
					}
					else if (playerWon == 999)
					{
						drawScreen();

						cout << "¡EMPATE! Presiona <<Intro>> para regresar al menú principal.";
						cin >> rawInput;

						rawInput = "";
						activeGame = false;
					}

					currentPlayer = switchPlayer(currentPlayer);
					turn++;
				};
			}

			currentOption = options::menu;
			showMessage = false;
			cleanValores();
		}
	}

	return 0;
}