#include "pch.h"
#include "TorqueDemo.h"

#include "AnchoredSpring.h"
#include "RigidBody.h"
#include "Gravity.h"

using namespace Annulus;

namespace Demos
{
	const std::float_t TorqueDemo::sRectangleLength = 200.0f;
	const std::float_t TorqueDemo::sRectangleHeight = 140.0f;

	TorqueDemo::TorqueDemo(sf::RenderWindow& renderWindow, Annulus::World& world) :
		Demo(renderWindow, world),
		mRigidBody(nullptr),
		mGravity(nullptr)
	{
		// Create the rigidbody.
		mRigidBody = new RigidBody();

		// Create the force generator.
		mGravity = new Gravity(*mRigidBody);
		//AnchoredSpring* anchoredSpring = new AnchoredSpring(*mRigidBody, glm::vec2(-sRectangleLength / 2, -sRectangleHeight / 2));
		//anchoredSpring->SetRestLength(200);

		// Create rectangle to visualize rigid body.
		mRectangle = new sf::RectangleShape(sf::Vector2f(sRectangleLength, sRectangleHeight));
		mRectangle->setOrigin(sRectangleLength / 2, sRectangleHeight / 2);
		mRectangle->setFillColor(sf::Color::Yellow);

		Initialize();
	}

	TorqueDemo::~TorqueDemo()
	{
		delete mRectangle;
	}

	void TorqueDemo::Initialize()
	{
		mRigidBody->AddForceRelative(glm::vec2(1000, 0), glm::vec2(0, 2));
		mRigidBody->SetAngularDamping(0.2f);
		mRigidBody->SetLinearDamping(0.1f);
	}

	void TorqueDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;

		mRectangle->setPosition(centerX + mRigidBody->GetPosition().x, centerY - mRigidBody->GetPosition().y);
		mRectangle->setRotation(mRigidBody->GetOrientation().GetOrientationDegrees() * -1);
	}

	void TorqueDemo::Draw()
	{
		mRenderWindow.draw(*mRectangle);
	}
}