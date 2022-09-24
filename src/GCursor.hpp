#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "GComponent.hpp"

class Cursor : public Component {
private:
	void ConfigurE();
	void UpdateCursoR();
	void SetCursorPositioN(sf::Vector2f pos);
public:
	enum ACT : uint8_t { UPDATE = 0 };

	explicit Cursor(unsigned int range = 10, unsigned int start_value = 0);
	unsigned int get();
	void set(unsigned int value);
	virtual void setSize(sf::Vector2f size);
	void on_update(Action* act);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void listen(const sf::Event& event);
protected:
private:
	sf::ConvexShape m_cursor;
	struct {
		unsigned int range = 0U;
		float resolution = 1.f;
		unsigned int value = 0U;
	} m_data;
	bool m_drag = false;
};

#endif // !CURSOR_HPP