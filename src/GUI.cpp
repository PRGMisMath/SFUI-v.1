#include "GUI.hpp"

GUI::GUI(sf::RenderWindow* parent) :
	Container(), window_size(parent->getSize())
{
}

GUI::GUI(sf::RenderWindow* parent, std::vector<Component*> components) :
	Container(components), window_size(parent->getSize())
{
}

void GUI::addComponent(Component* component)
{
	Container::addComponent(component);
	component->update(window_size);
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Component* c : this->m_compounds)
		c->draw(target, states);
}

void GUI::listen(const sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		window_size = { event.size.width,event.size.height };
	}
	for (Component* c : this->m_compounds)
		c->listen(event);
}

void GUI::update()
{
	for (Component* c : this->m_compounds)
		c->update();
}
