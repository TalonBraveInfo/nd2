#ifndef N_LIGHTNODE_H
#define N_LIGHTNODE_H
//------------------------------------------------------------------------------
/**
    @class nLightNode
    @ingroup NebulaSceneLightNodes

    @brief Base class of scene node which provide lighting information.

    (C) 2003 RadonLabs GmbH
*/
#include "scene/nabstractshadernode.h"
#include "gfx2/nlight.h"

//------------------------------------------------------------------------------
class nLightNode : public nAbstractShaderNode
{
public:
    /// constructor
    nLightNode();
    /// destructor
    virtual ~nLightNode();
    /// return true if node provides lighting information
    virtual bool HasLight() const;
    /// set the user defined shader parameters
    virtual bool RenderLight(nSceneServer* sceneServer, nRenderContext* renderContext, const matrix44& lightTransform);
    /// set light type (FIXME: for now always point!)
    void SetType(nLight::Type t);
    /// get light type
    nLight::Type GetType() const;

private:
    nLight light;
};

//------------------------------------------------------------------------------
/**
*/
inline
void
nLightNode::SetType(nLight::Type t)
{
    this->light.SetType(t);
}

//------------------------------------------------------------------------------
/**
*/
inline
nLight::Type
nLightNode::GetType() const
{
    return this->light.GetType();
}

//------------------------------------------------------------------------------
#endif



