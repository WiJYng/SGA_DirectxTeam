#include "StdAfx.h"
#include "cScene_00.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTrailRender.h"


cScene_00::cScene_00(void)
{
}

cScene_00::~cScene_00(void)
{
}

HRESULT cScene_00::Scene_Init()
{
	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling( &matScale, 0.01f, 0.01f, 0.01f );
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY( &matRotate, 180.0f * ONE_RAD );
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//���� �޽� �ε�
	cXMesh_Static* mesh = 
		RESOURCE_STATICXMESH->GetResource( 
		"./Resources/Meshes/Fighter/Fighter.X", &matCorrection );


	cXMesh_Static* box = 
		RESOURCE_STATICXMESH->GetResource( 
		"./Resources/Meshes/Disc.x" );

	//������Ʈ ����
	cBaseObject* pNewObject1 = new cBaseObject();
	pNewObject1->SetMesh( mesh );
	pNewObject1->SetActive( true );

	cBaseObject* pNewObject2 = new cBaseObject();
	pNewObject2->SetMesh( box );
	pNewObject2->SetActive( true );
	pNewObject2->pTransform->SetWorldPosition( 0, -10.0f, 0.0f );
	pNewObject2->IgnoreCreateShadow = true;		//�׸��� �ȱ׸���.
	pNewObject2->ApplyShadow = true;


	cBaseObject* pNewObject3 = new cBaseObject();
	pNewObject3->SetMesh( mesh );
	pNewObject3->SetActive( true );
	pNewObject3->pTransform->SetWorldPosition( 0, -5.0f, 0.0f );
	pNewObject3->ApplyShadow = true;


	//�M�� ������Ʈ Ǫ��
	this->renderObjects.push_back( pNewObject1 );
	this->renderObjects.push_back( pNewObject2 );
	this->renderObjects.push_back( pNewObject3 );

	

	//����Ʈ ��ġ
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition( 0, 20, 0 );
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld( 90.0f * ONE_RAD, 0, 0 );



	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init( 
		1.0f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		1.0f,					//��
		RESOURCE_TEXTURE->GetResource( "./Resources/Testures/TrailTest.png" ),	//���� Texture
		D3DXCOLOR( 1, 0, 0, 1 ),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource( "./Resources/Testures/TrailTest.png" )	//�ܰ� �׸��� �ܰ� �븻
		);


	return S_OK;
}

void cScene_00::Scene_Release()
{
	//������Ʈ ����
	for( int i = 0 ; i < this->renderObjects.size() ; i++ )
		SAFE_DELETE( this->renderObjects[i] );
	this->renderObjects.clear();
	this->cullObjects.clear();

	//Trail ����
	this->pTrailRender->Release();
	SAFE_DELETE( this->pTrailRender );
}

void cScene_00::Scene_Update( float timDelta )
{
	if( KEY_MGR->IsOnceDown( VK_RETURN ) ){
			//SCENE_MGR->ChangeScene( "������", 1 );
		SCENE_MGR->ChangeSceneWithLoading("Test00", "�ε���", 1, 1 );

	}

	//this->pSceneBaseDirectionLight->pTransform->DefaultControl2( timDelta ); //��

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	for( int i = 0 ; i < this->renderObjects.size() ; i++ ){
		
		this->renderObjects[i]->Update( timDelta );

		//�������� �ȿ� �ִ�?
		if( this->pMainCamera->Frustum.IsInFrustum( this->renderObjects[i] ) )
		{
			this->cullObjects.push_back( this->renderObjects[i] );
		}
	}


	//������Ʈ
	this->pTrailRender->Update( timDelta );
	this->pTrailRender->Transform.DefaultControl2( timDelta );


	//������� �غ�
	this->ReadyShadowMap( &this->renderObjects );  //�������� ������Ʈ �����Ѵ� ( �ݵ�� Render ���� �������� ������Ʈ���� �ض� )
}

void cScene_00::Scene_Render1()
{
	cXMesh_Static::SetCamera( this->pMainCamera );
	
	//���̽� ������ ����
	cXMesh_Static::SetBaseLight( this->pSceneBaseDirectionLight );

	
	
	for( int i = 0 ; i < this->cullObjects.size() ; i++ ){
		this->cullObjects[i]->Render();
	}

	//�������� �׷�����
	this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();


	//���� ( �ظ��ϸ� ���ĺ����̴ϱ� ���߿� �׸���... )
	this->pTrailRender->Render();
}


void cScene_00::Scene_RenderSprite()
{
	//������ ���� �׷�����....
	RECT rcSour = { 0, 0, 4096, 4096 };
	RECT rcDest = { 0, 0, 300, 300 };


	SPRITE_MGR->DrawArea( this->pDirectionLightCamera->GetShadowTexture(),
		&rcSour, 
		&rcDest );
}

