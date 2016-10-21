// スカイドーム クラス実装

#include "Sky.h"
#include "Camera.h"

// 定数
#define PATH_MESHSKY	_T("../data/model/sky.x")

// 静的メンバ
CMesh CSky::m_mesh;

// コンストラクタ
CSky::CSky(CGameScene* pScene) :
	CMeshObj(pScene),
	m_pCamera(NULL)
{
	m_uID = ID_SKY;
}

// デストラクタ
CSky::~CSky(void)
{
}

// 初期化
void CSky::Init()
{
	if (m_mesh.Initialize(PATH_MESHSKY)) {
		SetMesh(&m_mesh);
	}
	if (!m_pCamera) {
		m_pCamera = (CCamera*)Find(ID_CAMERA);
	}
}

// 更新
void CSky::Update()
{
	// 何もしない
}

// 更新後処理
void CSky::PostUpdate()
{
	D3DXVECTOR3 pos;
	if (m_pCamera) {
		pos = m_pCamera->GetPos();
	} else {
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, pos.x, pos.y, pos.z); 
	SetWorld(world);
}

// 描画前処理
void CSky::PreDraw()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	CMeshObj::Draw();
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_LIGHTING, TRUE);
}

// 描画
void CSky::Draw()
{
	// 何もしない
}

// 半透明描画
void CSky::DrawAlpha()
{
	// 何もしない
}

// 解放
void CSky::Fin()
{
	m_mesh.Finalize();
}