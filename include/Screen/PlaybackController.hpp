#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"

#include "Screen/CustomVideoPlayer.hpp"
#include "Video/VideoConfig.hpp"
#include "Util/EventArgs.hpp"
#include "Util/Scene.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/AudioSource.hpp"

#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/ScenesTransitionSetupDataSO.hpp"

#include "BeatSaber/GameSettings/MainSettingsHandler.hpp"

DECLARE_CLASS_CODEGEN(Cinema, PlaybackController, UnityEngine::MonoBehaviour,

    DECLARE_INSTANCE_FIELD(CustomVideoPlayer*, videoPlayer);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::AudioTimeSyncController*, audioTimeSyncController);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::SongPreviewPlayer*, songPreviewPlayer);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::BeatmapLevel*, currentLevel);
    DECLARE_INSTANCE_FIELD(BeatSaber::GameSettings::MainSettingsHandler*, mainSettingsHandler);
    DECLARE_INSTANCE_FIELD(UnityEngine::AudioSource*, activeAudioSource);
    DECLARE_INSTANCE_FIELD(System::Collections::IEnumerator*, prepareVideoCoroutine);

    DECLARE_INSTANCE_FIELD(float, lastKnownAudioSourceTime);
    DECLARE_INSTANCE_FIELD(float, previewStartTime);
    DECLARE_INSTANCE_FIELD(float, previewTimeRemaining);
    DECLARE_INSTANCE_FIELD_DEFAULT(bool, previewWaitingForVideoPlayer, true);
    DECLARE_INSTANCE_FIELD(bool, previewWaitingForPreviewPlayer);
    DECLARE_INSTANCE_FIELD(float, offsetAfterPrepare);

    public:

    Scene activeScene;
    std::shared_ptr<VideoConfig> videoConfig;
    std::chrono::system_clock::time_point audioSourceStartTime;

    UnityEngine::Video::VideoPlayer::EventHandler* configChangedPrepareHandler;
    UnityEngine::Video::VideoPlayer::FrameReadyEventHandler* configChangedFrameReadyHandler;
    UnityEngine::Video::VideoPlayer::EventHandler* onPrepareComplete;

    private:

    static inline UnityW<PlaybackController> instance;
    

    DECLARE_INSTANCE_METHOD(void, Destroy);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, PauseVideo);
    DECLARE_INSTANCE_METHOD(void, ResumeVideo);
    DECLARE_INSTANCE_METHOD(void, ApplyOffset, int offset);
    DECLARE_INSTANCE_METHOD(void, PlayerStartedAfterResync, UnityEngine::Video::VideoPlayer*, int64_t frame);
    DECLARE_INSTANCE_METHOD(void, FrameReady, UnityEngine::Video::VideoPlayer*, int64_t frame);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, StartPreview);
    DECLARE_INSTANCE_METHOD(void, StopPreview, bool stopPreviewMusic);
    DECLARE_INSTANCE_METHOD(void, OnMenuSceneLoaded);
    DECLARE_INSTANCE_METHOD(void, OnMenuSceneLoadedFresh, GlobalNamespace::ScenesTransitionSetupDataSO* transitionSetupData);
    DECLARE_INSTANCE_METHOD(void, SceneChanged);
    DECLARE_INSTANCE_METHOD(void, ConfigChangedPrepareHandler, UnityEngine::Video::VideoPlayer* sender);
    DECLARE_INSTANCE_METHOD(void, ConfigChangedFrameReadyHandler, UnityEngine::Video::VideoPlayer* sender, int64_t frameIdx);
    DECLARE_INSTANCE_METHOD(void, ShowSongCover);
    DECLARE_INSTANCE_METHOD(void, GameSceneActive);
    DECLARE_INSTANCE_METHOD(void, GameSceneLoaded);
    DECLARE_INSTANCE_METHOD(void, SetAudioSourcePanning, float pan);
    DECLARE_INSTANCE_METHOD(void, PlayVideo, float startTime);
    DECLARE_INSTANCE_METHOD(void, OnPrepareComplete, UnityEngine::Video::VideoPlayer*);
    DECLARE_INSTANCE_METHOD(void, StopPlayback);
    DECLARE_INSTANCE_METHOD(void, SceneTransitionInitCalled);
    DECLARE_INSTANCE_METHOD(void, UpdateSongPreviewPlayer, UnityEngine::AudioSource* activeAudioSource, float startTime, float timeRemaining, bool isDefault);
    DECLARE_INSTANCE_METHOD(void, StartSongPreview);

    DECLARE_DEFAULT_CTOR();

    public:

    static PlaybackController* get_instance();

    static void Create();
    float GetReferenceTime(std::optional<float> referenceTime = std::nullopt, std::optional<float> playbackSpeed = std::nullopt);
    void ResyncVideo(std::optional<float> referenceTime = std::nullopt, std::optional<float> playbackSpeed = std::nullopt);
    void OnConfigChanged(std::shared_ptr<VideoConfig> config);
    void OnConfigChanged(std::shared_ptr<VideoConfig> config, bool reloadVideo);
    void SetSelectedLevel(GlobalNamespace::BeatmapLevel* level, std::shared_ptr<VideoConfig> config);
    void DifficultySelected(ExtraSongDataArgs extraSongDataArgs);
    custom_types::Helpers::Coroutine PlayVideoAfterAudioSourceCoroutine(bool preview);
    custom_types::Helpers::Coroutine PlayVideoDelayedCoroutine(float delayStartTime);
    void PrepareVideo(std::shared_ptr<VideoConfig> video);
    custom_types::Helpers::Coroutine PrepareVideoCoroutine(std::shared_ptr<VideoConfig> video);
)