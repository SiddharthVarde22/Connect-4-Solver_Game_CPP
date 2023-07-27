#include <iostream>
using namespace std;

class Board
{
	private: 
		int rows = 6, columns = 7;
		char board[6][7];
		//Winner boardWinner = NONE;
		char boardWinner = ' ';
		int numberOfDotsToConnect = 4;

		int GetEmptyRowIncolumn(int column)
		{
			int row = -1;

			for(int i = rows - 1; i >= 0; i--)
			{
				if(board[i][column] == ' ')
				{
					row = i;
					break;
				}
			}
			return row;
		}

		int VerticalCheck(char playerColor, int lastInputRow, int lastInputColumn)
		{
			int length = 0;
			for(int i = lastInputRow;length < numberOfDotsToConnect && i < rows; i++)
			{
				if(board[i][lastInputColumn] == playerColor)
				{
					length++;
				}
				else
				{
					length = 0;
					break;
				}
			}

			return length;
		}
		
		int HorizontalCheck(char playerColor, int lastInputRow, int lastInputColumn)
		{
			int mostLeftPlayerInput;
			int length = 0;

			//Find the most left element that player entered (Continuously)
			for(int i = lastInputColumn; i >= 0; i--)
			{
				if(board[lastInputRow][i] == playerColor)
				{
					mostLeftPlayerInput = i;
				}
				else
				{
					break;
				}
			}

			//check horizontal
			for(int i = mostLeftPlayerInput;length < numberOfDotsToConnect && i < columns; i++)
			{
				if(board[lastInputRow][i] == playerColor)
				{
					length++;
				}
				else
				{
					length = 0;
					break;
				}
			}

			return length;
		}

		int RightDiagonalCheck(char playerColor, int lastInputRow, int lastInputColumn)
		{
			int mostUpperRightDiagonalElementRow;
			int mostUpperRightDiagonalElementColumn;
			int length = 0;

			for(int i = lastInputRow, j = lastInputColumn; i >= 0 && j >= 0; i--,j--)
			{
				if(board[i][j] == playerColor)
				{
					mostUpperRightDiagonalElementRow = i;
					mostUpperRightDiagonalElementColumn = j;
				}
				else
				{
					break;
				}
			}
			
			for(int i = mostUpperRightDiagonalElementRow, j = mostUpperRightDiagonalElementColumn;
				(length < numberOfDotsToConnect) && (i < rows) && (j < columns); i++, j++)
			{
				if(board[i][j] == playerColor)
				{
					length++;
				}
				else
				{
					length = 0;
					break;
				}
			}

			return length;
		}

		int LeftDiagonalCheck(char playerColor, int lastInputRow, int lastInputColumn)
		{
			int mostUpperLeftDiagonalElementRow;
			int mostUpperLeftDiagonalElementColumn;
			int length = 0;

			for(int i = lastInputRow, j = lastInputColumn; i >= 0 && j < columns; i--, j++)
			{
				if(board[i][j] == playerColor)
				{
					mostUpperLeftDiagonalElementRow = i;
					mostUpperLeftDiagonalElementColumn = j;
				}
				else
				{
					break;
				}
			}

			for(int i = mostUpperLeftDiagonalElementRow, j = mostUpperLeftDiagonalElementColumn;
				(length < numberOfDotsToConnect) && (i < rows) && (j >= 0); i++, j--)
			{
				if(board[i][j] == playerColor)
				{
					length++;
				}
				else
				{
					length = 0;
					break;
				}
			}

			return length;
		}

		void CheckForDraw()
		{
			for(int i = 0; i < columns; i++)
			{
				if(board[0][i] == ' ')
				{
					break;
				}
				else if (i == columns - 1)
				{
					boardWinner = '#';
				}
			}
		}

		void CheckIfConnected4OrNot(char playerColor, int lastInputRow, int lastInputColumn)
		{
			//check if the game is Over or Not
			int length = 0;
			//check downwards
			if(length < numberOfDotsToConnect)
			{
				length = VerticalCheck(playerColor, lastInputRow, lastInputColumn);
			}
			
			if(length < numberOfDotsToConnect)
			{
				length = HorizontalCheck(playerColor, lastInputRow, lastInputColumn);
			}

			if(length < numberOfDotsToConnect)
			{
				length = RightDiagonalCheck(playerColor, lastInputRow, lastInputColumn);
			}

			if(length < numberOfDotsToConnect)
			{
				length = LeftDiagonalCheck(playerColor, lastInputRow, lastInputColumn);
			}

			if(length < numberOfDotsToConnect)
			{
				CheckForDraw();
			}

			//Set the value of winning color
			if(length >= numberOfDotsToConnect)
			{
				boardWinner = playerColor;
			}
		}

