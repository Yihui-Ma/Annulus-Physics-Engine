#include "pch.h"
#include "Particle.h"
#include "Settings.h"

#include <iostream>

namespace Annulus
{
	const std::float_t Particle::sDefaultDamping = 0.999f;
	const std::float_t Particle::sDefaultMassInverse = 1;

	Particle::Particle() : mMassInverse(sDefaultMassInverse), mDamping(sDefaultDamping), mAcceleration(Settings::sDefaultGravity)
	{

	}

	const std::float_t& Particle::GetMassInverse() const
	{
		return mMassInverse;
	}

	void Particle::SetInverseMass(std::float_t inverseMass)
	{
		mMassInverse = inverseMass;
	}

	void Particle::SetMass(std::float_t mass)
	{
		// A particle cannot have 0 mass, it is practically impossible. Moreover, it isn't possible to solve for acceleration for such a particle.
		assert(mass != 0.0f);
		mMassInverse = 1 / mass;
	}

	void Particle::SetDamping(std::float_t damping)
	{
		// The damping factor ranges between 0 and 1 (exclusive of 1 since partically any particle will have some damping in its linear motion).
		assert(damping >= 0 && damping < 1);
		mDamping = damping;
	}

	void Particle::SetPosition(const glm::vec2& position)
	{
		mPosition = position;
	}

	void Particle::SetVelocity(const glm::vec2& velocity)
	{
		mVelocity = velocity;
	}

	void Particle::SetAcceleration(const glm::vec2& acceleration)
	{
		mAcceleration = acceleration;
	}

	void Particle::DebugParticle()
	{
		std::cout << std::endl;
		std::cout << "Position: " << mPosition.x << " " << mPosition.y << std::endl;
		std::cout << "Velocity: " << mVelocity.x << " " << mVelocity.y << std::endl;
		std::cout << "Acceleration: " << mAcceleration.x << " " << mAcceleration.y << std::endl;
		std::cout << std::endl;
	}

	void Particle::Integrate(std::chrono::nanoseconds nanoseconds)
	{
		// In case the mass isn't infinite, integrate.
		if(mMassInverse > 0.0f)
		{
			std::float_t seconds = nanoseconds.count() / 1000000000.0f;

			// Update position
			mPosition = mPosition + (mVelocity*seconds);

			// Estimate acceleration

			// Update velocity
			mVelocity *= glm::pow(mDamping, seconds);
			mVelocity += mAcceleration*seconds;

			// Clear the forces
		}
	}
}