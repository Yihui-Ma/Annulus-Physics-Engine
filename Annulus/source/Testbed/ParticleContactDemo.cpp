#include "pch.h"
#include "ParticleContactDemo.h"
#include "Particle.h"
#include "ParticleWorld.h"
#include "ParticleRod.h"
#include "ParticleCable.h"
#include "ParticleGravity.h"

using namespace Annulus;

namespace Demos
{
	const glm::vec2 ParticleContactDemo::sParticlePosition1 = glm::vec2(-100.0f, 0.0f);
	const glm::vec2 ParticleContactDemo::sParticlePosition2 = glm::vec2(100.0f, 0.0f);
	const glm::vec2 ParticleContactDemo::sParticlePosition3 = glm::vec2(-140.0f, -40.0f);
	const glm::vec2 ParticleContactDemo::sParticlePosition4 = glm::vec2(60.0f, -40.0f);

	ParticleContactDemo::ParticleContactDemo(sf::RenderWindow& renderWindow, Annulus::ParticleWorld& world) :
		ParticleDemo(renderWindow, world),
		mParticle1(nullptr),
		mParticle2(nullptr),
		mParticle3(nullptr),
		mParticle4(nullptr),
		mCircle1(nullptr),
		mCircle2(nullptr),
		mCircle3(nullptr),
		mCircle4(nullptr)
	{
		mParticle1 = mWorld.CreateParticle();
		mParticle2 = mWorld.CreateParticle();
		mParticle3 = mWorld.CreateParticle();
		mParticle4 = mWorld.CreateParticle();

		// Create the contacts
		ParticleRod* rod = new ParticleRod(*mParticle3, *mParticle4);
		rod->SetLength(200);

		ParticleCable* cable = new ParticleCable(*mParticle1, *mParticle3);
		cable->SetMaxLength(100);
		cable->SetRestitution(0.8f);

		ParticleCable* cable2 = new ParticleCable(*mParticle2, *mParticle4);
		cable2->SetMaxLength(100);
		cable2->SetRestitution(0.8f);

		ParticleGravity* gravity = new ParticleGravity(mWorld);
		gravity->RegisterParticle(*mParticle3);
		gravity->RegisterParticle(*mParticle4);


		mCircle1 = new sf::CircleShape(sParticleRadius);
		mCircle2 = new sf::CircleShape(sParticleRadius);
		mCircle3 = new sf::CircleShape(sParticleRadius);
		mCircle4 = new sf::CircleShape(sParticleRadius);

		Initialize();
	}

	ParticleContactDemo::~ParticleContactDemo()
	{

	}

	void ParticleContactDemo::Initialize()
	{
		// Initialize particles
		mParticle1->SetPosition(sParticlePosition1);
		mParticle1->SetDamping(0.9f);
		mParticle1->SetInverseMass(0.0f);
		mParticle1->SetVelocity(glm::vec2(0, 0));
		
		mParticle2->SetPosition(sParticlePosition2);
		mParticle2->SetDamping(0.9f);
		mParticle2->SetInverseMass(0.0f);
		mParticle2->SetVelocity(glm::vec2(0, 0));

		mParticle3->SetPosition(sParticlePosition3);
		mParticle3->SetDamping(0.9f);
		mParticle3->SetVelocity(glm::vec2(0, 0));

		mParticle4->SetPosition(sParticlePosition4);
		mParticle4->SetDamping(0.9f);
		mParticle4->SetVelocity(glm::vec2(0, 0));

		// Initialize circles to visualize particles
		mCircle1->setPosition(0, 0);
		mCircle1->setFillColor(sf::Color::Black);

		mCircle2->setPosition(0, 0);
		mCircle2->setFillColor(sf::Color::Black);

		mCircle3->setPosition(0, 0);
		mCircle3->setFillColor(sf::Color::Red);

		mCircle4->setPosition(0, 0);
		mCircle4->setFillColor(sf::Color::Red);
	}

	void ParticleContactDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		mCircle1->setPosition(centerX + mParticle1->GetPosition().x * sPixelPositionScaler, centerY - mParticle1->GetPosition().y * sPixelPositionScaler);
		mCircle2->setPosition(centerX + mParticle2->GetPosition().x * sPixelPositionScaler, centerY - mParticle2->GetPosition().y * sPixelPositionScaler);
		mCircle3->setPosition(centerX + mParticle3->GetPosition().x * sPixelPositionScaler, centerY - mParticle3->GetPosition().y * sPixelPositionScaler);
		mCircle4->setPosition(centerX + mParticle4->GetPosition().x * sPixelPositionScaler, centerY - mParticle4->GetPosition().y * sPixelPositionScaler);
	}

	void ParticleContactDemo::Draw()
	{
		mRenderWindow.draw(*mCircle1);
		mRenderWindow.draw(*mCircle2);
		mRenderWindow.draw(*mCircle3);
		mRenderWindow.draw(*mCircle4);
	}
}
