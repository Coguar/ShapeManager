#pragma once

class CEllipse :
	public sf::Shape
{
public:
	explicit CEllipse(const sf::Vector2f& radius = sf::Vector2f(0, 0), unsigned int pointsCount = 30);
	~CEllipse() = default;

	void setRadius(const sf::Vector2f& radius);
	const sf::Vector2f& getRadius() const;
	virtual unsigned int getPointCount() const;
	virtual sf::Vector2f getPoint(unsigned int index) const;

private:
	sf::Vector2f m_radius;
	unsigned int m_pointsCount = 30;
};
