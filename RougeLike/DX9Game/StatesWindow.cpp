#include "StatesWindow.h"
#include "TextureManager.h"
#include "Input.h"

#include "MenuWindow.h"

//�V���O���g���̃|�C���^
CStatesWindow* CStatesWindow::m_pStatesWindow = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CStatesWindow::CStatesWindow(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_WINDOW;

	//���͌o�ߎ��ԏ�����
	m_IntervalTime = 0;

	//�`��t���O�̏�����
	m_bDrawFlg = false;

	//�ʒu���̐ݒ�
	WindowSizeUpdate();
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CStatesWindow::~CStatesWindow(void)
{
	//�`��t���O�̏�����
	m_bDrawFlg = false;

	//���͌o�ߎ��ԏ�����
	m_IntervalTime = 0;
}
//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CStatesWindow::Create()
{
	//���g��������΍쐬
	if (!m_pStatesWindow)
	{
		m_pStatesWindow = new CStatesWindow;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CStatesWindow::Delete()
{
	//���g������΍폜
	if (m_pStatesWindow)
	{
		delete m_pStatesWindow;
		m_pStatesWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CStatesWindow* CStatesWindow::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ă�
	Create();
	return m_pStatesWindow;
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CStatesWindow::Update(void)
{
	//�`�揈�����s���Ă��Ȃ��ꍇ�������Ȃ�
	if (!m_bDrawFlg)
		return;

	m_IntervalTime++;

	//���͌o�ߎ��Ԃ����ȉ��̏ꍇ�������Ȃ�
	if (m_IntervalTime < ButtonIntervalTime)
		return;

	//����(L)���͖߂�(K)�ŃE�B���h�E�����
	if(CInput::GetKeyTrigger(DIK_L)|| CInput::GetJoyTrigger(0,2) || !m_pMenuWindow->GetDrawFlg())
	{
		m_bDrawFlg = false;
		m_IntervalTime = 0;
	}
}

//---------------------------------------------------------------------------------------
//�E�B���h�E�T�C�Y�̍X�V
//---------------------------------------------------------------------------------------
void CStatesWindow::WindowSizeUpdate(void)
{
	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 10.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(600.0f, 10.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f, 50.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(600.0f, 50.0f,0.0f);
}

//---------------------------------------------------------------------------------------
//�����o�ϐ��̃|�C���^��ݒ肷��
//---------------------------------------------------------------------------------------
void CStatesWindow::SetPointer()
{
	//�|�C���^�̎擾
	m_pMenuWindow = CMenuWindow::GetPointer();
}
