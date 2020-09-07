--[[----------------------------------------------------------------------------
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
------------------------------------------------------------------------------]]

if not _AK_PREMAKE then
    error('You must use the custom Premake5 scripts by adding the following parameter: --scripts="Scripts\\Premake"', 1)
end

local Plugin = {}
Plugin.name = "ambiBIN_generic"
Plugin.factoryheader = "../SoundEnginePlugin/ambiBIN_genericFXFactory.h"
Plugin.sdk = {}
Plugin.sdk.static = {}
Plugin.sdk.shared = {}
Plugin.authoring = {}

-- SDK STATIC PLUGIN SECTION
Plugin.sdk.static.includedirs = -- https://github.com/premake/premake-core/wiki/includedirs
{
	"../Spatial_Audio_Framework/dependencies/Win64/include",
	"../Spatial_Audio_Framework/examples/include",
	"../Spatial_Audio_Framework/framework/include",
	"C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/mkl/include",
}
Plugin.sdk.static.files = -- https://github.com/premake/premake-core/wiki/files
{
	"../ambiBIN_genericConfig.h",
	
    "ambiBIN_genericFX.cpp",
    "ambiBIN_genericFX.h",
    "ambiBIN_genericFXParams.cpp",
    "ambiBIN_genericFXParams.h",
	
--	"ambiBIN_genericFXShared.cpp",
 --   "ambiBIN_genericFXFactory.h",
	
	"../Spatial_Audio_Framework/examples/include/_common.h",
	"../Spatial_Audio_Framework/examples/include/ambi_bin.h",
	"../Spatial_Audio_Framework/examples/src/ambi_bin/ambi_bin.c",
	"../Spatial_Audio_Framework/examples/src/ambi_bin/ambi_bin_internal.h",
	"../Spatial_Audio_Framework/examples/src/ambi_bin/ambi_bin_internal.c",
	
	"../Spatial_Audio_Framework/framework/include/saf.h",
	"../Spatial_Audio_Framework/framework/modules/saf_cdf4sap/saf_cdf4sap.c",
	"../Spatial_Audio_Framework/framework/modules/saf_cdf4sap/saf_cdf4sap.h",
    "../Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa_internal.c",
    "../Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa_internal.h",
    "../Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa.c",
	"../Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa.h",
    "../Spatial_Audio_Framework/framework/modules/saf_hrir/saf_default_hrirs.c",
    "../Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir_internal.c",
    "../Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir_internal.h",
    "../Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir.c",
	"../Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir.h",
    "../Spatial_Audio_Framework/framework/modules/saf_reverb/saf_reverb_internal.c",
    "../Spatial_Audio_Framework/framework/modules/saf_reverb/saf_reverb_internal.h",
    "../Spatial_Audio_Framework/framework/modules/saf_reverb/saf_reverb.c",
	"../Spatial_Audio_Framework/framework/modules/saf_reverb/saf_reverb.h",
    "../Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh_internal.c",
    "../Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh_internal.h",
    "../Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh.c",
	"../Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh.h",
    "../Spatial_Audio_Framework/framework/modules/saf_sofa_reader/saf_sofa_reader.c",
	"../Spatial_Audio_Framework/framework/modules/saf_sofa_reader/saf_sofa_reader.h",
	"../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utilities.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_bessel.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_complex.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_decor.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_error.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_fft.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_filters.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_geometry.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_latticeCoeffs.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_loudspeaker_presets.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_matrixConv.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_misc.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_pitch.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_qmf.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_sensorarray_presets.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_sort.c",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_veclib.c",
	"../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_bessel.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_complex.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_decor.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_error.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_fft.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_filters.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_geometry.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_latticeCoeffs.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_loudspeaker_presets.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_matrixConv.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_misc.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_pitch.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_qmf.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_sensorarray_presets.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_sort.h",
    "../Spatial_Audio_Framework/framework/modules/saf_utilities/saf_utility_veclib.h",
    "../Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap_internal.c",
    "../Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap_internal.h",
    "../Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap.c",
	"../Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap.h",
	"../Spatial_Audio_Framework/framework/resources/afSTFT/afSTFT_protoFilter.h",
    "../Spatial_Audio_Framework/framework/resources/afSTFT/afSTFTlib.c",
	"../Spatial_Audio_Framework/framework/resources/afSTFT/afSTFTlib.h",
    "../Spatial_Audio_Framework/framework/resources/afSTFT/afSTFT_internal.h",
    "../Spatial_Audio_Framework/framework/resources/afSTFT/afSTFT_internal.c",
    "../Spatial_Audio_Framework/framework/resources/convhull_3d/convhull_3d.c",
	"../Spatial_Audio_Framework/framework/resources/convhull_3d/convhull_3d.h",
    "../Spatial_Audio_Framework/framework/resources/kissFFT/_kiss_fft_guts.h",
    "../Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fft.c",
    "../Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fftr.c",
	"../Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fft.h",
    "../Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fftr.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/common.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/fastest_coeffs.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/high_qual_coeffs.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/mid_qual_coeffs.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/samplerate_interface.c",
	"../Spatial_Audio_Framework/framework/resources/libsamplerate/samplerate_interface.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/samplerate.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/samplerate.c",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/src_config.h",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/src_linear.c",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/src_sinc.c",
    "../Spatial_Audio_Framework/framework/resources/libsamplerate/src_zoh.c",
    "../Spatial_Audio_Framework/framework/resources/md_malloc/md_malloc.c",
	"../Spatial_Audio_Framework/framework/resources/md_malloc/md_malloc.h",
}
Plugin.sdk.static.excludes = -- https://github.com/premake/premake-core/wiki/removefiles
{
}
Plugin.sdk.static.links = -- https://github.com/premake/premake-core/wiki/links
{
	"saf_mkl_custom.lib",
	"netcdf.lib",
	"libszip.lib",
	"libzlib.lib",
	"libhdf5.lib",
	"libhdf5_hl.lib",
}
Plugin.sdk.static.libsuffix = "FX"
Plugin.sdk.static.libdirs = -- https://github.com/premake/premake-core/wiki/libdirs
{
	"../Spatial_Audio_Framework/dependencies/Win64/lib",
}
Plugin.sdk.static.defines = -- https://github.com/premake/premake-core/wiki/defines
{
	"SAF_USE_INTEL_MKL=1",
	"SAF_ENABLE_SOFA_READER_MODULE=1",
}

