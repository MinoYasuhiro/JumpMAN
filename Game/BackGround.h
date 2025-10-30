#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
};

