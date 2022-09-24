#include "GPanel.hpp"

void Panel::CalcViewedAreas()
{
	const std::vector<Component*>& cs = this->m_content->getComponents();
	for (int i = 0; i < cs.size(); ++i)
		this->m_painted[i] = this->getViewedArea().intersects(sf::FloatRect(cs[i]->getPosition(), cs[i]->getSize()));
}

Panel::Panel() :
	Component(),
	m_content(), m_painted()
{
}

Panel::Panel(Container* content) : 
	Component(),
	m_content(content), m_painted(content->getComponents().size())
{
	this->CalcViewedAreas();
}

void Panel::actualise()
{
	this->CalcViewedAreas();
}

Container* Panel::getContent() const
{
	return this->m_content;
}

void Panel::setContent(Container* content)
{
	this->m_content = content;
	this->m_painted.resize(content->getComponents().size());
	this->actualise();
}

sf::FloatRect Panel::getViewedArea() const
{
	return sf::FloatRect({0.f,0.f}, this->getSize());
}

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Component::draw(target, states);

	sf::View prec_view = target.getView(), new_view{ this->getViewedArea()};
	new_view.setViewport(sf::FloatRect(this->getPosition().x / target.getSize().x, this->getPosition().y / target.getSize().y,
		this->getSize().x / target.getSize().x, this->getSize().y / target.getSize().y));
	target.setView(new_view);

	const std::vector<Component*>& cs = this->m_content->getComponents();
	for (int i = 0; i < cs.size(); ++i) {
		if (this->m_painted[i])
			target.draw(*cs[i]);
	}
	target.setView(prec_view);
}

void Panel::listen(const sf::Event& event)
{
	//...
}
