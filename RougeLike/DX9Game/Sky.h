// �X�J�C�h�[�� �N���X��`

#pragma once

#include "MeshObj.h"
#include "Camera.h"

class CSky : public CMeshObj
{
private:
	static CMesh	m_mesh;
	CCamera*		m_pCamera;

public:
	CSky(CGameScene* pScene);
	virtual ~CSky(void);

	virtual void Init();		// ������
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��
	virtual void DrawAlpha();	// �������`��
	virtual void Fin();			// ���
	void PostUpdate();			// �X�V�㏈��
	void PreDraw();				// �`��O����
};