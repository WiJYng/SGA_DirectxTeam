#pragma once

class cMeshMap;

class cMap
{
public :
	cMeshMap*				m_pMap;
private:
	//��
	
	cMeshMap*				m_pSurface_ter;

	//������
	cMeshMap*				m_pPotion;

	//������Ʈ��
	//�������Ա� ����
	cMeshMap*				m_pTrees_bossZoneLeft;
	cMeshMap*				m_pStones_bossZoneLeft;

	//�������Ա� ������ ��2����
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

	//����ī���� �� ������ ��1����
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

	//����ī���� �� ���� ����
	cMeshMap*				m_pStone_velicaLeft;
	cMeshMap*				m_pStone2_velicaLeft;
	cMeshMap*				m_pTree_velicaLeft;

	//����ī���� �� ������ ����
	cMeshMap*				m_pStone_velicaRight; //�� �ȶ� 
	cMeshMap*				m_pStone2_velicaRight;

	//����ī���� �� �� ����
	cMeshMap*				m_pTree_velicaFront;

	//����ī����
	cMeshMap*				m_pVelica; //�� �ȶ�

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	cMeshMap* GetMap(){ return m_pMap; }
	cMeshMap* GetSurface(){ return m_pSurface_ter; }
	cMeshMap* GetPotion(){ return m_pPotion; }

};