-- SDK SHARED PLUGIN SECTION
Plugin.sdk.shared.includedirs =
{
}
Plugin.sdk.shared.files =
{	-- ambiBIN_genericFXShared.cpp causes: ambiBIN_genericFX.lib(derror.obj) : error LNK2019: unresolved external symbol
    "ambiBIN_genericFXShared.cpp",
    "ambiBIN_genericFXFactory.h",
}	--authoring works without both of these if theyre in Plugin.sdk.static.files
Plugin.sdk.shared.excludes =
{
}
Plugin.sdk.shared.links =
{
}
Plugin.sdk.shared.libdirs =
{--experimenting
	"../Spatial_Audio_Framework/dependencies/Win64/lib",
}
Plugin.sdk.shared.defines =
{
	"SAF_USE_INTEL_MKL=1",
	"SAF_ENABLE_SOFA_READER_MODULE=1",
}

-- AUTHORING PLUGIN SECTION
Plugin.authoring.includedirs =
{
	"../Spatial_Audio_Framework/examples/include",
}
Plugin.authoring.files =
{

	"../ambiBIN_genericConfig.h",
	
	"../Spatial_Audio_Framework/examples/include/_common.h",
	"../Spatial_Audio_Framework/examples/include/ambi_bin.h",

    "ambiBIN_genericPlugin.cpp",
    "ambiBIN_genericPlugin.h",
    "ambiBIN_generic.cpp",
    "ambiBIN_generic.h",
    "ambiBIN_generic.def",
    "ambiBIN_generic.xml",
	
	"resource.h",
}
Plugin.authoring.excludes =
{
}
Plugin.authoring.links =
{
}
Plugin.authoring.libdirs =
{
}
Plugin.authoring.defines =
{
	"SAF_USE_INTEL_MKL=1",
	"SAF_ENABLE_SOFA_READER_MODULE=1",
}
Plugin.authoring.custom = function()
    buildoptions { "/bigobj" }
end

return Plugin
