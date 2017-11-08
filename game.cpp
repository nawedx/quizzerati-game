#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;
string getstring()
{
    string input;
    // let the terminal do the line editing
    nocbreak();
    echo();
    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();
    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }
    // restore your cbreak / echo settings here
    return input;
}
class display{
public:
	int splashScreen()
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		ifstream file;
		file.open("resources/ascii-art/splashscreen.txt");
		string s;
		for(int i=0; getline(file, s); i++)
			mvprintw(row/4+i, (col-s.size())/2, "%s", s.c_str());
		file.close();
		mvprintw(row/2, (col-11)/2, "1. NEW GAME\n");
		mvprintw(row/2+2, (col-11)/2, "2. HELP\n");
		mvprintw(row/2+4, (col-11)/2, "3. EXIT\n");
		mvprintw(row-row/6, (col-53)/2, "Enter 1, 2, 3 as per your preference and press enter.");			
		refresh();
		cin>>response;
		clear();
		refresh();
		return response;

	}
	void help()
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		ifstream file;
		file.open("resources/ascii-art/help.txt");
		string s;
		for(int i=0; getline(file, s); i++)
			mvprintw(row/4+i, (col-s.size())/2, "%s", s.c_str());
		file.close();
		getch();
		clear();
		refresh();		
	}
	int exit()
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		ifstream file;
		file.open("resources/ascii-art/exit.txt");
		string s;
		for(int i=0; getline(file, s); i++)
			mvprintw(row/3+i, (col-s.size())/2, "%s", s.c_str());
		file.close();
		getch();
		clear();
		refresh();
		return 0;
	}
};
class playerInfo{
	string playerName[6];
public:
	void getPlayerName(int playerCount)
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		for(int i=0; i<playerCount; i++)
		{
			mvprintw(row/3+(2*i), (col-25)/2-5, "Enter name of player %d : ", i+1);
			playerName[i] = getstring();
			refresh();
		}
		clear();
		refresh();
	}
};
class newGame : public playerInfo{
	int players;
public:
	void playerCount()
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		mvprintw(row/3, (col-25)/2-5, "Enter number of players : ");
		mvscanw(row/3, col/2+9, "%d", &players);
		clear();
		refresh();
	}
	int getPlayerCount()
	{
		return players;
	}
};


int main()
{
	display disp;
	int response=1;	
	while(response)
	{
		response=disp.splashScreen();
		if(response==1)
		{
			newGame game;
			game.playerCount();
			game.getPlayerName(game.getPlayerCount());
		}
		if(response==2)
			disp.help();
		if(response==3)
			response=disp.exit();
	}
	
	endwin();
	return 0;
}