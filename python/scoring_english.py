import re
import string


# Letters: anywhere in text. u :: 0.024, b :: 0.013
# Pairs: anywhere in words in text: in :: 0.026, th :: 0.038
# Words: of :: 0.037, my :: 0.00078, not :: 0.0016, i :: 0.00078
# Not case sensitive! Assume all text in lower case.


# score text with the sum of (the empirical stats - the stats above)**2
# choose text with minimal score.


def format_text(text):
    """
    Converts a string of text into a list of lower case words with no non-alphabetic characters.
    
    param text :: a Python string
    
    return :: a list of lower-case words stripped of all punctuation or whitespace.
    """
    assert type(text) == str
    if len(text) == 0:
        return []
    text = text.lower()  # make homogenous letter case
    text = "".join(c for c in text if (c.isalpha() or c in [" ", "\n", "\t"])) # remove numbers and punctuation
    text = re.split(r"[ \t\n]", text)  # Split into a list words, including the null word ""
    text = [word for word in text if word != ""]  # Remove null words
    assert type(text) == list
    for word in text:
        assert (type(word) == str and len(word) != 0)
    return text


def letter_freq(char, text):
    assert (type(char) == str and len(char) == 1)
    count = 0
    for word in text:
        count += word.count(char)
    return count


def pair_freq(pair, text):
    assert (type(pair) == str and len(pair) == 2)
    count = 0
    for word in text:
        count += word.count(pair)
    return count


def word_freq(word, text):
    assert(type(word) == str and word.isalpha())
    count = 0
    for words in text:
        if words == word:
            count += 1
    return count


def score_english(text):
    """
    Takes a string and tests it for plausible Englishness, giving a score of 0 for non-printable characters
    
    param text :: text to test
    
    return :: score of 0 or more. Perfect English should have a score of near 1!
    """
    if not all([c for c in text if c not in string.printable]):  # Tests that all elements of the text are valid printables
        return 0
    text = format_text(text)
    
    numletters = 0
    for word in text:
        numletters += len(word)
    num_u = letter_freq("u", text)
    num_b = letter_freq("b", text)
    num_e = letter_frew("e", text)

    numpairs = 0
    for word in text:
        numpairs += len(word) - 1
    num_in = pair_freq("in", text)
    num_th = pair_freq("th", text)    

    numwords = len(text)
    num_of = word_freq("of", text)
    num_my = word_freq("my", text)
    num_not = word_freq("not", text)
    num_i = word_freq("i", text)
    variable_scores = [num_e/num_letters - 0.127, num_u/numletters - 0.024, num_b/numletters - 0.013, num_in/numpairs - 0.026, num_th/numpairs - 0.038,\
                       num_of/numwords - 0.037, num_my/numwords - 0.00078, num_not/numwords - 0.0016, num_i/numwords - 0.00078]
    score = sum([1/(abs(var_score) + 1) for var_score in variable_scores])/len(variable_scores)
    return score
