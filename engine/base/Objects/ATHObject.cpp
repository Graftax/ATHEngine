#include "ATHObject.h"

#include "../Box2D/Box2D.h"
#include "../ATHRenderer/ATHRenderNode.h"

D3DMATRIX ATHObject::GetTransform()
{
	return m_matTransform;
}

ATHRenderNode* ATHObject::GetRenderNode()
{
	return m_pRenderNode;
}

b2Body*	ATHObject::GetBody()
{
	return m_pBody;
}


void ATHObject::Init( ATHRenderNode* _pRenderNode, b2Body* _pBody )
{
	m_bAlive = true;
	m_bActive = true;

	m_pRenderNode = _pRenderNode;
	m_pBody = _pBody;

	if( m_pBody )
		m_pBody->SetUserData( this );
}

void ATHObject::Update( float _fDT )
{
	if( m_pBody )
	{
		D3DXMATRIX matRot;
		D3DXMatrixRotationZ( &matRot, m_pBody->GetAngle() );

		D3DXMATRIX matTrans;
		D3DXMatrixTranslation( &matTrans, m_pBody->GetPosition().x, m_pBody->GetPosition().y, 0.0f );

		m_matTransform = matRot * matTrans;
	}

	if( m_pRenderNode )
	{
		m_pRenderNode->SetTransform( m_matTransform );
	}
}

void ATHObject::Shutdown()
{
	if( m_pBody )
		m_pBody->SetUserData( nullptr );

	m_pBody = nullptr;
	m_pRenderNode = nullptr;

}
