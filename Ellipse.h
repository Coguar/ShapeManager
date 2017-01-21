#pragma once

class CEllipse :
	public sf::Shape
{
public:
	explicit CEllipse(const sf::Vector2f& radius = sf::Vector2f(0, 0), unsigned int pointsCount = DEFOULT_ELLIPSE_POINTS_COUNT);
	~CEllipse() = default;

	void setRadius(const sf::Vector2f& radius);
	const sf::Vector2f& getRadius() const;
	unsigned int getPointCount() const override;
	sf::Vector2f getPoint(unsigned int index) const override;

private:
	sf::Vector2f m_radius;
	unsigned int m_pointsCount = DEFOULT_ELLIPSE_POINTS_COUNT;
};