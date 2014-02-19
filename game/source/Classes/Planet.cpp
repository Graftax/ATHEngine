#include "Planet.h"
#include "../../../engine/Box2D/Box2D.h"

#define PLANET_GRAVITY_CONSTANT 2.0f

Planet::Planet()
{
	ATHObject();
	m_fMass = 0.0f;
}

void Planet::Update(float _fDT)
{
	std::list< b2Body* >::iterator itrBody = m_liGravityTargets.begin();
	std::list< b2Body* >::iterator itrEnd = m_liGravityTargets.end();

	float fRadius = GetPropertyAsFloat("gravity-radius");

	while (itrBody != itrEnd)
	{
		b2Vec2 dirVec = m_pBody->GetWorldCenter() - (*itrBody)->GetWorldCenter();
		float fDist = dirVec.Normalize();
		float fForce = PLANET_GRAVITY_CONSTANT * GetMass() * (*itrBody)->GetMass() / ( fDist * fDist );
		fForce = fForce * (fDist / fRadius);

		(*itrBody)->ApplyForceToCenter(fForce * dirVec);

		itrBody++;
	}

}

void Planet::OnCollisionEnter(b2Contact* _pContact)
{
	ATHObject* pObjA = (ATHObject*)_pContact->GetFixtureA()->GetBody()->GetUserData();
	ATHObject* pObjB = (ATHObject*)_pContact->GetFixtureB()->GetBody()->GetUserData();

	// Check to see which object this one is
	if (this == pObjA)
	{
		if (_pContact->GetFixtureA()->IsSensor())
			m_liGravityTargets.push_back(_pContact->GetFixtureB()->GetBody());
	}
	else if (this == pObjB)
	{
		if(_pContact->GetFixtureB()->IsSensor())
			m_liGravityTargets.push_back(_pContact->GetFixtureA()->GetBody());
	}
}

void Planet::OnCollisionExit(b2Contact* _pContact)
{
	ATHObject* pObjA = (ATHObject*)_pContact->GetFixtureA()->GetBody()->GetUserData();
	ATHObject* pObjB = (ATHObject*)_pContact->GetFixtureB()->GetBody()->GetUserData();

	// Check to see which object this one is
	if (this == pObjA)
	{
		if (_pContact->GetFixtureA()->IsSensor())
			m_liGravityTargets.remove(_pContact->GetFixtureB()->GetBody());
	}
	else if (this == pObjB)
	{
		if (_pContact->GetFixtureB()->IsSensor())
			m_liGravityTargets.remove(_pContact->GetFixtureA()->GetBody());
	}
}