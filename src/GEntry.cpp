#include "GEntry.hpp"
#include "System.hpp"

void Entry::ConfigurE()
{
	this->setBoxAppear({ NULL, {0,0,0,0}, sf::Color::White, sf::Color::Black, 2 });
	this->m_input.setCharacterSize(24);
	this->m_input.setFillColor(sf::Color::Black);
	this->UpdatePoS();
}

void Entry::UpdatePoS()
{
	this->m_input.setPosition(5, this->m_box.getSize().y * .5f);
}

Entry::Entry(std::string txt_default) :
	Component(),
	m_input(txt_default, System::get().font), m_pointer(txt_default.size())
{
	this->ConfigurE();
}

std::string Entry::getText()
{
	return this->m_input.getString();
}

void Entry::setText(std::string txt)
{
	this->m_input.setString(txt);
}

void Entry::on_update(Action* act)
{
	this->addAction(act, Update);
}

void Entry::on_entry(Action* act)
{
	this->addAction(act, Enter);
}

void Entry::listen(const sf::Event& event)
{
	Component::listen(event);

	if (!this->m_canFocus || !System::get().has_focus(this)) return;
	switch (event.type)
	{
	case sf::Event::TextEntered:
		if (event.text.unicode < 127 && event.text.unicode > 31) {
			std::string modif = this->m_input.getString();
			modif.insert(this->m_pointer, 1, static_cast<char>(event.text.unicode));
			this->m_input.setString(modif);
			++this->m_pointer;
			this->execute(Update);
		}
		break;
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Enter:
			System::get().set_focus(NULL);
			this->execute(Enter);
		case sf::Keyboard::BackSpace:
			if (!this->m_input.getString().isEmpty() && this->m_pointer != 0) {
				this->m_input.setString(this->m_input.getString().substring(0, this->m_pointer - 1) + this->m_input.getString().substring(this->m_pointer, this->m_input.getString().getSize()));
				--this->m_pointer;
				this->execute(Update);
			}
			break;
		case sf::Keyboard::Right:
			if (this->m_pointer < this->m_input.getString().getSize())
				++this->m_pointer;
			break;
		case sf::Keyboard::Left:
			if (this->m_pointer != 0)
				--this->m_pointer;
			break;
		}
		break;
	}
}

void Entry::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Component::draw(target, states);

	states.transform *= this->getTransform();
	target.draw(this->m_input, states);
	if (System::get().has_focus(this) && (int)(.001 * System::time()) % 2) {
		sf::RectangleShape point_bar{ {2.f, (float)this->m_input.getCharacterSize()} };
		point_bar.setPosition({ this->m_input.findCharacterPos(this->m_pointer).x, this->m_input.findCharacterPos(this->m_pointer).y + 2 });
		point_bar.setFillColor(sf::Color());
		target.draw(point_bar, states);
	}
}
