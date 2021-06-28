#include "TTTmain.h"
#include <cstring>

wxBEGIN_EVENT_TABLE(TTTmain, wxFrame)
EVT_MENU(100, TTTmain::onMenuNewGame)
EVT_MENU(101, TTTmain::onMenuExit)
wxEND_EVENT_TABLE()

TTTmain::TTTmain() : wxFrame(nullptr, wxID_ANY, "TicTacToe", wxPoint(-1, -1), wxSize(800, 600)) {
	btn = new wxButton * [row * col];
	memset(board, '\0', sizeof(board));
	wxGridSizer* grid = new wxGridSizer(4, 3, 0, 0);
    wxFont font(36, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
   
    menuBar = new wxMenuBar();
    this->SetMenuBar(menuBar);
    wxMenu* menu = new wxMenu();
    menu->Append(100, "New Game");
    menu->Append(101, "Exit");
    menuBar->Append(menu, "File");
    
    start_btn = new wxButton(this, 10, wxT("Start"));
    start_btn->SetFont(font);
    grid->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND | wxALL);
    grid->Add(start_btn, 1, wxEXPAND | wxALL);
    grid->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND | wxALL);
    start_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TTTmain::onGameStart, this);
	
    for(int i = 0; i < row; i++){
		for (int j = 0; j < col; j++) {
			btn[j * row + i] = new wxButton(this, 1000 + (j * row + i));
            btn[j * row + i]->SetFont(font);
			grid->Add(btn[j * row + i], 1, wxEXPAND | wxALL);
			btn[j * row + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TTTmain::onButtonClick, this);
            btn[j * row + i]->Enable(false);
		}
	}
    
	this->SetSizer(grid);
	grid->Layout();
    count = 1;
}

TTTmain::~TTTmain() {
	delete[] btn;
}

void TTTmain::onButtonClick(wxCommandEvent& e) {
	int x = (e.GetId() - 1000) % row;
	int y = (e.GetId() - 1000) / row;

	btn[y * row + x]->Enable(false);
	board[x][y] = 'O';
	btn[y * row + x]->SetLabel("O");
    count++;
    findingMove();
    count++;

    if (checkForWin(board) == 1) {
        wxMessageBox("X wins");
        resetGame();
    } else if (checkForWin(board) == -1) {
        wxMessageBox("O wins");
        resetGame();
    } else if (count == 9) {
        wxMessageBox("Tie Game");
        resetGame();
    }
	e.Skip();
}

void TTTmain::onMenuNewGame(wxCommandEvent& e) {
    resetGame();
    e.Skip();
}

void TTTmain::onMenuExit(wxCommandEvent& e) {
    Close();
    e.Skip();
}

void TTTmain::onGameStart(wxCommandEvent& e) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            btn[j * row + i]->Enable(true);
        }
    }
    start_btn->Enable(false);
    findingMove();
}

void TTTmain::findingMove() {
    int bestScore = std::numeric_limits<int>::min();
    int bestMove[2] = {};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '\0') {
                board[i][j] = ai;
                int score = minimax(board, 0, false);
                board[i][j] = '\0';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }
    board[bestMove[0]][bestMove[1]] = 'X';
    btn[bestMove[1] * row + bestMove[0]]->SetLabel("X");
    btn[bestMove[1] * row + bestMove[0]]->Enable(false);
}

int TTTmain::minimax(char board[][3], int depth, bool isMaximum) {
    int winner = checkForWin(board);
    if (winner != 0) {
        return winner - depth;
    }
    if (isMaximum) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '\0') {
                    board[i][j] = ai;
                    int score = minimax(board, depth + 1, !isMaximum);
                    bestScore = std::max(score, bestScore);
                    board[i][j] = '\0';
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '\0') {
                    board[i][j] = human;
                    int score = minimax(board, depth + 1, !isMaximum);
                    bestScore = std::min(score, bestScore);
                    board[i][j] = '\0';
                }
            }
        }
        return bestScore;
    }
}

int TTTmain::checkForWin(char board[][3]) {
    //Rows
    for (int i = 0; i < row; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == ai) {
                return 1;
            } else if (board[i][0] == human) {
                return -1;
            }
        }
    }
    //Columns
    for (int i = 0; i < col; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == ai) {
                return 1;
            } else if (board[0][i] == human) {
                return -1;
            }
        }
    }
    //Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == ai) {
            return 1;
        } else if (board[0][0] == human) {
            return -1;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == ai) {
            return 1;
        } else if (board[0][2] == human) {
            return -1;
        }
    }
    return 0;
}

void TTTmain::resetGame() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            memset(board, '\0', sizeof(board));
            btn[j * row + i]->SetLabel("");
            btn[j * row + i]->Enable(false);
            count = 1;
        }
    }
    start_btn->Enable(true);
}