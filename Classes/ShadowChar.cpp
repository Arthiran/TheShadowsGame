#include "ShadowChar.h"

ShadowChar::ShadowChar()
{
	//None of these are in use rn
	//falling = false;
	//jump = 0;
	isShadow = false; //true=shadow mode
	noShadow = true;
					  //state = 0; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	maxSpeed = 100; //max speed a character can reach
}

ShadowChar::ShadowChar(Sprite * _sprite)
{
	isShadow = false; //true=shadow mode
	maxHealth = 3;
	health = 3;
	//state = 0; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	maxSpeed = 100; //max speed a character can reach
	noShadow = true;

	//copies properties of passed sprite to Character sprite
	sprite = Sprite::createWithTexture(_sprite->getTexture());
	sprite->setScale(_sprite->getScaleX(), _sprite->getScaleY());
	sprite->setRotation(_sprite->getRotation());
	sprite->setPosition(_sprite->getPosition());
	sprite->setAnchorPoint(_sprite->getAnchorPoint());
	maxSpeed = 500;

	//Health bar
	healthbar = Sprite::create("UA/Player/healthbar.png");
	healthbar->setPosition(getPosition() + Vec2(0, sprite->getContentSize().height / 2.0f) + Vec2(0, 100));
	healthbar->setRotation(0);
	healthbar->setScale(0.2f);
	healthbar->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthbar->setOpacity(0);
	healthframe = Sprite::create("UA/Player/healthframe.png");
	healthframe->setPosition(getPosition() + Vec2(0, sprite->getContentSize().height / 2.0f) + Vec2(0, 100));
	healthframe->setRotation(0);
	healthframe->setScale(0.2f);
	healthframe->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthframe->setOpacity(0);

	walkCycleP = Repeat::create(Sequence::create(FlipX::create(true), MoveBy::create(3.0f, Vec2(200, 0)), FlipX::create(false), MoveBy::create(3.0f, Vec2(-200, 0)),NULL), 999);
	walkCycleP->setTarget(getSprite());
	walkCycleP->retain();

	sprite->runAction((TintTo::create(0.1f, Color3B(0, 0, 0))));
}

void ShadowChar::flipWorld(int tag)//changes physics bodies to shadows
{
	bool dynamic = true;
	if (tag > 1) {//if tag is 2 (wall/floor), set to non dynamic
		dynamic = false;
	}
	if (isShadow == true) {//if not shadow
		if (sprite->isVisible() == true) {
			sprite->getPhysicsBody()->removeFromWorld();//removes physics body
			sprite->getPhysicsBody()->removeAllShapes(true);
		}
		isShadow = false;//makes u shadow
	}
	else {//if already a shadow
		PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());//gives player physics body
		body->setDynamic(dynamic);
		body->setMass(1);
		body->setTag(tag);
		body->setContactTestBitmask(0xFFFFFFFF);
		sprite->setPhysicsBody(body);
		isShadow = true;//mkaes u player againB
	}
	
}
void ShadowChar::getHit(int enemyX)
{
	//Particles
	ParticleSystem* healParticles = ParticleExplosion::createWithTotalParticles(50);
	healParticles->setSpeed(250);
	healParticles->setPosition(getPosition() + Vec2(10,0));
	healParticles->setScale(0.5f);
	healParticles->setStartColor(Color4F(0, 0, 0, 100));
	healParticles->setStartColorVar(Color4F(0, 0, 0, 50));
	healParticles->setEndColor(Color4F(0, 0, 0, 0));
	healParticles->setEndColorVar(Color4F(0, 0, 0, 0));
	healParticles->setGravity(Vec2(0, -1000));
	healParticles->setLife(2);
	healParticles->runAction(Sequence::create(FadeOut::create(2.0f), RemoveSelf::create(), NULL));
	getSprite()->getParent()->addChild(healParticles, -100);

	//Hit Velocity
	if (isShadow == true) {
		//getSprite()->runAction(Sequence::create(TintTo::create(0.1f, Color3B(255, 0, 0)), TintTo::create(0.1f, Color3B(255, 0, 0)), TintTo::create(0.1f, Color3B(255, 255, 255)), NULL));
		if (getPosition().x > enemyX) {
			getSprite()->getPhysicsBody()->setVelocity(Vec2(400, 300));
			//getSprite()->runAction(MoveBy::create(0.2f, Vec2(100, 0)));
		}
		else {
			getSprite()->getPhysicsBody()->setVelocity(Vec2(-400, 300));
			//getSprite()->runAction(MoveBy::create(0.2f, Vec2(-100, 0)));
		}


	}
	health--;
	std::cout << health << std::endl;

	if (health <= 0)
	{
		//healthbar->setTexture("UA/Player/healthbar0.png");
		////healthframe->stopAllActions();
		//healthbar->stopAllActions();
		//healthbar->runAction(
		//	Sequence::createWithTwoActions(
		//		Sequence::createWithTwoActions(
		//			FadeIn::create(0.2f), ScaleTo::create(0.5f, 0.1f, 0.1f)),
		//		Sequence::createWithTwoActions(
		//			Blink::create(0.3f, 3), FadeOut::create(0.5f))
		//	));
		//std::cout << "u dead" << std::endl;
	}
	else {
		if (health == 3)
			healthbar->setTexture("UA/Player/healthbar0.png");
		if (health == 2)
			healthbar->setTexture("UA/Player/healthbar1.png");
		if (health == 1)
			healthbar->setTexture("UA/Player/healthbar2.png");
		//healthframe->stopAllActions();
		healthbar->stopAllActions();
		//healthbar->setScaleX(0.2f * (health / maxHealth));
		healthbar->runAction(
			Sequence::createWithTwoActions(
				Sequence::createWithTwoActions(
					FadeIn::create(0.2f), ScaleTo::create(0.5f, 0.1f * health * 0.4f, 0.1f * health * 0.4f)),
				Sequence::createWithTwoActions(
					Blink::create(0.3f, 3), FadeOut::create(0.5f))
			));
		//healthframe->runAction(
		//	Sequence::createWithTwoActions(
		//		Sequence::createWithTwoActions(
		//			FadeIn::create(0.2f), MoveBy::create(0.5f, Vec3(0, 0, 0))),
		//		Sequence::createWithTwoActions(
		//			MoveBy::create(0.3f, Vec3(0, 0, 0)), FadeOut::create(0.5f))
		//	));
	}
}

