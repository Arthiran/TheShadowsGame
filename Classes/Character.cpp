#include "Character.h"

Character::Character()
{
	//None of these are in use rn
	//falling = false;
	//jump = 0;
	isShadow = false; //true=shadow mode
					  //state = 0; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	maxSpeed = 100; //max speed a character can reach
}

Character::Character(Sprite * _sprite)
{
	//name as above, to be implemented later
	//falling = false;
	//jump = 0;
	noShadow = true;
	isShadow = false; //true=shadow mode
	health = 1;
					  //state = 0; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	maxSpeed = 200; //max speed a character can reach

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
}
Character::Character(Sprite * _sprite, Character* _shadow, Animate* anim1, Animate* anim2)
{
	//falling = false;
	//jump = 0;
	_shadow->getSprite()->runAction(TintTo::create(0.01f, Color3B(0, 0, 0)));
	noShadow = false;
	health = 3;
	_shadow->health = 1;
	isShadow = false; //true=shadow mode
					  //state = 0; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	maxSpeed = 200; //max speed a character can reach

					//copies properties of passed sprite to Character sprite
	sprite = Sprite::createWithTexture(_sprite->getTexture());
	sprite->setScale(_sprite->getScaleX(), _sprite->getScaleY());
	sprite->setRotation(_sprite->getRotation());
	sprite->setPosition(_sprite->getPosition());
	sprite->setAnchorPoint(_sprite->getAnchorPoint());
	shadow.push_back(_shadow);//add shadow to shadow list, allows for gaps and more shadows then objects

	//set animations
	setAnimation(anim1, anim2);
	runAnimation(true);
	runAnimation(false);

	//Makes physics body
	PhysicsBody* body_ = PhysicsBody::createBox(Size(sprite->getContentSize() + Size(0, 0)));
	body_->setDynamic(true);
	body_->setMass(1);
	body_->setTag(0);//0 = player, 1=enemy, 3=wall
	body_->setContactTestBitmask(0xFFFFFFFF);
	sprite->setPhysicsBody(body_);
	maxSpeed = 500;
							  //Health bar
	healthbar = Sprite::create("UA/Player/healthbar.png");
	healthbar->setPosition(getPosition() + Vec2(0, sprite->getContentSize().height / 2.0f) + Vec2(0, 100));
	healthbar->setRotation(0);
	healthbar->setScale(0.1f);
	healthbar->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthbar->setOpacity(0);
	healthframe = Sprite::create("UA/Player/healthframe.png");
	healthframe->setPosition(getPosition() + Vec2(0, sprite->getContentSize().height / 2.0f) + Vec2(0, 100));
	healthframe->setRotation(0);
	healthframe->setScale(0.2f);
	healthframe->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthframe->setOpacity(0);

	walkCycleP = Repeat::create(Sequence::create(FlipX::create(true), MoveBy::create(3.0f, Vec2(200, 0)), FlipX::create(false), MoveBy::create(3.0f, Vec2(-200, 0)), NULL), 999);
	walkCycleS = Repeat::create(Sequence::create(FlipX::create(true), MoveBy::create(3.0f, Vec2(200, 0)), FlipX::create(false), MoveBy::create(3.0f, Vec2(-200, 0)), NULL), 999);
	walkCycleP->setTarget(getSprite());
	walkCycleS->setTarget((getShadow(0)->getSprite()));
	walkCycleP->retain();
	walkCycleS->retain();
}

