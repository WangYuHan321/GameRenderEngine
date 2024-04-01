#include "TimeLine.h"

#include "../../UI/Layout/Group.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Layout/TreeNode.h"
#include "../../UI/Plugin/DDSource.h"
#include "../../UI/Visual/Separator.h"
#include "../../UI/Plugin/TexturePreview.h"
#include "../../UI/Widgets/Text/TextClickable.h"
#include "../../UI/Widgets/Button/ButtonImage.h"
#include "../../UI/Widgets/Drag/DragSingleScalar.h"
#include "../../Global/ServiceLocator.h"
#include "../../Editor/Core/EditorResource.h"

TimeLine::TimeLine(const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting p_windowSetting):
	PanelWindow(p_title, p_opened, p_windowSetting)
{
	m_barGroup = &CreateWidget<Group>();
	m_sequencerGroup = &CreateWidget<Group>();

	InitBar();
	InitSequencer();
}

void TimeLine::InitBar()
{
	Image& speedImg = m_barGroup->CreateWidget<Image>(GLOBALSERVICE(EditorResource).GetTexture("Icon_Clock")->ID, ImVec2(40, 40));
	speedImg.lineBreak = false;

	DragSingleScalar<unsigned int>& speedItem = m_barGroup->CreateWidget<DragSingleScalar<unsigned int>>(ImGuiDataType_U32, 0, 100, 1, 1, "", "%d");
	speedItem.lineBreak = false;

	ButtonImage& stopBtn = m_barGroup->CreateWidget<ButtonImage>(GLOBALSERVICE(EditorResource).GetTexture("Icon_Stop")->ID, ImVec2(40, 40));
	stopBtn.lineBreak = false;

	ButtonImage& leftBtn = m_barGroup->CreateWidget<ButtonImage>(GLOBALSERVICE(EditorResource).GetTexture("Icon_LeftPlay")->ID, ImVec2(40, 40));
	leftBtn.lineBreak = false;

	ButtonImage& playBtn = m_barGroup->CreateWidget<ButtonImage>(GLOBALSERVICE(EditorResource).GetTexture("Icon_Play")->ID, ImVec2(40, 40));
	playBtn.lineBreak = false;

	ButtonImage& pauseBtn = m_barGroup->CreateWidget<ButtonImage>(GLOBALSERVICE(EditorResource).GetTexture("Icon_Pause")->ID, ImVec2(40, 40));
	pauseBtn.lineBreak = false;

	Text& curText = m_barGroup->CreateWidget<Text>("current");
	curText.lineBreak = false;

	Text& startText = m_barGroup->CreateWidget<Text>("Start");
	startText.lineBreak = false;

	Text& endText = m_barGroup->CreateWidget<Text>("End");
}

void TimeLine::InitSequencer()
{
	//Image& speedImg = m_sequencerGroup->CreateWidget<Image>(GLOBALSERVICE(EditorResource).GetTexture("Icon_Sequencer")->ID, ImVec2(800, 40));
	//speedImg.lineBreak = false;

}
