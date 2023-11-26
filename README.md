# transliteratemodule
Python module written in C++ to convert transliterated representation
of ancient languages to unicode (TLG's beta code and LaTeX cjhebrew
markup)

This library converts “transliterated” representations of non-English
languages, like TLG's Beta Code, to unicode. Supported
transliterations are:

o The Thesaurus Linguae Graecae’s Beta Code for Polytonic Greek,
  Hebrew and Coptic. 
o cjhebrew transliteration from the LaTeX package by that name

I don’t know much about Coptic, so the functions for that language
remain untested. The Beta Code representation for Hebrew does not
support vowel and diacritical marks by design, cjhebrew does. 

I’m only using the **cjhebrew** implementation with some earnest. None
of the other codecs see production use here. 

Function definitions in Python would look like:

```python

def betacode_greek_to_unicode(source, precombined=False, asterisk_syntax=False):
    """
    If `precombined` is True, output unicode codepoints that have 
        diacritical characters in them. 
    If `asterisk_syntax` is used, upper case Greek letters are marked by a “*”, 
        otherwise upper case Latin is mapped to upper case Greek.
    
    """"

def cjhebrew_to_unicode(source):
    pass
    
def betacode_hebrew_to_unicode(source):
    # Untested!
    pass
    
def betacode_coptic_to_unicode(source):
    # Untested!
    pass
    
```

If anyone finds this useful, please let me know your milage!


Diedrich Vorberg <diedrich@tux4web.de>


