#pragma once 

#include "engine/animations/Animator.h"




void NotifyStarted(void) {
	//AnimatorManager::GetSingleton().MarkAsRunning(this);

}
void NotifyAction(void) {

}
void Animator::Finish(bool isForced) {
	if (!HasFinished()) {
		state = isForced ? ANIMATOR_STOPPED : ANIMATOR_FINISHED;
		NotifyStopped();
	}
}

void Animator::Stop(void) {
	Finish(true);
}

void Animator::NotifyStopped(void) {
	//AnimatorManager::GetSingleton().MarkAsSuspended(this);
	if (onFinish)
		(onFinish)(this);
}

void Animator::NotifyAction(const Animation& anim) {
	if (onAction)
		(onAction)(this, anim);
}

void Animator::TimeShift(timestamp_t offset) {
	lastTime += offset;
}



void MovingAnimator::Progress(timestamp_t currTime) {
	while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
		lastTime += anim->GetDelay();
		NotifyAction(*anim);
		if (!anim->IsForever() && ++currRep == anim->GetReps()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

