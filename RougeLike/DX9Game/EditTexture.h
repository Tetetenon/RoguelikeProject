#pragma once
#include <d3dx9.h>


//�쐬:������
class CEditTexture
	{
	public:
		/**
		* �R���X�g���N�^
		* width �e�N�X�`���̉���
		* height �e�N�X�`���̏c��
		* pDevice DirectX�̃f�o�C�X
		*/
		CEditTexture(int width, int height, LPDIRECT3DDEVICE9 pDevice);

		/**
		* �f�X�g���N�^
		*/
		~CEditTexture();

		/**
		* �F�̃Z�b�g
		* x X���W
		* y Y���W
		*/
		void SetColor(int x, int y, DWORD col);

		/**
		* �F�̎擾
		* x X���W
		* y Y���W
		*/
		const DWORD GetColor(int x, int y) const;

		/**
		* �h��Ԃ�
		* ���b�N�����ł��݂܂�
		*/
		void FillColor(DWORD col);

		/**
		* �h��Ԃ�
		*/
		void FillColor( int x, int y, int w, int h, DWORD col);

		/**
		* �F�̃v���p�e�B
		*/
		_declspec(property(get = getter, put = SetColor)) DWORD color[][];

		/**
		* �e�N�X�`���ւ̃L���X�g
		*/
		operator IDirect3DBaseTexture9*() { return this ? m_pD3DTexture : nullptr; }
	private:
		LPDIRECT3DTEXTURE9 m_pD3DTexture;
		int m_nWidth;
		int m_nHeight;
	};