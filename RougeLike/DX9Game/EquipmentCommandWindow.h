#pragma once

#include <tchar.h>
#include"2DWindow.h"
#include "define.h"

#define FONT_MAX 10

class CTurn;
class CEquipmentInventory;

class CEquipmentCommandWindow:
	public C2DWindow
{
	static _TCHAR				m_CommandName[EQUIPMENT_COMMAND_MAX][FONT_MAX];			//�R�}���h��
	static LPD3DXFONT			m_Font;											//�`��p�t�H���g
	static RECT					m_Pos[EQUIPMENT_COMMAND_MAX];								//�E�B���h�E�\���ʒu

	static bool					m_bDrawFlg;										//�`��t���O

	static VERTEX_2D			m_aVertex[EQUIPMENT_COMMAND_MAX][NUM_VERTEX];				//�|���S�����_���i�[�p

	static CTurn				m_Turn;											//�X�e�[�g�ύX

	static CEquipmentInventory	m_Inbentory;									//�C���x���g���̕`��t���O�ύX�p

	int							m_EnterInterval;		//�A�C�e���I�����ɃG���^�[�L�[���N���b�N���Ă���o�������Ԃ��v������(�A����Trigger���������邱�Ƃ�����邽��)
public:
	CEquipmentCommandWindow(void);						//�R���X�g���N�^
	~CEquipmentCommandWindow(void);						//�f�X�g���N�^

	void Init();								//������
	void Fin();									//�I������

	void UpDate();								//�X�V��
	void Draw();								//�`��

	void DrawFlgChange();						//�`��t���O��ON/OFF����

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	void SetCommand();							//�E�B���h�E�̃R�}���h�𖄂߂�

	//�`��̃t���O�󋵂��擾
	static bool GetDrawFlg()	{return m_bDrawFlg;}
};

