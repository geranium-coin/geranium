#!/usr/bin/env bash
# Copyright (c) 2016-2019 The Geranium Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

GERANIUMD=${GERANIUMD:-$BINDIR/geraniumd}
GERANIUMCLI=${GERANIUMCLI:-$BINDIR/geranium-cli}
GERANIUMTX=${GERANIUMTX:-$BINDIR/geranium-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/geranium-wallet}
GERANIUMQT=${GERANIUMQT:-$BINDIR/qt/geranium-qt}

[ ! -x $GERANIUMD ] && echo "$GERANIUMD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a GEAMVER <<< "$($GERANIUMCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for geraniumd if --version-string is not set,
# but has different outcomes for geranium-qt and geranium-cli.
echo "[COPYRIGHT]" > footer.h2m
$GERANIUMD --version | sed -n '1!p' >> footer.h2m

for cmd in $GERANIUMD $GERANIUMCLI $GERANIUMTX $WALLET_TOOL $GERANIUMQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${GEAMVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${GEAMVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
