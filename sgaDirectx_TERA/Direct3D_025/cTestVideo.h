#pragma once

#include "cScene.h"
#include "cVideo.h"

class cTestVideo : public cScene
{
	cVideo*	m_pVideo;

	bool	m_bPlay;

public:
	cTestVideo();
	~cTestVideo();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};
