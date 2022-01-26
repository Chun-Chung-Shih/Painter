#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
	sf::VideoMode mode(642, 640);
	sf::RenderWindow window(mode, L"²���p�e�a");

	sf::Texture background;
	background.loadFromFile("background.png");
	sf::Sprite backgroundSprite(background);
	backgroundSprite.setPosition(0, 40);

	sf::RenderTexture renderTexture;
	renderTexture.create(600, 560);
	renderTexture.clear(sf::Color::White);
	renderTexture.display();

	sf::CircleShape cursor(10);
	cursor.setOrigin(10, 10);
	cursor.setFillColor(sf::Color::Black);

	sf::Sprite renderSprite(renderTexture.getTexture());
	sf::Vector2f offset(20, 60);
	renderSprite.setPosition(offset);

	std::vector<sf::Color> colors = {
		sf::Color::Red, sf::Color::Black, sf::Color::Green, 
		sf::Color::Cyan, sf::Color::Magenta, sf::Color::Yellow, 
		sf::Color::Blue
	};

	std::vector<sf::RectangleShape> swatch;
	for (size_t i = 0; i < colors.size(); i++) {
		sf::RectangleShape shape({ 20, 20 });
		shape.setOutlineColor(sf::Color(230, 230, 230));
		shape.setOutlineThickness(2);
		shape.setFillColor(colors[i]);
		shape.setPosition(20 + i * 20, 10);
		swatch.push_back(shape);
	}

	while (window.isOpen()) {
		sf::Event evt;
		if (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				for (const auto& color : swatch) {
					if (color.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
						cursor.setFillColor(color.getFillColor());
					}
				}
				break;
			case sf::Event::KeyPressed:
				//std::cout << evt.key.code << std::endl;
				switch (evt.key.code) {
				case sf::Keyboard::S:
					renderTexture.getTexture().copyToImage().saveToFile("test.png");
					break;
				case sf::Keyboard::Num1:
					cursor.setOutlineThickness(0.5);
					break;
				case sf::Keyboard::Num2:
					cursor.setFillColor(sf::Color::Black);
					break;
				case sf::Keyboard::Num3:
					cursor.setFillColor(sf::Color::Green);
					break;
				case sf::Keyboard::Num4:
					cursor.setFillColor(sf::Color::Cyan);
					break;
				case sf::Keyboard::Num5:
					cursor.setFillColor(sf::Color::Magenta);
					break;
				case sf::Keyboard::Num6:
					cursor.setFillColor(sf::Color::Yellow);
					break;
				case sf::Keyboard::Num7:
					cursor.setFillColor(sf::Color::Blue);
					break;
				}
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto pos = sf::Mouse::getPosition(window);
			cursor.setPosition(sf::Vector2f(pos) - offset);
			renderTexture.draw(cursor);
			renderTexture.display();
		}

		window.clear(sf::Color::White);
		for (const auto& s : swatch) {
			window.draw(s);
		}
		window.draw(backgroundSprite);
		window.draw(renderSprite);
		auto pos = sf::Mouse::getPosition(window);
		cursor.setPosition(sf::Vector2f(pos));
		window.draw(cursor);
		window.display();
	}
}