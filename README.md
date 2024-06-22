# bpe-cpp 🚀

A C++ implementation of the (byte-level) Byte Pair Encoding (BPE) algorithm commonly used in LLM tokenization, inspired by [karpathy/minbpe](https://github.com/karpathy/minbpe).

## Overview 📚

This project implements the BPE algorithm in C++, mirroring the functionality of the original Python implementation by Andrej Karpathy. The BPE algorithm is "byte-level" because it runs on UTF-8 encoded strings.

BPE was popularized for LLMs by the GPT-2 paper and is now used by all modern LLMs (e.g., GPT, Llama, Mistral) to train their tokenizers.

## Algorithm 🧩

The Byte Pair Encoding algorithm works by iteratively merging the most frequent pair of bytes (or tokens) in a sequence to create new tokens. This process continues until a desired vocabulary size is reached. The algorithm consists of three main components:

1. **Training** : Given a large text corpus, find the most common pair of tokens and merge them into a new token. Repeat this process until the desired vocabulary size is reached.

2. **Encoding** : Convert input text into a sequence of tokens by applying the learned merges.

3. **Decoding** : Convert a sequence of tokens back into text.

## Performance ⚡

As this is a C++ implementation, it takes significantly less time to run compared to the original Python version 🕐.

![Training Time](/assets/time.png)

Above Execution Time is for the following input:
```bash
Ｕｎｉｃｏｄｅ! 🅤🅝🅘🅒🅞🅓🅔‽ 🇺‌🇳‌🇮‌🇨‌🇴‌🇩‌🇪! 😄 The very name strikes fear and awe into the hearts of programmers worldwide. We all know we ought to “support Unicode” in our software (whatever that means—like using wchar_t for all the strings, right?). But Unicode can be abstruse, and diving into the thousand-page Unicode Standard plus its dozens of supplementary annexes, reports, and notes can be more than a little intimidating. I don’t blame programmers for still finding the whole thing mysterious, even 30 years after Unicode’s inception.
500
```

*Note: Actual performance may vary depending on your system and the size of the input data.*

## Getting Started 🚦

To compile the project, you'll need a C++ compiler that supports C++11 or later. The following command can be used to build the project:

```bash
g++ -std=c++11 -o program main.cpp -I$(brew --prefix icu4c)/include -I$(brew --prefix pcre2)/include -L$(brew --prefix icu4c)/lib -L$(brew --prefix pcre2)/lib -licuuc -licudata -lpcre2-8
```
After successfully compiling the project, you can run the program using:

```bash
./program
```

When running the program, provide input in the following format:

1. First line: Input string
2. Second line: Size of new vocabulary (must be ≥ 256)

Example:
```bash
Hello, World!
258
```
