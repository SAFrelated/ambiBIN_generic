/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2020 Audiokinetic Inc.
*******************************************************************************/

#include "ambiBIN_genericFX.h"
#include "../ambiBIN_genericConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreateambiBIN_genericFX(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ambiBIN_genericFX());
}

AK::IAkPluginParam* CreateambiBIN_genericFXParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ambiBIN_genericFXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(ambiBIN_genericFX, AkPluginTypeEffect, ambiBIN_genericConfig::CompanyID, ambiBIN_genericConfig::PluginID)

ambiBIN_genericFX::ambiBIN_genericFX()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

ambiBIN_genericFX::~ambiBIN_genericFX()
{
}

AKRESULT ambiBIN_genericFX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (ambiBIN_genericFXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

	int fs = (int)(unsigned long)in_rFormat.uSampleRate;

	ambi_bin_create(&hAmbi);
	ambi_bin_init(hAmbi, fs);
	ambi_bin_initCodec(hAmbi);

    return AK_Success;
}

AKRESULT ambiBIN_genericFX::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);

	ambi_bin_destroy(&hAmbi);
    return AK_Success;
}

AKRESULT ambiBIN_genericFX::Reset()
{
    return AK_Success;
}

AKRESULT ambiBIN_genericFX::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeEffect;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

#pragma optimize("", off)//needed for breakpoints, mark out for release
void ambiBIN_genericFX::Execute(AkAudioBuffer* io_pBuffer)
{
	ambi_bin_setYaw(hAmbi,						(float)m_pParams->RTPC.s_yaw);
	ambi_bin_setPitch(hAmbi,					(float)m_pParams->RTPC.s_pitch);
	ambi_bin_setRoll(hAmbi,						(float)m_pParams->RTPC.s_roll);
		
	ambi_bin_setFlipYaw(hAmbi,					(int)m_pParams->RTPC.b_bFlipYaw);
	ambi_bin_setFlipPitch(hAmbi,				(int)m_pParams->RTPC.b_bFlipPitch);
	ambi_bin_setFlipRoll(hAmbi,					(int)m_pParams->RTPC.b_bFlipRoll);

	ambi_bin_setUseDefaultHRIRsflag(hAmbi,		(int)m_pParams->RTPC.b_useDefaultHRIRsFLAG);
	ambi_bin_setEnableMaxRE(hAmbi,				(int)m_pParams->RTPC.b_enableMaxRE);
	ambi_bin_setEnableDiffuseMatching(hAmbi,	(int)m_pParams->RTPC.b_enableDiffuseMatching);
	ambi_bin_setEnablePhaseWarping(hAmbi,		(int)m_pParams->RTPC.b_enablePhaseWarping);
	ambi_bin_setEnableRotation(hAmbi,			(int)m_pParams->RTPC.b_enableRotation);
	ambi_bin_setRPYflag(hAmbi,					(int)m_pParams->RTPC.b_useRollPitchYawFlag);

	ambi_bin_setInputOrderPreset(hAmbi,			(_SH_ORDERS)m_pParams->RTPC.e_SH_ORDERS);

	if(ambi_bin_getDecodingMethod(hAmbi)!= (_AMBI_BIN_DECODING_METHODS)m_pParams->RTPC.e_AMBI_BIN_DECODING_METHODS)
	    ambi_bin_setDecodingMethod(hAmbi,		(_AMBI_BIN_DECODING_METHODS)m_pParams->RTPC.e_AMBI_BIN_DECODING_METHODS);	

	ambi_bin_setChOrder(hAmbi,					(_CH_ORDER)m_pParams->RTPC.e_CH_ORDER);								 
	ambi_bin_setNormType(hAmbi,					(_NORM_TYPES)m_pParams->RTPC.e_NORM_TYPES);
	
	ambi_bin_initCodec(hAmbi);		// re-init codec internal parameters 

	float* intData = (float*)io_pBuffer->GetInterleavedData(); //  nChannels x nSamples
	int nSamples = (int)io_pBuffer->MaxFrames();
	int nChannels = (int)io_pBuffer->NumChannels();
	int framesize = ambi_bin_getFrameSize();

	float** f_buffer = (float**)malloc2d(nChannels, framesize, sizeof(float));

	if (nSamples % framesize == 0) {
		for (int fr = 0; fr < nSamples / framesize; fr++) {
		
			for (AkUInt32 i = 0; i < nChannels; i++) {
				float * pfChan = (float*)io_pBuffer->GetChannel(i);
				memcpy(f_buffer[i], &pfChan[fr*framesize], framesize * sizeof(float));
			}

				ambi_bin_process(hAmbi, f_buffer, f_buffer, nChannels, nChannels, framesize);

			for (AkUInt32 i = 0; i < nChannels; i++) {
				float * pfChan = (float*)io_pBuffer->GetChannel(i);
				memcpy(&pfChan[fr*framesize], f_buffer[i], framesize * sizeof(float));
			}
		}
	}
	else
		io_pBuffer->ClearData();

	free(f_buffer);
}
#pragma optimize("", on)//needed for breakpoints, mark out for release

AKRESULT ambiBIN_genericFX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
