#include "Util/Events.hpp"
#include "main.hpp"

#include "GlobalNamespace/LevelCollectionViewController.hpp"
#include "GlobalNamespace/LobbySetupViewController.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"

using namespace GlobalNamespace;

MAKE_AUTO_HOOK_MATCH(LevelCollectionViewController_HandleLevelCollectionTableViewDidSelectLevel, &LevelCollectionViewController::HandleLevelCollectionTableViewDidSelectLevel, void, LevelCollectionViewController* self, LevelCollectionTableView* tableView, BeatmapLevel* level)
{
    Cinema::Events::SetSelectedLevel(level);
    INFO("Level Selected");
    LevelCollectionViewController_HandleLevelCollectionTableViewDidSelectLevel(self, tableView, level);
}

MAKE_AUTO_HOOK_MATCH(LevelCollectionViewController_HandleLevelCollectionTableViewDidSelectPack, &LevelCollectionViewController::HandleLevelCollectionTableViewDidSelectPack, void, LevelCollectionViewController* self, LevelCollectionTableView* tableView)
{
    Cinema::Events::SetSelectedLevel(nullptr);
    LevelCollectionViewController_HandleLevelCollectionTableViewDidSelectPack(self, tableView);
}

MAKE_AUTO_HOOK_MATCH(MainMenuViewController_DidActivate, &MainMenuViewController::DidActivate, void, MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    Cinema::Events::SetSelectedLevel(nullptr);
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_AUTO_HOOK_MATCH(LobbySetupViewController_DidActivate, &LobbySetupViewController::DidActivate, void, LobbySetupViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    Cinema::Events::SetSelectedLevel(nullptr);
    LobbySetupViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}