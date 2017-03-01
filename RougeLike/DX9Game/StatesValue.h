#pragma once
//���j�b�g�̃X�e�[�^�X�l���o�͂���
#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesValue :
	public C2DTexture
{
private:
	//�V���O���g��
	static CStatesValue* m_pStatesvalue;
	//�e�X�e�[�^�X�f�[�^�̊i�[
	int m_nStatesValue[STATES_FONT_MAX];
	//�|���S�����
	VERTEX_2D	m_aVertex[STATES_FONT_MAX * 2][NUM_VERTEX];

	CStatesValue(void);			//�R���X�g���N�^
	~CStatesValue(void);		//�f�X�g���N�^
public:
	static void Create();				//���̂̍쐬
	static void Delete();				//���̂̍폜
	static CStatesValue* GetPointer();	//���̂̃|�C���^��n��

	void Draw ();				//�`��

	void SetVertex();			//�|���S�����̐ݒ�
	
	//�`�悷��U���̒l��ݒ肷��
	void SetNumAttack(int nAttack)	{m_nStatesValue[STATES_FONT_ATTACK] = nAttack;}

	//�`�悷��h��̒l��ݒ肷��
	void SetNumDefence(int nDefence)	{m_nStatesValue[STATES_FONT_DEFENCE] = nDefence;}

	//�`�悷��o���l�̒l��ݒ肷��
	void SetNumExp(int nExp)	{m_nStatesValue[STATES_FONT_EXP] = nExp;}
};

