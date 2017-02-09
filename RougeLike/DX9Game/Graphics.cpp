//=======================================================================================
//
//	  DirectX Graphics9 �N���X
//
//=======================================================================================
#include <windows.h>
#include <tchar.h>
#include "define.h"
#include "Graphics.h"

LPDIRECT3DDEVICE9		CGraphics::m_pDevice = NULL;	// Direct3DDevice9 �I�u�W�F�N�g
D3DPRESENT_PARAMETERS	CGraphics::m_D3DPP;				// Direct3DDevice9 �I�u�W�F�N�g


#define CAMERA_POS_X 0
#define CAMERA_POS_Y 50.0f
#define CAMERA_POS_Z -50.0f


//---------------------------------------------------------------------------------------
// �O���t�B�b�N���̏�����
//---------------------------------------------------------------------------------------
bool CGraphics::Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow)
{
	// �f�o�C�X���e�[�u��
	struct TCreateDevice {
		D3DDEVTYPE	type;			// �f�o�C�X�̎��
		DWORD		behavior;		// �f�o�C�X�̓���
	};
	const int c_nMaxDevice = 3;
	const TCreateDevice device[c_nMaxDevice] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// �n�[�h�E�F�A�V�F�[�_���g��
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};
	int		nDev;			// �f�o�C�X��ʃJ�E���^

	// Direct3D�I�u�W�F�N�g�𐶐�
	if ((m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		MessageBox(hWnd, _T("Direct3D�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return false;
	}
	// Direct3D �������p�����[�^�̐ݒ�
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DPP.BackBufferWidth        = (UINT)nWidth;				// �Q�[����ʃT�C�Y
	m_D3DPP.BackBufferHeight       = (UINT)nHeight;
	m_D3DPP.Windowed               = bWindow;					// �E�B���h�E���[�h��?
	m_D3DPP.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	m_D3DPP.EnableAutoDepthStencil = true;						// �y�o�b�t�@�L��
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;				// �y�o�b�t�@�t�H�[�}�b�g
	//m_D3DPP.AutoDepthStencilFormat = D3DFMT_D16;				// �y�o�b�t�@�t�H�[�}�b�g
	if (bWindow) {
		// �E�B���h�E���[�h
		m_D3DPP.BackBufferFormat           = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	} else {
		// �t���X�N���[�����[�h
		m_D3DPP.BackBufferFormat           = D3DFMT_X8R8G8B8;				// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	for (nDev = 0; nDev < c_nMaxDevice; nDev++) {
		if (SUCCEEDED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[nDev].type, hWnd,	// �f�o�C�X���쐬
					  device[nDev].behavior, &m_D3DPP, &m_pDevice))) break;
	}
	if (nDev >= c_nMaxDevice) {
		MessageBox(hWnd, _T("�f�o�C�X�̍쐬�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return false;
	}

	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(m_pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);

	//-------- ��������R�c�֘A
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&m_MatView,
						&D3DXVECTOR3(CAMERA_POS_X,CAMERA_POS_Y,CAMERA_POS_Z),
						&D3DXVECTOR3(  0.0f, 0.0f,     0.0f),		// �����_���W
						&D3DXVECTOR3(  0.0f, 1.0f,     0.0f));		// �A�b�v�x�N�g��
	m_pDevice->SetTransform(D3DTS_VIEW, &m_MatView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		(float)m_nWidth / m_nHeight, NEAR_CLIP, FAR_CLIP);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);

	// �}�e���A���̐ݒ�
	D3DMATERIAL9	mtrl;				// �}�e���A���I�u�W�F�N�g
	ZeroMemory(&mtrl, sizeof(mtrl));	// ��������[���ŃN���A
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	m_pDevice->SetMaterial(&mtrl);

	// ���C�g�̐ݒ�
	D3DXVECTOR3	vecDir;					// �������w�肷��x�N�g��
	D3DLIGHT9	light;					// ���C�g�I�u�W�F�N�g

	ZeroMemory(&light, sizeof(light));	//���C�g�̏�����

	light.Type = D3DLIGHT_DIRECTIONAL;	// ���s����
	
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;

	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);					// ���̌��������߂�
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// ���K�������x�N�g����Ԃ�
	m_pDevice->SetLight(0, &light);
	m_pDevice->LightEnable(0, TRUE);	// ���C�g0��L��

	//�����_�[�X�e�[�g�p�����[�^�̐ݒ�
	m_pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

	//�e�N�X�`���X�e�[�W�p�����[�^�̐ݒ�
	m_pDevice -> SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
	m_pDevice -> SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_DIFFUSE);
	m_pDevice -> SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_TEXTURE);

	m_pDevice -> SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	m_pDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
	m_pDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);

	
	//�T���v���[�X�e�[�g�p�����[�^�\�̐ݒ�
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return true;
}

//---------------------------------------------------------------------------------------
// �O���t�B�b�N���̃N���[���A�b�v
//---------------------------------------------------------------------------------------
void CGraphics::Finalize()
{
	SAFE_RELEASE(m_pFont);		// D3DXFont �I�u�W�F�N�g�����
	SAFE_RELEASE(m_pDevice);	// Direct3DDevice �I�u�W�F�N�g�����
	SAFE_RELEASE(m_pD3D);		// Direct3D �I�u�W�F�N�g�����
}

//---------------------------------------------------------------------------------------
// �`��N���X����
//---------------------------------------------------------------------------------------
CGraphics* CGraphics::Create(HWND hWnd, int nWidth, int nHeight, bool bWindow)
{
	CGraphics* pGraph = new CGraphics();
	if (pGraph) {
		if (!pGraph->Initialize(hWnd, nWidth, nHeight, bWindow)) {
			SAFE_DELETE(pGraph);
		}
	}
	return pGraph;
}

//---------------------------------------------------------------------------------------
// �`��N���X���
//---------------------------------------------------------------------------------------
void CGraphics::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// �����_�����O�J�n
//---------------------------------------------------------------------------------------
bool CGraphics::Begin()
{
	// �r���[�|�[�g���N���A
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
					 D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	return SUCCEEDED(m_pDevice->BeginScene());	// �V�[���J�n
}

//---------------------------------------------------------------------------------------
// �����_�����O�I��
//---------------------------------------------------------------------------------------
void CGraphics::End()
{
	m_pDevice->EndScene();						// �V�[���I��
}

//---------------------------------------------------------------------------------------
// �o�b�N�o�b�t�@����
//---------------------------------------------------------------------------------------
void CGraphics::SwapBuffer()
{
	// �o�b�N�o�b�t�@�ɕ`�悵�����e��\��
	if (FAILED(m_pDevice->Present(NULL, NULL, NULL, NULL))) {
		m_pDevice->Reset(&m_D3DPP);
	}
}

//---------------------------------------------------------------------------------------
// �f�o�b�O������`��
//---------------------------------------------------------------------------------------
void CGraphics::DrawText(int nX, int nY, LPCTSTR psz)
{
	RECT rcStr = {nX, nY, m_nWidth, m_nHeight};
	m_pFont->DrawText(NULL, psz, -1, &rcStr, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}

//=======================================================================================
//	End of File
//=======================================================================================