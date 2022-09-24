#include "Cursor.hpp"

#include "System.hpp"

void Cursor::ConfigurE()
{
	this->m_box.setSize({ (this->m_data.max_value - this->m_data.min_value) / (float)this->m_data.resolution, 10.f });
	this->setBoxAppear({ NULL, {0,0,0,0}, sf::Color(230, 230, 230), sf::Color(200, 200, 200), 2 });
	this->m_cursor.setPoint(0, sf::Vector2f(-2, -2));
	this->m_cursor.setPoint(1, sf::Vector2f(2, -2));
	this->m_cursor.setPoint(2, sf::Vector2f(2, 6));
	this->m_cursor.setPoint(3, sf::Vector2f(0, 8));
	this->m_cursor.setPoint(4, sf::Vector2f(-2, 6));
	this->m_cursor.setFillColor(sf::Color(230, 230, 230));
	this->m_cursor.setOutlineColor(sf::Color(200, 200, 200));
	this->m_cursor.setOutlineThickness(2);
}

void Cursor::UpdateSizE()
{
	// Complete
}

void Cursor::UpdateCursoR()
{
	this->m_cursor.setPosition({ this->m_data.value * this->m_data.resolution, this->m_box.getSize().y * .5f });
}

void Cursor::SetCursorPositioN(sf::Vector2f pos)
{
	float relX = this->getInverseTransform().transformPoint(pos).x / this->m_data.resolution;
	if (relX < 0) this->m_data.value = 0;
	else if (relX > this->m_data.range) this->m_data.value = this->m_data.range;
	else this->m_data.positon = (unsigned int)relX;
	this->UpdateCursoR();
}


Cursor::Cursor(int range) :
	Component(),
	m_cursor()
{
	this->m_data.range = range;
	this->ConfigurE();
}

unsigned int Cursor::get()
{
	return this->m_data.value;
}

void Cursor::set(unsigned int value)
{
	this->m_data.value = (value > this->m_data.range) ? this->m_data.range : value;
}

void Cursor::setSize(sf::Vector2f size)
{
	// Complete
}

void Cursor::on_update(Action* act)
{
	this->addAction(act, UPDATE);
}


void Cursor::listen(const sf::Event& event)
{
	Component::listen(event);
	// Focus sur le curseur
	if (this->m_canFocus && event.type == sf::Event::MouseButtonPressed && this->m_cursor.getLocalBounds().contains(this->getInverseTransform().transformPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))))
		System::get().set_focus(this);

	switch (event.type)	{
	case sf::Event::MouseButtonPressed:
		if (System::get().has_focus(this)) {
			this->SetCursorPositioN(sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
			this->execute(UPDATE);
		}
	}
}

void Cursor::update()
{
	Component::update();
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Component::draw(target, states);

	states.transform *= this->getTransform();
	target.draw(this->m_cursor, states);
}
