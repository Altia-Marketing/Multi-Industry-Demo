/* Copyright (c) 2021-2023 Altia Acquisition Corporation dba Altia, Inc.
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Altia, Inc. The intellectual and technical concepts
 * contained herein are proprietary to Altia, Inc. and may be covered by
 * U.S. and Foreign Patents, patents in process, and are protected by trade
 * secret or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written permission is
 * obtained from Altia, Inc.
 *
 * ALTIA, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * ALTIA, INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#ifndef altia3d_h
#define altia3d_h

/* These types must match those in altiaBase.h */
typedef int Altia3DId;
#ifdef ALTIABASE_H
typedef ALTIA_CHAR Altia3DChar;
typedef ALTIA_INT Altia3DInt;
#else
typedef AltiaCharType Altia3DChar;
typedef int Altia3DInt;
#endif

typedef float Altia3DFloat;
typedef Altia3DFloat Altia3DVec2[2];
typedef Altia3DFloat Altia3DVec3[3];
typedef Altia3DFloat Altia3DVec4[4];
typedef Altia3DVec3 Altia3DMx3[3];
typedef Altia3DVec4 Altia3DMx4[4];
typedef Altia3DVec3 Altia3DVert;
typedef Altia3DVec3 Altia3DNorm;
typedef Altia3DVec2 Altia3DUV;
typedef unsigned short Altia3DIdx;

