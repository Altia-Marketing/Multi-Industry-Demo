
This DeepScreen port has support for pre-compiled shaders loadable via BAM assets.

To pre-compile the shaders:
1.  Ensure the "Package BAM Attribute Files" code generation option is enabled
    in your design and that the "Shader Binary Format" option specifies the
    correct identifier for your target hardware.
2.  Copy the shader_builder directory to a Linux system that has your shader
    compiler.
3.  In the build_shaders.sh script, update the COMPILECMD variable to match the
    invocation of your shader compiler.  The sample version invokes
    "shader_compiler" as follows:
    shader_compiler $INSRC $OUTBIN $([ "$TYPE" == "vertex" ] && echo v || echo f )
    Where:
      - INSRC is the input shader source file
      - OUTBIN is the output compiled shader binary
      - The third argument is a type argument to the compiler, "v" when TYPE is
        "vertex" and "f" otherwise.

    For each shader, the values of INSRC, OUTBIN and TYPE will be generated and
    the compile_shader script function will be called.
    *** The INSRC and OUTBIN assignments must not be modified. ***
    TYPE can be either "vertex" or "fragment".
4.  Run the script.
5.  Copy all of the resulting .sdf files to the out/reflash/<design name>/datafiles 
    directory, creating it if necessary.
6.  Re-run the binary asset manager to rebuild the design's assets with the
    pre-compiled shaders and copy the result to your hardware target per the
    DeepScreen Binary Asset Manager User's Guide.
