#include "stdafx.h"
#include "cMap.h"
#include "cMeshMap.h"


cMap::cMap()
:m_pMap(NULL)
, m_pSurface_ter(NULL)

, m_pPotion(NULL)

, m_pTrees_bossZoneLeft(NULL)
, m_pStones_bossZoneLeft(NULL)

, m_pHouse2(NULL)
, m_pStone1_house2(NULL)
, m_pStone2_house2(NULL)
, m_pFlag1_house2(NULL)
, m_pFlag2_house2(NULL)
, m_pCart_house2(NULL)
, m_pCartburned_house2(NULL)
, m_pFence1_house2Back(NULL)
, m_pFence2_house2Back(NULL)
, m_pFence1_house2Front(NULL)
, m_pFence2_house2Front(NULL)
, m_pFence3_house2Front(NULL)
, m_pFence4_house2Front(NULL)

, m_pHouse1(NULL)
, m_pDoor_House1(NULL)

, m_pWoodFence0_house1(NULL)
, m_pWoodFence1_house1(NULL)
, m_pWoodFence2_house1(NULL)
, m_pWoodFence3_house1(NULL)
, m_pWoodFence4_house1(NULL)
, m_pWoodFence5_house1(NULL)
, m_pWoodFence6_house1(NULL)

, m_pStoneFence1_house1(NULL)
, m_pStoneFence2_house1(NULL)
, m_pStoneFence3_house1(NULL)
, m_pStoneFence4_house1(NULL)
, m_pStoneFence5_house1(NULL)
, m_pStoneFence6_house1(NULL)
, m_pStoneFence7_house1(NULL)
, m_pStoneFence8_house1(NULL)
, m_pStoneFence9_house1(NULL)
, m_pStoneFence10_house1(NULL)

, m_pTree0_house1(NULL)
, m_pTree1_house1(NULL)
, m_pTree2_house1(NULL)
, m_pTree3_house1(NULL)
, m_pTree4_house1(NULL)
, m_pTree5_house1(NULL)
, m_pTree6_house1(NULL)
, m_pTree7_house1(NULL)
, m_pTree8_house1(NULL)

, m_pStone_velicaLeft(NULL)
, m_pStone2_velicaLeft(NULL)
, m_pTree_velicaLeft(NULL)

, m_pStone_velicaRight(NULL)
, m_pStone2_velicaRight(NULL)

, m_pTree_velicaFront(NULL)

, m_pVelica(NULL)
{
}
cMap::~cMap()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pSurface_ter);

	SAFE_DELETE(m_pPotion);

	SAFE_DELETE(m_pTrees_bossZoneLeft);
	SAFE_DELETE(m_pStones_bossZoneLeft);

	SAFE_DELETE(m_pHouse2);

	SAFE_DELETE(m_pStone1_house2);
	SAFE_DELETE(m_pStone2_house2);

	SAFE_DELETE(m_pFlag1_house2);
	SAFE_DELETE(m_pFlag2_house2);

	SAFE_DELETE(m_pCart_house2);
	SAFE_DELETE(m_pCartburned_house2);

	SAFE_DELETE(m_pFence1_house2Back);
	SAFE_DELETE(m_pFence2_house2Back);

	SAFE_DELETE(m_pFence1_house2Front);
	SAFE_DELETE(m_pFence2_house2Front);
	SAFE_DELETE(m_pFence3_house2Front);
	SAFE_DELETE(m_pFence4_house2Front);

	SAFE_DELETE(m_pHouse1);
	SAFE_DELETE(m_pDoor_House1);

	SAFE_DELETE(m_pWoodFence0_house1);
	SAFE_DELETE(m_pWoodFence1_house1);
	SAFE_DELETE(m_pWoodFence2_house1);
	SAFE_DELETE(m_pWoodFence3_house1);
	SAFE_DELETE(m_pWoodFence4_house1);
	SAFE_DELETE(m_pWoodFence5_house1);
	SAFE_DELETE(m_pWoodFence6_house1);

	SAFE_DELETE(m_pStoneFence1_house1);
	SAFE_DELETE(m_pStoneFence2_house1);
	SAFE_DELETE(m_pStoneFence3_house1);
	SAFE_DELETE(m_pStoneFence4_house1);
	SAFE_DELETE(m_pStoneFence5_house1);
	SAFE_DELETE(m_pStoneFence6_house1);
	SAFE_DELETE(m_pStoneFence7_house1);
	SAFE_DELETE(m_pStoneFence8_house1);
	SAFE_DELETE(m_pStoneFence9_house1);
	SAFE_DELETE(m_pStoneFence10_house1);

	SAFE_DELETE(m_pTree0_house1);
	SAFE_DELETE(m_pTree1_house1);
	SAFE_DELETE(m_pTree2_house1);
	SAFE_DELETE(m_pTree3_house1);
	SAFE_DELETE(m_pTree4_house1);
	SAFE_DELETE(m_pTree5_house1);
	SAFE_DELETE(m_pTree6_house1);
	SAFE_DELETE(m_pTree7_house1);
	SAFE_DELETE(m_pTree8_house1);

	SAFE_DELETE(m_pStone_velicaLeft);
	SAFE_DELETE(m_pStone2_velicaLeft);
	SAFE_DELETE(m_pTree_velicaLeft);

	SAFE_DELETE(m_pStone_velicaRight);
	SAFE_DELETE(m_pStone2_velicaRight);

	SAFE_DELETE(m_pTree_velicaFront);

	SAFE_DELETE(m_pVelica);
}

