#include "Esthetics.hpp"
#include "System.hpp"

Appear Esthetics::getAppearFromShape(sf::Shape* shape)
{
	if (shape == NULL)
		return {};
	else
		return { shape->getTexture(), shape->getTextureRect(), shape->getFillColor(), shape->getOutlineColor(), shape->getOutlineThickness() };
}

Esthetics::Esthetics() :
	m_appears(1),
	m_time(System::time()),
	m_delay(200),
	m_current(0),
	fl_cycle(0)
{
}

void Esthetics::cycle(bool repeat)
{
	this->fl_cycle = (repeat) ? 3 : 1;
}

void Esthetics::addAppear(const Appear& appear, int index)
{
	if (index == -1)
		this->m_appears.push_back(appear);
	else
		this->m_appears.insert(this->m_appears.begin() + index, appear);
}

void Esthetics::removeAppear(int index)
{
	if (index == -1)
		this->m_appears.pop_back();
	else
		this->m_appears.erase(this->m_appears.begin() + index);
}

void Esthetics::clearAppears()
{
	this->m_appears.resize(1);
}

void Esthetics::setAppear(sf::Shape& shape, int index)
{
	shape.setFillColor(this->m_appears[index].m_fillColor);
	shape.setOutlineColor(this->m_appears[index].m_outlineColor);
	shape.setOutlineThickness(this->m_appears[index].m_outlineThickness);
	shape.setTextureRect(this->m_appears[index].m_textureRect);
	shape.setTexture(this->m_appears[index].m_texture);
	this->m_current = index;
}

void Esthetics::reloadAppear(sf::Shape& shape)
{
	this->setAppear(shape, this->m_current);
}

void Esthetics::nextAppear(sf::Shape& shape)
{
	this->setAppear(shape, (this->m_current + 1) % this->m_appears.size());
}

unsigned int Esthetics::getDelay() const
{
	return this->m_delay;
}

void Esthetics::setDelay(unsigned int delay)
{
	this->m_delay = delay;
}

Appear& Esthetics::getAppear(int index)
{
	return this->m_appears[index];
}

bool Esthetics::isCycling()
{
	return this->fl_cycle & 1U;
}

void Esthetics::update(sf::Shape& shape)
{
	if ((this->fl_cycle & 1U) && System::time() >= this->m_time + this->m_delay) {
		this->nextAppear(shape);
		this->m_time = System::time();
		if (!(this->fl_cycle & 2) && this->m_current == 0)
			this->fl_cycle = 0;
	}
}
