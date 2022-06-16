//
// Created by Iannis on 14/06/2022.
//

#ifndef JEUDELESPACE_INPUTKEY_HPP
#define JEUDELESPACE_INPUTKEY_HPP

#include <optional>
#include <string>

struct InputKey {
    std::optional<int> KeyMain;
    std::optional<int> KeySecondary;
};

#endif //JEUDELESPACE_INPUTKEY_HPP
