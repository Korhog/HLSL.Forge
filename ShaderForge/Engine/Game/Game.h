#pragma once
#include "pch.h"

#include <GameObject.h>
#include <Phis2D.h>

namespace MarcusEngine {
	/*
	Игра, тут содержатся все рисуемые объекты
	*/
	class IGame abstract {
	protected:
		std::shared_ptr<MarcusEngine::Phis2D::World2D> m_world;
	public:
		IGame();
		std::vector<std::shared_ptr<GameObject>> m_game_objects;
		// Обновляем 
		virtual void Update() abstract;
		virtual void Render(ID3D11DeviceContext1* context) abstract;
		virtual void AddGameObject(std::shared_ptr<GameObject> gameObject) abstract;

		// Params
		__declspec(property(get = GetWorld)) std::shared_ptr<MarcusEngine::Phis2D::World2D> World;
		std::shared_ptr<MarcusEngine::Phis2D::World2D> GetWorld() { return m_world; }
	};

	class Game2D : public IGame {
	private:
	public:
		// Обновляем 
		virtual void Update() override;
		virtual void Render(ID3D11DeviceContext1* context) override;
		virtual void AddGameObject(std::shared_ptr<GameObject> gameObject) override;
	};
}
