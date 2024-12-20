#include "Util/Util.hpp"
#include "Hooks/MultiplayerHooks.hpp"
#include "logger.hpp"

#include <regex>

#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"

/*
 * https://cs.android.com/android/platform/superproject/+/master:frameworks/base/core/java/android/os/FileUtils.java;l=997?q=isValidFatFilenameChar
 */
static const std::regex searchRegex("[\"\\*\\:\\<\\>\\?\\\\\\|/]");

namespace Cinema::Util
{

    std::string ReplaceIllegalFilesystemChar(const std::string& s)
    {
        return std::regex_replace(s, searchRegex, "_");
    }

    std::string GetEnvironmentName()
    {
        using UnityEngine::SceneManagement::SceneManager;
        std::string environmentName("MainMenu");
        int sceneCount = SceneManager::get_sceneCount();
        for(int i = 0; i < sceneCount; i++)
        {
            StringW sceneName = SceneManager::GetSceneAt(i).name;
            if(!sceneName.ends_with("Environment"))
            {
                continue;
            }

            environmentName = static_cast<std::string>(sceneName);
            break;
        }

        return environmentName;
    }

    bool IsMultiplayer()
    {
        return MultiplayerHooks::IsMultiplayer();
    }
} 