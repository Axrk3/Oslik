#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation {
public:
	std::vector<IntRect> frames, flippedFrames;
	float currentFrame, speed;
	bool flip, isPlaying;
	Sprite sprite;

	Animation() {}
	Animation(Texture& texture, int x, int y, int w, int h, int count, float _speed, int step);

	void tick(float time);
};

class AnimationManager {
public:
	String currentAnimation;
	std::map<String, Animation> animList;

	AnimationManager() {}

	void create(String name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step);
	void draw(RenderWindow& window, int x, int y);
	void set(String name);
	void flip(bool b);
	void tick(float time);
	void pause();
	void play();
};