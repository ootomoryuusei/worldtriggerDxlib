#pragma once
#include "Icon.h"

#include"TriggerSetUIFrames.h"

class TriggerSetUI :
    public Icon
{
public:
	TriggerSetUI(GameObject* parent);
	~TriggerSetUI();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	const auto& GetpFrames() const{ return p_frames_; }
private:

	TriggerSetUIFrames* p_frames_;
};

