// �X�J�C�h�[�� �N���X��`

#pragma once

#include "MeshObj.h"
#include "Camera.h"

class CSky : public CMeshObj
{
private:
	//�ϐ�
	static CMesh	m_mesh;
	static CCamera*	m_pCamera;
	static CSky*	m_pSky;		//�V���O���g��

	//�֐�
	CSky(CGameScene* pScene);
	~CSky(void);
public:
	static void Create(CGameScene* pScene);	//��I�u�W�F�N�g�̍쐬
	static void Delete();	//��I�u�W�F�N�g�̍폜

	static CSky* GetPointer();	//�I�u�W�F�N�g�̃|�C���^��n��

	void Init();		// ������
	void Update();		// �X�V
	void Draw();		// �`��
	void DrawAlpha();	// �������`��
	void Fin();			// ���
	void PostUpdate();			// �X�V�㏈��
	void PreDraw();				// �`��O����
};