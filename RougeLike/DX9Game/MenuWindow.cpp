#include "MenuWindow.h"
#include "TextureManager.h"
#include "Input.h"

bool CMenuWindow::m_bDrawFlg = false;							//���j���[�E�C���h�E�`��t���O

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMenuWindow::CMenuWindow(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_MENU_WINDOW;

	//�`��t���O�̏�����
	m_bDrawFlg = false;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 50.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 50.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,360.0f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,360.0f ,0.0f);
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMenuWindow::~CMenuWindow(void)
{
	//�`��t���O�̏�����
	m_bDrawFlg = false;
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CMenuWindow::Update(void)
{
	//K���͂Ŗ߂�
	if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0,2))
	{
		//�`��t���O��|��
		m_bDrawFlg = false;
	}
}