Vec2 ShadowChar::getPosition()
{
	
	return getSprite()->getPosition();
}


void ShadowChar::update(float dt)
{
	if (isShadow == true) {//if not shadow
		sprite->setRotation(0);//stay upright
		if (abs(sprite->getPhysicsBody()->getVelocity().x) > maxSpeed) { //max speed = 500
			sprite->getPhysicsBody()->setVelocity(Vec2(maxSpeed * ((sprite->getPhysicsBody()->getVelocity().x) / abs(sprite->getPhysicsBody()->getVelocity().x)),
				sprite->getPhysicsBody()->getVelocity().y));//if player is more than max speed, set to max speed
		}
	}
	else {//if shadow
		sprite->setRotation(0);//stay upright
	}
	healthbar->setPosition(getPosition() + Vec2(0, 50));
	healthframe->setPosition(getPosition() + Vec2(0, 50));
}

void ShadowChar::update(float dt, Vec2 P)
{
	maxSpeed = 200;
	if (isShadow == true) {//if not shadow
	//enemy tings
		if (health > 0)
		{
			if (abs(P.x - getPosition().x) > 100.0f && abs(P.y - getPosition().y) > 100.0f) {//range = 200pixels rn. can change later
				if (loopDone == true) {
					//getSprite()->stopAllActions();
					//runAnimation(false);
					//if (noShadow == false) {
					//	getShadow(0)->getSprite()->stopAllActions();
					//	runAnimation(false);
					//}
					getSprite()->runAction(walkCycleP);
					loopDone = false;
				}
			}
			else {
				if (loopDone == false) {
					loopDone = true;
					getSprite()->stopAction(walkCycleP);
					//runAnimation(false);
				}
				//getSprite()->getPhysicsBody()->resetForces();
				if (getPosition().x > P.x) {
					sprite->setFlippedX(false);
					getSprite()->getPhysicsBody()->setVelocity(Vec2(getSprite()->getPhysicsBody()->getVelocity().x - 10, getSprite()->getPhysicsBody()->getVelocity().y));
				}
				else {
					sprite->setFlippedX(true);
					getSprite()->getPhysicsBody()->setVelocity(Vec2(getSprite()->getPhysicsBody()->getVelocity().x + 10, getSprite()->getPhysicsBody()->getVelocity().y));
				}

			}
		}
	}

	if (isShadow == true) {//if not shadow
		sprite->setRotation(0);//stay upright
		if (abs(sprite->getPhysicsBody()->getVelocity().x) > maxSpeed) { //max speed = 500
			sprite->getPhysicsBody()->setVelocity(Vec2(maxSpeed * ((sprite->getPhysicsBody()->getVelocity().x) / abs(sprite->getPhysicsBody()->getVelocity().x)),
				sprite->getPhysicsBody()->getVelocity().y));//if player is more than max speed, set to max speed
		}
	}
	else {//if shadow
		sprite->setRotation(0);//stay upright
	}
	healthbar->setPosition(getPosition() + Vec2(0, 50));
	healthframe->setPosition(getPosition() + Vec2(0, 50));

}

Sprite * ShadowChar::getSprite()
{
	return sprite;
}

ShadowChar * ShadowChar::getShadow(int i)
{
	return this;
}

void ShadowChar::attack(Scene* scene)
{
	auto atk = Sprite::create("UA/Player/healthbar0.png");
	if (isShadow == true) {
		if (getShadow(0)->getSprite()->isFlippedX() == true)
			atk->setPosition(getPosition() + Vec2(-30, 0));
		else
			atk->setPosition(getPosition() + Vec2(30, 0));
	}
	else {
		if (getSprite()->isFlippedX() == true)
			atk->setPosition(getPosition() + Vec2(-30, 0));
		else
			atk->setPosition(getPosition() + Vec2(30, 0));
	}
	atk->setRotation(0);
	atk->setScale(0.2f);
	atk->setAnchorPoint(Vec2(0.5f, 0.5f));
	//atk->setVisible(false);
	PhysicsBody* hitbox = PhysicsBody::createBox(sprite->getContentSize());
	hitbox->setDynamic(false);
	hitbox->setMass(1);
	hitbox->setTag(4);//0 = player, 1=enemy, 3=wall
	hitbox->setContactTestBitmask(0xFFFFFFFF);
	atk->setPhysicsBody(hitbox);
	scene->addChild(atk);
	hitbox->setVelocity(Vec2(10, 0));

	atk->runAction(Sequence::create(DelayTime::create(0.25f), RemoveSelf::create(), NULL));
}
