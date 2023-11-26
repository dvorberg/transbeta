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

class forward_greek_trie: public trie<char, wchar_t>, public code_container
{
public:
    virtual void add_pair(char *beta, wchar_t *wchar) {
        add(beta, wchar);
    }

    /* Return true if c is a whitespace character. */
    virtual int between_words(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == 0 || c == ','
            || c == ':' || c == ';' || c == '.';
    }
};
    
class asterisk_combining_trie_t: public forward_greek_trie
{
public:
    asterisk_combining_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_asterisk_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};
asterisk_combining_trie_t *asterisk_combining_trie =
    new asterisk_combining_trie_t();


class asterisk_precombined_trie_t: public forward_greek_trie
{
public:
    asterisk_precombined_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_precombined_asterisk_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};

asterisk_precombined_trie_t *asterisk_precombined_trie =
    new asterisk_precombined_trie_t();



class case_combining_trie_t: public forward_greek_trie
{
public:
    case_combining_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_case_code_table(this);
        add_specials_code_table(this);
        finalize();
    }

    inline int upcase_letter(wchar_t c) {
        //          Α              Ω
        return c >= 0x0391 && c <= 0x03A9;
    }

    inline int capital_modifyer(wchar_t c) {
        return c == 0x0313 || c == 0x0314 || c == 0x0301 || c == 0x0300;
    }
};

case_combining_trie_t *case_combining_trie =
    new case_combining_trie_t();


class case_precombined_trie_t: public forward_greek_trie
{
public:
    case_precombined_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_precombined_case_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};

case_precombined_trie_t *case_precombined_trie =
    new case_precombined_trie_t();


forward_greek_trie *forward_tries_wchar[2][2] =
{ { new case_combining_trie_t(),
    new case_precombined_trie_t() },
  { new asterisk_combining_trie_t(),
    new asterisk_precombined_trie_t() }};




namespace transliterate
{
    size_t betacode_greek_to_wchar(char *betacode,
                                   wchar_t *output_buffer,
                                   size_t buffer_length,
                                   int precombined = false,
                                   int asterisk_syntax = false)
    {
        if (precombined) precombined = 1;
        if (asterisk_syntax) asterisk_syntax = 1;
    
        return forward_tries_wchar[asterisk_syntax][precombined]->process(
            betacode, output_buffer, buffer_length);
    }
}