Character::Character(Sprite * _sprite, Character* _shadow)
{
	//falling = false;
	//jump = 0;
	_shadow->getSprite()->runAction(TintTo::create(0.01f, Color3B(0, 0, 0)));
	noShadow = false;
	health = 3;
	_shadow->health = 1;
	isShadow = false; //true=shadow mode
					  //state = 0; //0=grounded,1=jumping,2=falling,3=wall,4=dash
	maxSpeed = 200; //max speed a character can reach

				  //copies properties of passed sprite to Character sprite
	sprite = Sprite::createWithTexture(_sprite->getTexture());
	sprite->setScale(_sprite->getScaleX(), _sprite->getScaleY());
	sprite->setRotation(_sprite->getRotation());
	sprite->setPosition(_sprite->getPosition());
	sprite->setAnchorPoint(_sprite->getAnchorPoint());
	//Makes physics body
	PhysicsBody* body_ = PhysicsBody::createBox(Size(sprite->getContentSize() + Size(0,0)));
	body_->setDynamic(true);
	body_->setMass(1);
	body_->setTag(0);//0 = player, 1=enemy, 3=wall
	body_->setContactTestBitmask(0xFFFFFFFF);
	sprite->setPhysicsBody(body_);
	maxSpeed = 500;
	shadow.push_back(_shadow);//add shadow to shadow list, allows for gaps and more shadows then objects
	//Health bar
	healthbar = Sprite::create("UA/Player/healthbar.png");
	healthbar->setPosition(getPosition() + Vec2(0, sprite->getContentSize().height / 2.0f) + Vec2(0, 100));
	healthbar->setRotation(0);
	healthbar->setScale(0.1f);
	healthbar->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthbar->setOpacity(0);
	healthframe = Sprite::create("UA/Player/healthframe.png");
	healthframe->setPosition(getPosition() + Vec2(0, sprite->getContentSize().height / 2.0f) + Vec2(0, 100));
	healthframe->setRotation(0);
	healthframe->setScale(0.2f);
	healthframe->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthframe->setOpacity(0);

	walkCycleP = Repeat::create(Sequence::create(FlipX::create(true), MoveBy::create(3.0f, Vec2(200, 0)), FlipX::create(false), MoveBy::create(3.0f, Vec2(-200, 0)),NULL), 999);
	walkCycleS = Repeat::create(Sequence::create(FlipX::create(true), MoveBy::create(3.0f, Vec2(200, 0)), FlipX::create(false), MoveBy::create(3.0f, Vec2(-200, 0)),NULL), 999);
	walkCycleP->setTarget(getSprite());
	walkCycleS->setTarget((getShadow(0)->getSprite()));
	walkCycleP->retain();
	walkCycleS->retain();
}


