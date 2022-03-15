#include "FBX.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

//�~����
static const float PI = 3.141592654f;
//���˓_�̖@���x�N�g��
static float3 N;

//Schlick�ɂ��ߎ�
//f0��f90�̒l��(1 - cosine)��5���lerp����
//f0 : ���������ɓ��˂����Ƃ��̔��˗�
//f90 : �������s�ɓ��˂����Ƃ��̔��˗�
//cosine : 2�x�N�g���̂Ȃ��p�̃R�T�C��(���ϒl)
float SchlickFresnel(float f0, float f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}

float3 BRDF(float3 L, float3 V)
{
	//�@���ƃ��C�g�����̓���
	float NdotL = dot(N, L);
	//�@���ƃJ���������̓���
	float NdotV = dot(N, V);
	//���C�g�����ƃJ���������̒���(�n�[�t�x�N�g��)
	float3 H = normalize(L + V);
	//�@���ƃn�[�t�x�N�g���̓���
	float NdotH = dot(N, H);
	//���C�g�ƃn�[�t�x�N�g���̓���
	float LdotH = dot(L, H);

	//�ǂ��炩��90�x�ȏ�ł���ΐ^������Ԃ�
	if (NdotL < 0.0f || NdotV < 0.0f)
	{
		return float3(0, 0, 0);
	}
	//�g�U���˗�
	float diffuseReflectance = 1.0f / PI;

	//���ˊp��90�x�̏ꍇ�̊g�U���˗�
	float energyBias = 0.5f * roughness;
	float Fd90 = energyBias + 2.0f * LdotH * LdotH * roughness;
	//�����Ă������̊g�U���˗�
	float FL = SchlickFresnel(1.0f, Fd90, NdotL);
	//�o�Ă������̊g�U���˗�
	float FV = SchlickFresnel(1.0f, Fd90, NdotV);
	//�����ďo�Ă����܂ł̊g�U���˗�
	float energyFacter = lerp(1.0f, 1.0f / 1.51f, roughness);
	float Fd = FL * FV * energyFacter;

	//�g�U���ˍ�
	float3 diffuseColor = diffuseReflectance * Fd * baseColor * (1 - metalness);


	return diffuseColor;
}

float4 main(VSOutput input) : SV_TARGET
{
	//�ʂ̏���static�ϐ��ɑ�����A�֐�����Q�Əo����悤�ɂ���
	N = input.normal;
	//�ŏI�I��RGB
	float3 finalRGB = float3(0, 0, 0);
	//���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	//���s����
	for (int i = 0; i < DIRLIGHT_NUM; i++)
	{
		if (dirLights[i].active)
		{
			continue;
		}
		//BRDF�̌��ʂƃ��C�g�F�̍���
		finalRGB += BRDF(dirLights[i].lightv, eyedir) * dirLights[i].lightcolor;
	}

	return float4(finalRGB, 1);
}