#include "StatesWindow.h"
#include "TextureManager.h"
#include "Input.h"

#include "MenuWindow.h"

//�X�e�[�^�X�E�B���h�E�`��t���O
bool CStatesWindow::m_bDrawFlg = false;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CStatesWindow::CStatesWindow(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_WINDOW;

	//�`��t���O�̏�����
	m_bDrawFlg = false;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f,				  50.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(240.0f,				  50.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f,SCREEN_HEIGHT - 250.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(240.0f,SCREEN_HEIGHT - 250.0f,0.0f);
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CStatesWindow::~CStatesWindow(void)
{
	//�`��t���O�̏�����
	m_bDrawFlg = false;
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CStatesWindow::Update(void)
{
	//�`�揈�����s���Ă��Ȃ��ꍇ�������Ȃ�
	if (!m_bDrawFlg)
		return;
	//����(L)���͖߂�(K)�ŃE�B���h�E�����
	if(CInput::GetKeyTrigger(DIK_L)|| CInput::GetJoyTrigger(0,2) || !CMenuWindow::GetDrawFlg())
	{
		m_bDrawFlg = false;
	}
}

//---------------------------------------------------------------------------------------
//�E�B���h�E�T�C�Y�̍X�V
//---------------------------------------------------------------------------------------
void CStatesWindow::WindowSizeUpdate(void)
{
	if(m_bDrawFlg)
	{
		//�ʒu���̐ݒ�
		m_aVertex[0].pos = D3DXVECTOR3( 10.0f,				  50.0f,0.0f);
		m_aVertex[1].pos = D3DXVECTOR3(240.0f,				  50.0f,0.0f);
		m_aVertex[2].pos = D3DXVECTOR3( 10.0f,SCREEN_HEIGHT - 250.0f,0.0f);
		m_aVertex[3].pos = D3DXVECTOR3(240.0f,SCREEN_HEIGHT - 250.0f,0.0f);
	}
	else
	{
		//�ʒu���̐ݒ�
		m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 50.0f,0.0f);
		m_aVertex[1].pos = D3DXVECTOR3(240.0f, 50.0f,0.0f);
		m_aVertex[2].pos = D3DXVECTOR3( 10.0f,195.0f,0.0f);
		m_aVertex[3].pos = D3DXVECTOR3(240.0f,195.0f,0.0f);
	}
}