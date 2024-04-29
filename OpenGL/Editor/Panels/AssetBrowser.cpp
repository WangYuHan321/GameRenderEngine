#include "AssetBrowser.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Layout/TreeNode.h"
#include "../../File/Path/PathParser.h"
#include "../../UI/Plugin/DDSource.h"
#include "../../UI/Visual/Separator.h"
#include "../../Core/Util/SystemCall.h"
#include "../../UI/Widgets/InputField/InputText.h"
#include "../../UI/Plugin/TexturePreview.h"
#include "../../UI/Plugin/ContextualMenu.h"
#include "../../UI/Widgets/Text/TextClickable.h"
#include "../../Editor/Core/EditorAction.h"

class ScriptBrowserContextualMenu : public ContextualMenu
{
public:
    void CreateScript(const std::string& p_name, const std::string& p_path)
    {
        std::string fileContent = "local " + p_name + " =\n{\n}\n\nfunction " + p_name +
        ":OnStart()\nend\n\nfunction " + p_name + ":OnUpdate(deltaTime)\nend\n\nfunction " +
        p_name + ":OnAwake()\nend\n\nfunction " + p_name + ":OnStart()\nend\n\nfunction " + 
        p_name + ":OnEnable()\nend\n\nfunction " + p_name + ":OnDisable()\nend\n\nfunction " +
        p_name + ":OnEnd()\nend\n\nfunction " + p_name + ":OnDestroy()\nend\n\nfunction " +
        p_name + ":OnUpdate(deltaTime)\nend\n\nfunction " + p_name + ":OnFixedUpdate(deltaTime)\nend\n\nfunction " +
        p_name + ":OnLateUpdate(deltaTime)\nend\n\nfunction " + p_name + ":OnCollisionStart(otherObject)\nend\n\nfunction " +
        p_name + ":OnCollisionEnter(otherObject)\nend\n\nfunction " + p_name + ":OnCollisionStay(otherObject)\nend\n\nfunction " +
        p_name + ":OnCollisionStop(otherObject)\nend\n\nfunction " + p_name + ":OnCollisionExit(otherObject)\nend\n\nfunction " +
        p_name + ":OnTriggerStart(otherObject)\nend\n\nfunction " + p_name + ":OnTriggerEnter(otherObject)\nend\n\nfunction " +
        p_name + ":OnTriggerStop(otherObject)\nend\n\nfunction " + p_name + ":OnTriggerExit(otherObject)\nend\n\n" +
        "return " + p_name;
        std::ofstream outFile(p_path);
        outFile << fileContent << std::endl;

        Close();
    }

    ScriptBrowserContextualMenu(Group& p_treeNode, std::string dirPath) :
        m_treeNode(p_treeNode)
    {
        auto& showInExplore = CreateWidget<MenuItem>("Show InExplore");
        showInExplore.ClickedEvent += [dirPath]()
        {
            SystemCall::ShowInExplorer(dirPath);
        };


        auto& newScriptMenu = CreateWidget<MenuList>("New Script...");
        auto& newName = newScriptMenu.CreateWidget<InputText>("");
        newScriptMenu.ClickedEvent += [this, &newName]
        {
            newName.content = "";
        };

        newName.EnterPressedEvent += [this, dirPath](std::string p_newName)
        {
            std::string newPath = dirPath + p_newName + ".lua";

            if (!std::filesystem::exists(newPath))
            {
                CreateScript(p_newName, newPath);
            }
        };

    }

private:
    Group& m_treeNode;
};

class AssetBrowserContextualMenu : public ContextualMenu
{
public:
    AssetBrowserContextualMenu(Group& p_treeNode, std::string dirPath) :
        m_treeNode(p_treeNode)
    {
        auto& showInExplore = CreateWidget<MenuItem>("Show InExplore");
        showInExplore.ClickedEvent += [dirPath]()
        {
            SystemCall::ShowInExplorer(dirPath);
        };

    }

private:
    Group& m_treeNode;
};

class EngineBrowserContextualMenu : public ContextualMenu
{
public:
    EngineBrowserContextualMenu(Group& p_treeNode, std::string dirPath) :
        m_treeNode(p_treeNode)
    {
        auto& showInExplore = CreateWidget<MenuItem>("Show InExplore");
        showInExplore.ClickedEvent += [dirPath]()
        {
            SystemCall::ShowInExplorer(dirPath);
        };

    }

private:
    Group& m_treeNode;
};

//class TextureBrowserContextualMenu : public ContextualMenu
//{
//
//}

