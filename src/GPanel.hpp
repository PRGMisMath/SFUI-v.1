#ifndef PANEL_HPP
#define PANEL_HPP

#include "GComponent.hpp"
#include "GContainer.hpp"

class Panel : public Component {
protected:
	void CalcViewedAreas();
public:
	Panel();
	explicit Panel(Container* content);
	void actualise();
	Container* getContent() const;
	void setContent(Container* content);
	virtual sf::FloatRect getViewedArea() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void listen(const sf::Event& event);
protected:
	virtual void update(sf::Vector2f window_size);
private:
	Container* m_content;
	std::vector<bool> m_painted;
};

#endif // !PANEL_HPP
