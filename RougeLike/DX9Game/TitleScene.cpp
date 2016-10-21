#include "TitleScene.h"
#include "define.h"
#include "Input.h"
#include "GameState.h"

bool CTitleScene::m_bCreate = false;		//���������t���O

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CTitleScene::CTitleScene(void):
m_pGraphics(NULL)
{
	//�^�C�g���e�N�X�`���`��N���X�̎��̂��쐬
	m_pTitle = new CTitle();
	//�t�F�[�h�C���N���X�쐬
	m_pFade = new CFade();
	//�v���X�X�y�[�X�쐬
	m_pPress = new CPressSpace();
	//��������
	m_bCreate = true;
	//�t�F�[�h�����t���O��������
	m_bFadeSuccess = false;
	//�t�F�[�h�C���J�n�t���O��������
	m_bFadeStart = false;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CTitleScene::~CTitleScene(void)
{
	//�����ɐ������Ă�����폜�J��
	if(m_bCreate)
	{
		//�^�C�g���|�C���^�̒��g�폜�A���
		delete m_pTitle;
		//�t�F�[�h�C���N���X�폜
		delete m_pFade;
		//�v���X�X�y�[�X�N���X�̒��g�̊J��
		delete m_pPress;

		//������ԋU
		m_bCreate = false;
	}
}

//---------------------------------------------------------------------------------------
//�^�C�g���V�[���̍쐬
//---------------------------------------------------------------------------------------
CTitleScene* CTitleScene::Create(CGraphics* pGraph)
{
	//���g�̍쐬
	CTitleScene* pTitleScene = new CTitleScene();

	//�쐬�ł������m�F
	if (pTitleScene) 
	{
		//���������s��
		if (!pTitleScene->Initialize(pGraph))
		{
			//�����������Ɏ��s������폜����
			SAFE_DELETE(pTitleScene);
		}
	}

	//����������^�C�g���V�[���̃|�C���^�A���s����NULL
	return pTitleScene;
}

//---------------------------------------------------------------------------------------
//�^�C�g���V�[���̊J��
//---------------------------------------------------------------------------------------
void CTitleScene::Release()
{
	//�I������
	Finalize();

	if(m_bCreate)
	{
		//���g�̍폜
		delete this;
	}
}

//---------------------------------------------------------------------------------------
//�����_�����O����
//---------------------------------------------------------------------------------------
void CTitleScene::Render()
{
	//�`��J�n
	if (m_pGraphics->Begin()) 
	{
		Draw();					// �`�揈��

		m_pGraphics->End();		// �`��I��
	}
	m_pGraphics->SwapBuffer();		// �o�b�N�o�b�t�@����
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CTitleScene::Update()
{
	//���͍X�V
	CInput::Update();

	//�v���X�X�y�[�X�X�V
	m_pPress ->Update();

	//SPACE��������Ă�����A�Q�[���V�[���ֈڍs
	if(CInput::GetKeyTrigger(DIK_SPACE))
	{
		//�t�F�[�h�C���J�n�t���O�𗧂Ă�
		m_bFadeStart = true;
	}
	//�t�F�[�h�C���J�n�t���O�������Ă����ꍇ�A�t�F�[�h�̏������s��
	if(m_bFadeStart)
	{
		//�t�F�[�h�C���̍X�V
		m_pFade ->Update();
	}
	//�t�F�[�h�C��������������A�X�e�[�g��ύX����
	if(m_pFade ->GetFadeAlpha() >= 255)
	{
		CGameState::Update();
	}
}

//---------------------------------------------------------------------------------------
//����������
//---------------------------------------------------------------------------------------
bool CTitleScene::Initialize(CGraphics* pGraph)
{
	//�O���t�B�b�N�f�o�C�X�̃|�C���^�擾
	m_pGraphics = pGraph;

	//����
	return true;
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CTitleScene::Finalize()
{
	
}
//---------------------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------------------
void CTitleScene::Draw()
{
	// �����������`��
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();

	//�������`��ݒ�
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�^�C�g���e�N�X�`���̕`��
	m_pTitle->Draw();

	//�v���X�X�y�[�X�`��
	m_pPress ->Draw();
	
	//�t�F�[�h���J�n����Ă���΁A�`����s��
	if(m_bFadeStart)
	{
		m_pFade ->Draw();
	}
	
	//�`��ݒ�����ɖ߂�(�s����)
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}