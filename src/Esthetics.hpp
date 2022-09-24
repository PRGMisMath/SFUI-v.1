#ifndef ESTHETICS_HPP
#define ESTHETICS_HPP

#include<SFML/Graphics.hpp>
#include<vector>

struct Appear
{
	const sf::Texture* m_texture;
	sf::IntRect m_textureRect;
	sf::Color m_fillColor;
	sf::Color m_outlineColor;
	float m_outlineThickness;
};

class Esthetics {
public:
	static Appear getAppearFromShape(sf::Shape* shape);

	Esthetics();
	unsigned int getDelay() const;
	void setDelay(unsigned int delay);
	Appear& getAppear(int index);
	bool isCycling();
	void cycle(bool repeat);
	void addAppear(const Appear& appear, int index = -1); // index = -1 <==> last position
	void removeAppear(int index = -1); // index = -1 <==> last position
	void clearAppears();
	void setAppear(sf::Shape& shape, int index);
	void reloadAppear(sf::Shape& shape);
	void nextAppear(sf::Shape& shape);
	void update(sf::Shape& shape);
private:
	std::vector<Appear> m_appears;
	time_t m_time;
	unsigned int m_delay;
	int m_current;
	uint8_t fl_cycle; // 0b-------1 -> will update ; 0b------1- -> will repeat
};

#endif // !ESTHETICS_HPP
