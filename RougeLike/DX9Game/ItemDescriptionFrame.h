#pragma once
#include "C2DTexture.h"
#include "Item.h"

#define DESCRIPTION_FONT_MAX	(100)

class CItemDescriptionFrame :
	public C2DTexture
{
private:
	//�V���O���g��
	static CItemDescriptionFrame* m_pItemdescriptionFrame;
	LPD3DXFONT		m_Font;						//�������`��p�t�H���g
	RECT			m_FontPosition;				//�����p�t�H���g�ʒu
	_TCHAR			m_Description[ITEM_MAX][DESCRIPTION_FONT_MAX];	//������

	CItemDescriptionFrame(void);		//�R���X�g���N�^
	~CItemDescriptionFrame(void);		//�f�X�g���N�^
public:
	static void Create();
	static void Delete();
	static CItemDescriptionFrame* GetPointer();

	void Draw(int ItemNumber);			//�`��

	void SetVertex(void);				//�|���S�����̐ݒ�
	void SetFontPos(void);				//�t�H���g�`��ʒu�ݒ�

	void FontDataSet(void);				//�t�H���g����͂���
};