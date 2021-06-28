#include "TTTapp.h"

wxIMPLEMENT_APP(TTTapp);

TTTapp::TTTapp() {}

TTTapp::~TTTapp() {}

bool TTTapp::OnInit() {
	f1 = new TTTmain();
	f1->Show();
	return true;
}