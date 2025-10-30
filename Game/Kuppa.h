#pragma once
class Kuppa : public IGameObject
{
public:
	Kuppa();
	~Kuppa();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	ModelRender m_modelRender;
};

