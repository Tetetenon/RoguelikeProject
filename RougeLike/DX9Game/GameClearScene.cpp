#include "GameClearScene.h"
#include "Input.h"
#include "GameState.h"
#include "define.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CGameClearScene::CGameClearScene(void):
m_pGraphics(NULL)
{
	//�Q�[���N���A�N���X�̎��Ԑ���
	m_GameClear = new CGameClear();
	//�v���X�X�y�[�X�쐬
	m_pPress = new CPressSpace();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CGameClearScene::~CGameClearScene(void)
{
	//���U���g�N���X�̎��ԍ폜
	delete m_GameClear;
	//�v���X�X�y�[�X�N���X�̒��g�̊J��
	delete m_pPress;
}

//---------------------------------------------------------------------------------------
//���U���g�V�[���̐���
//---------------------------------------------------------------------------------------
CGameClearScene* CGameClearScene::Create(CGraphics* pGraph)
{
	//���U���g�N���X�̎��Ԑ���
	CGameClearScene* pResualtScene = new CGameClearScene();

	//�����������������ǂ���
	if (pResualtScene) 
	{
		if (!pResualtScene->Initialize(pGraph))
		{
			//���s�����������Ĉ��S�ɏ���
			SAFE_DELETE(pResualtScene);
		}
	}
	//���U���g�N���X�������ł������Ԃ�
	return pResualtScene;
}

//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CGameClearScene::Release()
{
	//���g�̏I������
	Finalize();
	//���g�̍폜
	delete this;
}

//---------------------------------------------------------------------------------------
//�����_�����O
//---------------------------------------------------------------------------------------
void CGameClearScene::Render()
{
	if (m_pGraphics->Begin()) 
	{	// �`��J�n

		Draw();					// �`�揈��

		m_pGraphics->End();		// �`��I��
	}
	m_pGraphics->SwapBuffer();		// �o�b�N�o�b�t�@����
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CGameClearScene::UpDate()
{
	//���͏��̍X�V
	CInput::Update();

	//�v���X�X�y�[�X�X�V
	m_pPress ->Update();

	//����SPACE��������Ă���΃^�C�g���V�[���ֈڍs
	if(CInput::GetKeyTrigger(DIK_SPACE))
	{
		CGameState::StateUpdate(STATE_TITLE);
	}
}
//---------------------------------------------------------------------------------------
//����������
//---------------------------------------------------------------------------------------
bool CGameClearScene::Initialize(CGraphics* pGraph)
{
	//�f�o�C�X�̃|�C���^��ݒ肷��
	m_pGraphics = pGraph;

	//�����������Ƃ�Ԃ�
	return true;
}


//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CGameClearScene::Finalize()
{

}

//---------------------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------------------
void CGameClearScene::Draw()
{
	// �����������`��
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���U���g�e�N�X�`���`��
	m_GameClear->Draw();

	//�v���X�X�y�[�X�`��
	m_pPress ->Draw();
	
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}