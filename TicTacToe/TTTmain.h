#pragma once
#include "wx/wx.h";

class TTTmain : public wxFrame {
	private:
		const int row = 3;
		const int col = 3;
		const char ai = 'X';
		const char human = 'O';
		int count;
		int playerWins = 0;
		int aiWins = 0;
		wxButton** btn;
		wxButton* start_btn;
		wxMenuBar* menuBar = nullptr;
		char board[3][3];
	
	public:
		TTTmain();
		~TTTmain();

	private:
		void onButtonClick(wxCommandEvent&);
		void onMenuNewGame(wxCommandEvent&);
		void onMenuExit(wxCommandEvent&);
		void onGameStart(wxCommandEvent&);
		void findingMove();
		int minimax(char[][3], int, bool);
		int checkForWin(char[][3]);
		void resetGame();

		wxDECLARE_EVENT_TABLE();
};

