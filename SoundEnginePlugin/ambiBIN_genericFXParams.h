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

#ifndef ambiBIN_genericFXParams_H
#define ambiBIN_genericFXParams_H

#include <AK/SoundEngine/Common/IAkPlugin.h>
#include <AK/Plugin/PluginServices/AkFXParameterChangeHandler.h>

// Add parameters IDs here, those IDs should map to the AudioEnginePropertyID attributes in the xml property definition.

// SLIDERS
static const AkPluginParamID PARAM_S_YAW_ID							= 0;
static const AkPluginParamID PARAM_S_PITCH_ID						= 1;
static const AkPluginParamID PARAM_S_ROLL_ID						= 2;

// BUTTONS
static const AkPluginParamID PARAM_B_BFLIPYAW_ID					= 3;
static const AkPluginParamID PARAM_B_BFLIPPITCH_ID					= 4;
static const AkPluginParamID PARAM_B_BFLIPROLL_ID					= 5;

static const AkPluginParamID PARAM_B_USEDEFAULTHRIRSFLAG_ID			= 6;
static const AkPluginParamID PARAM_B_ENABLEMAXRE_ID					= 7;
static const AkPluginParamID PARAM_B_ENABLEDIFFUSEMATCHING_ID		= 8;
static const AkPluginParamID PARAM_B_ENABLEPHASEWARPING_ID			= 9;
static const AkPluginParamID PARAM_B_ENABLEROTATION_ID				= 10;
static const AkPluginParamID PARAM_B_USEROLLPITCHYAWFLAG_ID			= 11;

// ENUMS (combo box values)
static const AkPluginParamID PARAM_E_SH_ORDERS_ID					= 12;
static const AkPluginParamID PARAM_E_AMBI_BIN_DECODING_METHODS_ID	= 13;
static const AkPluginParamID PARAM_E_CH_ORDER_ID					= 14;
static const AkPluginParamID PARAM_E_NORM_TYPES_ID					= 15;

static const AkUInt32 NUM_PARAMS = 16;

enum e_SH_ORDERS {
	ORDER_FIRST		= 1,		// First-order (4 channels)
	ORDER_SECOND	= 2,		// Second-order (9 channels)
	ORDER_THIRD		= 3,		// Third-order (16 channels)
	ORDER_FOURTH	= 4,		// Fourth-order (25 channels)
	ORDER_FIFTH		= 5,		// Fifth-order (36 channels)
	ORDER_SIXTH		= 6,		// Sixth-order (49 channels)
	ORDER_SEVENTH	= 7			// Seventh-order (64 channels)
};

enum e_AMBI_BIN_DECODING_METHODS {
	METHOD_LS		= 1,		// Least-squares (LS) decoder
	METHOD_LSDIFFEQ = 2,		// Least-squares (LS) decoder with diffuse-field spectral equalisation
	METHOD_SPR		= 3,		// Spatial resampling decoder (on the same lines as the virtual loudspeaker approach)
	METHOD_TA		= 4,		// Time-alignment (TA)
	METHOD_MAGLS	= 5			// Magnitude least-squares decoder (MagLS)
};

enum e_CH_ORDER {
	ACN				= 1,		// Ambisonic Channel Numbering (ACN)
	FUMA			= 2			// (Legacy) Furse-Malham/B-format (WXYZ)
};

enum e_NORM_TYPES {
	N_N3D			= 1,		// orthonormalised (N3D)
	N_SN3D			= 2,		// Schmidt semi-normalisation (SN3D)
	N_FUMA			= 3			// (Legacy) Furse-Malham scaling
};

struct ambiBIN_genericRTPCParams
{
	// Sliders
    AkReal32 s_yaw;
	AkReal32 s_pitch;
	AkReal32 s_roll;

	// Buttons (tick boxes) (these booleans are actually handled as ints both in Wwise (required for RTPC) and in SAF)
	bool b_bFlipYaw;
	bool b_bFlipPitch;
	bool b_bFlipRoll;

	bool b_useDefaultHRIRsFLAG;	// pars->sofa_filepath must be valid to set this to 0 
	bool b_enableMaxRE;
	bool b_enableDiffuseMatching;
	bool b_enablePhaseWarping;
	bool b_enableRotation;
	bool b_useRollPitchYawFlag;

	// Combo boxes
	e_SH_ORDERS						e_SH_ORDERS;
	e_AMBI_BIN_DECODING_METHODS		e_AMBI_BIN_DECODING_METHODS;
	e_CH_ORDER						e_CH_ORDER;
	e_NORM_TYPES					e_NORM_TYPES;
};

struct ambiBIN_genericNonRTPCParams
{
};

struct ambiBIN_genericFXParams
    : public AK::IAkPluginParam
{
    ambiBIN_genericFXParams();
    ambiBIN_genericFXParams(const ambiBIN_genericFXParams& in_rParams);

    ~ambiBIN_genericFXParams();

    /// Create a duplicate of the parameter node instance in its current state.
    IAkPluginParam* Clone(AK::IAkPluginMemAlloc* in_pAllocator);

    /// Initialize the plug-in parameter node interface.
    /// Initializes the internal parameter structure to default values or with the provided parameter block if it is valid.
    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize);

    /// Called by the sound engine when a parameter node is terminated.
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator);

    /// Set all plug-in parameters at once using a parameter block.
    AKRESULT SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize);

    /// Update a single parameter at a time and perform the necessary actions on the parameter changes.
    AKRESULT SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize);

    AK::AkFXParameterChangeHandler<NUM_PARAMS> m_paramChangeHandler;

    ambiBIN_genericRTPCParams RTPC;
    ambiBIN_genericNonRTPCParams NonRTPC;

} AK_ALIGN_DMA;

#endif // ambiBIN_genericFXParams_H
