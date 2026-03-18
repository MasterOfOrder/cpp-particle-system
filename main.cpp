#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>

class Particle {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Color particleColor;
    sf::Time lifetime;
    sf::Vector2f position;

    Particle(float x, float y, float& speed, float& angle, sf::Color& color, sf::Time lifetime)
        : velocity(speed * std::cos(angle), speed * std::sin(angle)), particleColor(color), lifetime(lifetime), position(x, y) {
        shape.setRadius(2);
        shape.setFillColor(particleColor);
        shape.setPosition(position);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dots Game");
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> angleDist(0, 2 * M_PI);
    std::uniform_real_distribution<float> speedDist(50, 150);
    std::uniform_int_distribution<int> colorDist(0, 255);
    sf::Clock clock;
    sf::RectangleShape rectangle;
    std::vector<Particle> particles;
    rectangle.setSize(sf::Vector2f(800, 600));
    rectangle.setFillColor(sf::Color(0, 0, 0, 128));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float deltaTime = clock.restart().asSeconds();
        for (int i = 0; i < 10; ++i) {
            float speed = speedDist(rng);
            float angle = angleDist(rng);
            sf::Color color(colorDist(rng), colorDist(rng), colorDist(rng));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                particles.emplace_back(mousePos.x, mousePos.y, speed, angle, color, sf::seconds(1));
            }
        }
        for (auto& particle : particles) {
            particle.lifetime -= sf::seconds(deltaTime);
            particle.position += particle.velocity * deltaTime;
            particle.position.y += 100 * deltaTime;
            if (particle.lifetime <= sf::Time::Zero) {
                particle.shape.setFillColor(sf::Color(0, 0, 0, 0));
            } else {
                float alpha = (particle.lifetime.asSeconds() / 1.0f) * 255;
                particle.shape.setFillColor(sf::Color(particle.particleColor.r, particle.particleColor.g, particle.particleColor.b, static_cast<sf::Uint8>(alpha)));
                particle.shape.setPosition(particle.position);
            }
        }
        particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return p.lifetime <= sf::Time::Zero; }), particles.end());
        window.clear();
        window.draw(rectangle);
        for (const auto& particle : particles) {
            window.draw(particle.shape);
        }
        window.display();
    }
    return 0;
}