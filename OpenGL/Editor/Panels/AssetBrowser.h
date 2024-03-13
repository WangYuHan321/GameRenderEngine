#include <filesystem>
#include "../../UI/Layout/Group.h"
#include "../../UI/Panel/PanelWindow.h"

class TreeNode;

class AssetBrowser :
    public PanelWindow
{

public:
    AssetBrowser(const std::string& p_title,
        bool p_opened,
        const PanelWindowSetting& p_windowSetting,
        const std::string& p_engineAssetFolder = "",
        const std::string& p_projectAssetFolder = "",
        const std::string& p_projectScriptFolder = ""
    );

    void Fill();

    void Clear();

    void Refresh();

private:

    void ParseFolder(TreeNode* p_root, std::filesystem::directory_entry& p_directory, bool p_isEngineItem, bool p_scriptFolder = false);
    void ConsiderItem(TreeNode* p_root, const std::filesystem::directory_entry& p_entry, bool p_isEngineItem, bool p_autoOpen = false, bool p_scriptFolder = false);


private:

    std::string m_engineAssetFolder;
    std::string m_projectAssetFolder;
    std::string m_projectScriptFolder;
    Group* m_assetList;
    std::unordered_map<TreeNode*, std::string> m_pathUpdate;

};
