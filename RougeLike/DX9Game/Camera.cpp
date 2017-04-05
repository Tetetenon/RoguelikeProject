#include "Camera.h"
#include "Input.h"
#include "define.h"
#include "GameState.h"
//親クラスはC3DObj
#include"Unit.h"

#include "Sky.h"
#include"UnitManager.h"
#include "Turn.h"

#define CAMERA_POS_X 0.0f
#define CAMERA_POS_Y 15.0f
#define CAMERA_POS_Z -10.0f

//デバッグ用カメラ位置(元に戻すこと)
#define DEBUG_CAMERA_POS_Y 160.0f
#define DEBUG_CAMERA_POS_Z -1.0f

#define LOOK_POS_X	0.0f
#define LOOK_POS_Y	1.0f
#define LOOK_POS_Z	0.0f

#define UP_DIR_X	0.0f
#define UP_DIR_Y	1.0f
#define UP_DIR_Z	0.0f


D3DXMATRIX CCamera::m_view;	//ビューマトリックス
CCamera* CCamera::m_pCamera = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CCamera::CCamera(CGameScene* pScene):
	C3DObj(pScene),
	m_pSky(NULL),
	m_pPlayer(NULL),
	m_fFovy(FOVY),
	m_fAspect((float)SCREEN_WIDTH / SCREEN_HEIGHT),
	m_fZNear(NEAR_CLIP),
	m_fZFar(FAR_CLIP)
{
	//カメラIDを設定
	m_uID = ID_CAMERA;

	//ビューマトリクスの初期化
	D3DXMatrixIdentity(&m_view);

	m_pos = D3DXVECTOR3(CAMERA_POS_X,CAMERA_POS_Y,CAMERA_POS_Z);
	m_pos2 = D3DXVECTOR3(CAMERA_POS_X,DEBUG_CAMERA_POS_Y,DEBUG_CAMERA_POS_Z);
	
	m_at = D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z);
	m_at2 = m_at;

	m_Up = D3DXVECTOR3(UP_DIR_X,UP_DIR_Y,UP_DIR_Z);
	m_Up2 = m_Up;

	
	m_cp = CP_TPVIEW;

	//タイマーの初期化
	m_nTimer = 0.0f;

	//カメラモード切替フラグ
	m_bSwitch = false;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CCamera::~CCamera(void)
{
}
//---------------------------------------------------------------------------------------
//オブジェクトの作成
//---------------------------------------------------------------------------------------
void CCamera::Create(CGameScene* pScene)
{
	//ポインタの中身がなければ作成
	if (!m_pCamera)
	{
		m_pCamera = new CCamera(pScene);
	}
}
//---------------------------------------------------------------------------------------
//オブジェクトの削除
//---------------------------------------------------------------------------------------
void CCamera::Delete()
{
	//NULLチェック
	if (m_pCamera)
	{
		//削除
		delete m_pCamera;
		//中身をきれいにする
		m_pCamera = NULL;
	}
}
//---------------------------------------------------------------------------------------
//オブジェクトのポインタを渡す
//---------------------------------------------------------------------------------------
CCamera* CCamera::GetPointer()
{
	return m_pCamera;
}
//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CCamera::Init ()
{
	D3DXMATRIX world;
	//行列の作成
	D3DXMatrixTranslation(&world,CAMERA_POS_X,CAMERA_POS_Y,CAMERA_POS_Z);
	SetWorld(world);

	//スカイドーム取得
	m_pSky = CSky::GetPointer();

	//プレイヤーオブジェクトの探索、設定
	CUnitManager* pUnitManager = CUnitManager::GetPointer();


	m_pPlayer = pUnitManager->Find(OBJ_NUM_PLAYER);
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CCamera::Update()
{
	//カメラ位置をデバッグと通常を切り替える
	if(CInput::GetKeyTrigger(DIK_C))
	{
		m_bSwitch = !m_bSwitch;
	}
}
//---------------------------------------------------------------------------------------
//更新後処理
//---------------------------------------------------------------------------------------
void CCamera::PostUpdate()
{
	//視野に基づいた左手座標系パースペクティブ射影行列の作成
	D3DXMatrixPerspectiveFovLH(&m_proj,m_fFovy,m_fAspect,m_fZNear,m_fZFar);

	if(m_pPlayer)
	{
		D3DXVECTOR3 Pos = m_pPlayer ->GetPos();
		if(m_bSwitch)
		{
			m_pos = D3DXVECTOR3(CAMERA_POS_X,DEBUG_CAMERA_POS_Y,DEBUG_CAMERA_POS_Z);

			D3DXVec3TransformCoord(&m_at,&D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z),&m_pPlayer ->GetWorld());
			
			m_at.x = 0.0f;
			m_at.y = 1.0f;
			m_at.z = 0.0f;
		}
		else
		{
			//戦闘時以外カメラ位置を更新
			if (m_pPlayer->GetUnitTurnState() != CTurn::GAME_STATE_ATTACK)
			{
					m_pos = D3DXVECTOR3(Pos.x + CAMERA_POS_X,CAMERA_POS_Y,Pos.z  + CAMERA_POS_Z);

					D3DXMATRIX PlayerWorld = m_pPlayer ->GetWorld();

					D3DXVec3TransformCoord(&m_at,&D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z),&PlayerWorld);
					
					m_at.x = PlayerWorld._41;
					m_at.y = 1.0f;
					m_at.z = PlayerWorld._43;
			}
		}

		D3DXVec3TransformNormal(&m_Up,&D3DXVECTOR3(UP_DIR_X,UP_DIR_Y,UP_DIR_Z),&m_pPlayer ->GetWorld());
		
		m_Up.x = 0.0f;
		m_Up.y = 1.0f;
		m_Up.z = 0.0f;

		D3DXMatrixLookAtLH(&m_view,&m_pos,&m_at,&m_Up);

		SetPos(m_pos);
	}
	else
	{
		//左手座標系ビュー行列の作成
		D3DXMatrixLookAtLH(&m_view,&GetPos(),&(GetPos() + GetForward()),&GetUp());
	}
	
	//スカイドームポインタNULLチェック
	if (m_pSky) 
	{
		//更新
		m_pSky->PostUpdate();
	}
}
//---------------------------------------------------------------------------------------
//描画前処理
//---------------------------------------------------------------------------------------
void CCamera::PreDraw()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();

	//第一引数の設定を使用し、第二引数のトランスフォームを行う
	pD -> SetTransform(D3DTS_PROJECTION,&m_proj);

	pD -> SetTransform(D3DTS_VIEW,&m_view);
	
	//スカイドームポインタNULLチェック
	if (m_pSky) 
	{
		//描画
		m_pSky->PreDraw();
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CCamera::Draw()
{
}
//---------------------------------------------------------------------------------------
//半透明描画
//---------------------------------------------------------------------------------------
void CCamera::DrawAlpha()
{

}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CCamera::Fin()
{
	m_pSky = NULL;
}
