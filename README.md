
# T5 Text Search and Summarize Engine
# Table of Contents
- [Table of Contents](#table-of-contents)
- [T5 Text Search and Summarize Engine Demo](#t5-text-search-and-summarize-engine-demo)
- [Features](#features)
- [Installation/Usage](#installationusage)
- [Architecture ](#architecure)
  - [1. T5 Text Summarizer Architecture](#t5-text-summarize-architecture)
  - [2. Text Searcher Architecture](#text-search-architecture)
- [Current Issues](#current-issues)
- [Contributing](#contributing)
- [Roadmap](#roadmap)
- [Acknowledgements](#acknowledgements)
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
# Architecture
T5 Text Search and Summarize Engine has two core components, a **Transformer-Based Pre-Trained T5 Model Fine-Tuner** used for text summarization and a **Ultra Fast Text Searcher**.
## 1. T5 Text Summarizer Architecture
T5 model can be used for wide range of NLP tasks such as Translation, summarization, Classification, Regression and Q&A if fine-tuned with a dataset relevant to the desired task.

![](https://cdn-images-1.medium.com/max/947/1*voAo0zBPTCVrwcut1oHtEg.png)

To see how T5 is able to achieve these results, the motivation and the architecture behind T5 should be studied.
### 1.1 T5 Initial Architecture and Background
T5 (**T**ext-**t**o-**T**ext **T**ransfer **T**ransformer) model is a result of a systematic study conducted by Google researchers as presented  in [Exploring the Limits of Transfer Learning with a Unified Text-to-Text Transformer](https://arxiv.org/abs/1910.10683) by Colin Raffel, Noam Shazeer, Adam Roberts, Katherine Lee, Sharan Narang, Michael Matena, Yanqi Zhou, Wei Li, Peter J. Liu.

In their study, researchers start with a baseline model roughly equivalent to the original Transformer proposed by 
Vaswani et al. (2017) with 3 main exceptions of removing the Layer Norm bias, placing the layer normalization outside residual path and using a different position embedding scheme. They finalize their T5 models by altering one aspect of the setup at a time and evaluating the best performance.

![transformer-architecture](https://miro.medium.com/max/1000/1*tkC_NqylGH4hv2rTLPOf5A.png)

Initial specifics of the T5 baseline model:
- Encoder-decoder structure with 12 blocks and 222 million parameters
- Blocks comprising self-attention, optional encoder-decoder attention and a feed-forward network
- Feed-forward network in each block with a Dense-ReLu-Dense structure and dropout probability of 0.1
- Pre-training with unsupervised learning i.i.d denoising objective of predicting missing or corrupted tokens
- Pre-training for 2^19=524,288 steps on C4 dataset before fine-tuning
- Pre-training using a maximum sequence length of 512 and a batch size of 128 sequences
- Pre-training using standard maximum likelihood, cross-entropy loss and teacher forcing
- Optimizing using AdaFactor and "inverse square root" learning rate schedule
- Fine-tuning  with batches of 128-length-512 sequences and learning rate of 0.0001
- Checkpoint saving every 5,000 steps and reporting results on the checkpoint with highest performance

Overall performance of baseline T5 Models is shown in the figure below.
![baseline-performance](https://miro.medium.com/max/1400/1*RfzVjzpod7Da-pXwKEwJNg.png)

### 1.2 T5 Final Architecture
T5 baseline models architecture has experienced dramatic improvement to achieve state-of-the-art results on NLP benchmarks by the findings of the systematic study conducted by Google researchers as presented in [Exploring the Limits of Transfer Learning with a Unified Text-to-Text Transformer](https://arxiv.org/abs/1910.10683) by Colin Raffel, Noam Shazeer, Adam Roberts, Katherine Lee, Sharan Narang, Michael Matena, Yanqi Zhou, Wei Li, Peter J. Liu.

Final specifics of the T5 model include the same training procedure and hyperparameters apart from the following changes:
- **Objective** Finalized T5 base model's objective is the span-corruption objective with a span length of 3 and corruption rate of 15% of the original sequence, inspired by SpanBert (Joshiet al., 2019) instead of the initial i.i.d denoising objective.
![t5-objective](https://1.bp.blogspot.com/-POb379Q1jkE/XqHoSjv1HVI/AAAAAAAAAiM/BDvTxIcBIVYsWvnVc6HdnxV9MBqL-YkUwCLcBGAsYHQ/s640/parameter-tuning-T5-Google.png)

- **Longer training** Finalized T5 base model uses increased number of both the batch size (2^11 sequences of length 512) and training steps (1 million steps) corresponding to a total of 1 trillion pre-training tokens
- **Model sizes** Finalized T5 model is available in following sizes:
	- **Base.** 12-headed attention, 12 layers in each encoder and decoder with 220 million parameters
	- **Small.** 8-headed attention, 6 layers in each encoder and decoder with 60 million parameters
	-  **Large.** 16-headed attention, 24 layers in each encoder and decoder with 770 million parameters
	-  **3B.**  32-headed attention 24 layers in each encoder and decoder with 2.8 billion parameters
	 -  **11B.**  128-headed attention 24 layers in each encoder and decoder with 11 billion parameters
- **Fine-tuning** The finalized T5 model is fine-tuned with a smaller batch size of 8 length-512 sequences for each GLUE and SuperGlue tasks with checkpoints being saved every 1,000 steps.
- **Beam Search** Finalized T5 model uses beam search with a beam width of 4 parameters and a length penalty of 0.6 for the WMT translations and CNN/DM summarization tasks.

Overall performance of finalized T5 Models is shown in the figure below.

![final-performance](https://miro.medium.com/max/1400/0*5HilfwNe2Wg3Jsxd.png)
	
# Current Issues
# Contributing
# Roadmap
# Acknowledgements
# License
