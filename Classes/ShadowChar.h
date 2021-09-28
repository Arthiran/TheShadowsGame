
#include "Character.h"
using namespace cocos2d;

class ShadowChar : public Character {

public:
	ShadowChar();
	ShadowChar(Sprite*);
	
	void getHit(int);
	void flipWorld(int tag);
	Vec2 getPosition();
	void update(float dt);
	void update(float dt, Vec2 P);
	Sprite* getSprite();
	ShadowChar * getShadow(int i);
	void attack(Scene* scene);
	//Vec2* Position;


private:
	int maxSpeed; //max speed a character can reach
	Sprite* sprite; //character sprite

};