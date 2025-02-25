//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2021 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cursespp/LayoutBase.h>
#include <cursespp/ShortcutsWindow.h>
#include <cursespp/ITopLevelLayout.h>
#include <app/layout/BrowseLayout.h>
#include <app/layout/DirectoryLayout.h>
#include <app/layout/NowPlayingLayout.h>
#include <app/layout/CategorySearchLayout.h>
#include <app/layout/TrackSearchLayout.h>
#include <app/window/TransportWindow.h>
#include <musikcore/audio/PlaybackService.h>
#include <musikcore/support/Preferences.h>
#include <musikcore/library/ILibrary.h>

#include <sigslot/sigslot.h>

namespace musik {
    namespace cube {
        class LibraryLayout :
            public cursespp::LayoutBase,
            public cursespp::ITopLevelLayout,
            public sigslot::has_slots<>
        {
            public:
                DELETE_CLASS_DEFAULTS(LibraryLayout)

                LibraryLayout(
                    musik::core::audio::PlaybackService& playback,
                    musik::core::ILibraryPtr library);

                cursespp::IWindowPtr FocusNext() override;
                cursespp::IWindowPtr FocusPrev() override;
                cursespp::IWindowPtr GetFocus() override;
                bool SetFocus(cursespp::IWindowPtr window) override;
                void ProcessMessage(musik::core::runtime::IMessage &message) override;
                void OnVisibilityChanged(bool visible) override;

                void SetShortcutsWindow(
                    cursespp::ShortcutsWindow* w) override;

                bool KeyPress(const std::string& key) override;

            protected:
                void OnLayout() override;
                void OnAddedToParent(IWindow* newParent) override;
                void OnRemovedFromParent(IWindow* oldParent) override;

            private:
                void LoadLastSession();

                void OnCategorySearchResultSelected(
                    CategorySearchLayout* layout,
                    std::string fieldType,
                    int64_t fieldId);

                void OnMainLayoutFocusTerminated(
                    LayoutBase::FocusDirection direction);

                void InitializeWindows();

                void ShowNowPlaying();
                void ShowBrowse(const std::string& category = "");
                void ShowCategorySearch();
                void ShowCategoryChooser();
                void ShowTrackSearch();
                void ShowDirectoryChooser();
                void ShowDirectories(const std::string& directory = "");

                void ChangeMainLayout(std::shared_ptr<cursespp::LayoutBase> newLayout);
                void OnLayoutChanged();
                void UpdateShortcutsWindow();

                musik::core::audio::PlaybackService& playback;
                musik::core::audio::ITransport& transport;
                musik::core::ILibraryPtr library;
                std::shared_ptr<musik::core::Preferences> prefs;
                std::shared_ptr<BrowseLayout> browseLayout;
                std::shared_ptr<DirectoryLayout> directoryLayout;
                std::shared_ptr<TransportWindow> transportView;
                std::shared_ptr<NowPlayingLayout> nowPlayingLayout;
                std::shared_ptr<CategorySearchLayout> categorySearchLayout;
                std::shared_ptr<TrackSearchLayout> trackSearchLayout;
                std::shared_ptr<cursespp::LayoutBase> visibleLayout;
                cursespp::ShortcutsWindow* shortcuts;
                std::string lastBrowseCategoryType;
        };
    }
}
