//------------------------------------------------------------------------------
//  nguitextureview_main.cc
//  (C) 2004 RadonLabs GmbH
//------------------------------------------------------------------------------
#include "gui/nguitextureview.h"
#include "gui/nguiserver.h"
#include "gfx2/ntexture2.h"

nNebulaClass(nGuiTextureView, "nguiwidget");

//------------------------------------------------------------------------------
/**
*/
nGuiTextureView::nGuiTextureView()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
nGuiTextureView::~nGuiTextureView()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
nGuiTextureView::Render()
{
    if (this->IsShown())
    {
        // render background (necessary so that alpha channel
        // of texture will be visible)
        nGuiServer::Instance()->DrawBrush(this->GetScreenSpaceRect(), this->defaultBrush);

        // render actual texture
        if (this->refTexture.isvalid())
        {
            const vector4& curGlobalColor = nGuiServer::Instance()->GetGlobalColor();
            static const rectangle uvs(vector2(0.0f, 0.0f), vector2(1.0f, 1.0f));
            static const vector4 white(1.0f, 1.0f, 1.0f, 1.0f);
            nGuiServer::Instance()->SetGlobalColor(white);
            nGuiServer::Instance()->DrawTexture(this->GetScreenSpaceRect(), uvs, white, this->refTexture.get());
            nGuiServer::Instance()->SetGlobalColor(curGlobalColor);
        }
        return true;
    }
    return false;
}