void Character::flipWorld(int tag)//changes physics bodies to shadows
{
	
	bool dynamic = true;
	if (tag > 1) {//if tag is 2 (wall/floor), set to non dynamic
		dynamic = false;
	}
	if (isShadow == false) {//if not shadow
		if (sprite->isVisible() == true) {
			sprite->getPhysicsBody()->removeFromWorld();//removes physics body
			sprite->getPhysicsBody()->removeAllShapes(true);
		}
		for (int i = 0; i < shadow.size(); i++) {//give shadows physics body
			if (shadow[i]->getSprite()->isVisible() == true) {
				PhysicsBody* body = PhysicsBody::createBox(shadow[i]->getSprite()->getContentSize());
				body->setDynamic(dynamic);
				body->setMass(1);
				body->setTag(tag);
				body->setContactTestBitmask(0xFFFFFFFF);
				shadow[i]->getSprite()->setPhysicsBody(body);
			}
		}
		isShadow = true;//makes u shadow
	}
	else {//if already a shadow
		for (int i = 0; i < shadow.size(); i++) {//removee shadows physics bodies
			if (shadow[i]->getSprite()->isVisible() == true) {
				shadow[i]->getSprite()->getPhysicsBody()->removeFromWorld();
				shadow[i]->getSprite()->getPhysicsBody()->removeAllShapes(true);
			}
		}
		if (sprite->isVisible() == true) {
			PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());//gives player physics body
			body->setDynamic(dynamic);
			body->setMass(1);
			body->setTag(tag);
			body->setContactTestBitmask(0xFFFFFFFF);
			sprite->setPhysicsBody(body);

		}
		isShadow = false;//mkaes u player againB
	}
	
}
void Character::getHit(int enemyX)
{
	//Particles
	int z = -50;
	ParticleSystem* healParticles = ParticleExplosion::createWithTotalParticles(50);
	healParticles->setSpeed(250);
	healParticles->setPosition(getPosition() + Vec2(10,0));
	healParticles->setScale(0.5f);
	if (isShadow == false && noShadow == false) {
		healParticles->setStartColor(Color4F(180, 0, 0, 100));
		healParticles->setStartColorVar(Color4F(1, 1, 0, 50));
		healParticles->setEndColor(Color4F(170, 0, 0, 0));
		healParticles->setEndColorVar(Color4F(1, 0, 0, 0));
		//Shadow Particle
		ParticleSystem* particles = ParticleExplosion::createWithTotalParticles(50);
		particles->setSpeed(250);
		particles->setPosition(getShadow(0)->getSprite()->getPosition() + Vec2(10,0));
		particles->setScale(0.5f);
		particles->setStartColor(Color4F(0, 0, 0, 100));
		particles->setStartColorVar(Color4F(0, 0, 0, 50));
		particles->setEndColor(Color4F(0, 0, 0, 0));
		particles->setEndColorVar(Color4F(0, 0, 0, 0));
		particles->setGravity(Vec2(0, -1000));
		particles->setLife(2);
		particles->runAction(Sequence::create(FadeOut::create(2.0f), RemoveSelf::create(), NULL));
		getSprite()->getParent()->addChild(particles, -100);
	}
	else {
		healParticles->setStartColor(Color4F(0, 0, 0, 100));
		healParticles->setStartColorVar(Color4F(0, 0, 0, 50));
		healParticles->setEndColor(Color4F(0, 0, 0, 0));
		healParticles->setEndColorVar(Color4F(0, 0, 0, 0));
		z = -100;
	}
	healParticles->setGravity(Vec2(0, -1000));
	healParticles->setLife(2);
	healParticles->runAction(Sequence::create(FadeOut::create(2.0f), RemoveSelf::create(), NULL));
	getSprite()->getParent()->addChild(healParticles, z);

	//HitVelocity
	if (isShadow == false) {
		//getSprite()->runAction(Sequence::create(TintTo::create(0.1f, Color3B(255, 0, 0)), Blink::create(0.1f,4), TintTo::create(0.1f, Color3B(0, 0, 0)), NULL));
		if (getPosition().x < enemyX) {
			getSprite()->getPhysicsBody()->setVelocity(Vec2(-400, 300));
			//getSprite()->runAction(MoveBy::create(0.2f, Vec2(-100, 0)));
		}
		else {
			getSprite()->getPhysicsBody()->setVelocity(Vec2(400, 300));
			//getSprite()->runAction(MoveBy::create(0.2f, Vec2(100, 0)));
		}

	}
	else {
		if (noShadow == false) {
			//getShadow(0)->getSprite()->runAction(Sequence::create(TintTo::create(0.1f, Color3B(255, 0, 0)), Blink::create(0.1f, 4), TintTo::create(0.1f, Color3B(0, 0, 0)), NULL));
			if (getPosition().x < enemyX) {
				getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(-400, 300));
				//getShadow(0)->getSprite()->runAction(MoveBy::create(0.2f, Vec2(-100, 0)));
			}
			else {
				getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(400, 300));
				//getShadow(0)->getSprite()->runAction(MoveBy::create(0.2f, Vec2(100, 00)));
			}
		}
	
	}
	health--;
	std::cout << health << std::endl;

	if (health <= 0)
	{
		if (sprite->getPhysicsBody()->getTag() == 0) {
			healthbar->setTexture("UA/Player/healthbar0.png");
			//healthframe->stopAllActions();
			healthbar->stopAllActions();
			healthbar->runAction(
				Sequence::createWithTwoActions(
					Sequence::createWithTwoActions(
						FadeIn::create(0.2f), ScaleTo::create(0.5f, 0.1f, 0.1f)),
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
			std::cout << "u dead" << std::endl;
		}
		else {
			//sprite->runAction(Sequence::create(Blink::create(0.3f, 3), RemoveSelf::create(), NULL));

		}
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



Vec2 Character::getPosition()
{
	if (isShadow == true && noShadow == false) {
		return getShadow(0)->getSprite()->getPosition();
	}
	else {
		return getSprite()->getPosition();
	}
}


void Character::setAnimation(Animate* anim1, Animate* anim2) {
	enemyWalkP = anim1;
	enemyWalkS = anim2;
	enemyWalkP->retain();
	enemyWalkS->retain();
}

void Character::runAnimation(bool shadow) {
	if (shadow == false) {
		//getSprite()->stopAllActions();
		getSprite()->runAction(Repeat::create(enemyWalkP,99999));
	}
	else {
		//getShadow(0)->getSprite()->stopAllActions();
		getShadow(0)->getSprite()->runAction(Repeat::create(enemyWalkS,99999));
	}
}


void Character::update(float dt)
{
	if (isShadow == false) {//if not shadow
		sprite->setRotation(0);//stay upright
		if (abs(sprite->getPhysicsBody()->getVelocity().x) > maxSpeed) { //max speed = 500
			sprite->getPhysicsBody()->setVelocity(Vec2(maxSpeed * ((sprite->getPhysicsBody()->getVelocity().x) / abs(sprite->getPhysicsBody()->getVelocity().x)),
				sprite->getPhysicsBody()->getVelocity().y));//if player is more than max speed, set to max speed
		}
		for (int i = 0; i < shadow.size(); i++) {
			shadow[i]->getSprite()->setRotation(0);
			shadow[i]->getSprite()->setPosition(sprite->getPosition() + Vec2(-25, 25));//set shadow location
		}
	}
	else {//if shadow
		sprite->setRotation(0);//stay upright
		for (int i = 0; i < shadow.size(); i++) {//for all shadows
			shadow[i]->getSprite()->setRotation(0);
			if (abs(shadow[i]->getSprite()->getPhysicsBody()->getVelocity().x) > maxSpeed) { //max speed = 500
				shadow[i]->getSprite()->getPhysicsBody()->setVelocity(Vec2(maxSpeed * ((shadow[i]->getSprite()->getPhysicsBody()->getVelocity().x) / abs(shadow[i]->getSprite()->getPhysicsBody()->getVelocity().x)),
					shadow[i]->getSprite()->getPhysicsBody()->getVelocity().y));//if more than max peed, set to max speed
			}
		}
	}
	healthbar->setPosition(getPosition() + Vec2(0, 50));
	healthframe->setPosition(getPosition() + Vec2(0, 50));
}

void Character::update(float dt, Vec2 P)
{

	if (eInit == false) {
		getSprite()->getPhysicsBody()->removeFromWorld();//removes physics body
		getSprite()->getPhysicsBody()->removeAllShapes(true);
		PhysicsBody* body = PhysicsBody::createBox(getSprite()->getContentSize());//gives player physics body
		body->setDynamic(true);
		body->setMass(1);
		body->setTag(1);
		body->setContactTestBitmask(0xFFFFFFFF);
		getSprite()->setPhysicsBody(body);
		eInit = true;
	}

	maxSpeed = 200;
	if (noShadow == false) {
		getShadow(0)->maxSpeed = 200;
		if (isShadow == false)
		getShadow(0)->getSprite()->setFlippedX(getSprite()->isFlippedX());
		else
			getSprite()->setFlippedX(getShadow(0)->getSprite()->isFlippedX());
	}
	//enemy tings
	if (health > 0)
	{
		if (abs(P.x - getPosition().x) > 300.0f || abs(P.y - getPosition().y) > 200.0f) {//range = 200pixels rn. can change later
			if (loopDone == true) {
				if (isShadow == false) {
					//getSprite()->stopAllActions();
					//runAnimation(false);
					//if (noShadow == false) {
					//	getShadow(0)->getSprite()->stopAllActions();
					//	runAnimation(true);
					//}
					if (animState == 1)
						getSprite()->stopAction(walkCycleS);
					if (animState != 0) {
						getSprite()->runAction(walkCycleP);
						animState = 0;
					}
				}
				else {
					//getSprite()->stopAllActions();
					//runAnimation(false);
					//if (noShadow == false) {
					//	getShadow(0)->getSprite()->stopAllActions();
					//	runAnimation(true);
					//}
					if (animState == 0)
						getSprite()->stopAction(walkCycleP);
					if (animState != 1) {
						getShadow(0)->getSprite()->runAction(walkCycleS);
						animState = 1;
					}
				}
				loopDone = false;
			}
		}
		else {
			if (loopDone == false) {
				if (isShadow == false) {
					if (animState == 0)
						getSprite()->stopAction(walkCycleP);
					if (animState == 1)
						getSprite()->stopAction(walkCycleS);
					animState = 3;
					//getSprite()->stopAllActions();
					//runAnimation(false);
					//getShadow(0)->getSprite()->stopAllActions();
					//runAnimation(true);
				}
				else {
					if (animState == 0)
						getSprite()->stopAction(walkCycleP);
					if (animState == 1)
						getSprite()->stopAction(walkCycleS);
					animState = 3;
					//getShadow(0)->getSprite()->stopAllActions();
					//runAnimation(true);
				}
				
				loopDone = true;
			}
			if (isShadow == false) {
				if (getPosition().x > P.x) {
					sprite->setFlippedX(false);
					getSprite()->getPhysicsBody()->setVelocity(Vec2(getSprite()->getPhysicsBody()->getVelocity().x - 10, getSprite()->getPhysicsBody()->getVelocity().y));
				}
				else {
					sprite->setFlippedX(true);
					getSprite()->getPhysicsBody()->setVelocity(Vec2(getSprite()->getPhysicsBody()->getVelocity().x + 10, getSprite()->getPhysicsBody()->getVelocity().y));
				}
			}
			else {
				if (getPosition().x > P.x) {
					getShadow(0)->getSprite()->setFlippedX(false);
					getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x - 10, getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
				}
				else {
					getShadow(0)->getSprite()->setFlippedX(true);
					getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x + 10, getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
				}
			}
		}
		if (isShadow == false) {
			getShadow(0)->getSprite()->setPosition(getSprite()->getPositionX() - 25, getSprite()->getPositionY() + 25);
		}
		else {
			getSprite()->setPosition(getShadow(0)->getSprite()->getPositionX() + 25, getShadow(0)->getSprite()->getPositionY() - 25);
		}
	}

	if (isShadow == false) {//if not shadow
		sprite->setRotation(0);//stay upright
		if (abs(sprite->getPhysicsBody()->getVelocity().x) > maxSpeed) { //max speed = 500
			sprite->getPhysicsBody()->setVelocity(Vec2(maxSpeed * ((sprite->getPhysicsBody()->getVelocity().x) / abs(sprite->getPhysicsBody()->getVelocity().x)),
				sprite->getPhysicsBody()->getVelocity().y));//if player is more than max speed, set to max speed
		}
		for (int i = 0; i < shadow.size(); i++) {
			shadow[i]->getSprite()->setRotation(0);
			shadow[i]->getSprite()->setPosition(sprite->getPosition() + Vec2(-25, 25));//set shadow location
		}
	}
	else {//if shadow
		sprite->setRotation(0);//stay upright
		for (int i = 0; i < shadow.size(); i++) {//for all shadows
			shadow[i]->getSprite()->setRotation(0);
			if (abs(shadow[i]->getSprite()->getPhysicsBody()->getVelocity().x) > maxSpeed) { //max speed = 500
				shadow[i]->getSprite()->getPhysicsBody()->setVelocity(Vec2(maxSpeed * ((shadow[i]->getSprite()->getPhysicsBody()->getVelocity().x) / abs(shadow[i]->getSprite()->getPhysicsBody()->getVelocity().x)),
					shadow[i]->getSprite()->getPhysicsBody()->getVelocity().y));//if more than max peed, set to max speed
			}
		}
	}
	healthbar->setPosition(getPosition() + Vec2(0, 50));
	healthframe->setPosition(getPosition() + Vec2(0, 50));
	
}

Sprite * Character::getSprite()
{
	return sprite;
}

Character * Character::getShadow(int i)
{
	return shadow.at(i);
}

void Character::attack(Scene* scene)
{
	Vec2 loco;
	auto atk = Sprite::create("UA/Player/hitbox.png");
	if (isShadow == true) {
		if (getShadow(0)->getSprite()->isFlippedX() == true) {
			//loco = (getPosition() + Vec2(-40, 0));
			atk->setPosition(getPosition() + Vec2(-40, -40));
		}
		else {
			//loco = (getPosition() + Vec2(40, 0));
			atk->setPosition(getPosition() + Vec2(40, -40));
		}
	}
	else {
		if (getSprite()->isFlippedX() == true) {
			//loco = (getPosition() + Vec2(-40, 0));
			atk->setPosition(getPosition() + Vec2(-40, -40));
		}
		else {
			//loco = (getPosition() + Vec2(40, 0));
			atk->setPosition(getPosition() + Vec2(40,-40));
		}
	}
	atk->setRotation(0);
	atk->setScale(0.1f);
	atk->setAnchorPoint(Vec2(0.5f, 0.5f));
	atk->setVisible(false);
	PhysicsBody* hitbox = PhysicsBody::createBox(sprite->getContentSize());
	hitbox->setDynamic(false);
	hitbox->setMass(1);
	hitbox->setTag(4);//0 = player, 1=enemy, 3=wall
	hitbox->setContactTestBitmask(0xFFFFFFFF);
	atk->setPhysicsBody(hitbox);
	scene->addChild(atk);

	//Shadow Particle
	ParticleSystem* particles = ParticleExplosion::createWithTotalParticles(400);
	particles->setSpeed(100);
	particles->setPosition(atk->getPosition());
	particles->setScale(0.5f);
	particles->setStartColor(Color4F(0, 0, 0, 1));
	if (isShadow == true) particles->setStartColorVar(Color4F(0, 0, 0, 1));
	else particles->setStartColorVar(Color4F(0.5f, 0, 0.5f, 0));
	particles->setEndColor(Color4F(0, 0, 0, 0));
	particles->setEndColorVar(Color4F(0, 0, 0, 0));
	particles->setGravity(Vec2(0, 2500));

	int layer;
	particles->setLife(0.05);
	particles->runAction(Sequence::create(FadeOut::create(1.5f), RemoveSelf::create(), NULL));
	if (isShadow == true) layer = -100;
	else layer = -60;
	scene->addChild(particles, layer);

	atk->runAction(ScaleTo::create(0.35f, 0.3f));
	atk->runAction(Sequence::create(MoveBy::create(0.35f, Vec2(0,50)), RemoveSelf::create(), NULL));
}
