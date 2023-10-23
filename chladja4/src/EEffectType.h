//
// Created by chladas on 4/16/23.
//

#pragma once

/**
 *      Enum that represent types effect, it's used when reading effects from file.
 *      Used first characters from the variable name to be more readable and clear.
 */
enum EEffectType
{
    resource      = 'r',
    base          = 'b',
    unit          = 'u',
    refill        = 'f',
    swapCards     = 's'
};
