// Copyright (c) 2009-2010 Gem Nakamoto
// Copyright (c) 2009-2018 The Geranium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GERANIUM_SCRIPT_GERANIUMCONSENSUS_H
#define GERANIUM_SCRIPT_GERANIUMCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_GERANIUM_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/geranium-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBGERANIUMCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define GERANIUMCONSENSUS_API_VER 1

typedef enum geraniumconsensus_error_t
{
    geraniumconsensus_ERR_OK = 0,
    geraniumconsensus_ERR_TX_INDEX,
    geraniumconsensus_ERR_TX_SIZE_MISMATCH,
    geraniumconsensus_ERR_TX_DESERIALIZE,
    geraniumconsensus_ERR_AMOUNT_REQUIRED,
    geraniumconsensus_ERR_INVALID_FLAGS,
} geraniumconsensus_error;

/** Script verification flags */
enum
{
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    geraniumconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = geraniumconsensus_SCRIPT_FLAGS_VERIFY_P2SH | geraniumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               geraniumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | geraniumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               geraniumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | geraniumconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int geraniumconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, geraniumconsensus_error* err);

EXPORT_SYMBOL int geraniumconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, geraniumconsensus_error* err);

EXPORT_SYMBOL unsigned int geraniumconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // GERANIUM_SCRIPT_GERANIUMCONSENSUS_H
