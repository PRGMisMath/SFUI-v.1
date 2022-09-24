#include "GButton.hpp"

#include "System.hpp"

void Button::ConfigurE()
{
	this->m_label.setCharacterSize(24);
	this->m_label.setFillColor(sf::Color::Black);
	this->setBoxAppear({ NULL, {0,0,0,0}, sf::Color(190, 190, 230), sf::Color::Black, 2 });
	this->m_esthet.addAppear({ NULL, {0,0,0,0}, sf::Color(230, 230, 255), sf::Color::Black, 2 });
	this->m_esthet.setDelay(200);
	this->UpdatePoS();
}

void Button::UpdatePoS()
{
	if (this->m_draw != NULL)
		this->m_draw->setPosition(sf::Vector2f(this->m_box.getSize().x / 2, this->m_box.getSize().y / 2));
	this->m_label.setPosition(
		{ (this->m_box.getSize().x - (this->m_label.findCharacterPos(this->m_label.getString().getSize()).x - this->m_label.getPosition().x)) * .5f, 
		(this->m_box.getSize().y - this->m_label.getCharacterSize() - 5) * .5f }
	);
}

Button::Button(std::string txt) :
	Component(),
	m_label(txt, System::get().font),
	m_draw(NULL)
{
	this->m_box.setSize({ txt.size() * 16.f, 30.f });
	this->ConfigurE();
}

std::string Button::getText()
{
	return this->m_label.getString();
}

void Button::setText(std::string txt)
{
	this->m_label.setString(txt);
}

void Button::setSize(sf::Vector2f size)
{
	Component::setSize(size);
	this->UpdatePoS();
}

void Button::on_click(Action *act)
{
	this->addAction(act, Click);
}

void Button::click()
{
	this->execute(Click);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Component::draw(target, states);

	states.transform *= this->getTransform();
	if (this->m_draw != NULL)
		target.draw(*this->m_draw, states);
	target.draw(this->m_label, states);
}

void Button::listen(const sf::Event& event)
{
	Component::listen(event);
	if (System::get().has_focus(this) && event.type == sf::Event::MouseButtonPressed) {
		this->m_esthet.cycle(false);
		this->click();
	}
}