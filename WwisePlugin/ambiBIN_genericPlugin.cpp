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

#include "ambiBIN_genericPlugin.h"
#include "../SoundEnginePlugin/ambiBIN_genericFXFactory.h"

#include <AK/Tools/Common/AkAssert.h>

AK_STATIC_LINK_PLUGIN(ambiBIN_genericFX)	// linking for SoundEngine .dll

static LPCWSTR s_yaw						= L"s_yaw";
static LPCWSTR s_pitch						= L"s_pitch";
static LPCWSTR s_roll						= L"s_roll";

static LPCWSTR b_bFlipYaw					= L"b_bFlipYaw";
static LPCWSTR b_bFlipPitch					= L"b_bFlipPitch";
static LPCWSTR b_bFlipRoll					= L"b_bFlipRoll";

static LPCWSTR b_useDefaultHRIRsFLAG		= L"b_useDefaultHRIRsFLAG";
static LPCWSTR b_enableMaxRE				= L"b_enableMaxRE";
static LPCWSTR b_enableDiffuseMatching		= L"b_enableDiffuseMatching";
static LPCWSTR b_enablePhaseWarping			= L"b_enablePhaseWarping";
static LPCWSTR b_enableRotation				= L"b_enableRotation";
static LPCWSTR b_useRollPitchYawFlag		= L"b_useRollPitchYawFlag";

static LPCWSTR e_SH_ORDERS					= L"e_SH_ORDERS";
static LPCWSTR e_AMBI_BIN_DECODING_METHODS	= L"e_AMBI_BIN_DECODING_METHODS";
static LPCWSTR e_CH_ORDER					= L"e_CH_ORDER";
static LPCWSTR e_NORM_TYPES					= L"e_NORM_TYPES";

ambiBIN_genericPlugin::ambiBIN_genericPlugin()
    : m_pPSet(nullptr)
{
}

ambiBIN_genericPlugin::~ambiBIN_genericPlugin()
{
}

void ambiBIN_genericPlugin::Destroy()
{
    delete this;
}

void ambiBIN_genericPlugin::SetPluginPropertySet(AK::Wwise::IPluginPropertySet* in_pPSet)
{
    m_pPSet = in_pPSet;
}

bool ambiBIN_genericPlugin::GetBankParameters(const GUID& in_guidPlatform, AK::Wwise::IWriteData* in_pDataWriter) const
{
	// Write equivalent of read for bank data. Called when the soundbanks are generated in the authoring. 
	// Be consistent with the set function ambiBIN_genericFXParams::SetParamsBlock(). The parameters need to be in the same order.

	CComVariant varProp;

	// floats
	m_pPSet->GetValue(in_guidPlatform, s_yaw, varProp);
	in_pDataWriter->WriteReal32(varProp.fltVal);

	m_pPSet->GetValue(in_guidPlatform, s_pitch, varProp);
	in_pDataWriter->WriteReal32(varProp.fltVal);

	m_pPSet->GetValue(in_guidPlatform, s_roll, varProp);
	in_pDataWriter->WriteReal32(varProp.fltVal);

	// booleans
	m_pPSet->GetValue(in_guidPlatform, b_bFlipYaw, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);
	//in_pDataWriter->WriteBool(varProp.boolVal);
	//in_pDataWriter->WriteInt32(varProp.boolVal);
	//in_pDataWriter->WriteInt32(varProp.iVal);

	m_pPSet->GetValue(in_guidPlatform, b_bFlipPitch, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_bFlipRoll, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_useDefaultHRIRsFLAG, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_enableMaxRE, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_enableDiffuseMatching, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_enablePhaseWarping, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_enableRotation, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, b_useRollPitchYawFlag, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);;

	// enumerations
	m_pPSet->GetValue(in_guidPlatform, e_SH_ORDERS, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, e_AMBI_BIN_DECODING_METHODS, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, e_CH_ORDER, varProp);	// something wrong with this specific one, the value from combo box doesn't update
	in_pDataWriter->WriteInt32(varProp.lVal);

	m_pPSet->GetValue(in_guidPlatform, e_NORM_TYPES, varProp);
	in_pDataWriter->WriteInt32(varProp.lVal);

	return true;
}
