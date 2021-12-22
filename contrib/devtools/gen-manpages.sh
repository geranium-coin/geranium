#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

GERANIUMD=${BITCOIND:-$BINDIR/geraniumd}
GERANIUMCLI=${BITCOINCLI:-$BINDIR/geranium-cli}
GERANIUMTX=${BITCOINTX:-$BINDIR/geranium-tx}
GERANIUMQT=${BITCOINQT:-$BINDIR/qt/geranium-qt}

[ ! -x $GERANIUMD ] && echo "$GERANIUMD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
GEAMVER=($($GERANIUMCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bitcoind if --version-string is not set,
# but has different outcomes for bitcoin-qt and bitcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$GERANIUMD --version | sed -n '1!p' >> footer.h2m

for cmd in $GERANIUMD $GERANIUMCLI $GERANIUMTX $GERANIUMQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${GEAMVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${GEAMVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
