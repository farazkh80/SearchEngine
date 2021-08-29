from confetti import Config
import os

__all__ = ["config"]

config = Config({
    'os-system': 'win-64', # change to match running os supported options: 'win-32', 'win-64' and 'unix'
    'search_data_path': os.path.join('data','search-data','bigDataset.txt'),
    'search_engine_binary_path': {
        'win-32': os.path.join('Search-Engine', 'win-exes', 'win-32-exe','Search-Engine.exe'),
        'win-64': os.path.join('Search-Engine', 'win-exes', 'win-64-exe','Search-Engine.exe'),
        'unix': os.path.join('Search-Engine','/searchengine')
    },
    'fine_tune_dataset_path': os.path.join('data','summarization-data', 'news_summary.csv'),
    'model_ckpt_path': {
        't5-base': 't5-base-full-seeded.ckpt',
        't5-small': 't5-small-full-seeded.ckpt'
    }
})