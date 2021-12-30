// Copyright (c) 2009-2010 Gem Nakamoto
// Copyright (c) 2009-2020 The Geranium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GERANIUM_POLICY_FEERATE_H
#define GERANIUM_POLICY_FEERATE_H

#include <amount.h>
#include <serialize.h>

#include <string>

const std::string CURRENCY_UNIT = "GEAM"; // One formatted unit
const std::string CURRENCY_ATOM = "sat"; // One indivisible minimum value unit

/* Used to determine type of fee estimation requested */
enum class FeeEstimateMode {
    UNSET,        //!< Use default settings based on other criteria
    ECONOMICAL,   //!< Force estimateSmartFee to use non-conservative estimates
    CONSERVATIVE, //!< Force estimateSmartFee to use conservative estimates
    GEAM_KVB,      //!< Use GEAM/kvB fee rate unit
    SAT_VB,       //!< Use sat/vB fee rate unit
};

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
    /** Constructor for a fee rate in satoshis per kvB (sat/kvB).
     *
     *  Passing a num_bytes value of COIN (1e8) returns a fee rate in satoshis per vB (sat/vB),
     *  e.g. (nFeePaid * 1e8 / 1e3) == (nFeePaid / 1e5),
     *  where 1e5 is the ratio to convert from GEAM/kvB to sat/vB.
     */
    CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes);
    /**
     * Return the fee in satoshis for the given size in bytes.
     */
    CAmount GetFee(uint32_t num_bytes) const;
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
    std::string ToString(const FeeEstimateMode& fee_estimate_mode = FeeEstimateMode::GEAM_KVB) const;

    SERIALIZE_METHODS(CFeeRate, obj) { READWRITE(obj.nGemsPerK); }
};

#endif //  GERANIUM_POLICY_FEERATE_H
