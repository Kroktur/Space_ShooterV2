#pragma once

#include "IGameObject.h"


class ISpawner : public IComposite
{
public:
	ISpawner(IComposite* scene):IComposite(scene){}
	void ProssesInput(const sf::Event& event) override;
	void Render() override;
	void Update(const float& deltatime) override;
	virtual void Spawn() = 0;
};
