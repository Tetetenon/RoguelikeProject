// �X�J�C�h�[�� �N���X����

#include "Sky.h"
#include "Camera.h"

// �萔
#define PATH_MESHSKY	_T("../data/model/sky.x")

// �ÓI�����o
CMesh CSky::m_mesh;

// �R���X�g���N�^
CSky::CSky(CGameScene* pScene) :
	CMeshObj(pScene),
	m_pCamera(NULL)
{
	m_uID = ID_SKY;
}

// �f�X�g���N�^
CSky::~CSky(void)
{
}

// ������
void CSky::Init()
{
	if (m_mesh.Initialize(PATH_MESHSKY)) {
		SetMesh(&m_mesh);
	}
	if (!m_pCamera) {
		m_pCamera = (CCamera*)Find(ID_CAMERA);
	}
}

// �X�V
void CSky::Update()
{
	// �������Ȃ�
}

// �X�V�㏈��
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

// �`��O����
void CSky::PreDraw()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	CMeshObj::Draw();
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_LIGHTING, TRUE);
}

// �`��
void CSky::Draw()
{
	// �������Ȃ�
}

// �������`��
void CSky::DrawAlpha()
{
	// �������Ȃ�
}

// ���
void CSky::Fin()
{
	m_mesh.Finalize();
}