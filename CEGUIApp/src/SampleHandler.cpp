/***********************************************************************
created:    4/6/2012
author:     Lukas E Meindl
*************************************************************************/
/***************************************************************************
*   Copyright (C) 2004 - 2012 Paul D Turner & The CEGUI Development Team
*
*   Permission is hereby granted, free of charge, to any person obtaining
*   a copy of this software and associated documentation files (the
*   "Software"), to deal in the Software without restriction, including
*   without limitation the rights to use, copy, modify, merge, publish,
*   distribute, sublicense, and/or sell copies of the Software, and to
*   permit persons to whom the Software is furnished to do so, subject to
*   the following conditions:
*
*   The above copyright notice and this permission notice shall be
*   included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
*   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
*   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
*   OTHER DEALINGS IN THE SOFTWARE.
***************************************************************************/
#include "SampleHandler.h"

#include "Sample.h"
#include "CEGUI/DynamicModule.h"
#include "CEGUI/System.h"
#include "CEGUI/Renderer.h"
#include "CEGUI/TextureTarget.h"
#include "CEGUI/BitmapImage.h"
#include "CEGUI/GUIContext.h"
#include "CEGUI/Texture.h"
#include "CEGUI/ImageManager.h"
#include "CEGUI/Window.h"

using namespace CEGUI;


SampleHandler::SampleHandler(Sample* sample)
    : d_sample(sample)
{
}

SampleHandler::~SampleHandler()
{
}

CEGUI::String SampleHandler::getNameText()
{
    return d_sample->getName();
}

CEGUI::String SampleHandler::getSummaryText()
{
    return "Summary:\n" + d_sample->getSummary();
}

CEGUI::String SampleHandler::getCreditsText()
{
    return "Credits:\n" + d_sample->getCredits();
}

CEGUI::String SampleHandler::getDescriptionText()
{
    return "Description:\n" + d_sample->getDescription();
}

CEGUI::String SampleHandler::getUsedFilesText()
{
    return "Used files:\n" + d_usedFilesString;
}

void SampleHandler::setSampleWindow(CEGUI::Window* sampleWindow)
{
    d_sampleWindow = sampleWindow;
}

CEGUI::Window* SampleHandler::getSampleWindow()
{
    return d_sampleWindow;
}

void SampleHandler::initialise(int width, int height)
{
    initialiseSamplePreviewRenderTarget(static_cast<float>(width), static_cast<float>(height));
    initialiseSample();
}

void SampleHandler::deinitialise()
{
     if(d_sample)
        d_sample->deinitialise();


    CEGUI::System& system(System::getSingleton());

    if(d_guiContext)
    {
        system.destroyGUIContext(*d_guiContext);
        d_guiContext = nullptr;
    }

    if(d_textureTarget)
    {
        system.getRenderer()->destroyTextureTarget(d_textureTarget);
        d_textureTarget = nullptr;
    }

    if(d_textureTargetImage)
    {
        CEGUI::ImageManager::getSingleton().destroy(*d_textureTargetImage);
        d_textureTargetImage = nullptr;
    }
}

GUIContext* SampleHandler::getGuiContext()
{
    return d_guiContext;
}

void SampleHandler::handleNewWindowSize(int width, int height)
{
    const float widthF = static_cast<float>(width);
    const float heightF = static_cast<float>(height);

    setTextureTargetImageArea(widthF, heightF);

    if(d_textureTarget)
    {
        CEGUI::Sizef windowSize(widthF, heightF);
        d_textureTarget->declareRenderSize(windowSize);

        RenderingSurface* rs = d_sampleWindow->getRenderingSurface();
        if (rs) rs->invalidate();
    }
}

CEGUI::Image& SampleHandler::getRTTImage()
{
    return *d_textureTargetImage;
}

void SampleHandler::setGUIContextRTT()
{
    d_guiContext->setRenderTarget(*d_textureTarget);
}

void SampleHandler::clearRTTTexture()
{
    d_textureTarget->clear();
}

void SampleHandler::setTextureTargetImageArea(float width, float height)
{
    if(d_textureTarget)
    {
        bool isTextureTargetVerticallyFlipped = d_textureTarget->getOwner().isTexCoordSystemFlipped();
        CEGUI::Rectf renderArea;
        if(isTextureTargetVerticallyFlipped)
            renderArea = CEGUI::Rectf(0.0f, height, width, 0.0f);
        else
            renderArea = CEGUI::Rectf(0.0f, 0.0f, width, height);


        if(d_textureTargetImage)
            d_textureTargetImage->setImageArea(renderArea);
    }
}

void SampleHandler::onEnteringSample()
{
    d_sample->onEnteringSample();
}

void SampleHandler::update(float timeSinceLastUpdate)
{
    d_sample->update(timeSinceLastUpdate);
}

void SampleHandler::initialiseSample()
{
    d_sample->initialise(d_guiContext);
    d_usedFilesString = d_sample->getUsedFilesString();
}

void SampleHandler::initialiseSamplePreviewRenderTarget(float width, float height)
{
    CEGUI::System& system(System::getSingleton());

    CEGUI::Sizef size(width, height);

    //! Creating a texture target to render the GUIContext onto
    d_textureTarget = system.getRenderer()->createTextureTarget(false);
    d_guiContext = &system.createGUIContext(static_cast<RenderTarget&>(*d_textureTarget));
    d_guiContext->initDefaultInputSemantics();
    d_textureTarget->declareRenderSize(size);

    //! Creating an image based on the TextureTarget's texture, which allows us to use the rendered-to-texture inside CEGUI for previewing the sample
    CEGUI::String imageName(d_textureTarget->getTexture().getName());
    d_textureTargetImage = static_cast<CEGUI::BitmapImage*>(&CEGUI::ImageManager::getSingleton().create("BitmapImage", "SampleBrowser/" + imageName));
    d_textureTargetImage->setTexture(&d_textureTarget->getTexture());

    //! Helper function to set the image's area
    setTextureTargetImageArea(width, height);
}

const Sample* SampleHandler::getSample() const
{
    return d_sample;
}
