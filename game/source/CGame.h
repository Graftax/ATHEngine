#ifndef CGame_h__
#define CGame_h__

#include <Windows.h>
#include "../../engine/ATHUtil/UTimer.h"

#include <vector>
#include <string>
using std::string;
using namespace std;

class ATHRenderer;
class ATHObjectManager;

class CGame
{
	// Data Members ////
	bool bFullscreen;
	bool bShutdown;

	float m_fElapsedTime;
	float m_fGameTime;

	int m_nScreenWidth;
	int m_nScreenHeight;

	CTimer m_Timer;
	float			m_fFrameTime;
	unsigned int	m_unFrameCounter;

	ATHRenderer*		m_pRenderer;
	ATHObjectManager*	m_pObjectManager;

	////////////////////

	// default constructor
	CGame();
	// copy constructor
	CGame(const CGame&);
	// assignment operator
	CGame& operator=(const CGame&);
	// destructor
	~CGame();

	// utility functions
	void PreUpdate( float fDT );
	bool Update( float fDT );
	void PostUpdate( float fDT );
	void Render();

public:


	static CGame* GetInstance();

	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);
	void TestInit();

	bool Main();
	void Shutdown();

	float GetElapsedTime() {return m_fElapsedTime; }
	void SetElapsedTime(float t) { m_fElapsedTime = t; }
	
	int GetScreenWidth() {return m_nScreenWidth;  }
	int GetScreenHeight() {return m_nScreenHeight; }
};


#endif // CGame_h__