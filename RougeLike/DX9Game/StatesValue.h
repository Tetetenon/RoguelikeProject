#pragma once
//���j�b�g�̃X�e�[�^�X�l���o�͂���
#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesValue :
	public C2DTexture
{
private:
	//�e�X�e�[�^�X�f�[�^�̊i�[
	static int m_nStatesValue[STATES_FONT_MAX];
	//�|���S�����
	static VERTEX_2D	m_aVertex[STATES_FONT_MAX * 2][NUM_VERTEX];
public:
	CStatesValue(void);			//�R���X�g���N�^
	~CStatesValue(void);		//�f�X�g���N�^

	void Draw ();				//�`��

	void SetVertex();			//�|���S�����̐ݒ�
	
	//�`�悷��U���̒l��ݒ肷��
	static void SetNumAttack(int nAttack)	{m_nStatesValue[STATES_FONT_ATTACK] = nAttack;}

	//�`�悷��h��̒l��ݒ肷��
	static void SetNumDefence(int nDefence)	{m_nStatesValue[STATES_FONT_DEFENCE] = nDefence;}

	//�`�悷��o���l�̒l��ݒ肷��
	static void SetNumExp(int nExp)	{m_nStatesValue[STATES_FONT_EXP] = nExp;}

};

