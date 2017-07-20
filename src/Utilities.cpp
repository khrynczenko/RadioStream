#include "../include/Utilities.hpp"
#include <Windows.h>
#include <iostream>

float volume_int_to_float(int vol)
{
	return float(vol) / 100.f;
}

unsigned int volume_float_to_int(float vol)
{
	return unsigned int(vol*100.f);
}

bool str_to_bool(const std::string& str)
{
	return str == "true" ? true : false;
}

std::string bool_to_str(bool b)
{
	return b ? "true" : "false";
}

char easytolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}


void copy_to_clipboard(const std::string& message)
{
#ifdef _WIN32
    std::cout << message;
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        HGLOBAL hg = GlobalAlloc(GHND, message.size() + 1);
        
        memcpy(GlobalLock(hg), message.c_str(), message.size() + 1);
        GlobalUnlock(hg);
        if (!SetClipboardData(CF_TEXT, hg))
            throw std::exception("Could not set new data to clipboard.");
        CloseClipboard();
        GlobalFree(hg);
    }
    else
    {
        throw std::exception("Could not open clipboard.");
    }
#elif defined __linux__
#include <X11/Xlib.h>
    void copy_to_clipboard(const std::string& message)
    {
    }
#endif
}




