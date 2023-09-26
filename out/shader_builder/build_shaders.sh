#!/bin/bash

# Use this generated script to precompile the shaders for your design.
#
# To precompile the shaders:
# 1.  Ensure the "Package BAM Attribute Files" code generation option is enabled
#     in your design.
# 2.  Copy this script and all accompanying shader src files to a Linux system
#     that has your shader compiler.
# 3.  Update the COMPILECMD variable to match the invocation of your shader
#     compiler.  The sample version here invokes shader_compiler as follows:
#     shader_compiler <shader source> <shader bin> <type>
#     Where:
#       <shader source> is the input shader source file
#       <shader bin> is the output compiled shader binary
#       <type> is a type argument to the compiler
#
#     For each shader, the values of INSRC, OUTBIN and TYPE will be generated.
#     *** INSRC and OUTBIN must not be modified. ***
#     TYPE can be either "vertex" or "fragment".
# 4.  Copy all of the .sdf files to the out/reflash/<design name>/datafiles 
#     directory.
# 5.  Re-run the binary asset manager to rebuild the design's assets with the
#     pre-compiled shaders.

compile_shader() {
    COMPILECMD="./shader_compiler $INSRC $OUTBIN -$([ "$TYPE" == "vertex" ] && echo v || echo f )"
    echo $COMPILECMD
    $COMPILECMD
}

INSRC=f7ff00f5.src; OUTBIN=f7ff00f5.sdf; TYPE=vertex
compile_shader
INSRC=568f0073.src; OUTBIN=568f0073.sdf; TYPE=fragment
compile_shader
INSRC=bfaa02a6.src; OUTBIN=bfaa02a6.sdf; TYPE=vertex
compile_shader
INSRC=a99400bb.src; OUTBIN=a99400bb.sdf; TYPE=fragment
compile_shader
INSRC=909011e.src; OUTBIN=909011e.sdf; TYPE=fragment
compile_shader
INSRC=539200b7.src; OUTBIN=539200b7.sdf; TYPE=fragment
compile_shader
INSRC=646300b5.src; OUTBIN=646300b5.sdf; TYPE=fragment
compile_shader
INSRC=204b011e.src; OUTBIN=204b011e.sdf; TYPE=fragment
compile_shader
INSRC=a9720102.src; OUTBIN=a9720102.sdf; TYPE=fragment
compile_shader
INSRC=7d4500bb.src; OUTBIN=7d4500bb.sdf; TYPE=fragment
compile_shader
INSRC=6b5a0150.src; OUTBIN=6b5a0150.sdf; TYPE=fragment
compile_shader
INSRC=fc60018e.src; OUTBIN=fc60018e.sdf; TYPE=fragment
compile_shader
INSRC=453a00a7.src; OUTBIN=453a00a7.sdf; TYPE=fragment
compile_shader
