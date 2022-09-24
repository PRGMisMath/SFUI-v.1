#include "GCursor.hpp"

#include "System.hpp"

void Cursor::ConfigurE()
{
	this->m_box.setSize({ this->m_data.range * this->m_data.resolution, 10.f });
	this->setBoxAppear({ NULL, {0,0,0,0}, sf::Color(230, 230, 230), sf::Color(200, 200, 200), 2 });
	this->m_cursor.setPointCount(5);
	this->m_cursor.setPoint(0, sf::Vector2f(-3, -3));
	this->m_cursor.setPoint(1, sf::Vector2f(3, -3));
	this->m_cursor.setPoint(2, sf::Vector2f(3, 9));
	this->m_cursor.setPoint(3, sf::Vector2f(0, 12));
	this->m_cursor.setPoint(4, sf::Vector2f(-3, 9));
	this->m_cursor.setFillColor(sf::Color(230, 230, 230));
	this->m_cursor.setOutlineColor(sf::Color(200, 200, 200));
	this->m_cursor.setOutlineThickness(2);
}

void Cursor::UpdateCursoR()
{
	this->m_cursor.setPosition({ this->m_data.value * this->m_data.resolution, 0.f });
}

void Cursor::SetCursorPositioN(sf::Vector2f pos)
{
	float relX = this->getInverseTransform().transformPoint(pos).x / this->m_data.resolution;
	if (relX < 0) this->m_data.value = 0;
	else if (relX > this->m_data.range) this->m_data.value = this->m_data.range;
	else this->m_data.value = (unsigned int)relX;
	this->UpdateCursoR();
}


Cursor::Cursor(unsigned int range, unsigned int start_value) :
	Component(),
	m_cursor()
{
	this->m_data.range = range;
	this->m_data.value = start_value;
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
	this->m_cursor.scale({ size.y / this->m_box.getSize().y, size.y / this->m_box.getSize().y });
	this->m_data.resolution *= size.x / this->m_box.getSize().x;
	Component::setSize(size);
	this->UpdateCursoR();
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

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (System::get().has_focus(this)) {
			this->SetCursorPositioN(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			this->execute(UPDATE);
			this->m_drag = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		this->m_drag = false;
		break;
	case sf::Event::MouseMoved:
		if (this->m_drag) {
			this->SetCursorPositioN(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			this->execute(UPDATE);
		}
		break;
	}
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Component::draw(target, states);

	states.transform *= this->getTransform();
	target.draw(this->m_cursor, states);
}
