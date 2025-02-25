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

#include <cursespp/curses_config.h>
#include <cursespp/Window.h>
#include <cursespp/IInput.h>
#include <cursespp/IKeyHandler.h>
#include <sigslot/sigslot.h>
#include <vector>

namespace cursespp {
    class TextInput:
        public cursespp::Window,
        public cursespp::IKeyHandler,
        public cursespp::IInput
    {
        public:
            sigslot::signal1<TextInput*> EnterPressed;
            sigslot::signal2<TextInput*, std::string> TextChanged;

            enum Style { StyleBox, StyleLine };

            TextInput(InputMode inputMode = IInput::InputNormal);
            TextInput(Style style, InputMode inputMode = IInput::InputNormal);

            virtual ~TextInput();

            /* IInput */
            bool Write(const std::string& key) override;
            size_t Length() noexcept override;
            size_t Position() override;

            InputMode GetInputMode() noexcept override {
                return this->inputMode;
            }

            /* IWindow */
            bool KeyPress(const std::string& key) override;
            void OnRedraw() override;

            /* IMouseHandler */
            bool ProcessMouseEvent(const IMouseHandler::Event& event) override;

            /* regular methods we define */
            void SetRawKeyBlacklist(const std::vector<std::string>&& blacklist);
            void SetTruncate(bool truncate) noexcept;
            void SetHint(const std::string& hint);
            void SetEnterEnabled(bool enabled) noexcept;

            Style GetStyle() noexcept {
                return style;
            }

            /* virtual methods we define */
            virtual void SetText(const std::string& value);

            virtual std::string GetText() {
                return this->buffer;
            }

            virtual void SetInputMode(InputMode inputMode) noexcept {
                this->inputMode = inputMode;
            };

        private:
            bool OffsetPosition(int delta);

            std::vector<std::string> rawBlacklist;
            std::string buffer, hintText;
            int position;
            bool enterEnabled;
            bool truncate;
            size_t bufferLength;
            Style style;
            InputMode inputMode;
    };
}
