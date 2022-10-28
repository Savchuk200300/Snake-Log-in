#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

	const int width = 20;
	const int heigth = 20;
	int x, y, fruitX, fruitY, score;
	int TailX[100], TailY[100];
	int nTail;
	enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirecton dir;
	bool gameOver;
	void setup();
	void Draw();
	void Input();
	void Logic();
		
	class Log{
		string username;
		string password;
		string un;
		string pw;
		
		
	public:
		
		bool IsLoggedIn() {
			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;
			ifstream read(username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password) {
				return true;

			}
			else
			{ 
				return false;
			}
			
		}
		void Chose() {
			bool status;
			int choice;
			cout << "1: Register\n2: Login\n3: Option\n Your choice: ";
			cin >> choice;
			if (choice == 1) {
				cout << "select a username : ";
					cin >> username;
					cout << "select a password : ";
					cin >> password;
					ofstream file;
					file.open(username + ".txt");

					file << username << endl << password;
					file.close();
					Chose();
			}
			else 
				if (choice == 3) {
					cout << "Tap w to go up" << endl;
					cout << "Tap d to go right" << endl;
					cout << "Tap s to go down" << endl;
					cout << "Tap a to go left" << endl;
					Chose();
				}
				if (choice == 2) {
					status = IsLoggedIn();
					if (status) {
						
						setup();
						while (!gameOver) {
							Draw();
							Input();
							Logic();
							Sleep(10);
						}
						ofstream file;
						file.open(username + ".txt");

						file << username << endl << password << endl << score;
						file.close();
					}
					else cout << "Failure" << endl;
					Chose();
					
				}
			

		}
	};
	void setup()
	{
		gameOver = false;
		dir = STOP;
		x = width / 2;
		y = heigth / 2;
		fruitX = rand() % width;
		fruitY = rand() % heigth;
		score = 0;

	}
	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;

		for (int i = 0; i < heigth; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j == 0)
					cout << "#";
				if (i == y && j == x)
					cout << "0";
				else
					if (i == fruitY && j == fruitX)
						cout << "F";
					else {
						bool print = false;
						for (int k = 0; k < nTail; k++)
						{

							if (TailX[k] == j && TailY[k] == i) {
								cout << "o";
								print = true;
							}
						}
						if (!print)
							cout << " ";
					}
				if (j == width - 1)
					cout << "#";
			}
			cout << endl;

		}
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		cout << "Score: " << score << endl;

	}
	void Input()
	{
		if (_kbhit()) {
			switch (_getch())
			{
			case 'a':
				dir = LEFT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				gameOver = true;
				break;

			}
		}
	}
	void Logic()
	{
		int PrevX = TailX[0];
		int PrevY = TailY[0];
		int Prev2X, Prev2Y;
		TailX[0] = x;
		TailY[0] = y;
		for (int i = 1; i < nTail; i++) {
			Prev2X = TailX[i];
			Prev2Y = TailY[i];
			TailX[i] = PrevX;
			TailY[i] = PrevY;
			PrevX = Prev2X;
			PrevY = Prev2Y;
		}
		switch (dir)
		{

		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
		}
		//if (x > width || x < 0 || y > heigth|| y<0) {
			//gameOver = true;

		if (x >= width) x = 0; else if (x < 0) x = width - 1;
		if (y >= heigth) y = 0; else if (y < 0) y = heigth - 1;

		for (int i = 0; i < nTail; i++){
			if (TailX[i] == x && TailY[i] == y)
				gameOver = true; 
			}

		if (x == fruitX && y == fruitY) {
			score += 10;
			fruitX = rand() % width;
			fruitY = rand() % heigth;
			nTail++;
		}
	}

int main()
{
	Log log;
	log.Chose();

	return 0;
}

