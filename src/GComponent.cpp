#include "GComponent.hpp"

#include "System.hpp"

Component::Component() :
	Transformable(),
	ActionsManager(),
	m_esthet(),
	m_box()
{
}

void Component::setBoxAppear(Appear appear)
{
	this->m_esthet.getAppear(0) = appear;
	this->m_esthet.reloadAppear(this->m_box);
}

Appear Component::getBoxAppear()
{
	return this->m_esthet.getAppear(0);
}

sf::Vector2f Component::getSize() const
{
	return this->m_box.getSize();
}

void Component::setSize(sf::Vector2f size)
{
	this->m_box.setSize(size);
}

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	target.draw(m_box, states);
}

void Component::listen(const sf::Event& event)
{
	if (this->m_canFocus && event.type == sf::Event::MouseButtonPressed && m_box.getLocalBounds().contains(this->getInverseTransform().transformPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))))
		System::get().set_focus(this);
	else if (System::get().has_focus(this) && event.type == sf::Event::MouseButtonPressed)
		System::get().set_focus(NULL);
}

void Component::update()
{
	this->m_esthet.update(this->m_box);
}

bool Component::isFocusable() const
{
	return this->m_canFocus;
}

void Component::canFocus(bool canFocus)
{
	this->m_canFocus = canFocus;
}

