<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

# T5 Text Search and Summarize Engine

# Table of Contents

- [T5 Text Search and Summarize Engine](#t5-text-search-and-summarize-engine)
- [Table of Contents](#table-of-contents)
- [T5 Text Search and Summarize Engine Demo](#t5-text-search-and-summarize-engine-demo)
- [Features](#features)
- [Installation/Usage](#installationusage)
- [Project Overview](#project-overview)
  - [1. T5 Text Summarizer](#1-t5-text-summarizer)
    - [1.1 T5 Background](#11-t5-background)
    - [1.2 T5 Final Architecture:](#12-t5-final-architecture)
    - [1.3 T5 Summarization Fine Tuning](#13-t5-summarization-fine-tuning)
  - [2. Text Search Engine](#2-text-search-engine)
    - [2.1 Text Dataset Architecture](#21-text-dataset-architecture)
    - [2.2 Text Search Logic](#22-text-search-logic)
- [Current Issues](#current-issues)
- [Contributing](#contributing)
- [Roadmap](#roadmap)
- [Acknowledgements](#acknowledgements)
- [License](#license)

- [License](#license)

# T5 Text Search and Summarize Engine Demo

# Features

- Multiple T5 Text Summarization Models
  - t5-small
  - t5-base
  - t5-large
- Single Keyword Search
- Single Keyword Search and Summarize
- Multiple Keyword Search
- Multiple Keyword Search and Summarize

# Installation/Usage

# Project Overview

T5 Text Search and Summarize Engine has two core components, a **Transformer-Based Pre-Trained T5 Model Fine-Tuner** used for text summarization and a **Token-Based Text Searcher**. The primary use of this project is for news text summarization, however, it can be expanded for any type of natural language summarization.

## 1. T5 Text Summarizer

The T5 Text Summarizer part of this project uses the pre-trained PyTorch `transformers.ioT5ForConditionalGeneration` model from the **Hugging Face Transformers API** and **Pytorch Lightning** research framework for handling cross-hardware training, model check-pointing and logging.

T5 model can be used for wide range of NLP tasks such as Translation, summarization, Classification, Regression and Q&A if fine-tuned with a dataset relevant to the desired task.

![](https://cdn-images-1.medium.com/max/947/1*voAo0zBPTCVrwcut1oHtEg.png)

To see how T5 is able to achieve these results, a brief explanation of background and architecture behind T5 is provided below.

### 1.1 T5 Background

[T5](https://arxiv.org/abs/1910.10683) (**T**ext-**t**o-**T**ext **T**ransfer **T**ransformer) model is a result of a systematic study conducted by Google researchers as presented in [Exploring the Limits of Transfer Learning with a Unified Text-to-Text Transformer](https://arxiv.org/abs/1910.10683) by Colin Raffel, Noam Shazeer, Adam Roberts, Katherine Lee, Sharan Narang, Michael Matena, Yanqi Zhou, Wei Li, Peter J. Liu.

In their study, researchers start with a baseline model roughly equivalent to the [original Transformer](https://arxiv.org/abs/1706.03762) proposed by [Vaswani et al. (2017)](https://arxiv.org/abs/1706.03762) with 3 main exceptions of removing the Layer Norm bias, placing the layer normalization outside residual path and using a different position embedding scheme. For training, T5 uses [C4](tensorlow.text.c4) dataset, a heuristic filtered version of common crawl web extracted text. In filtering, any line that didn’t end in a terminal punctuation mark, or containing the word javascript or any pages that had a curly bracket get removed. It deduplicates the dataset by taking a sliding window of 3 sentence chunks so that only one of them appeared the dataset. It ends up with 750 gigabytes of clean-ish English text.

The final T5 model is obtained by altering the model setup one aspect at a time and choosing the option with the best performance.

![transformer-architecture](https://miro.medium.com/max/1400/1*iJcUH1F0TmCQE5p2wQt9og.png)

### 1.2 T5 Final Architecture:

- **Input and Output Format** T5 uses a "text-to-text" format to provide a consistent training objective for the diverse set of tasks described in part [1. T5 Text Summarizer](#1-t5-text-summarizer), i.e. input is "translate English to German: That is good" and the output is "Das ist gut".
  <br>
- **Objective** Finalized T5 base model's objective is the span-corruption objective with a span length of 3 and corruption rate of 15% of the original sequence, inspired by SpanBert ([Joshiet al., 2019](https://arxiv.org/abs/1907.10529))
  <br>
- **Longer training** Finalized T5 base model uses a batch size of $2^{11}$ sequences of length 512 and training steps of 1 million steps, corresponding to a total of 1 trillion pre-training tokens
  <br>
- **Model sizes** Finalized T5 model is available in following sizes:
  - **Base.** 12-headed attention, 12 layers in each encoder and decoder with 220 million parameters
  - **Small.** 8-headed attention, 6 layers in each encoder and decoder with 60 million parameters
  - **Large.** 16-headed attention, 24 layers in each encoder and decoder with 770 million parameters
  - **3B.** 32-headed attention 24 layers in each encoder and decoder with 2.8 billion parameters
  - **11B.** 128-headed attention 24 layers in each encoder and decoder with 11 billion parameters
    <br>
- **Fine-tuning** The finalized T5 model is fine-tuned with a batch size of 8 length-512 sequences for each GLUE and SuperGlue tasks with checkpoints being saved every 1,000 steps.
  <br>
- **Beam Search** Finalized T5 model uses beam search with a beam width of 4 parameters and a length penalty of 0.6 for the WMT translations and CNN/DM summarization tasks.

Overall performance of finalized T5 Models is shown in the figure below.

![final-performance](https://miro.medium.com/max/1400/0*5HilfwNe2Wg3Jsxd.png)

### 1.3 T5 Summarization Fine Tuning

For fine-tuning T5 for the task of news summarization, a [news dataset] with +4500 news text and summary has been used.

Hyper parameters used:

- **For tokenization**
  - text_max_token_len: 512 tokens
  - summary_max_token_len: 128 tokens
  - padding: "max_length"
  - truncation: True
  - add_special_tokens: True
    <br>
- **For Fine-Tuning**
  - epochs: 3
  - batch_size: 8
  - test_size: 0.1
    <br>
- **For Summarization**
  - max_length: 150
  - num_beams: 2
  - repetition_penalty: 1.0
  - length_penalty: 1.0
  - early_stopping: True

Currently, only two of **Hugging Face** T5 models are fine-tuned which are `t5-small` trained with GPU and `t5-base` trained with a 8-core v2 TPU.

## 2. Text Search Engine

The Text Searching Engine is developed purely in `C` and `C++` for optimized speed and memory handling. The search engine is initialized with a static dataset containing thousands of news and articles rendered from the web.
After initialization, the search engine is tasked with searching for a certain word in the dataset and display the documents(news) containing the searched keyword with a custom ranking scheme.

### 2.1 Text Dataset Architecture

The dataset initialization is achieved by leveraging `Trie` for storing tokens (denoted as `Trienode`) and `Linked List` data structures for mapping document id to news/document text (denoted as `Mymap`) and storing times of occurrences of each token in all news/document ids(denoted as `Listnode`).

![search-dataset-setup](!visuals/../visuals/search-dataset-setup.jpg)

### 2.2 Text Search Logic

Text searching is achieved through main functionalities:

1. `/tf` : given a `<key-word>` and a document `<id>`, will search the `<keyword>` token in the `Trienode` and retrieving the times of occurrences for the corresponding `<id>` of the token's `<Listnode>`, ultimately returning the number of times the `<key-word>` has been detected in document with id `<id>`.
   <br>
2. `/df` : given a `<key-word>`, will leverage the `/tf` function to search through all the documents and return the total number of times the `<key-word>` has been detected in the whole dataset.
   <br>
3. `/search`: given a set of `<keyword1,keyword2,..>` will leverage `/tf` search to find the number of occurrences of each keyword in documents, calculate a logarithmic score for ranking scheme and store it in a list(denoted as `Scorelist`) and finally display the results in a descending order of scores which is achieved through transforming the `Scorelist` to a `Maxheap`, and removing highest scores one at a time.

# Current Issues

# Contributing

# Roadmap

# Acknowledgements

# License
