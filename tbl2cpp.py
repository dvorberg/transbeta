#!/usr/bin/env python

## This file is part of libtransliterate
##
## Copyright 2012–23 by Diedrich Vorberg <diedrich@tux4web.de>
##
## All Rights Reserved.
##
## For more Information on orm see the README and LICENSE file.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
## CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
## INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
## MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
## DISCLAIMED.

import sys, re

whitespace_re = re.compile(r"\s+")
def splitfields(s):
    return whitespace_re.split(s)

underscore_re = re.compile(r"(_$)|(__$)")
def underscore_replacer(match):
    space, underscore = match.groups()
    if space is None:
        return "_"
    else:
        return " "

def quote_quote(s):
    s = s.replace("\\", "\\\\")
    s = s.replace('"', '\\"')
    return s


def pair(line):
    ret = line.split("//")[0].strip()
    if ret == "":
        return None
    else:
        parts = splitfields(ret)
        beta = parts[0]

        beta = underscore_re.sub(underscore_replacer, beta)
        beta = quote_quote(beta)

        return beta, [ int(hex, 16) for hex in parts[1:] ]

def main():
    print("// DO NOT MODIFY!")
    print("// This file has been automatically generated.")
    print()

    pairs = [ pair(line) for line in sys.stdin.readlines() ]
    pairs = [ pair for pair in pairs if pair is not None ]

    for counter, (beta, codepoints) in enumerate(pairs):
        codepoints.append(0)
        codepoints = [ "0x%04x" % codepoint for codepoint in codepoints ]
        codepoints = ", ".join(codepoints)
        print('static wchar_t tpl%i[] = {%s};' % ( counter, codepoints, ))
        print('container->add_pair((char *)"%s", tpl%s);' % (
            beta, counter, ))

main()
