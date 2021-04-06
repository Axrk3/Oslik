#include "Animation.h"

Animation::Animation(Texture& texture, int x, int y, int w, int h, int count, float _speed, int step) {
	speed = _speed;
	sprite.setTexture(texture);

	currentFrame = 0;
	isPlaying = true;
	flip = false;

	for (int i = 0; i < count; i++) {
		frames.push_back(IntRect(x + i * step, y, w, h));
		flippedFrames.push_back(IntRect(x + i * step + w, y, -w, h));
	}
}

void Animation::tick(float time) {
	if (!isPlaying) return;
	currentFrame += speed * time;

	if (currentFrame > frames.size()) {
		currentFrame -= frames.size();
	}

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip) {
		sprite.setTextureRect(flippedFrames[i]);
	}
}

void AnimationManager::create(String name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step) {
	animList[name] = Animation(texture, x, y, w, h, count, speed, step);
	currentAnimation = name;
}

void AnimationManager::draw(RenderWindow& window, int x, int y) {
	animList[currentAnimation].sprite.setPosition(x, y);
	window.draw(animList[currentAnimation].sprite);
}

void AnimationManager::set(String name) {
	currentAnimation = name;
}

void AnimationManager::flip(bool b) {
	animList[currentAnimation].flip = b;
}

void AnimationManager::tick(float time) {
	animList[currentAnimation].tick(time);
}

void AnimationManager::pause() {
	animList[currentAnimation].isPlaying = false;
}

void AnimationManager::play() {
	animList[currentAnimation].isPlaying = true;
}