typedef signed char Altia3DBool;
#define Altia3DTrue (Altia3DBool)1
#define Altia3DFalse (Altia3DBool)0

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif
    /*-------------------------------------------------------------------------
     * This enum is a bitfield used to indicate what changed in a Programmable
     * Scene Graph (PSG) when calling altia3DPSGChanged().
     *
     * Altia3DPSGChgHintNone - This value indicates there is no change to the PSG.
     *                     Use this value when only material data have changed.
     * Altia3DPSGChgHintNode - This bit indicates there is a change in at least
     *                     one of the node's transformation or pivot data.
     *                     When on, this flag will cause the node's trans-
     *                     formation matrix to be recalculated if the node's
     *                     dirty flag is also true.
     * Altia3DPSGChgHintMesh - This bit indicates that one or more mesh nodes
     *                     have been added to the PSG. When on, this flag will
     *                     cause internal caches to be reconfigured.
     * Altia3DPSGChgHintGeom - This bit indicates that one or more mesh
     *                     geometry data have been added to the PSG. When on,
     *                     this flag will initialize those new geometry data.
     *                     Note that geometry data can be initialized before
     *                     rendering using altia3DGeomInit(). When geometry
     *                     data is no longer needed, altia3DGeomCleanup() may
     *                     be used to free their resources.
     * Altia3DPSGChgHintAll - This value is a shortcut to turn on all bit flags.
     */
    typedef enum
    {
        Altia3DPSGChgHintNone = 0x00,
        Altia3DPSGChgHintNode = 0x01,
        Altia3DPSGChgHintMesh = 0x02,
        Altia3DPSGChgHintGeom = 0x04,
        Altia3DPSGChgHintAll = 0xFF
    } Altia3DPSGChgHint;

    /*-------------------------------------------------------------------------
     * This enum defines how the geometry data will be used for rendering.
     *
     * Altia3DRenderTypeTriangle - Render as triangles (most common)
     * Altia3DRenderTypeLine     - Render as lines
     * Altia3DRenderTypePoint    - Render as points
     */
    typedef enum
    {
        Altia3DRenderTypeTriangle,
        Altia3DRenderTypeLine,
        Altia3DRenderTypePoint
    } Altia3DRenderType;

    /*-------------------------------------------------------------------------
     * This structure contains the geometry data for a mesh node.
     *
     * vertCnt - The number of vertices in the vert array and normal vectors in
     *           the norm array.
     * vert - Array of vertices. This memory may be freed once the geometry has
     *        been initialized.
     * norm - Array of normal vectors. This memory may be freed once the
     *        geometry has been initialized.
     * uvCnt - The number of UVs in the uv array.
     * uv - Array of UV coordinates. This memory may be freed once the geometry
     *      has been initialized.
     * idxCnt - The number of indices in the idx array. This is an optional
     *          method of rendering where vertices with the same coordinates
     *          are reused.
     * idx - Array of indices. This memory may be freed once the geometry has
     *       been initialized.
     * cen - The center point of all the vertices. This point will affect the
     *       order in which the meshes are rendered. The render order will
     *       ensure that transparent meshes are rendered after other meshes
     *       that are farther way from the camera.
     * eglId - A reference to internal resources allocated to the geometry.
     *         This member must be initialized to NULL. It will be set when the
     *         geometry is initialized by altia3DGeomInit(), altia3DSetPSG(),
     *         or altia3DPSGChanged(). It will reset when altia3DGeomCleanup()
     *         is called.
     */
    typedef struct Altia3DGeom
    {
        Altia3DInt vertCnt;
        Altia3DVert *vert;
        Altia3DNorm *norm;
        Altia3DInt uvCnt;
        Altia3DUV *uv;
        Altia3DInt idxCnt;
        Altia3DIdx *idx;
        Altia3DVec3 cen;
        void *eglId; /* Must be init to NULL */
    } Altia3DGeom;

    /*-------------------------------------------------------------------------
     * This enum lists the supported variable types for a material variable. It
     * is used to determine which of the 'val' union member should be used in the
     * Altia3DMatVar structure.
     *
     * Altia3DVarTypeNone   - Invalid or unknown type
     * Altia3DVarTypeInt    - Integer type used with val.i
     * Altia3DVarTypeFloat  - Float type used with val.f
     * Altia3DVarTypeVec2   - Vector of 2 floats type used with val.vec2
     * Altia3DVarTypeVec3   - Vector of 3 floats type used with val.vec3
     * Altia3DVarTypeVec4   - Vector of 4 floats type used with val.vec4
     * Altia3DVarTypeMx3    - Matrix of 3x3 floats type used with val.mx3
     * Altia3DVarTypeMx4    - Matrix of 4x4 floats type used with val.mx4
     * Altia3DVarTypeTex2   - 2D texture type used with val.tex2
     */
    typedef enum
    {
        Altia3DVarTypeNone,
        Altia3DVarTypeInt,
        Altia3DVarTypeFloat,
        Altia3DVarTypeVec2,
        Altia3DVarTypeVec3,
        Altia3DVarTypeVec4,
        Altia3DVarTypeMx3,
        Altia3DVarTypeMx4,
        Altia3DVarTypeTex2
    } Altia3DVarType;

    /*-------------------------------------------------------------------------
     * This structure contains the data of a material variable. It is populated
     * by altia3DGetMatVar() and customized by changing one of the val members.
     *
     * varId - The variable ID associated with the variable name given to the
     *         altia3DGetMatVar() function.
     * type - The variable type (see Altia3DVarType)
     * val - A union of variable values based on the type:
     *       i - Integer value associated with the Altia3DVarTypeInt type
     *       f - Floating point value associated with the Altia3DVarTypeFloat type
     *       vec2 - Vector of 2 floats associated with the Altia3DVarTypeVec2 type
     *       vec3 - Vector of 3 floats associated with the Altia3DVarTypeVec3 type
     *       vec4 - Vector of 4 floats associated with the Altia3DVarTypeVec4 type
     *       mx3 - Matrix of 3x3 floats associated with the Altia3DVarTypeMx3 type
     *       mx4 - Matrix of 4x4 floats associated with the Altia3DVarTypeMx4 type
     *       tex2 - Texture ID associated with the Altia3DVarTypeTex2 type
     *              returned by altia3DGetTexId()
     */
    typedef struct Altia3DMatVar
    {
        Altia3DId varId;
        Altia3DVarType type;
        union
        {
            Altia3DInt i;
            Altia3DFloat f;
            Altia3DVec2 vec2;
            Altia3DVec3 vec3;
            Altia3DVec4 vec4;
            Altia3DMx3 mx3;
            Altia3DMx4 mx4;
            Altia3DId tex2;
        } val;
    } Altia3DMatVar;

    /*-------------------------------------------------------------------------
     * This structure defines a material for a mesh node.
     *
     * matId - The material ID returned by altia3DGetMatId().
     * matOvrdId - The FX material override ID. This member must be initialized
     *             to -1. It is used internally by the FX engine.
     * varCnt - The number of variables in the var array. Variable
     *          customization is optional and this count may be set to 0.
     * var - Array of pointers to variables the client wants to customize. This
     *       is optional and may be set to NULL.
     */
    typedef struct Altia3DMaterial
    {
        Altia3DId matId;
        Altia3DId matOvrdId; /* Init to -1 */
        Altia3DInt varCnt;
        Altia3DMatVar **var;
    } Altia3DMaterial;

    /*-------------------------------------------------------------------------
     * This structure contains the data for a mesh node.
     *
     * renderType - See Altia3DRenderType above
     * mat - Pointer to the material structure allowing multiple mesh nodes to
     *       share the same material.
     * geom - Pointer to the geometry structure allowing multiple mesh nodes to
     *        share the same geometry.
     * reverseWinding - False to use CCW face winding (default).  True to use CW.
     */
    typedef struct Altia3DMesh
    {
        Altia3DRenderType renderType;
        Altia3DMaterial *mat;
        Altia3DGeom *geom;
        Altia3DBool reverseWinding;
    } Altia3DMesh;

    /*-------------------------------------------------------------------------
     * This structure contains the data to transform a node.
     *
     * pos - The positional (or translational) data in the x, y, and z
     *       direction where +y is up.
     * rot - The rotational data in degrees along the x, y, and z axes subject
     *       to the rotation pivot point.
     * scale - The scaling factor in the x, y, and z direction subject to the
     *         scaling pivot point.
     */
    typedef struct Altia3DXform
    {
        Altia3DVec3 pos;
        Altia3DVec3 rot;
        Altia3DVec3 scale;
    } Altia3DXform;

    /*-------------------------------------------------------------------------
     * This structure contains the scaling and rotation pivot data of a node.
     *
     * sPivot - The scaling pivot point relative to the center of the mesh
     *          geometry
     * sOffset - The offset to apply after the scaling operation
     * rPivot - The rotation pivot point relative to the center of the mesh
     *          geometry
     * sOffset - The offset to apply after the rotation operation
     */
    typedef struct Altia3DPivot
    {
        Altia3DVec3 sPivot;
        Altia3DVec3 sOffset;
        Altia3DVec3 rPivot;
        Altia3DVec3 rOffset;
    } Altia3DPivot;

    /*-------------------------------------------------------------------------
     * This enum lists the currently supported node types.
     *
     * None - A node with this type has no additional data and may be used as a
     *        parent node. This type of node is used to transform a group of
     *        other nodes. The root node is typically a node of this type.
     * Mesh - A mesh node will be assigned this type. It must have an associated
     *        mesh pointer in the data union. Mesh nodes may have children but
     *        keep in mind that the children's transformation will be relative
     *        to their parent's coordinate system.
     */
    typedef enum
    {
        Altia3DNodeTypeNone,
        Altia3DNodeTypeMesh
    } Altia3DNodeType;

    /*-------------------------------------------------------------------------
     * This structure defines a node in the Programmable Scene Graph (PSG). A
     * PSG is constructed by connecting nodes to each other via the parent
     * pointer and child pointer array. The root of the CSG will be assigned to
     * a Programmable Scene node defined in the 3D Scene using
     * altia3DSetPSG().
     *
     * parent - Pointer to the parent node or NULL for the root node
     * childCnt - The number of children in the child array
     * child - Array of pointers to child nodes or NULL for leaf nodes
     * type - The type of node (see Altia3DNodeType)
     * data - A union of node type data. For a Altia3DNodeTypeMesh node
     *        type, the mesh pointer must not be NULL.
     * vis - A flag indicating whether the node and its children will be
     *       rendered.
     * tagCnt - The number of tags in the tag array
     * tag - Array of tag IDs or NULL for no tags
     * xform - Transformation data (see Altia3DXform). Note that transformation
     *         data are relative to the parent node.
     * pivot - Pointer to the pivot data. Most nodes will not need custom
     *         pivots and therefore may share a default pivot structure.
     *         Nodes with custom pivots will point to their own pivot
     *         structure (see Altia3DPivot).
     * lcs - The transformation matrix used by the render engine and should be
     *       initialized to the identity matrix.
     * dirty - A flag indicating that xform or pivot data has changed. This
     *         should be initialized to Altia3DTrue and set to Altia3DTrue
     *         anytime transformation and pivot data has changed. When calling
     *         altia3DPSGChanged() the hint parameter should also set the
     *         Altia3DPSGChgHintNode bit. This flag will be cleared by the
     *         rendering engine.
     */
    typedef struct Altia3DNode
    {
        struct Altia3DNode *parent;
        Altia3DInt childCnt;
        struct Altia3DNode **child;

        /* Node type */
        Altia3DNodeType type;
        union
        {
            Altia3DMesh *mesh;
        } data;

        /* Node data */
        Altia3DBool vis;
        Altia3DInt tagCnt;
        Altia3DId *tag;

        /* Orientation */
        Altia3DXform xform;
        Altia3DPivot *pivot;
        Altia3DMx4 lcs;
        Altia3DBool dirty; /* Init to Altia3DTrue */
    } Altia3DNode;

    /*-------------------------------------------------------------------------
     * Function prototype for the callback function registered using the
     * below altiaSetShaderOverride() API.
     *
     * mode - Altia 2D shader type that needs to be overridden with a custom
     *        shader.  The shader mode types ALTIA_SHADER_MODE_xxx are listed
     *        below
     * objId - Altia Object ID (from the Altia dsn) that is being rendered
     *        using the shader of 'mode' type
     *
     * Returns a non-zero shader program ID if overriding with a custom shader.
     *   If overriding with custom shader then application should call the
     *   glUseProgram() to load the custom shader and set the necessary shader
     *   variables.  Altia render pipeline functions will set the default shader
     *   variables in the custom shader if they exist.  Please inspect the
     *   shader programs placed in egl_shaders.c to identify all the variable
     *   names.
     * Return zero if not overriding with a custom shader.
     */
    typedef unsigned int (*AltiaShaderOverrideFuncT)(
                const unsigned int mode,
                const int objId);

    /*-------------------------------------------------------------------------
     * Defines for various shader types used by Altia to render 2D objects.
     */

    /* Shader program to render vector objects like rectangles, polygons and ellipses */
    #define ALTIA_SHADER_MODE_VECTOR                        1U
    /* Shader program to render lines */
    #define ALTIA_SHADER_MODE_WIDE_LINE                     2U
    /* Shader program to render 8-bit alpha format textures */
    #define ALTIA_SHADER_MODE_TEXTURE_A8                    3U
    /* Shader program to render pattern fills on vector objects */
    #define ALTIA_SHADER_MODE_PATTERN_FILL                  4U
    /* Shader program to render RGBA textures without premultiplied alpha */
    #define ALTIA_SHADER_MODE_TEXTURE_RGBA                  5U
    /* Shader program to render RGBA textures with premultiplied alpha */
    #define ALTIA_SHADER_MODE_TEXTURE_RGBA_PREMULT          6U
    /* Shader program to render pattern fills using ETC1 compressed texture */
    #define ALTIA_SHADER_MODE_PATTERN_FILL_R8               7U
    /* Shader program to render ETC1-RGBA textures */
    #define ALTIA_SHADER_MODE_TEXTURE_RGB_A8                8U
    /* Shader program to render ETC1-A8 textures */
    #define ALTIA_SHADER_MODE_TEXTURE_R8                    9U
    /* Shader program to render Alphamask composite */
    #define ALTIA_SHADER_MODE_AMASK                         10U
    /* Shader program to composite layer textures with Chroma-key enabled */
    #define ALTIA_SHADER_MODE_CHROMAKEY                     11U
    /* Shader program to composite layer textures with Chroma-key disabled */
    #define ALTIA_SHADER_MODE_COMPOSITE                     12U
    /* Shader program to render 3DScene with FXAA */
    #define ALTIA_SHADER_MODE_FXAA_RGBA_PREMULT             13U
    /* Shader program to render 8-bit alpha format textures with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_A8                  14U
    /* Shader program to render RGBA format textures with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_RGBA                15U
    /* Shader program to render premultiplied alpha RGBA format textures with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_RGBA_PREMULT        16U
    /* Shader program to render ETC1-RGBA format textures with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_RGB_A8              17U
    /* Shader program to render ETC1-A8 format textures with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_R8                  18U
    /* Shader program to render Alphamask composite with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_AMASK               19U
    /* Shader program to render FXAA 3DScene with a nonaffine transform */
    #define ALTIA_SHADER_MODE_NONAFFINE_FXAA_RGBA_PREMULT   20U
    /* Blur versions of shaders above - used in Blur Containers */
    #define ALTIA_SHADER_MODE_TEXTURE_A8_BLUR               21U
    #define ALTIA_SHADER_MODE_PATTERN_FILL_BLUR             22U
    #define ALTIA_SHADER_MODE_TEXTURE_RGBA_BLUR             23U
    #define ALTIA_SHADER_MODE_TEXTURE_RGBA_PREMULT_BLUR     24U
    #define ALTIA_SHADER_MODE_PATTERN_FILL_R8_BLUR          25U
    #define ALTIA_SHADER_MODE_TEXTURE_RGB_A8_BLUR           26U
    #define ALTIA_SHADER_MODE_TEXTURE_R8_BLUR               27U
    #define ALTIA_SHADER_MODE_AMASK_BLUR                    28U
    #define ALTIA_SHADER_MODE_CHROMAKEY_BLUR                29U
    #define ALTIA_SHADER_MODE_COMPOSITE_BLUR                30U
    #define ALTIA_SHADER_MODE_FXAA_RGBA_BLUR                31U
    #define ALTIA_SHADER_MODE_NONAFFINE_A8_BLUR             32U
    #define ALTIA_SHADER_MODE_NONAFFINE_RGBA_BLUR           33U
    #define ALTIA_SHADER_MODE_NONAFFINE_RGBA_PREMULT_BLUR   34U
    #define ALTIA_SHADER_MODE_NONAFFINE_RGB_A8_BLUR         35U
    #define ALTIA_SHADER_MODE_NONAFFINE_R8_BLUR             36U
    #define ALTIA_SHADER_MODE_NONAFFINE_AMASK_BLUR          37U
    #define ALTIA_SHADER_MODE_NONAFFINE_FXAA_RGBA_BLUR      38U
    /* End of blur shaders */

    /*-------------------------------------------------------------------------
     * List of Altia 2D shader variables:
     *
     * Vertex shader variable used to set the graphic's x-y render position
     *  attribute highp vec2 a_position
     *
     * Vertex shader var to set the active texture coordinates data when
     * rendering with an affine transform
     *  attribute highp vec2 a_texCoord
     *
     * Vertex shader var to set the active texture coordinates data when
     *  rendering with a nonaffine transform
     *  attribute highp vec3 a_texCoordNonaffine
     *
     * Vertex shader vars used for rendering Line(s)
     *  attribute highp vec2 a_prev
     *  attribute highp vec2 a_next
     *  attribute highp float a_side
     *
     * Vertex shader uniform used to set the perspective matrix
     *  uniform highp mat4 u_pmvMatrix
     *
     * Vertex shader uniform used to set the render transform matrix
     *  uniform highp mat4 u_objXForm
     *
     * Fragment shader uniform to set the color for the graphic being rendered.
     * While drawing vector objects or A8 format textures, it is used to set the
     * foreground color.  In case of others, Altia uses it to set the opacity.
     *  uniform vec4 u_color
     *
     * Fragment shader uniform to set the active texture
     *  uniform sampler2D u_texture
     *
     * Fragment shader uniform to set a secondary active texture.  This is used
     * while rendering either an Alphamask object or while rendering ETC1 compressed
     * texture that contains alpha.
     *  uniform sampler2D u_texture2
     *
     * Fragment shader uniform to set the pattern color while performing pattern
     * fills on vector objects.
     *  uniform vec3 u_patternColor
     *
     * Fragment shader uniform to set the Chroma key color while compositing
     * LM layers.
     *  uniform vec3 u_chromaColor
     *
     * Fragment shader uniform to set threshold for color difference from the Chroma
     * key color while compositing LM layers.
     *  uniform vec3 u_minColorDiff
     *
     * Fragment shader uniforms to set the math operators used in combining color and
     * mask layers of an Alphamask object.
     *  uniform float u_alphaOperator
     *  uniform float u_alphaOffset
     *
     * Fragment shader uniforms used to perform FXAA blits of 3D scenes.
     *  uniform float u_threshold
     *  uniform float u_span
     *  uniform float u_texWidth
     *  uniform float u_texHeight
     */

    /*-------------------------------------------------------------------------
     * Function prototype for the callback function registered using the
     * below altiaGetShaderVarLoc() API.
     *
     * progId - Identifier for the custom shader program being queried for
     *        shader variable location
     * varType - Indicates if the shader variable being queried is an Uniform or
     *        an Attribute.  (0: Uniform type, 1: Attribute type)
     * varName - Shader variable name whose location is being queried
     *
     * Returns a value >= 0 if the shader variable location exists
     *  Return -1 if the shader variable location doesn't exist
     */
    typedef int (*AltiaShaderVarLocFuncT)(
                const unsigned int progId,
                const unsigned char varType,
                const char * varName);

    /*-------------------------------------------------------------------------
     * This function is callable from the user application.
     * It registers two callback functions that shall be implemented by the user
     * application:
     * override_func - A callback to override the default Altia 2D shaders with
     *    a custom shader.  Custom shaders could be used to colorize, tint or
     *    alter the rendered graphics.
     * varloc_func - A callback function for Altia to query the shader variable
     *    locations in the custom shader overriding the default Altia 2D shader.
     */
    extern void altiaSetShaderOverride(
                    AltiaShaderOverrideFuncT override_func,
                    AltiaShaderVarLocFuncT varloc_func);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* altia3d_h */
