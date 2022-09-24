#include "GScrollPane.hpp"

#include "System.hpp"

sf::FloatRect ScrollPane::CalcInternalSizE(float margin)
{
	if (this->m_content->getComponents().size() == 0) return { 0,0,10,10 };
	sf::FloatRect res{ this->m_content->getComponents()[0]->getPosition(), this->m_content->getComponents()[0]->getPosition() };
	for (Component* c : this->m_content->getComponents()) {
		if (c->getPosition().x < res.left) res.left = c->getPosition().x;
		if (c->getPosition().y < res.top) res.top = c->getPosition().y;
		if (c->getPosition().x + c->getSize().x > res.width) res.width = c->getPosition().x + c->getSize().x;
		if (c->getPosition().y + c->getSize().y > res.height) res.height = c->getPosition().y + c->getSize().y;
	}
	return sf::FloatRect(res.left - margin, res.top - margin, res.width - res.left + 2*margin, res.height - res.top + 2*margin);
}

void ScrollPane::ConfigurE()
{
	this->setBoxAppear({ NULL, {0,0,0,0}, sf::Color::White, sf::Color::Black, 2 });
	// Add ScrollBar
}

ScrollPane::ScrollPane() :
	Component(),
	m_content(),
	m_boundings(), m_view(),
	m_transform(),
	m_scrollBox(), m_scrollBars()
{
	this->ConfigurE();
}

ScrollPane::ScrollPane(Container* content, float margin) :
	Component(),
	m_content(content),
	m_boundings(), m_view(),
	m_transform(),
	m_scrollBox(), m_scrollBars()
{
	this->m_boundings = this->CalcInternalSizE(margin);
	this->m_view = { this->m_boundings.left, this->m_boundings.top, 0, 0 };
	this->ConfigurE();
}

void ScrollPane::actualise(float margin)
{
	this->m_boundings = this->CalcInternalSizE(margin);
}

void ScrollPane::setViewedArea(sf::FloatRect view)
{
	this->m_view = view;
	this->m_transform = sf::Transform::Identity;
	this->m_transform.translate({ -view.left, -view.top });
}

sf::FloatRect ScrollPane::getViewedArea() const
{
	return this->m_view;
}

void ScrollPane::setBoundingBox(sf::FloatRect boundingBox)
{
	this->m_boundings = boundingBox;
}

sf::FloatRect ScrollPane::getBoundingBox() const
{
	return this->m_boundings;
}

void ScrollPane::setSize(sf::Vector2f size)
{
	Component::setSize(size);
	this->setViewedArea(sf::FloatRect(this->m_view.left, this->m_view.top, size.x, size.y));
}

void ScrollPane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Component::draw(target, states);
	
	sf::View prec_view = target.getView(), new_view{ this->m_view };
	new_view.setViewport(sf::FloatRect(this->getPosition().x / target.getSize().x, this->getPosition().y / target.getSize().y,
		this->getSize().x / target.getSize().x, this->getSize().y / target.getSize().y));
	target.setView(new_view);

	for (Component* c : this->m_content->getComponents()) {
		if (this->m_view.intersects(sf::FloatRect(c->getPosition(),c->getSize())))
			target.draw(*c);
	}
	target.setView(prec_view);
	states.transform *= this->getTransform();
	target.draw(this->m_scrollBox, states);
	target.draw(this->m_scrollBars[Vertical], states);
	target.draw(this->m_scrollBars[Horizontal], states);
}

void ScrollPane::listen(const sf::Event& event)
{
	Component::listen(event);

	sf::Event intEvent = event;
	sf::Vector2f new_pos;
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		new_pos = (this->m_transform * this->getTransform()).getInverse().transformPoint({ (float)event.mouseButton.x, (float)event.mouseButton.y });
		intEvent.mouseButton.x = new_pos.x;
		intEvent.mouseButton.y = new_pos.y;
		break;
	case sf::Event::MouseMoved:
		new_pos = (this->m_transform * this->getTransform()).getInverse().transformPoint({ (float)event.mouseMove.x, (float)event.mouseMove.y });
		intEvent.mouseMove.x = new_pos.x;
		intEvent.mouseMove.y = new_pos.y;
		break;
	case sf::Event::MouseWheelScrolled:
		new_pos = (this->m_transform * this->getTransform()).getInverse().transformPoint({ (float)event.mouseWheelScroll.x, (float)event.mouseWheelScroll.y });
		intEvent.mouseWheelScroll.x = new_pos.x;
		intEvent.mouseWheelScroll.y = new_pos.y;
		break;
	}
	for (Component* c : this->m_content->getComponents())
		c->listen(intEvent);

	switch (event.type) {
	case sf::Event::MouseWheelScrolled:
		if (this->m_canFocus && m_box.getLocalBounds().contains(this->getInverseTransform().transformPoint(sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y)))) {
			sf::Vector2f movent{ -5 * event.mouseWheelScroll.delta * (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel), -5 * event.mouseWheelScroll.delta * (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) };
			this->m_view = { this->m_view.left + movent.x, this->m_view.top + movent.y, this->m_view.width, this->m_view.height };
			if (this->m_view.left + this->m_view.width > this->m_boundings.left + this->m_boundings.width)
				this->m_view.left = this->m_boundings.left + this->m_boundings.width - this->m_view.width;
			if (this->m_view.top + this->m_view.height > this->m_boundings.top + this->m_boundings.height)
				this->m_view.top = this->m_boundings.top + this->m_boundings.height - this->m_view.height;
			if (this->m_view.left < this->m_boundings.left)
				this->m_view.left = this->m_boundings.left;
			if (this->m_view.top < this->m_boundings.top)
				this->m_view.top = this->m_boundings.top;
			this->m_transform = sf::Transform::Identity;
			this->m_transform.translate({ -this->m_view.left, -this->m_view.top });
		}
		break;
	}
}

void ScrollPane::update()
{
	Component::update();

	for (Component* c : this->m_content->getComponents())
		c->update();
}
