
#include "cocos2d.h"
#include <iostream>
#include <fstream>
#include <ui\UITextField.h>
using namespace cocos2d;

class Character {

public:
	Character();
	Character(Sprite*);
	Character(Sprite*, Character*);
	Character(Sprite*, Character*, Animate*, Animate* );
	

	virtual void getHit(int);
	int health = 1;
	int maxHealth;
	virtual void flipWorld(int tag);
	virtual Vec2 getPosition();
	virtual void update(float dt);
	virtual void update(float dt, Vec2 P);
	virtual Sprite* getSprite();
	virtual Character * getShadow(int i);
	void attack(Scene* scene);
	unsigned int atk = 0;
	bool attacking = false;
	bool noShadow;
	bool hit;
	bool enemy = false;
	bool isShadow; //true=shadow mode
	//Vec2* Position;
	Sprite* healthbar;
	Sprite* healthframe;
	int animState = 0;//0=idle,1=walk,
	bool loopDone = true;

	Repeat* walkCycleP;
	Repeat* walkCycleS;
	Animate* enemyWalkP;
	Animate* enemyWalkS;
	void setAnimation(Animate* anim1, Animate* anim2);
	void runAnimation(bool);

protected:
	bool eInit = false;
	//bool falling;
	//int jump;
	//int state; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	std::vector<Character*> shadow; //list of shadows corosponding to charcater
	int maxSpeed; //max speed a character can reach
	Sprite* sprite; //character sprite

};