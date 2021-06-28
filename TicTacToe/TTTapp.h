#pragma once
#include "wx/wx.h";
#include "TTTmain.h";

class TTTapp : public wxApp {
	private:
		TTTmain* f1 = nullptr;

	public:
		TTTapp();
		~TTTapp();
		virtual bool OnInit();
};