void cMap::Setup()
{
	//����
	m_pMap = new cMeshMap();
	m_pMap->Setup("./Tera/Map/EntireMap/moveMap/moveMap.X");
	m_pSurface_ter = new cMeshMap();
	m_pSurface_ter->Setup("Tera/Map/EntireMap/moveMapSurface/moveMapSurface.X");

	//������
	m_pPotion = new cMeshMap();
	m_pPotion->Setup("Tera/Item/Potion.X");

	//������Ʈ��
	//�������Ա� ����
	m_pTrees_bossZoneLeft = new cMeshMap();
	m_pTrees_bossZoneLeft->Setup("Tera/Map/EntireMap/ST_beside_bossZone/Trees_besideBossZone.X");

	m_pStones_bossZoneLeft = new cMeshMap();
	m_pStones_bossZoneLeft->Setup("Tera/Map/EntireMap/ST_beside_bossZone/Stones_besideBossZone.X");

	//�������Ա� ������ (��2����)
	m_pHouse2 = new cMeshMap;
	m_pHouse2->Setup("Tera/Map/EntireMap/House2/House2.X");

	m_pStone1_house2 = new cMeshMap;
	m_pStone1_house2->Setup("Tera/Map/EntireMap/House2/Stone1_house2.X");

	m_pStone2_house2 = new cMeshMap;
	m_pStone2_house2->Setup("Tera/Map/EntireMap/House2/Stone2_house2.X");

	m_pFlag1_house2 = new cMeshMap;
	m_pFlag1_house2->Setup("Tera/Map/EntireMap/House2/Flag.X");

	m_pFlag2_house2 = new cMeshMap;
	m_pFlag2_house2->Setup("Tera/Map/EntireMap/House2/Flag2.X");

	m_pCart_house2 = new cMeshMap;
	m_pCart_house2->Setup("Tera/Map/EntireMap/House2/Cart.X");

	m_pCartburned_house2 = new cMeshMap;
	m_pCartburned_house2->Setup("Tera/Map/EntireMap/House2/Cart_burned.X");

	m_pFence1_house2Back = new cMeshMap;
	m_pFence1_house2Back->Setup("Tera/Map/EntireMap/House2/Fence1_house2Back.X");

	m_pFence2_house2Back = new cMeshMap;
	m_pFence2_house2Back->Setup("Tera/Map/EntireMap/House2/Fence2_house2Back.X");

	m_pFence1_house2Front = new cMeshMap;
	m_pFence1_house2Front->Setup("Tera/Map/EntireMap/House2/Fence1_house2Front.X");

	m_pFence2_house2Front = new cMeshMap;
	m_pFence2_house2Front->Setup("Tera/Map/EntireMap/House2/Fence2_house2Front.X");

	m_pFence3_house2Front = new cMeshMap;
	m_pFence3_house2Front->Setup("Tera/Map/EntireMap/House2/Fence3_house2Front.X");

	m_pFence4_house2Front = new cMeshMap;
	m_pFence4_house2Front->Setup("Tera/Map/EntireMap/House2/Fence4_house2Front.X");

	////����ī���� �� ������ ��1����
	m_pHouse1 = new cMeshMap;
	m_pHouse1->Setup("Tera/Map/EntireMap/House1/House1.X");
	m_pDoor_House1 = new cMeshMap;
	m_pDoor_House1->Setup("Tera/Map/EntireMap/House1/door_house.X");

	m_pWoodFence0_house1 = new cMeshMap;
	m_pWoodFence0_house1->Setup("Tera/Map/EntireMap/House1/WoodFence0_house1.X");	 
	m_pWoodFence1_house1 = new cMeshMap;								
	m_pWoodFence1_house1->Setup("Tera/Map/EntireMap/House1/WoodFence1_house1.X");	
	m_pWoodFence2_house1 = new cMeshMap;								
	m_pWoodFence2_house1->Setup("Tera/Map/EntireMap/House1/WoodFence2_house1.X");		
	m_pWoodFence3_house1 = new cMeshMap;								
	m_pWoodFence3_house1->Setup("Tera/Map/EntireMap/House1/WoodFence3_house1.X");
	m_pWoodFence4_house1 = new cMeshMap;								
	m_pWoodFence4_house1->Setup("Tera/Map/EntireMap/House1/WoodFence4_house1.X");
	m_pWoodFence5_house1 = new cMeshMap;								 
	m_pWoodFence5_house1->Setup("Tera/Map/EntireMap/House1/WoodFence5_house1.X");		 
	m_pWoodFence6_house1 = new cMeshMap;								 
	m_pWoodFence6_house1->Setup("Tera/Map/EntireMap/House1/WoodFence6_house1.X");

	m_pStoneFence1_house1 = new cMeshMap;
	m_pStoneFence1_house1->Setup("Tera/Map/EntireMap/House1/StoneFence1_house1.X");
	m_pStoneFence2_house1 = new cMeshMap;
	m_pStoneFence2_house1->Setup("Tera/Map/EntireMap/House1/StoneFence2_house1.X");
	m_pStoneFence3_house1 = new cMeshMap;
	m_pStoneFence3_house1->Setup("Tera/Map/EntireMap/House1/StoneFence3_house1.X");
	m_pStoneFence4_house1 = new cMeshMap;
	m_pStoneFence4_house1->Setup("Tera/Map/EntireMap/House1/StoneFence4_house1.X");
	m_pStoneFence5_house1 = new cMeshMap;				   
	m_pStoneFence5_house1->Setup("Tera/Map/EntireMap/House1/StoneFence5_house1.X");
	m_pStoneFence6_house1 = new cMeshMap;				   
	m_pStoneFence6_house1->Setup("Tera/Map/EntireMap/House1/StoneFence6_house1.X");
	m_pStoneFence7_house1 = new cMeshMap;				   
	m_pStoneFence7_house1->Setup("Tera/Map/EntireMap/House1/StoneFence7_house1.X");
	m_pStoneFence8_house1 = new cMeshMap;				   
	m_pStoneFence8_house1->Setup("Tera/Map/EntireMap/House1/StoneFence8_house1.X");
	m_pStoneFence9_house1 = new cMeshMap;				   
	m_pStoneFence9_house1->Setup("Tera/Map/EntireMap/House1/StoneFence9_house1.X");

	m_pTree0_house1 = new cMeshMap;
	m_pTree0_house1->Setup("Tera/Map/EntireMap/House1/Tree0_house1.X");
	m_pTree1_house1 = new cMeshMap;					 
	m_pTree1_house1->Setup("Tera/Map/EntireMap/House1/Tree1_house1.X");
	m_pTree2_house1 = new cMeshMap;					 
	m_pTree2_house1->Setup("Tera/Map/EntireMap/House1/Tree2_house1.X");
	m_pTree3_house1 = new cMeshMap;					 
	m_pTree3_house1->Setup("Tera/Map/EntireMap/House1/Tree3_house1.X");
	m_pTree4_house1 = new cMeshMap;					 
	m_pTree4_house1->Setup("Tera/Map/EntireMap/House1/Tree4_house1.X");
	m_pTree5_house1 = new cMeshMap;					 
	m_pTree5_house1->Setup("Tera/Map/EntireMap/House1/Tree5_house1.X");
	m_pTree6_house1 = new cMeshMap;					 
	m_pTree6_house1->Setup("Tera/Map/EntireMap/House1/Tree6_house1.X");

	//����ī���� �� ���� ����
	m_pStone_velicaLeft = new cMeshMap;
	m_pStone_velicaLeft->Setup("Tera/Map/EntireMap/ST_velicaLeft/Stone_velicaLeft.X");
	m_pStone2_velicaLeft = new cMeshMap;
	m_pStone2_velicaLeft->Setup("Tera/Map/EntireMap/ST_velicaLeft/Stone2_velicaLeft.X");
	m_pTree_velicaLeft = new cMeshMap;
	m_pTree_velicaLeft->Setup("Tera/Map/EntireMap/ST_velicaLeft/Tree_velicaLeft.X");

	//����ī���� �� ������ ����
	m_pStone_velicaRight = new cMeshMap;
	m_pStone_velicaRight->Setup("Tera/Map/EntireMap/ST_velicaRight/Stone_velicaRight.X");
	m_pStone2_velicaRight = new cMeshMap;
	m_pStone2_velicaRight->Setup("Tera/Map/EntireMap/ST_velicaRight/Stone2_velicaRight.X");

	//����ī���� �� �� ����
	m_pTree_velicaFront = new cMeshMap;
	m_pTree_velicaFront->Setup("Tera/Map/EntireMap/ST_velicaFront/Tree_velicaFront.X");

	//����ī����
	m_pVelica = new cMeshMap;
	m_pVelica->Setup("Tera/Map/EntireMap/Velica/Velica.X");


}
void cMap::Update()
{

}
void cMap::Render()
{
	//����
	if (m_pMap)
		m_pMap->Render();

	//if (m_pSurface_ter)
	//	m_pSurface_ter->Render();


	//������
	if (m_pPotion) 
		m_pPotion->Render();


	//���� (�� ���� ���� ������Ʈ��)
	//�������Ա� ����
	if (m_pTrees_bossZoneLeft)
		m_pTrees_bossZoneLeft->Render();
	if (m_pStones_bossZoneLeft)
		m_pStones_bossZoneLeft->Render();


	//�������Ա� ������ ��2����
	if (m_pHouse2)
		m_pHouse2->Render();
	if (m_pStone1_house2)
		m_pStone1_house2->Render();
	if (m_pStone2_house2)
		m_pStone2_house2->Render();
	if (m_pFlag1_house2)
		m_pFlag1_house2->Render();
	if (m_pFlag2_house2)
		m_pFlag2_house2->Render();


	if (m_pCart_house2)
		m_pCart_house2->Render();
	if (m_pCartburned_house2)
		m_pCartburned_house2->Render();

	if (m_pFence1_house2Back)
		m_pFence1_house2Back->Render();
	if (m_pFence2_house2Back)
		m_pFence2_house2Back->Render();

	if (m_pFence1_house2Front)
		m_pFence1_house2Front->Render();
	if (m_pFence2_house2Front)
		m_pFence2_house2Front->Render();
	if (m_pFence3_house2Front)
		m_pFence3_house2Front->Render();
	if (m_pFence4_house2Front)
		m_pFence4_house2Front->Render();


	////����ī���� �� ������ ��1����
	if (m_pHouse1)
		m_pHouse1->Render();
	if (m_pDoor_House1)
		m_pDoor_House1->Render();

	if (m_pWoodFence0_house1)
		m_pWoodFence0_house1->Render();
	if (m_pWoodFence1_house1)
		m_pWoodFence1_house1->Render();
	if (m_pWoodFence2_house1)
		m_pWoodFence2_house1->Render();
	if (m_pWoodFence3_house1)
		m_pWoodFence3_house1->Render();
	if (m_pWoodFence4_house1)
		m_pWoodFence4_house1->Render();
	if (m_pWoodFence5_house1)
		m_pWoodFence5_house1->Render();
	if (m_pWoodFence6_house1)
		m_pWoodFence6_house1->Render();

	if (m_pStoneFence1_house1)
		m_pStoneFence1_house1->Render();
	if (m_pStoneFence2_house1)
		m_pStoneFence2_house1->Render();
	if (m_pStoneFence3_house1)
		m_pStoneFence3_house1->Render();
	if (m_pStoneFence4_house1)
		m_pStoneFence4_house1->Render();
	if (m_pStoneFence5_house1)
		m_pStoneFence5_house1->Render();
	if (m_pStoneFence6_house1)
		m_pStoneFence6_house1->Render();
	if (m_pStoneFence7_house1)
		m_pStoneFence7_house1->Render();
	if (m_pStoneFence8_house1)
		m_pStoneFence8_house1->Render();
	if (m_pStoneFence9_house1)
		m_pStoneFence9_house1->Render();


	if (m_pTree0_house1)
		m_pTree0_house1->Render();
	if (m_pTree1_house1)
		m_pTree1_house1->Render();
	if (m_pTree2_house1)
		m_pTree2_house1->Render();
	if (m_pTree3_house1)
		m_pTree3_house1->Render();
	if (m_pTree4_house1)
		m_pTree4_house1->Render();
	if (m_pTree5_house1)
		m_pTree5_house1->Render();
	if (m_pTree6_house1)
		m_pTree6_house1->Render();


	//����ī���� �� ���� ����
	if (m_pStone_velicaLeft)
		m_pStone_velicaLeft->Render();
	if (m_pStone2_velicaLeft)
		m_pStone2_velicaLeft->Render();
	if (m_pTree_velicaLeft)
		m_pTree_velicaLeft->Render();

	//����ī���� �� ������ ����
	if (m_pStone_velicaRight)
		m_pStone_velicaRight->Render();
	if (m_pStone2_velicaRight)
		m_pStone2_velicaRight->Render();

	//����ī���� �� �� ����
	if (m_pTree_velicaFront)
		/*m_pTree_velicaFront->Render();*/

	//����ī����
	if (m_pVelica)
		m_pVelica->Render();
}
