#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GComponent.hpp"

class Button : public Component
{
private:
	void ConfigurE();
	void UpdatePoS();
public:
	enum ACT : uint8_t { Click = 0 };

	explicit Button(std::string txt = "");
	std::string getText();
	void setText(std::string txt);
	virtual void setSize(sf::Vector2f size);
	void on_click(Action *act);
	void click();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void listen(const sf::Event& event);
protected:
private:
	sf::Text m_label;
	sf::Shape* m_draw;
};

#endif // !BUTTON_HPP