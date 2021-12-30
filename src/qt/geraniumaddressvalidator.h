// Copyright (c) 2011-2020 The Geranium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GERANIUM_QT_GERANIUMADDRESSVALIDATOR_H
#define GERANIUM_QT_GERANIUMADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class GeraniumAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GeraniumAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Geranium address widget validator, checks for a valid geranium address.
 */
class GeraniumAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GeraniumAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // GERANIUM_QT_GERANIUMADDRESSVALIDATOR_H
