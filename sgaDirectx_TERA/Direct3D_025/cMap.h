#pragma once

class cMeshMap;
class cDecalEffect;

class cMap
{
public :
	cMeshMap*				m_pMap;
private:
	//decalEffect용
	vector<D3DXVECTOR3> pMapVertex;		//맵mesh 정점정보
	LPD3DXMESH			pMapMesh;		//맵mesh정보
	cDecalEffect*		playerPosDecal;


	//맵
	cMeshMap*				m_pSurface_ter;

	//아이템
	cMeshMap*				m_pPotion;

	//오브젝트들
	//보스존입구 왼쪽
	cMeshMap*				m_pTrees_bossZoneLeft;
	cMeshMap*				m_pStones_bossZoneLeft;

	//보스존입구 오른쪽 집2지역
	cMeshMap*				m_pHouse2;

	cMeshMap*				m_pStone1_house2;
	cMeshMap*				m_pStone2_house2;

	cMeshMap*				m_pFlag1_house2;
	cMeshMap*				m_pFlag2_house2;

	cMeshMap*				m_pCart_house2;
	cMeshMap*				m_pCartburned_house2;
	cMeshMap*				m_pFence1_house2Back;
	cMeshMap*				m_pFence2_house2Back;

	cMeshMap*				m_pFence1_house2Front;
	cMeshMap*				m_pFence2_house2Front;
	cMeshMap*				m_pFence3_house2Front;
	cMeshMap*				m_pFence4_house2Front;

	//벨리카마을 밖 오른쪽 집1지역
	cMeshMap*				m_pHouse1;
	cMeshMap*				m_pDoor_House1;

	cMeshMap*				m_pWoodFence0_house1;
	cMeshMap*				m_pWoodFence1_house1;
	cMeshMap*				m_pWoodFence2_house1;
	cMeshMap*				m_pWoodFence3_house1;
	cMeshMap*				m_pWoodFence4_house1;
	cMeshMap*				m_pWoodFence5_house1;
	cMeshMap*				m_pWoodFence6_house1;

	cMeshMap*				m_pStoneFence1_house1;
	cMeshMap*				m_pStoneFence2_house1;
	cMeshMap*				m_pStoneFence3_house1;
	cMeshMap*				m_pStoneFence4_house1;
	cMeshMap*				m_pStoneFence5_house1;
	cMeshMap*				m_pStoneFence6_house1;
	cMeshMap*				m_pStoneFence7_house1;
	cMeshMap*				m_pStoneFence8_house1;
	cMeshMap*				m_pStoneFence9_house1;
	cMeshMap*				m_pStoneFence10_house1;

	cMeshMap*				m_pTree0_house1;
	cMeshMap*				m_pTree1_house1;
	cMeshMap*				m_pTree2_house1;
	cMeshMap*				m_pTree3_house1;
	cMeshMap*				m_pTree4_house1;
	cMeshMap*				m_pTree5_house1;
	cMeshMap*				m_pTree6_house1;
	cMeshMap*				m_pTree7_house1;
	cMeshMap*				m_pTree8_house1;

	//벨리카마을 밖 왼쪽 지역
	cMeshMap*				m_pStone_velicaLeft;
	cMeshMap*				m_pStone2_velicaLeft;
	cMeshMap*				m_pTree_velicaLeft;

	//벨리카마을 밖 오른쪽 지역
	cMeshMap*				m_pStone_velicaRight; //★ 안뜸 
	cMeshMap*				m_pStone2_velicaRight;

	//벨리카마을 밖 앞 지역
	cMeshMap*				m_pTree_velicaFront;

	//벨리카마을
	cMeshMap*				m_pVelica; //★ 안뜸

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	cMeshMap* GetMap(){ return m_pMap; }
	cMeshMap* GetSurface(){ return m_pSurface_ter; }
	cMeshMap* GetPotion(){ return m_pPotion; }

	void GeneratePlayerPos();

};

