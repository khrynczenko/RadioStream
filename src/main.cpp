#include <iostream>
#include <nana/gui.hpp>
#include "../include/Application.hpp"
#include <string>
//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
int main()
{
	nana::internationalization i18n;
	//Translate these 2 words into Chinese.

	i18n.set("OK", "Elo");
	i18n.set("Cancel", "Yo");
	try {
		Application app{};
		nana::exec();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	catch (...)
	{
		std::cout << "Unidentified exception.";
	}
}