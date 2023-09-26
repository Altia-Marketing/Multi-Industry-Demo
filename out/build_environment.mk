################################################################################
#
# @copyright Copyright (c) 2016-2023 Altia Inc.
#
# Permission to use, copy, and modify this software for any purpose is
# hereby granted, provided that this copyright notice appears in all
# copies and that the entity using, copying, or modifying this software
# has purchased an Altia Deep Screen license. Permission to sell or
# distribute this source code is denied.
#
# Altia makes no representations about the suitability of this software for any
# purpose.  It is provided "as is" without express or implied warranty.
#
# ALTIA INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
# IN NO EVENT SHALL ALTIA INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
# DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
################################################################################

ALTIA_C_ENVIRONMENT = -c -Wall -fsigned-char -fno-strict-aliasing -Wno-missing-braces -Wno-unused-variable -Wno-char-subscripts -Wno-unused-function -Wno-unused-variable -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-result -std=gnu99 -finput-charset=ISO-8859-1 -O3 -fPIC -language=c -mcpu=cortex-a72.cortex-a53 -march=armv8-a+crc+crypto -DTOOLCHAIN_GCC -DFT2_BUILD_LIBRARY -DFT2_NO_FILEIO -DU_ATTRIBUTE_DEPRECATED= -DU_COMMON_IMPLEMENTATION -DU_STATIC_IMPLEMENTATION -DU_SHOW_CPLUSPLUS_API=0 -DDEEPSCREEN -DALTIAGL -DAltiafp -DAltiaFunctionPrototyping -DNeedNestedPrototypes -DNeedFunctionPrototypes -DAltiaUseAnimationIds=1 -DALTIA_ALIGN= -DALTIA_CONST=const -DALTIAUNICODEAPI -DUNICODE -D_UNICODE -DALTIA_MERGE_EXTENTS_PAD=2 -DLINUX -DNDEBUG -DVARIANT_le -DVARIANT_aarch64 -DVARIANT_g -DBUILDENV_qss -DANTIALIAS -DANTIALIAS_3D -DAPIENTRY=GL_APIENTRY -DNO_DAO_DLL -DNO_PRELOAD -DALTIA_DRV_LOADIMAGE -DMPLOT_POINT_CACHE_SIZE=128 -DALTIA_FONT_PRELOAD -DALTIA_FONT_USE_CACHE -DSIZEOF_LONG=8 -DALTIA_COMPOSITOR_DRM=1 -DALTIA_COMPOSITOR_WAYLAND=0 -DALTIA_COMPOSITOR_OPENGLES2=0 -DALTIA_COMPOSITOR_FB=0 -DALTIA_ENABLE_SAVE_IMAGE_BUILTIN=1 -DDRIVER_FB_ANDROID_RENDERER=0 -DDRIVER_WARPING_ENABLED=0 -DDRIVER_HW_WARPING=0 -DALTIA_SAVE_FONT_BITMAP -DWCHAR_IS_WCHAR_T -DUCHAR_SIZE=4 -DUCHAR_TYPE=wchar_t -DALTIA_DRV_LOADASSET -DALTIA_DRV_LOADASSET_CHUNKS
ALTIA_CXX_ENVIRONMENT = -c -Wall -fsigned-char -fno-strict-aliasing -Wno-missing-braces -Wno-unused-variable -Wno-char-subscripts -Wno-unused-function -Wno-unused-variable -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-result -O3 -fPIC -mcpu=cortex-a72.cortex-a53 -march=armv8-a+crc+crypto -DFT2_BUILD_LIBRARY -DFT2_NO_FILEIO -DU_ATTRIBUTE_DEPRECATED= -DU_COMMON_IMPLEMENTATION -DU_STATIC_IMPLEMENTATION -DU_SHOW_CPLUSPLUS_API=0 -DHB_NO_MT -DHAVE_FREETYPE -DHAVE_CONFIG_H -DHAVE_OT -DHAVE_UCDN -DHB_INTERNAL= -DHB_NO_INSTANCE_ASSERTION -DTOOLCHAIN_GCC -DFT2_BUILD_LIBRARY -DFT2_NO_FILEIO -DU_ATTRIBUTE_DEPRECATED= -DU_COMMON_IMPLEMENTATION -DU_STATIC_IMPLEMENTATION -DU_SHOW_CPLUSPLUS_API=0 -DDEEPSCREEN -DALTIAGL -DAltiafp -DAltiaFunctionPrototyping -DNeedNestedPrototypes -DNeedFunctionPrototypes -DAltiaUseAnimationIds=1 -DALTIA_ALIGN= -DALTIA_CONST=const -DALTIAUNICODEAPI -DUNICODE -D_UNICODE -DALTIA_MERGE_EXTENTS_PAD=2
