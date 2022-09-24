#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include<SFML/Graphics.hpp>
#include "Action.hpp"
#include "Esthetics.hpp"

class Component : public sf::Drawable, public sf::Transformable, public ActionsManager
{
public:
	Component();
	void setBoxAppear(Appear appear);
	Appear getBoxAppear();
	sf::Vector2f getSize() const;
	void setSize(sf::Vector2f size);
	bool isFocusable() const;
	void canFocus(bool canFocus);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void listen(const sf::Event& event);
protected:
	virtual void update();
	virtual void update(sf::Vector2f window_size);

	friend class GUI;
	friend class ScrollPane;
protected:
	sf::RectangleShape m_box;
	Esthetics m_esthet;
	bool m_canFocus = true;
};

#endif