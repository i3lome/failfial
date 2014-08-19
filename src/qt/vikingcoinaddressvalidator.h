// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef VIKINGCOINADDRESSVALIDATOR_H
#define VIKINGCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class VikingcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit VikingcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Vikingcoin address widget validator, checks for a valid vikingcoin address.
 */
class VikingcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit VikingcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // VIKINGCOINADDRESSVALIDATOR_H
