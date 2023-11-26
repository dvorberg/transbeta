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

class coptic_to_wchar_trie_t:
    public trie<char, wchar_t>,
    public code_container
{
public:
    virtual void add_pair(char *beta, wchar_t *wchar) {
        add(beta, wchar);
    }

    /* Return true if c is a whitespace character. */
    virtual int between_words(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == 0 || c == '-';
    }
    
    coptic_to_wchar_trie_t() {
        root = new trie<char, wchar_t>::node(0);
        add_coptic_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};
    
coptic_to_wchar_trie_t *coptic_to_wchar_trie =
    new coptic_to_wchar_trie_t();


namespace transliterate
{
    size_t betacode_coptic_to_wchar(char *coptic,
                                    wchar_t *output_buffer,
                                    size_t buffer_length)
    {
        return coptic_to_wchar_trie->process(coptic, output_buffer,
                                             buffer_length);
    }
}

