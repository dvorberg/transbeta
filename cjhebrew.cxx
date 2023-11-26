// -*- mode: c++; encoding: utf-8; -*_
//
// This file is part of libtransliterate
//
// Copyright 2012–23 by Diedrich Vorberg <diedrich@tux4web.de>
//
// All Rights Reserved.
//
// For more Information on orm see the README and LICENSE file.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.

#include "trie.h"
#include "code_tables.h"

class cjhebrew_to_wchar_trie_t:
    public trie<char, wchar_t>,
    public code_container
{
public:
    /* Return true if c is a whitespace character. */
    virtual int between_words(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == 0;
    }
    
    void add_pair(char *beta, wchar_t *codepoint) {
        add((char *)beta, codepoint);
    }

    cjhebrew_to_wchar_trie_t() {
        root = new trie<char, wchar_t>::node(0);
        add_cjhebrew_code_table(this);
        finalize();
    }
};

cjhebrew_to_wchar_trie_t *cjhebrew_to_wchar_trie =
    new cjhebrew_to_wchar_trie_t();


namespace transliterate
{
    size_t cjhebrew_to_wchar(char *cjhebrew,
                             wchar_t *output_buffer,
                             size_t buffer_length)
    {
        return cjhebrew_to_wchar_trie->process(cjhebrew, output_buffer,
                                               buffer_length);
    }
}

