// Copyright (c) 2009-2010 Gem Nakamoto
// Copyright (c) 2009-2019 The Geranium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GERANIUM_SUPPORT_CLEANSE_H
#define GERANIUM_SUPPORT_CLEANSE_H

#include <stdlib.h>

/** Secure overwrite a buffer (possibly containing secret data) with zero-bytes. The write
 * operation will not be optimized out by the compiler. */
void memory_cleanse(void *ptr, size_t len);

#endif // GERANIUM_SUPPORT_CLEANSE_H
