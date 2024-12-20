#include "Video/VideoConfig.hpp"
#include "Util/Util.hpp"
#include "Video/VideoLoader.hpp"
#include "main.hpp"

namespace Cinema
{

    bool VideoConfig::get_IsWIPLevel() const
    {
        return levelDir.has_value() && levelDir->find("CustomWIPLevels") != std::string::npos;
    }

    bool VideoConfig::get_IsOfficialConfig() const
    {
        return configByMapper.value_or(false);
    }

    bool VideoConfig::get_TransparencyEnabled() const
    {
        return ((!transparency.has_value()) || transparency.has_value() && !transparency.value());
    }

    bool VideoConfig::get_IsDownloading() const
    {
        return downloadState == DownloadState::Preparing ||
               downloadState == DownloadState::Downloading ||
               downloadState == DownloadState::DownloadingVideo ||
               downloadState == DownloadState::DownloadingAudio;
    }

    std::optional<std::string> VideoConfig::get_VideoPath()
    {
        if(levelDir.has_value() && IsWIPLevel)
        {
            std::filesystem::path levelPath(levelDir.value());
            auto path = levelPath.parent_path();
            auto mapFolderName = levelPath.filename().string();

            DEBUG("Found Parent folder {}", path.string());
            auto folder = path / "CinemaWIPVideos" / mapFolderName;
            videoFile = GetVideoFileName(folder);
            return folder / videoFile.value();
        }

        if(levelDir.has_value())
        {
            try
            {
                videoFile = GetVideoFileName(levelDir.value());
                return std::filesystem::path(levelDir.value()) / videoFile.value();
            } catch(const std::exception& e)
            {
                ERROR("Failed to combine video path for {}: {}", videoFile.value(), e.what());
                return std::nullopt;
            }
        }

        DEBUG("VideoPath is null");
        return std::nullopt;
    }

    std::optional<std::string> VideoConfig::get_ConfigPath() const
    {
        if(levelDir.has_value())
        {
            return VideoLoader::GetConfigPath(levelDir.value());
        }
        return std::nullopt;
    }

    bool VideoConfig::get_isPlayable() const
    {
        return true;
    }

    std::string VideoConfig::GetVideoFileName(std::string levelPath) const
    {
        std::string fileName = Cinema::Util::ReplaceIllegalFilesystemChar(videoFile.value_or(title.value_or(videoID.value_or("video"))));
        if(!fileName.ends_with(".mp4"))
        {
            fileName.append(".mp4");
        }
        return fileName;
    }

    std::string VideoConfig::ToString() const
    {
        return fmt::format("[{}] {} by {} ({})", videoID, title, author, duration);
    }

    float VideoConfig::GetOffsetInSec() const
    {
        return offset / 1000.0f;
    }

    DownloadState VideoConfig::UpdateDownloadState()
    {
        return (downloadState = (VideoPath.has_value() && (videoID.has_value() || videoUrl.has_value()) 
                                && std::filesystem::exists(VideoPath.value()) ? 
                                DownloadState::Downloaded 
                                : DownloadState::NotDownloaded));
    }
} // namespace Cinema