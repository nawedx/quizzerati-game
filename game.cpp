#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;
string roundList[] = {"Technology", "Sports", "Politics", "Science", "Literature"};
string questionsFileList[] = {"questions/technology.txt", "questions/sports.txt", "questions/science.txt", "questions/politics.txt", "questions/literature.txt"};

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
protected:
	string playerName[6];
public:
	void getPlayerName(int playerCount)
	{
		int i, row, col;
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
	string showPlayer(int playerNumber)
	{	
		return playerName[playerNumber-1];
	}
};

class round{
	int roundNumber;
public:
	void updateRound()
	{
		roundNumber++;
	}
	int getRoundNumber()
	{
		return roundNumber;
	}
	void displayRound(int j)
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		mvprintw(row/3, (col-9)/2, "Round : %d", j+1);
		mvprintw(row/3+4, (col-roundList[j].size())/2, "%s", roundList[j].c_str());
		getch();
		clear();
		refresh();
	}
};

class score{
protected:
	int points[6];
public:
	score()
	{
		for(int i=0; i<6; i++)
			points[i]=0;
	}
	void scoreUpdateDirect(int playerID, bool responseStatus)
	{
		if(responseStatus==true)
			points[playerID]+=10;
		else if(responseStatus==false)
			points[playerID]-=5;
	}
	void scoreUpdatePass(int playerID, bool responseStatus)
	{
		if(responseStatus==true)
			points[playerID]+=5;
		else if(responseStatus==false)
			points[playerID]-=2;
	}
	int getScore(int playerID)
	{
		return points[playerID];
	}
};

class questionImport{
protected:
	string ques, a, b, c, d, correctOption, givenOption;
public:
		

};

class newGame : public playerInfo, public round, public score{
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
	void showAllScore()
	{
		int i, row, col, response;
		initscr();
		getmaxyx(stdscr, row, col);
		mvprintw(row/3-3, (col-13)/2, "Current Score");
		for(int i=0; i<players; i++)
		{
			mvprintw(row/3+(2*i), (col-25)/2-5, "%s : %d", playerName[i].c_str(), points[i]);					
			refresh();
		}
		getch();
		clear();
		refresh();		
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
			//int num=game.getPlayerCount();
			game.getPlayerName(game.getPlayerCount());
			for(int i=0; i<5; i++)
			{
				game.updateRound();
				ifstream fin;
				fin.open(questionsFileList[i]);
				game.displayRound(i);
				int row, col;
				initscr();
				getmaxyx(stdscr, row, col);
				for(int j=0; j<game.getPlayerCount(); j++)
				{
					string ques, a, b, c, d, correctOption, givenOption;
					getline(fin, ques);
					getline(fin, a);
					getline(fin, b);
					getline(fin, c);
					getline(fin, d);
					getline(fin, correctOption);
					//cout<<ques<<endl<<a<<endl<<b<<endl<<c<<endl<<d<<endl<<correctOption<<endl;
					for(int k=j, m=0; m<game.getPlayerCount(); k++, m++)
					{
						k=k%game.getPlayerCount();
						mvprintw(row/5, (col-9)/2, "Player : %d", k+1);
						mvprintw(row/3, (col-ques.size())/2, "%s", ques.c_str());
						mvprintw(row/3+4, col/3, "%s", a.c_str());
						mvprintw(row/3+4, 2*(col/3), "%s", b.c_str());
						mvprintw(row/3+8, col/3, "%s", c.c_str());
						mvprintw(row/3+8, 2*(col/3), "%s", d.c_str());
						mvprintw(row/3+14, col/2-1, " ");
						givenOption = getstring();
						//cout<<givenOption<<endl;
						refresh();				
						if(givenOption[0]=='P')
							continue;

						if(givenOption[0]==correctOption[0])
						{
							clear();
							mvprintw(row/3, (col-14)/2, "Correct answer");
							refresh();
							game.scoreUpdateDirect(j, true);
							getch();
							break;
						}
						else{
							clear();
							mvprintw(row/3, (col-12)/2, "Wrong answer");
							refresh();
							game.scoreUpdateDirect(j, false);
							getch();
							break;
						}
						refresh();
					}
				}
				fin.close();
				clear();
				game.showAllScore();
				refresh();
				

			}
			

		}
		if(response==2)
			disp.help();
		if(response==3)
			response=disp.exit();
	}
	
	endwin();
	return 0;
}