#pragma once

#include "cocos2d.h"
using namespace cocos2d;

#include <string>

enum class TextAlignment
{
	LEFT = 0,
	CENTER = 1,
	RIGHT = 2,
};
class Text
{
public:
	Text(
		Scene* _parentScene,
		Vec2* _position,
		const std::string& _text,
		float _fontSize,
		TextAlignment _alignment,
		Color3B _color = Color3B::BLACK,
		const std::string& _fontDirectory = "fonts/Amatic-Bold.ttf"
	)
		: parentScene(_parentScene)

	{
		fontSize = _fontSize;
		fontDirectory = _fontDirectory;
		text = _text;
		alignment = _alignment;

		label = Label::createWithTTF(text, fontDirectory, fontSize);

		setColor(_color);
		setAlignment(_alignment);
		setPosition(_position);
		parentScene->addChild(label);
	}

	~Text()
	{
		label->cleanup()
		parentScene->removeChild(label);
		label = nullptr;
	}

	void setPosition(Vec2 _position)
	{
		position = _position;
		label->setPosition(position);
	}
	void setText(const std::string& _text)
	{
		text = _text;
		label->setString(text);
	}
	void setColor(Color3B _color)
	{
		color = _color;
		label->setColor(color);
	}
	void setAlignment(TextAlignment _alignment)
	{
		alignment = _alignment;
		float x = static_cast<float>(alignment) * 0.5f;
		label->setAnchorPoint(Vec2(x, 0.0f));
private:
	Scene* parentScene;
	Label* label;

	Vec2 position;
	std::string text;
	float fontSize;
	TextAlignment alignment;
	Color3B color;
	std::string fontDirectory;
};