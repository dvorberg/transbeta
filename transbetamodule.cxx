// -*- mode: objc; encoding: utf-8; -*_
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

#include "transliterate.h"

inline PyObject *construct_return_value(wchar_t *buffer, size_t length)
{
    return Py_BuildValue("u#", buffer, (int)length);
}

PyObject *betacode_greek_to_unicode(PyObject *self, PyObject *args)
{
    char *input = NULL;
    int precombined = 0, asterisk_syntax = 0;
    
    if ( ! PyArg_ParseTuple(args, "s|ii",
							&input, &precombined, &asterisk_syntax))
    {
        return NULL;
    }

    size_t buflen = strlen(input) * 2 + 2;
    wchar_t *buffer = (wchar_t *)alloca(buflen * sizeof(wchar_t));
    size_t length = transliterate::betacode_greek_to_wchar(
        input, buffer, buflen, precombined, asterisk_syntax);

    PyObject *ret = construct_return_value(buffer, length);
        
    return ret;
}

PyObject *cjhebrew_to_unicode(PyObject *self, PyObject *args)
{
    char *input = NULL;
    
    if (!PyArg_ParseTuple(args, "s", &input))
    {
        return NULL;
    }

    size_t buflen = strlen(input) * 2;
    wchar_t *buffer = (wchar_t *)alloca(buflen*sizeof(wchar_t));
    size_t length = transliterate::cjhebrew_to_wchar(input, buffer, buflen);

    PyObject *ret = construct_return_value(buffer, length);
	
    return ret;
}

PyObject *betacode_hebrew_to_unicode(PyObject *self, PyObject *args)
{
    char *input = NULL;
    
    if (!PyArg_ParseTuple(args, "s", &input))
    {
        return NULL;
    }

    size_t buflen = strlen(input) * 2;
    wchar_t *buffer = (wchar_t *)alloca(buflen*sizeof(wchar_t));
    size_t length = transliterate::betacode_hebrew_to_wchar(
		input, buffer, buflen);

    PyObject *ret = construct_return_value(buffer, length);
	
    return ret;
}

PyObject *betacode_coptic_to_unicode(PyObject *self, PyObject *args)
{
    char *input = NULL;
    
    if (!PyArg_ParseTuple(args, "s", &input))
    {
        return NULL;
    }

    size_t buflen = strlen(input) * 2;
    wchar_t *buffer = (wchar_t *)alloca(buflen*sizeof(wchar_t));
    size_t length = transliterate::betacode_coptic_to_wchar(
		input, buffer, buflen);

    PyObject *ret = construct_return_value(buffer, length);
	
    return ret;
}

static PyMethodDef methods[] = {
    { "betacode_greek_to_unicode" , betacode_greek_to_unicode, METH_VARARGS,
      "Convert betacode for polytonic Greek into a unicode string.\n"
      "INPUT: string of beta code\n"
      "PRECOMBINED: Output precombined unicode characters (default: false)\n"
      "ASTERISK_SYNTAX: Use *-syntax for capital letters (default: false, \n"
	  "    i.e. map Latin upper case letters to their Greek counterparts.)\n"},
    { "cjhebrew_to_unicode", cjhebrew_to_unicode, METH_VARARGS,
      "Convert cjhebrew into a unicode string.\n"
      "INPUT: string of beta code\n"},
    { "betacode_hebrew_to_unicode", betacode_hebrew_to_unicode, METH_VARARGS,
      "__UNTESTED__ Convert betacode hebrew into a unicode string.\n"
      "INPUT: string of beta code\n"},	
    { "betacode_coptic_to_unicode", betacode_coptic_to_unicode, METH_VARARGS,
      "__UNTESTED__ Convert betacode coptic into a unicode string.\n"
      "INPUT: string of beta code\n"},	
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef transbeta_module = {
    PyModuleDef_HEAD_INIT,
    "transbeta",   /* name of module */
    "Python module written in C++ to convert transliterated representation "
    "of ancient languages to unicode "
    "(TLG’s beta code and "
    "LaTeX cjhebrew markup)", /* module documentation, may be NULL */
    -1, /* size of per-interpreter state of the module,
           or -1 if the module keeps state in global variables. */
    methods
};

PyMODINIT_FUNC
PyInit_transbeta(void)
{
    return PyModule_Create(&transbeta_module);
}
