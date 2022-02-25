#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <map>
#include <vector>

class Audio final
{// �I�[�f�B�I
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	template <class T1, class T2> using map = std::map<T1, T2>;

public: // �T�u�N���X

	class XAudio2VoiceCallback : public IXAudio2VoiceCallback
	{// �I�[�f�B�I�R�[���o�b�N
	public:
		// �{�C�X�����p�X�̊J�n��
		//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
		void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
		// �{�C�X�����p�X�̏I����
		STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
		// �o�b�t�@�X�g���[���̍Đ����I��������
		STDMETHOD_(void, OnStreamEnd) (THIS) {};
		// �o�b�t�@�̎g�p�J�n��
		STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
		// �o�b�t�@�̖����ɒB������
		STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
		{
			// �o�b�t�@���������
			delete[] pBufferContext;
		};
		// �Đ������[�v�ʒu�ɒB������
		STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
		// �{�C�X�̎��s�G���[��
		STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
	};

	// �`�����N�w�b�_
	struct Chunk
	{
		char id[4]; // �`�����N����ID
		int	size; // �`�����N�T�C�Y
	};

	// RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		Chunk chunk;   // "RIFF"
		char type[4]; // "WAVE"
	};

	// FMT�`�����N
	struct FormatChunk
	{
		Chunk chunk; // "fmt "
		WAVEFORMAT fmt; // �g�`�t�H�[�}�b�g
	};

	//�����f�[�^
	struct SoundData
	{
		WAVEFORMATEX wfex; // �g�`�t�H�[�}�b�g
		char* pBuffer; // �o�b�t�@�̐擪�A�h���X
		unsigned int dataSize; // �o�b�t�@�̃T�C�Y
	};

public: // �����o�֐�
	// ������
	bool Initialize();
	// �T�E���h�t�@�C���̓ǂݍ���
	void LoadWave(int soundNumber, const char* filename);
	// �T�E���h�t�@�C���̍Đ�
	void PlayWave(int soundNumber);
	void LoopPlayWave(int soundNumber);
	void LoopStopWave();

private:
	Audio();
	~Audio();

public:
	Audio(const Audio& audio) = delete;
	Audio& operator=(const Audio& audio) = delete;

	static Audio* GetInstance();

private: // �����o�ϐ�
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	XAudio2VoiceCallback voiceCallback;

	map<int, SoundData> soundDatas;
	std::vector<IXAudio2SourceVoice*> pSourceVoices;
	XAUDIO2_BUFFER buf{};
};