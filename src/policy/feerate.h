// Copyright (c) 2009-2010 Gem Nakamoto
// Copyright (c) 2009-2019 The Geranium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GERANIUM_POLICY_FEERATE_H
#define GERANIUM_POLICY_FEERATE_H

#include <amount.h>
#include <serialize.h>

#include <string>

extern const std::string CURRENCY_UNIT;

/**
 * Fee rate in satoshis per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nGemsPerK; // unit is satoshis-per-1,000-bytes

public:
    /** Fee rate of 0 satoshis per kB */
    CFeeRate() : nGemsPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nGemsPerK): nGemsPerK(_nGemsPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }
    /** Constructor for a fee rate in satoshis per kB. The size in bytes must not exceed (2^63 - 1)*/
    CFeeRate(const CAmount& nFeePaid, size_t nBytes);
    /**
     * Return the fee in satoshis for the given size in bytes.
     */
    CAmount GetFee(size_t nBytes) const;
    /**
     * Return the fee in satoshis for a size of 1000 bytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nGemsPerK < b.nGemsPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nGemsPerK > b.nGemsPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nGemsPerK == b.nGemsPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nGemsPerK <= b.nGemsPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nGemsPerK >= b.nGemsPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nGemsPerK != b.nGemsPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nGemsPerK += a.nGemsPerK; return *this; }
    std::string ToString() const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(nGemsPerK);
    }
};

#endif //  GERANIUM_POLICY_FEERATE_H
