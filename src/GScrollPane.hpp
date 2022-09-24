#ifndef SCROLL_PANE_HPP
#define SCROLL_PANE_HPP

#include "GComponent.hpp"
#include "GContainer.hpp"

class ScrollPane : public Component {
private:
	sf::FloatRect CalcInternalSizE(float margin);
	void ConfigurE();
public:
	enum : uint8_t { Vertical = 0, Horizontal = 1 };

	ScrollPane();
	explicit ScrollPane(Container* content, float margin = 0.f);
	void actualise(float margin = 0.f);
	void setViewedArea(sf::FloatRect view);
	sf::FloatRect getViewedArea() const;
	void setBoundingBox(sf::FloatRect boundingBox);
	sf::FloatRect getBoundingBox() const;
	virtual void setSize(sf::Vector2f size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void listen(const sf::Event& event);
protected:
	virtual void update();
private:
	Container* m_content;
	sf::FloatRect m_view;
	sf::FloatRect m_boundings;
	sf::Transform m_transform;
	sf::VertexArray m_scrollBox;
	sf::VertexArray m_scrollBars[2];
};

#endif // !SCROLL_PANE_HPP
