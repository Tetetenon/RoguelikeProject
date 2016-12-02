#pragma once
//�e�N�X�`���`��N���X

#include "Structure.h"

class C2DTexture
{
protected:
	VERTEX_2D		m_aVertex[NUM_VERTEX];		//�|���S�����i�[
	int				m_nTextureID;				//�g�p����e�N�X�`��ID
public:
	C2DTexture(void);							//�R���X�g���N�^
	~C2DTexture(void);							//�f�X�g���N�^

	virtual void Draw();						//�`��

	void SetVertex();							//�|���S������ݒ肷��

	void SetPos(float fPosX,float fPosY,float fHalfSizeX,float fHalfSizeY);	//�|���S���̈ʒu����ݒ肷��
	void SetPosLeftUpOrigin(float fPosX, float fPosY, float fWidth, float fHeight);
	void SetTextureID(int nID)	{m_nTextureID = nID;}				//�e�N�X�`��ID��ݒ肷��
	void SetAlpha(int nAlpha);												//�|���S���̃A���t�@�l��ݒ肷��
};

