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

#include "ambiBIN_genericFXParams.h"

#include <AK/Tools/Common/AkBankReadHelpers.h>

ambiBIN_genericFXParams::ambiBIN_genericFXParams()
{
}

ambiBIN_genericFXParams::~ambiBIN_genericFXParams()
{
}

ambiBIN_genericFXParams::ambiBIN_genericFXParams(const ambiBIN_genericFXParams& in_rParams)
{
    RTPC = in_rParams.RTPC;
    NonRTPC = in_rParams.NonRTPC;
    m_paramChangeHandler.SetAllParamChanges();
}	

AK::IAkPluginParam* ambiBIN_genericFXParams::Clone(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ambiBIN_genericFXParams(*this));
}

AKRESULT ambiBIN_genericFXParams::Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{

    if (in_ulBlockSize == 0)
    {
        // Initialize default parameter values here
        RTPC.s_yaw							= 0.0f;
		RTPC.s_pitch						= 0.0f;
		RTPC.s_roll							= 0.0f;

		RTPC.b_bFlipYaw						= false;
		RTPC.b_bFlipPitch					= false;
		RTPC.b_bFlipRoll					= false;

		RTPC.b_useDefaultHRIRsFLAG			= true;
		RTPC.b_enableMaxRE					= true;			
		RTPC.b_enableDiffuseMatching		= false;
		RTPC.b_enablePhaseWarping			= false;
		RTPC.b_enableRotation				= true;
		RTPC.b_useRollPitchYawFlag			= false;

		RTPC.e_SH_ORDERS				    = ORDER_FIRST;
		RTPC.e_AMBI_BIN_DECODING_METHODS	= METHOD_LS;
		RTPC.e_CH_ORDER						= ACN;
		RTPC.e_NORM_TYPES					= N_N3D;
		
        m_paramChangeHandler.SetAllParamChanges();
        return AK_Success;
    }

    return SetParamsBlock(in_pParamsBlock, in_ulBlockSize);
}

AKRESULT ambiBIN_genericFXParams::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT ambiBIN_genericFXParams::SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    AKRESULT eResult = AK_Success;
    AkUInt8* pParamsBlock = (AkUInt8*)in_pParamsBlock;

    // Set bank data here
    RTPC.s_yaw							= READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
	RTPC.s_pitch						= READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
	RTPC.s_roll							= READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);

	RTPC.b_bFlipYaw						= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_bFlipPitch					= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_bFlipRoll					= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);

	RTPC.b_useDefaultHRIRsFLAG			= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_enableMaxRE					= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_enableDiffuseMatching		= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_enablePhaseWarping			= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_enableRotation				= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.b_useRollPitchYawFlag			= READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	
/*
	RTPC.b_bFlipYaw						= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_bFlipPitch					= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_bFlipRoll				    = READBANKDATA(bool, pParamsBlock, in_ulBlockSize);

	RTPC.b_useDefaultHRIRsFLAG			= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_enableMaxRE					= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_enableDiffuseMatching		= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_enablePhaseWarping			= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_enableRotation				= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	RTPC.b_useRollPitchYawFlag			= READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
	*/
	RTPC.e_SH_ORDERS					= (e_SH_ORDERS)READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.e_AMBI_BIN_DECODING_METHODS	= (e_AMBI_BIN_DECODING_METHODS)READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.e_CH_ORDER						= (e_CH_ORDER)READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	RTPC.e_NORM_TYPES					= (e_NORM_TYPES)READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
	
	/*
	RTPC.e_SH_ORDERS					= e_SH_ORDERS(READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize));
	RTPC.e_AMBI_BIN_DECODING_METHODS	= e_AMBI_BIN_DECODING_METHODS(READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize));
	RTPC.e_CH_ORDER						= e_CH_ORDER(READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize));
	RTPC.e_NORM_TYPES					= e_NORM_TYPES(READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize));
	*/

    CHECKBANKDATASIZE(in_ulBlockSize, eResult);
    m_paramChangeHandler.SetAllParamChanges();

    return eResult;
}

AKRESULT ambiBIN_genericFXParams::SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize)
{
    AKRESULT eResult = AK_Success;

    // Handle parameter change here
    switch (in_paramID)
    {
    case PARAM_S_YAW_ID:
        RTPC.s_yaw = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(PARAM_S_YAW_ID);
        break;
	case PARAM_S_PITCH_ID:
		RTPC.s_pitch = *((AkReal32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_S_PITCH_ID);
		break;
	case PARAM_S_ROLL_ID:
		RTPC.s_roll = *((AkReal32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_S_ROLL_ID);
		break;
	case PARAM_B_BFLIPYAW_ID:
		RTPC.b_bFlipYaw = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_BFLIPYAW_ID);
		break;
	case PARAM_B_BFLIPPITCH_ID:
		RTPC.b_bFlipPitch = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_BFLIPPITCH_ID);
		break;
	case PARAM_B_BFLIPROLL_ID:
		RTPC.b_bFlipRoll = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_BFLIPROLL_ID);
		break;
	case PARAM_B_USEDEFAULTHRIRSFLAG_ID:
		RTPC.b_useDefaultHRIRsFLAG = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_USEDEFAULTHRIRSFLAG_ID);
		break;
	case PARAM_B_ENABLEMAXRE_ID:	// (required true for playback(?))
		RTPC.b_enableMaxRE = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_ENABLEMAXRE_ID);
		break;
	case PARAM_B_ENABLEDIFFUSEMATCHING_ID:
		RTPC.b_enableDiffuseMatching = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_ENABLEDIFFUSEMATCHING_ID);
		break;
	case PARAM_B_ENABLEPHASEWARPING_ID:
		RTPC.b_enablePhaseWarping = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_ENABLEPHASEWARPING_ID);
		break;
	case PARAM_B_ENABLEROTATION_ID:
		RTPC.b_enableRotation = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_ENABLEROTATION_ID);
		break;
	case PARAM_B_USEROLLPITCHYAWFLAG_ID:
		RTPC.b_useRollPitchYawFlag = *((AkInt32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_B_USEROLLPITCHYAWFLAG_ID);
		break;
	case PARAM_E_SH_ORDERS_ID:
		RTPC.e_SH_ORDERS = (e_SH_ORDERS) *reinterpret_cast<const AkInt32*>(in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_E_SH_ORDERS_ID);
		break;
	case PARAM_E_AMBI_BIN_DECODING_METHODS_ID:
		RTPC.e_AMBI_BIN_DECODING_METHODS = (e_AMBI_BIN_DECODING_METHODS) *reinterpret_cast<const AkInt32*>(in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_E_AMBI_BIN_DECODING_METHODS_ID);
		break;
	case PARAM_E_CH_ORDER_ID:
		RTPC.e_CH_ORDER = (e_CH_ORDER) *reinterpret_cast<const AkInt32*>(in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_E_CH_ORDER_ID);
		break;
	case PARAM_E_NORM_TYPES_ID:
		RTPC.e_NORM_TYPES = (e_NORM_TYPES) *reinterpret_cast<const AkInt32*>(in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_E_NORM_TYPES_ID);
		break;

    default:
        eResult = AK_InvalidParameter;
        break;
    }

    return eResult;
}
