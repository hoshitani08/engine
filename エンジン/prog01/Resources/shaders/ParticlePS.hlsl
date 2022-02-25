#include "Particle.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃe�N�X�`��
SamplerState smp : register(s0);      //0�ԃT���v���[

float4 main(GSOutput input) : SV_TARGET
{
	return tex.Sample(smp, input.uv) * input.color;
	//return float4(1, 1, 1, 1);
}