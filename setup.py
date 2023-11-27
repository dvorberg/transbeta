#!/usr/bin/env python3
# -*- mode: python; encoding: utf-8; -*_

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

"""
setup.py file for transbeta
"""

from distutils.core import setup, Extension

name = "transbeta"

transliterate = Extension( name,
                           sources=["betacode_coptic.cxx",
                                    "betacode_greek.cxx",
                                    "betacode_hebrew.cxx",
                                    "cjhebrew.cxx",
                                    "code_tables.cxx",
                                    "transbetamodule.cxx",])

setup (name = name,
       version = "0.2",
       author      = "Diedrich Vorberg <diedrich@tux4web.de>",
       description = "Python module written in C++ to convert transliterated representation of ancient languages to unicode (TLG's beta code and LaTeX cjhebrew markup)",
       ext_modules = [ transliterate ],
       py_modules = [ name ],
       package_data={name: ["*.h", "*.inc"]})