AssetBrowser::AssetBrowser(const std::string& p_title,
    bool p_opened,
    const PanelWindowSetting& p_windowSetting,
    const std::string& p_engineAssetFolder,
    const std::string& p_projectAssetFolder,
    const std::string& p_projectScriptFolder
) : PanelWindow(p_title, p_opened, p_windowSetting),
m_engineAssetFolder(p_engineAssetFolder),
m_projectAssetFolder(p_projectAssetFolder),
m_projectScriptFolder(p_projectScriptFolder)
{
    m_assetList = &CreateWidget<Group>();

    Fill();
}

void AssetBrowser::Fill()
{
    m_assetList->CreateWidget<Separator>();
    ConsiderItem(nullptr, std::filesystem::directory_entry(m_engineAssetFolder), true);
    m_assetList->CreateWidget<Separator>();
    ConsiderItem(nullptr, std::filesystem::directory_entry(m_projectAssetFolder), false);
    m_assetList->CreateWidget<Separator>();
    ConsiderItem(nullptr, std::filesystem::directory_entry(m_projectScriptFolder), false, false, true);
}

void AssetBrowser::Clear()
{

}

void AssetBrowser::Refresh()
{

}

void AssetBrowser::ParseFolder(TreeNode* p_root, std::filesystem::directory_entry& p_directory, bool p_isEngineItem, bool p_scriptFolder)
{
    for (auto item : std::filesystem::directory_iterator(p_directory))
    {
        if (item.is_directory())
        {
            ConsiderItem(p_root, item, p_isEngineItem, false, p_scriptFolder);
        }
    }

    for (auto& item : std::filesystem::directory_iterator(p_directory))
        if (!item.is_directory())
            ConsiderItem(p_root, item, p_isEngineItem, false, p_scriptFolder);
}

void AssetBrowser::ConsiderItem(TreeNode* p_root, const std::filesystem::directory_entry& p_entry, bool p_isEngineItem, bool p_autoOpen, bool p_scriptFolder)
{
    bool isDirectory = p_entry.is_directory();

    std::string itemName = PathParser::getInstance()->GetFileNameByPath(p_entry.path().string());
    std::string itemPath = p_entry.path().string();
    if (isDirectory)
        itemPath += '\\';

    EFileType fileType = PathParser::getInstance()->GetFileType(itemName);

    if (fileType == EFileType::NONE && !isDirectory)
        return;

    auto& itemGroup = p_root ? p_root->CreateWidget<Group>() : m_assetList->CreateWidget<Group>();

    uint32 textureID = isDirectory ? EDITOR_CONTEXT(m_editorResource)->GetTexture("Icon_Folder")->ID : EDITOR_CONTEXT(m_editorResource)->GetTexture("Icon_" + PathParser::getInstance()->GetFileTypeToString(fileType))->ID;

    auto& itemImg = itemGroup.CreateWidget<Image>( textureID, ImVec2(32, 32)).lineBreak = false;

    if (isDirectory)
    {
        auto& treeNode = itemGroup.CreateWidget<TreeNode>(itemName);//ÓÒ±ß×ÖÌå
     
        if (itemName == "Script")
            treeNode.AddPlugin<ScriptBrowserContextualMenu>(itemGroup, itemPath);
        
        if(itemName == "Asset")
            treeNode.AddPlugin<AssetBrowserContextualMenu>(itemGroup, itemPath);

        if (itemName == "Engine")
            treeNode.AddPlugin<EngineBrowserContextualMenu>(itemGroup, itemPath);

        if (p_autoOpen)
            treeNode.Open();

        auto& ddSource = treeNode.AddPlugin<DDSource<std::pair<std::string, Group*>>>("Folder", itemName, std::make_pair(itemPath, &itemGroup));

        treeNode.OpenedEvent += [this, &treeNode, itemPath, p_isEngineItem, p_scriptFolder]
        {
            treeNode.RemoveAllWidgets();
            std::string updatedPath = itemPath;
            std::filesystem::directory_entry dir(updatedPath);
            ParseFolder(&treeNode, dir, p_isEngineItem, p_scriptFolder);
        };

        treeNode.ClosedEvent += [this, &treeNode]
        {
            treeNode.RemoveAllWidgets();
        };
    }
    else
    {
        auto& clickableText = itemGroup.CreateWidget<TextClickable>(itemName);

        auto& ddSource = clickableText.AddPlugin<DDSource<std::pair<std::string, Group*>>>("File", itemName, std::make_pair(itemPath, &itemGroup));

        if (fileType == EFileType::TEXTURE)
        {
            auto& preview = clickableText.AddPlugin<TexturePreview>();
            preview.SetPath(itemName);
        }

    }

}