#ifndef ENTRY_HPP
#define ENTRY_HPP

#include "GComponent.hpp"
#include<string>

class Entry : public Component {
private:
	void ConfigurE();
	void UpdatePoS();
public:
	enum ACT : uint8_t { Update = 0, Enter = 1 };

	Entry(std::string txt_default = "");
	std::string getText();
	void setText(std::string txt);
	void on_update(Action* act);
	void on_entry(Action* act);
	virtual void listen(const sf::Event& event);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
private:
	unsigned int m_pointer;
	sf::Text m_input;
};

#endif