	public :
		Board()
		{
			for(int i = 0;i < rows; i++)
			{
				for(int j = 0; j < columns; j++)
				{
					board[i][j] = ' ';
				}
			}
		}
		
		void PrintTheBoard()
		{
			for(int i = 0; i < rows; i++)
			{
				cout<< "\n---------------" << endl;
				//cout << "Row " << i << endl;
				cout << "|";
				for(int j = 0; j < columns; j++)
				{
					cout << board[i][j];
					cout << "|";
				}
			}
			cout<< "\n---------------" << endl;
		}

		int GetColumns()
		{
			return columns;
		}

		bool OccupieTheSlotOnTheBoard(int column, char playerColor)
		{
			int row = GetEmptyRowIncolumn(column);
			if(row == -1)
			{
				return false;
			}

			board[row][column] = playerColor;
			PrintTheBoard();
			CheckIfConnected4OrNot(playerColor, row, column);
			return true;
		}

		char GetGameWinner()
		{
			return boardWinner;
		}
};

class Player
{
	char color;
	string name;

	public:
		Player(char color, string name)
		{
			this->color = color;
			this->name = name;
		}

		char GetPlayerColor()
		{
			return color;
		}

		string GetPlayerName()
		{
			return name;
		}
};

class Input
{
	int maxInput;

	public:
		Input(int maxInput)
		{
			this->maxInput = maxInput;
		}

		int TakeInput()
		{
			int playerInput;
			cout << "enter column number between 1 to " << maxInput << " \t";
			cin >> playerInput;
			playerInput--;
			if(playerInput >= maxInput || playerInput < 0)
			{
				cout << "enter valid Input\n";
				playerInput = TakeInput();
			}
			return playerInput;
		}
};

enum Winner
{
	NONE,
	RED,
	BLUE,
	DRAW,
};

class GameplayManager
{
	Board playBoard;
	Input input = Input(playBoard.GetColumns());
	Player player1 = Player('R', "Player1");
	Player player2 = Player('B', "Player2");

	//bool isGameOver = false;
	Winner winnerOfGame = NONE;

	void PlayerTurn(Player player)
	{
		bool columnIsEmpty;

		do
		{
			cout << player.GetPlayerName() << " " << player.GetPlayerColor() << endl;
			int playerInput = input.TakeInput();
			columnIsEmpty = playBoard.OccupieTheSlotOnTheBoard(playerInput, player.GetPlayerColor());
			if(columnIsEmpty == false)
			{
				cout << "Column You entered is already full\nPlease choose another column\n";
			}
		} while (columnIsEmpty == false);
	}

	void CheckForWinner()
	{
		char winnerColor = playBoard.GetGameWinner();
		switch (winnerColor)
		{
			case 'R':
				winnerOfGame = RED;
				break;
			case 'B':
				winnerOfGame = BLUE;
				break;
			case ' ':
				winnerOfGame = NONE;
				break;
			default:
				winnerOfGame = DRAW;
				break;
		}
	}

	void IntroduceTheGame()
	{
		cout << "-----------------------------------------\n";
		cout << "| \t \t Hello \t \t\t|\n| \t Welcome to Connect-4 Game \t|\n";
		cout << "-----------------------------------------\n";

		cout <<"\nRules :\n";
		cout <<"1 - Player 1 has Color Red(R)\nPlayer 1 has first Turn\n";
		cout <<"2 - Player 2 has Color Blue(B)\nPlayer 2 has next Turn\n"
		<<	"Both players gets their turn One after another\n";
		cout << "3 - Players needs to Connect 4 places continuous"
		<< "Horizontally/Vertically/Diagonally to win the game\n";
	}

	void ShowTheWinner()
	{
		string winner;

		switch (winnerOfGame)
		{
		case RED:
			winner = "\t     Winner is Player1 - RED \t\t";
			break;
		case BLUE:
			winner = "\t    Winner is Player2 - BLUE \t\t";
			break;
		default:
			winner = "\t\t   Game DRAW\t\t\t";
			break;
		}

		cout << "-------------------------------------------------\n";
		cout << "| \t \t \t \t \t \t|\n";
		cout << "|"<< winner <<"|\n";
		cout << "| \t \t \t \t \t \t|\n";
		cout << "-------------------------------------------------\n";
	}

	public:
		GameplayManager()
		{
			IntroduceTheGame();
			playBoard.PrintTheBoard();
		}
		void Gameplay()
		{
			while(winnerOfGame == NONE)
			{
				PlayerTurn(player1);
				CheckForWinner();
				if(winnerOfGame == NONE)
				{
					PlayerTurn(player2);
				}
				CheckForWinner();
			}

			ShowTheWinner();
		}
};

int main()
{
	GameplayManager gameplayManager = GameplayManager();
	gameplayManager.Gameplay();

	return 0;
}