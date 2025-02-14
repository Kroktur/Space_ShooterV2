#include "SceneBase.h"

class Game : public ISceneBase
{
public:
	Game(sf::RenderWindow* window, const float& framerate, const std::string& execFilePath);
	virtual ~Game()override = default;
	virtual void Update(const float& deltatime) override;
	virtual void ProssesInput(const sf::Event& event)override;
	virtual void Render() override;
private:
	sf::RectangleShape m_Ship;
};

