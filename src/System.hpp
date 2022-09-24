#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<chrono>

#define FONT_FILE_NAME "Ressource\\times.ttf"

class System
{
public:
	static System& get() {
		static System glob_sys;
		return glob_sys;
	}
private:
	System() { font.loadFromFile(FONT_FILE_NAME); }
	System(const System&) = delete;
	System operator=(const System&) = delete;
public:
	const void* get_focus();
	void set_focus(void* focus);
	bool has_focus(const void* focus);
	static time_t time();
private:
	void* m_focus = nullptr; // The 'void*' might be change to be a mother class for all GUI application
	// Add a scroll priority (SP) ==> ScrollPane::listen(event) { SP=NULL; [...] SP=this; }
public:
	sf::Font font;
};

#endif // !SYSTEM_HPP
