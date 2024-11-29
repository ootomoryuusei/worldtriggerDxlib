#include "animator.h"
#include <DxLib.h>
#include "Engine/time.h"

Animator::Animator()
{
	attachIndex = -1;
	frameSpeed = 0.5f;
}

Animator::~Animator()
{
	if (attachIndex >= 0)
		MV1DetachAnim(baseModel, attachIndex);
}

void Animator::Update()
{
	if (attachIndex < 0)
		return;

	frame += frameSpeed * 60.0f * Time::DeltaTime();
	if (loopMode) {
		if (frame>=maxFrame) {
			frame -= maxFrame;
		}
	} else {
		if (frame>maxFrame) {
			frame = maxFrame;
		}
	}
	MV1SetAttachAnimTime(baseModel, attachIndex, frame);
}

void Animator::SetModel(int model)
{
	baseModel = model;
}

void Animator::Play(int animModel, bool loop)
{
	if (animModel == curAnim)
		return;

	curAnim = animModel;
	if (attachIndex>=0) {
		MV1DetachAnim(baseModel, attachIndex);
		attachIndex = -1;
	}
	attachIndex = MV1AttachAnim(baseModel, 0,
									animModel);
	loopMode = loop;
	frame = 0;
	maxFrame = MV1GetAttachAnimTotalTime(
						baseModel, attachIndex);
	MV1SetAttachAnimTime(baseModel, attachIndex, 0);
}
