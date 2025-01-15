/***********************************************************************
    created:    Aug 22 2014
    author:     Luca Ebach <lucaebach@gmail.com>
                (based on original code by Tomas Lindquist Olsen)
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2014 Paul D Turner & The CEGUI Development Team
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
#include "SampleEditor.h"
#include "CEGUI/SchemeManager.h"
#include "CEGUI/WindowManager.h"
#include "CEGUI/FontManager.h"
#include "CEGUI/text/Font.h"
#include "CEGUI/GUIContext.h"
#include "CEGUI/widgets/ScrollablePane.h"
#include "CEGUI/widgets/ScrolledContainer.h"
#include "CEGUI/widgets/FrameWindow.h"

#ifdef _WIN32
#include "FileDialogWin.hpp"
#endif // _WIN32


 //----------------------------------------------------------------------------//
SampleEditor::SampleEditor()
{
    Sample::d_name = "ScrollablePaneDemo";
    Sample::d_credits = "Tomas Lindquist Olsen, Vladimir 'Niello' Orlov";
    Sample::d_description =
        "The ScrollbarPane sample shows different scenarios of ScrollablePane usage. "
        "It uses the WindowsLook, which gives it a look similar to old Windows apps. "
        "The background consists of several ScrollablePanes to which windows "
        "can be added, using the menu bar. The items on each pane can be "
        "moved freely and the pane can be scrolled with the scrollbars.";
    Sample::d_summary =
        "Some scenarios of ScrollablePane usage.";
}

//----------------------------------------------------------------------------//
bool SampleEditor::initialise(CEGUI::GUIContext* guiContext)
{
    using namespace CEGUI;

    d_usedFiles = String(__FILE__);
    d_guiContext = guiContext;

    // this sample will use WindowsLook
    SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");

    // load the default font
    FontManager::FontList loadedFonts = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
    Font* font = loadedFonts.empty() ? nullptr : loadedFonts.front();
    guiContext->setDefaultFont(font);

    // set the cursor
    guiContext->setDefaultCursorImage("WindowsLook/MouseArrow");

    // set the default tooltip type
    guiContext->setDefaultTooltipType("WindowsLook/Tooltip");

    auto wm = WindowManager::getSingletonPtr();

    // create a root window
    auto root = wm->createWindow("DefaultWindow");
    root->setSize(USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));

    guiContext->setRootWindow(root);

    // create a menubar.
    // this will fit in the top of the screen and have options for the Sample
    UDim bar_bottom(0.f, font ? (font->getLineSpacing() * 1.5f) : 0.f);

    Window* bar = wm->createWindow("WindowsLook/Menubar");
    bar->setArea(UDim(0, 0), UDim(0, 0), UDim(1, 0), bar_bottom);
    root->addChild(bar);

    // fill out the menubar
    createMenu(bar);

    // Create the first, fixed-size scrollable pane. This scrollable pane will be
    // a kind of virtual desktop in the sense that it's bigger than the screen.

    auto panelFixed = wm->createWindow("WindowsLook/Static");
    panelFixed->setArea(URect(UDim(0, 0), bar_bottom, UDim(1.0f, -1), UDim(1.0f, -1)));
    panelFixed->setProperty("BackgroundColours", "tl:FFBFBFBF tr:FFBFBFBF bl:FFBFBFBF br:FFBFBFBF");
    panelFixed->subscribeEvent(Window::EventKeyDown,
        Event::Subscriber(&SampleEditor::keyDownEventHandler, this));
    root->addChild(panelFixed);


    return true;
}

//----------------------------------------------------------------------------//
void SampleEditor::createMenu(CEGUI::Window* bar)
{
    using namespace CEGUI;

    auto d_wm = WindowManager::getSingletonPtr();

    FontManager::FontList loadedFonts = FontManager::getSingleton().createFromFile("Sthupo.font");
    //FontManager::FontList loadedFonts = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
    Font* defaultFont = loadedFonts.empty() ? 0 : loadedFonts.front();

    // file menu item
    Window* file = d_wm->createWindow("WindowsLook/MenuItem");
    file->setText(U"文件");
    file->setFont(defaultFont);
    bar->addChild(file);

    // file popup
    Window* popup = d_wm->createWindow("WindowsLook/PopupMenu");
    file->addChild(popup);

    // quit item in file menu
    Window* item = d_wm->createWindow("WindowsLook/MenuItem");
    item->setText(U"选择加载的Obj文件");
    item->setFont(defaultFont);
    item->subscribeEvent("Clicked", Event::Subscriber(&SampleEditor::fileQuit, this));
    popup->addChild(item);

    // Sample menu item
    Window* Sample = d_wm->createWindow("WindowsLook/MenuItem");
    Sample->setText("Sample");
    Sample->setFont(defaultFont);
    bar->addChild(Sample);

    // Sample popup
    popup = d_wm->createWindow("WindowsLook/PopupMenu");
    Sample->addChild(popup);

    // Sample -> new window
    item = d_wm->createWindow("WindowsLook/MenuItem");
    item->setText("New dialog");
    item->setFont(defaultFont);
    item->setTooltipText("Hotkey: Space");
    item->subscribeEvent("Clicked", Event::Subscriber(&SampleEditor::addNewChild, this));
    popup->addChild(item);
}

bool SampleEditor::fileQuit(const CEGUI::EventArgs&)
{
    FileOpenDialog();

    return true;
}

//----------------------------------------------------------------------------//
void SampleEditor::deinitialise()
{
    // everything we did is cleaned up by CEGUI
}

//----------------------------------------------------------------------------//
bool SampleEditor::addNewChild(const CEGUI::EventArgs&)
{
    using namespace CEGUI;

    // Add a dialog to this pane so we have some more stuff to drag around :)
    Window* dlg = WindowManager::getSingletonPtr()->createWindow("WindowsLook/FrameWindow");
    dlg->setMinSize(USize(UDim(0, 200), UDim(0, 100)));
    dlg->setSize(USize(UDim(0, 200), UDim(0, 100)));
    dlg->setText("Drag me around too!");

    // Move the new dialog to the center of the viewable area
    const glm::vec2 offset = d_pane->getContentPane()->getPixelPosition();
    const Sizef viewportSize = d_pane->getViewableArea().getSize();
    const UVector2 pos(
        UDim(0, viewportSize.d_width / 2.f - offset.x - 100.f),
        UDim(0, viewportSize.d_height / 2.f - offset.y - 50.f));
    dlg->setPosition(pos);

    dlg->subscribeEvent(FrameWindow::EventCloseClicked, [dlg]()
        {
            WindowManager::getSingletonPtr()->destroyWindow(dlg);
        });

    d_pane->addChild(dlg);

    return true;
}

//----------------------------------------------------------------------------//
bool SampleEditor::keyDownEventHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& args = static_cast<const CEGUI::KeyEventArgs&>(e);
    if (args.d_key == CEGUI::Key::Scan::Space)
    {
        addNewChild(CEGUI::EventArgs());
        return true;
    }

    return false;
}
