/***********************************************************************
created:    2/6/2012
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
#ifndef _Sample_Handler_h_
#define _Sample_Handler_h_

#include "CEGUI/String.h"

// forward declarations
#include "CEGUI/ForwardRefs.h"

namespace CEGUI
{
    class BitmapImage;
}

class Sample;

class SampleHandler
{
public:
    SampleHandler(Sample* instance);
    virtual ~SampleHandler();

    virtual void initialise(int width, int height);

    virtual void deinitialise();

    virtual CEGUI::GUIContext* getGuiContext();
    virtual void handleNewWindowSize(int width, int height);

    void setTextureTargetImageArea(float width, float height);
    virtual CEGUI::Image& getRTTImage();

    virtual void setGUIContextRTT();
    virtual void clearRTTTexture();

    virtual void onEnteringSample();
    virtual void update(float timeSinceLastUpdate);

    void setSampleWindow(CEGUI::Window* sampleWindow);
    CEGUI::Window* getSampleWindow();

    CEGUI::String getNameText();
    CEGUI::String getSummaryText();
    CEGUI::String getDescriptionText();
    CEGUI::String getUsedFilesText();
    CEGUI::String getCreditsText();

    const Sample* getSample() const;

protected:
    //! The Sample we are wrapping in this class
    Sample*                 d_sample = nullptr;
    //! A string containing a list of files used for the sample
    CEGUI::String           d_usedFilesString;
    //! The root window of the sample
    CEGUI::Window*          d_sampleWindow = nullptr;
    //! The GUIContext created to contain the sample root
    CEGUI::GUIContext*      d_guiContext = nullptr;
    //! The texture target onto which the Sample will be rendered
    CEGUI::TextureTarget*   d_textureTarget = nullptr;
    //! The Bitmap image which is used to display the Sample as a rendered preview in connection with the texture target
    CEGUI::BitmapImage*     d_textureTargetImage = nullptr;

private:
    void initialiseSamplePreviewRenderTarget(float width, float height);
    void initialiseSample();
};

#endif

