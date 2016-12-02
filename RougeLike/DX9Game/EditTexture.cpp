#include <cassert>
#include "EditTexture.h"

/**
* �e�N�X�`���̍쐬
*/
static const bool CreateTexture(int width, int height, LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9* ppTexture)
	{
	HRESULT hr = pDevice->CreateTexture(
		width,				// ����
		height,				// ����
		1,					// �~�b�v�}�b�v
		0,					// �g�p�ړI
		D3DFMT_A8R8G8B8,	// �t�H�[�}�b�g�J���[
		D3DPOOL_MANAGED,	// �������Ǘ����@
		ppTexture,			// ������
		NULL);				// ���g�p����
	return FAILED(hr) ? false : true;
	}

/**
* �h�b�g�̏�������
*/
static void WriteBit(DWORD* pBits, int line, int x, int y, DWORD col)
	{
	pBits[y*line + x] = col;
	}

/**
* �h�b�g�̎擾
*/
static DWORD LoadBit(DWORD* pBits, int line, int x, int y)
	{
	return pBits[y*line + x];
	}

	
/**
* �R���X�g���N�^
*/
CEditTexture::CEditTexture(int width, int height, LPDIRECT3DDEVICE9 pDevice)
	: m_pD3DTexture(nullptr)
	, m_nWidth(width)
	, m_nHeight(height)
	{
	CreateTexture(width, height, pDevice, &m_pD3DTexture);
	}

/**
* �f�X�g���N�^
*/
CEditTexture::~CEditTexture()
	{
	if (m_pD3DTexture)
		{
		m_pD3DTexture->Release();
		m_pD3DTexture = nullptr;
		}
	}

/**
* �F�̃Z�b�g
*/
void CEditTexture::SetColor(int x, int y, DWORD col)
	{
	// �e�N�X�`�����Ȃ����
	if(!m_pD3DTexture) return;
	// �͈̓`�F�b�N
	assert(x >= 0 && x < m_nWidth);
	assert(y >= 0 && y < m_nHeight);
	// �e�N�X�`���̃��b�N
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	if (FAILED(hr)) return;
	// �������o�C�g�P�ʂ���f�[�^�P�ʂ�
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	// ��������
	WriteBit(pBits,line,x,y,col);
	// �A�����b�N
	m_pD3DTexture->UnlockRect(0);
	}

/**
* �F�̎擾
*/
const DWORD CEditTexture::GetColor(int x, int y) const
	{
	// �e�N�X�`�����Ȃ����
	if(!m_pD3DTexture) return NULL;
	// �͈̓`�F�b�N
	assert(x >= 0 && x < m_nWidth);
	assert(y >= 0 && y < m_nHeight);
	// �e�N�X�`���̃��b�N
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	if (FAILED(hr)) return NULL;
	// �������o�C�g�P�ʂ���f�[�^�P�ʂ�
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	// ��������
	DWORD col = LoadBit(pBits,line,x,y);
	// �A�����b�N
	m_pD3DTexture->UnlockRect(0);
	return col;
	}

void CEditTexture::FillColor(DWORD col)
	{
	// �e�N�X�`�����Ȃ����
	if(!m_pD3DTexture) return;
	// �e�N�X�`���̃��b�N
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	// �������o�C�g�P�ʂ���f�[�^�P�ʂ�
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	for (int x = 0; x < m_nWidth; ++x)
		{
		for (int y = 0; y < m_nHeight; ++y)
			{
				WriteBit(pBits,line,x,y,col);
			}
		}
	// �A�����b�N
	m_pD3DTexture->UnlockRect(0);
	}

void CEditTexture::FillColor( int _x, int _y, int w, int h, DWORD col)
{
	// �e�N�X�`�����Ȃ����
	if(!m_pD3DTexture) return;
	// �͈̓`�F�b�N
	const int right = _x + w;
	const int bottom = _y + h;
	assert(_x >= 0 && _x < m_nWidth);
	assert(_y >= 0 && _y < m_nHeight);
	assert(right - 1 < m_nWidth);
	assert(bottom - 1 < m_nHeight);
	// �e�N�X�`���̃��b�N
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	// �������o�C�g�P�ʂ���f�[�^�P�ʂ�
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	for (int x = _x; x < right; ++x)
	{
		for (int y = _y; y < bottom; ++y)
		{
			WriteBit(pBits,line,x,y,col);
		}
	}
	// �A�����b�N
	m_pD3DTexture->UnlockRect(0);
}

