#ifndef GUI_HPP
#define GUI_HPP

#include "GComponent.hpp"

#include "GContainer.hpp"

class GUI : public sf::Drawable, public Container {
public:
	GUI(sf::RenderWindow* parent);
	explicit GUI(sf::RenderWindow* parent, std::vector<Component*> components);
	virtual void addComponent(Component* component);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void listen(const sf::Event& event);
	void update();
private:
	// None ==> Maybe a view
	sf::Vector2f window_size;
};

#endif // !GUI_HPP
